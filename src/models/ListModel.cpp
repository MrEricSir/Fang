/*
 * Author: Christophe Dumez <dchris@gmail.com>
 * License: Public domain (No attribution required)
 * Website: http://cdumez.blogspot.com/
 * Version: 1.0
 */
 
#include "ListModel.h"

#include <QDebug>
 
ListModel::ListModel(ListItem* prototype, QObject *parent) :
    QAbstractListModel(parent), m_prototype(prototype), _selected(NULL)
{
    
}
 
int ListModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_list.size();
}
 
QVariant ListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_list.size())
    return QVariant();
  return m_list.at(index.row())->data(role);
}

// Added by Eric (TM)
bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() < 0 || index.row() >= m_list.size())
      return false;
    
    return m_list.at(index.row())->setData(value, role);
}

void ListModel::setData(int row, const QString &field_name, QVariant new_value)
{
    if (row < 0 || row >= m_list.size())
      return;
    
    QHash<int, QByteArray> roleNames = m_list.at(row)->roleNames();
    foreach(int roleIndex, roleNames.keys()) {
        if (field_name == roleNames[roleIndex]) {
             m_list.at(row)->setData(new_value, roleIndex);
            
            return;
        }
    }
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if(index.row() < 0 || index.row() >= m_list.size())
      return Qt::NoItemFlags;
    
    return m_list.at(index.row())->flags();
}

void ListModel::move(int from, int to)
{
    // From: https://qt.gitorious.org/qt-labs/qml-object-model/source/7c2207640a65dc59a420ebf71a45e38350840313:qobjectlistmodel.cpp
    if (!beginMoveRows(QModelIndex(), from, from, QModelIndex(), to > from ? to+1 : to))
        return;
    
    m_list.move(from, to);
    endMoveRows();
}
 
ListModel::~ListModel() {
  delete m_prototype;
  clear();
}
 
void ListModel::appendRow(ListItem *item)
{
  appendRows(QList<ListItem*>() << item);
}
 
void ListModel::appendRows(const QList<ListItem *> &items)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
  foreach(ListItem *item, items) {
    connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
    m_list.append(item);
  }
  endInsertRows();
  
  foreach(ListItem* item, items) {
      emit added(item);
  }
  
  emit countChanged(count());
}
 
void ListModel::insertRow(int row, ListItem *item)
{
  beginInsertRows(QModelIndex(), row, row);
  connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
  m_list.insert(row, item);
  endInsertRows();
  
  emit added(item);
  
  emit countChanged(count());
}
 
void ListModel::handleItemChange()
{
  ListItem* item = static_cast<ListItem*>(sender());
  QModelIndex index = indexFromItem(item);
  if(index.isValid())
    emit dataChanged(index, index);
}
 
ListItem * ListModel::find(const QString &id) const
{
  foreach(ListItem* item, m_list) {
    if(item->id() == id) return item;
  }
  return 0;
}
 
QModelIndex ListModel::indexFromItem(const ListItem *item) const
{
  Q_ASSERT(item);
  for(int row=0; row<m_list.size(); ++row) {
    if(m_list.at(row) == item) return index(row);
  }
  return QModelIndex();
}
 
void ListModel::clear()
{
    foreach(ListItem* item, m_list) {
        emit removed(item);
    }
    
    m_list.clear();
    
    emit countChanged(count());
}

void ListModel::setSelected(ListItem *selected)
{
    _selected = selected;
    emit selectedChanged(_selected);
    emit selectedIndexChanged(selectedIndex());
}

int ListModel::selectedIndex()
{
    return m_list.indexOf(_selected);
}

void ListModel::setSelectedIndex(int selectedIndex)
{
    setSelected(m_list.at(selectedIndex));
}
 
bool ListModel::removeRow(int row, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  ListItem* toRemove = NULL;
  if(row < 0 || row >= m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row);
  toRemove = m_list.takeAt(row);
  endRemoveRows();
  
  emit removed(toRemove);
  emit countChanged(count());
  
  return true;
}
 
bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  QList<ListItem*> toRemove;
  
  if(row < 0 || (row+count) >= m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row+count-1);
  for(int i=0; i<count; ++i) {
      toRemove.append(m_list.takeAt(row));
  }
  endRemoveRows();
  
  foreach(ListItem* item, toRemove) {
      emit removed(item);
  }
  
  emit countChanged(this->count());
  
  return true;
}

bool ListModel::removeItem(const ListItem *item)
{
    QModelIndex index = indexFromItem(item);
    int row = index.row();
    
    qDebug() << "Remove item at: " << row;
    
    if (row == -1)
        return false; // Not found.
    
    return removeRow(row);
}
 
ListItem * ListModel::takeRow(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  ListItem* item = m_list.takeAt(row);
  endRemoveRows();
  
  emit removed(item);
  emit countChanged(count());
  
  return item;
}
