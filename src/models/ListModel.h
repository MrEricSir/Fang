/*
 * Author: Christophe Dumez <dchris@gmail.com>
 * License: Public domain (No attribution required)
 * Website: http://cdumez.blogspot.com/
 * Version: 1.0
 */
 
#ifndef LISTMODEL_H
#define LISTMODEL_H
 
#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "../FangObject.h"

class FeedItem;

class ListItem: public FangObject {
  Q_OBJECT
 
public:
  ListItem(QObject* parent = nullptr) : FangObject(parent) {}
  virtual ~ListItem() {}
  virtual QString id() const { return "invalid id"; }
  virtual QVariant data(int role) const { Q_UNUSED(role); return QVariant(); }
  virtual bool setData(const QVariant &value, int role) { Q_UNUSED(value); Q_UNUSED(role); return false; }
  virtual Qt::ItemFlags flags() const { return Qt::NoItemFlags; }
  virtual QHash<int, QByteArray> roleNames() const { return QHash<int, QByteArray>(); }
 
signals:
  void dataChanged();
};
 
class ListModel : public QAbstractListModel
{
  Q_OBJECT
 
  // Must manually set in C++ layer
  Q_PROPERTY(ListItem* selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
  Q_PROPERTY(int count READ count NOTIFY countChanged)
  
public:
  explicit ListModel(ListItem* prototype, QObject* parent = nullptr);
  ~ListModel();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  inline int count() const { return rowCount(); }
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  Q_INVOKABLE QVariant dataByField(int row, const QString &field_name) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  void appendRow(ListItem* item);
  void appendRows(const QList<ListItem*> &items);
  void insertRow(int row, ListItem* item);
  Q_INVOKABLE bool removeRow(int row, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  bool removeItem(const ListItem* item);
  ListItem* takeRow(int row);
  ListItem* find(const QString &id) const;
  QModelIndex indexFromItem(const ListItem* item) const;
  void clear();
  inline QHash<int, QByteArray> roleNames() const { return m_prototype->roleNames(); }
  inline ListItem* row(int row) { return m_list.at(row); }
  Q_INVOKABLE inline FeedItem* rowAs(int row) { return (FeedItem*)(m_list.at(row)); }
  inline ListItem* selected() { return _selected; }
  void setSelected(ListItem* selected);
  int selectedIndex();
  void setSelectedIndex(int selectedIndex);

public slots:
  void setData(int row, const QString &field_name, QVariant new_value);
  void move(int from, int to);
  
signals:
  void added(ListItem* item);
  void removed(ListItem* item);
  
  void selectedChanged(ListItem* selected);
  void selectedIndexChanged(int selectedIndex);
  void countChanged(int newCount);
  
protected:
  // Returns the role # for a given role name, or -1 if it's invalid.
  int roleNameToRole(const QString& field_name) const;

private slots:
  void handleItemChange();
 
private:
  ListItem* m_prototype;
  QList<ListItem*> m_list;
  ListItem* _selected;
  QHash<QString, int> _roleNames;
};
 
#endif // LISTMODEL_H
