#include <QTest>
#include <QSignalSpy>
#include "../../src/models/FeedItem.h"
#include "../../src/models/ListModel.h"

/**
 * Verify ListModel operations using FeedItem as the concrete ListItem subclass.
 */
class TestListModel : public QObject
{
    Q_OBJECT

public:
    TestListModel();

private slots:
    void initTestCase();
    void cleanup();

    // Constructor
    void testConstructor_emptyModel();

    // Append
    void testAppendRow_singleItem();
    void testAppendRows_multipleItems();

    // Insert
    void testInsertRow_atBeginning();
    void testInsertRow_atMiddle();

    // Data access
    void testData_validIndex();
    void testData_invalidIndex();
    void testDataByField_validField();
    void testDataByField_invalidField();

    // Set data
    void testSetData_viaIndex();
    void testSetData_viaFieldName();

    // Flags
    void testFlags_validIndex();
    void testFlags_invalidIndex();

    // Remove
    void testRemoveRow_valid();
    void testRemoveRow_invalid();
    void testRemoveRows_multiple();
    void testRemoveItem_found();
    void testRemoveItem_notFound();
    void testTakeRow();

    // Find
    void testFind_existing();
    void testFind_nonExisting();

    // Index
    void testIndexFromItem_valid();
    void testIndexFromItem_null();
    void testIndexFromItem_notInModel();

    // Clear
    void testClear();

    // QML API
    void testGet_qmlApi();
    void testGet_outOfBounds();
    void testSetProperty();
    void testRemove_qmlApi();

    // Move
    void testMove_forwardSingle();
    void testMove_backwardSingle();
    void testMove_samePosition();
    void testMove_multipleItems();

    // Selection
    void testSelection_setSelected();
    void testSelection_setSelectedIndex();
    void testSelection_initialNull();

    // Data change propagation
    void testHandleItemChange();

private:
    FeedItem* createFeedItem(qint64 id, const QString& title);
};

TestListModel::TestListModel()
{
}

void TestListModel::initTestCase()
{
}

void TestListModel::cleanup()
{
}

FeedItem* TestListModel::createFeedItem(qint64 id, const QString& title)
{
    return new FeedItem(id, 0, title, "", QDateTime(), 0, QUrl(), QUrl(), "",
                        QUrl(), QDateTime(), -1, true, FeedTypeRSS, nullptr);
}

// Constructor

void TestListModel::testConstructor_emptyModel()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(model->count(), 0);
    QCOMPARE(model->selected(), nullptr);

    delete model;
}

// Append

void TestListModel::testAppendRow_singleItem()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");

    QSignalSpy addedSpy(model, &ListModel::added);
    QSignalSpy countSpy(model, &ListModel::countChanged);

    model->appendRow(item);

    QCOMPARE(model->rowCount(), 1);
    QCOMPARE(addedSpy.count(), 1);
    QCOMPARE(countSpy.count(), 1);
    QCOMPARE(countSpy.at(0).at(0).toInt(), 1);

    delete model;
    delete item;
}

void TestListModel::testAppendRows_multipleItems()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Third");

    QSignalSpy addedSpy(model, &ListModel::added);
    QSignalSpy countSpy(model, &ListModel::countChanged);

    QList<ListItem*> items;
    items << item1 << item2 << item3;
    model->appendRows(items);

    QCOMPARE(model->rowCount(), 3);
    QCOMPARE(addedSpy.count(), 3);
    QCOMPARE(countSpy.count(), 1); // One countChanged for the batch
    QCOMPARE(countSpy.at(0).at(0).toInt(), 3);

    delete model;
    delete item1;
    delete item2;
    delete item3;
}

// Insert

void TestListModel::testInsertRow_atBeginning()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");

    model->appendRow(item1);
    model->insertRow(0, item2);

    QCOMPARE(model->rowCount(), 2);
    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("Second"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("First"));

    delete model;
    delete item1;
    delete item2;
}

void TestListModel::testInsertRow_atMiddle()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Middle");

    model->appendRow(item1);
    model->appendRow(item2);
    model->insertRow(1, item3);

    QCOMPARE(model->rowCount(), 3);
    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("First"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("Middle"));
    QCOMPARE(model->data(model->index(2), FeedItem::TitleRole).toString(), QString("Second"));

    delete model;
    delete item1;
    delete item2;
    delete item3;
}

// Data access

void TestListModel::testData_validIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test Feed");
    model->appendRow(item);

    QModelIndex idx = model->index(0);
    QCOMPARE(model->data(idx, FeedItem::TitleRole).toString(), QString("Test Feed"));
    QCOMPARE(model->data(idx, FeedItem::UIDRole).toLongLong(), 1LL);

    delete model;
    delete item;
}

void TestListModel::testData_invalidIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QModelIndex idx = model->index(99);
    QVariant result = model->data(idx, FeedItem::TitleRole);
    QVERIFY(!result.isValid());

    delete model;
}

void TestListModel::testDataByField_validField()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test Feed");
    model->appendRow(item);

    QVariant result = model->dataByField(0, "title");
    QCOMPARE(result.toString(), QString("Test Feed"));

    delete model;
    delete item;
}

void TestListModel::testDataByField_invalidField()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QVariant result = model->dataByField(0, "nonexistent_field");
    QVERIFY(!result.isValid());

    delete model;
    delete item;
}

// Set data

void TestListModel::testSetData_viaIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QModelIndex idx = model->index(0);
    QVERIFY(model->setData(idx, QVariant("newTarget"), FeedItem::DropTargetRole));
    QCOMPARE(item->getDropTarget(), QString("newTarget"));

    delete model;
    delete item;
}

void TestListModel::testSetData_viaFieldName()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    model->setData(0, "dropTarget", QVariant("newTarget"));
    QCOMPARE(item->getDropTarget(), QString("newTarget"));

    delete model;
    delete item;
}

// Flags

void TestListModel::testFlags_validIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QModelIndex idx = model->index(0);
    Qt::ItemFlags flags = model->flags(idx);
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);
    QVERIFY(flags & Qt::ItemIsEditable);

    delete model;
    delete item;
}

void TestListModel::testFlags_invalidIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QModelIndex idx = model->index(99);
    Qt::ItemFlags flags = model->flags(idx);
    QCOMPARE(flags, Qt::NoItemFlags);

    delete model;
}

// Remove

void TestListModel::testRemoveRow_valid()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QSignalSpy removedSpy(model, &ListModel::removed);
    QSignalSpy countSpy(model, &ListModel::countChanged);

    QVERIFY(model->removeRow(0));
    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(removedSpy.count(), 1);
    QCOMPARE(countSpy.count(), 1);
    QCOMPARE(countSpy.at(0).at(0).toInt(), 0);

    delete model;
    delete item;
}

void TestListModel::testRemoveRow_invalid()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QVERIFY(!model->removeRow(0));
    QVERIFY(!model->removeRow(-1));
    QVERIFY(!model->removeRow(99));

    delete model;
}

void TestListModel::testRemoveRows_multiple()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Third");
    FeedItem* item4 = createFeedItem(4, "Fourth");

    QList<ListItem*> items;
    items << item1 << item2 << item3 << item4;
    model->appendRows(items);

    QSignalSpy removedSpy(model, &ListModel::removed);
    QSignalSpy countSpy(model, &ListModel::countChanged);

    // Remove items at index 1 and 2 (Second, Third)
    QVERIFY(model->removeRows(1, 2));
    QCOMPARE(model->rowCount(), 2);
    QCOMPARE(removedSpy.count(), 2);
    QCOMPARE(countSpy.count(), 1);

    delete model;
    delete item1;
    delete item2;
    delete item3;
    delete item4;
}

void TestListModel::testRemoveItem_found()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QVERIFY(model->removeItem(item));
    QCOMPARE(model->rowCount(), 0);

    delete model;
    delete item;
}

void TestListModel::testRemoveItem_notFound()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    // Don't add to model

    QVERIFY(!model->removeItem(item));

    delete model;
    delete item;
}

void TestListModel::testTakeRow()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QSignalSpy removedSpy(model, &ListModel::removed);

    ListItem* taken = model->takeRow(0);
    QCOMPARE(taken, item);
    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(removedSpy.count(), 1);

    delete model;
    delete item;
}

// Find

void TestListModel::testFind_existing()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(42, "Test");
    model->appendRow(item);

    ListItem* found = model->find("FeedItem_42");
    QCOMPARE(found, item);

    delete model;
    delete item;
}

void TestListModel::testFind_nonExisting()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    ListItem* found = model->find("FeedItem_999");
    QCOMPARE(found, nullptr);

    delete model;
    delete item;
}

// Index

void TestListModel::testIndexFromItem_valid()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    model->appendRow(item1);
    model->appendRow(item2);

    QModelIndex idx = model->indexFromItem(item2);
    QVERIFY(idx.isValid());
    QCOMPARE(idx.row(), 1);

    delete model;
    delete item1;
    delete item2;
}

void TestListModel::testIndexFromItem_null()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QModelIndex idx = model->indexFromItem(nullptr);
    QVERIFY(!idx.isValid());

    delete model;
}

void TestListModel::testIndexFromItem_notInModel()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");

    QModelIndex idx = model->indexFromItem(item);
    QVERIFY(!idx.isValid());

    delete model;
    delete item;
}

// Clear

void TestListModel::testClear()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    model->appendRow(item1);
    model->appendRow(item2);

    QSignalSpy removedSpy(model, &ListModel::removed);
    QSignalSpy countSpy(model, &ListModel::countChanged);

    model->clear();

    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(removedSpy.count(), 2);
    QCOMPARE(countSpy.count(), 1);
    QCOMPARE(countSpy.at(0).at(0).toInt(), 0);

    delete model;
    delete item1;
    delete item2;
}

// QML API

void TestListModel::testGet_qmlApi()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test Feed");
    model->appendRow(item);

    QVariantMap map = model->get(0);
    QVERIFY(!map.isEmpty());
    QCOMPARE(map["title"].toString(), QString("Test Feed"));
    QCOMPARE(map["uid"].toLongLong(), 1LL);

    delete model;
    delete item;
}

void TestListModel::testGet_outOfBounds()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QVariantMap map = model->get(0);
    QVERIFY(map.isEmpty());

    map = model->get(-1);
    QVERIFY(map.isEmpty());

    delete model;
}

void TestListModel::testSetProperty()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    model->setProperty(0, "dropTarget", QVariant("newTarget"));
    QCOMPARE(item->getDropTarget(), QString("newTarget"));

    delete model;
    delete item;
}

void TestListModel::testRemove_qmlApi()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Third");

    QList<ListItem*> items;
    items << item1 << item2 << item3;
    model->appendRows(items);

    model->remove(1, 1);
    QCOMPARE(model->rowCount(), 2);

    delete model;
    delete item1;
    delete item2;
    delete item3;
}

// Move

void TestListModel::testMove_forwardSingle()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Third");

    QList<ListItem*> items;
    items << item1 << item2 << item3;
    model->appendRows(items);

    // Move item from index 0 to index 2
    model->move(0, 2);

    // After: [Second, Third, First]
    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("Second"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("Third"));
    QCOMPARE(model->data(model->index(2), FeedItem::TitleRole).toString(), QString("First"));

    delete model;
    delete item1;
    delete item2;
    delete item3;
}

void TestListModel::testMove_backwardSingle()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    FeedItem* item3 = createFeedItem(3, "Third");

    QList<ListItem*> items;
    items << item1 << item2 << item3;
    model->appendRows(items);

    // Move item from index 2 to index 0
    model->move(2, 0);

    // After: [Third, First, Second]
    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("Third"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("First"));
    QCOMPARE(model->data(model->index(2), FeedItem::TitleRole).toString(), QString("Second"));

    delete model;
    delete item1;
    delete item2;
    delete item3;
}

void TestListModel::testMove_samePosition()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");

    QList<ListItem*> items;
    items << item1 << item2;
    model->appendRows(items);

    model->move(1, 1);

    // No change
    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("First"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("Second"));

    delete model;
    delete item1;
    delete item2;
}

void TestListModel::testMove_multipleItems()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "A");
    FeedItem* item2 = createFeedItem(2, "B");
    FeedItem* item3 = createFeedItem(3, "C");
    FeedItem* item4 = createFeedItem(4, "D");

    QList<ListItem*> items;
    items << item1 << item2 << item3 << item4;
    model->appendRows(items);

    // Move 2 items from index 0 to index 2
    // Step 1: src=0, dst=2 -> [B, C, A, D]
    // Step 2: src=0, dst=3 -> [C, A, D, B]
    model->move(0, 2, 2);

    QCOMPARE(model->data(model->index(0), FeedItem::TitleRole).toString(), QString("C"));
    QCOMPARE(model->data(model->index(1), FeedItem::TitleRole).toString(), QString("A"));
    QCOMPARE(model->data(model->index(2), FeedItem::TitleRole).toString(), QString("D"));
    QCOMPARE(model->data(model->index(3), FeedItem::TitleRole).toString(), QString("B"));

    delete model;
    delete item1;
    delete item2;
    delete item3;
    delete item4;
}

// Selection

void TestListModel::testSelection_setSelected()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QSignalSpy selectedSpy(model, &ListModel::selectedChanged);
    QSignalSpy indexSpy(model, &ListModel::selectedIndexChanged);

    model->setSelected(item);

    QCOMPARE(model->selected(), item);
    QCOMPARE(selectedSpy.count(), 1);
    QCOMPARE(indexSpy.count(), 1);
    QCOMPARE(indexSpy.at(0).at(0).toInt(), 0);

    delete model;
    delete item;
}

void TestListModel::testSelection_setSelectedIndex()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item1 = createFeedItem(1, "First");
    FeedItem* item2 = createFeedItem(2, "Second");
    model->appendRow(item1);
    model->appendRow(item2);

    QSignalSpy selectedSpy(model, &ListModel::selectedChanged);
    QSignalSpy indexSpy(model, &ListModel::selectedIndexChanged);

    model->setSelectedIndex(1);

    QCOMPARE(model->selected(), item2);
    QCOMPARE(model->selectedIndex(), 1);
    QCOMPARE(selectedSpy.count(), 1);
    QCOMPARE(indexSpy.count(), 1);

    delete model;
    delete item1;
    delete item2;
}

void TestListModel::testSelection_initialNull()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);

    QCOMPARE(model->selected(), nullptr);
    QCOMPARE(model->selectedIndex(), -1);

    delete model;
}

// Data change propagation

void TestListModel::testHandleItemChange()
{
    ListModel* model = new ListModel(new FeedItem(), nullptr);
    FeedItem* item = createFeedItem(1, "Test");
    model->appendRow(item);

    QSignalSpy dataChangedSpy(model, &QAbstractItemModel::dataChanged);

    // Trigger a data change on the item
    item->setTitle("New Title");

    QCOMPARE(dataChangedSpy.count(), 1);

    delete model;
    delete item;
}

QTEST_MAIN(TestListModel)

#include "tst_listmodel.moc"
