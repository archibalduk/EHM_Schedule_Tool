#pragma once

// Application headers
#include "include/column_data/column_data.h"
#include "include/tables/game_child_table.h"

// Qt headers
#include <QDataStream>

namespace ehm_dal::tables {
template<class T_ChildAbstractTableItem,
         class T_ParentAbstractTableItem,
         class T_ColumnData = ehm_dal::column_data::ColumnData>
/*!
 * \brief The GameChildTreeTable class is a model for child data of a parent table. Each parent
 * item can have mulitple child items (such as `Staff` which each may have multiple related
 * `StaffHistory` entries).
 */
class GameChildTreeTable
    : public GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>
{
public:
    GameChildTreeTable(const QString &table_name,
                       const ehm_dal::tables::TableIndex table_id,
                       const TableType table_type);

    // Child data
    // NOTE the sibling() function fails QAbstractItemModelTester but does work
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex sibling(int row, int column, const QModelIndex &idx) const override;

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;

    // Get data - counts
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Indexes
    bool hasIndex(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(qint32 row,
                      qint32 column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;

    // Table model type
    inline QString modelName() const override { return QStringLiteral("Game child tree table"); }
    inline constexpr AbstractBaseModel::AbstractTableModelType modelType() const override
    {
        return AbstractBaseModel::AbstractTableModelType::GameChildTreeTable;
    }

private:
    static constexpr qint32 parent_row_column_count_{1}; // Column count for parent rows
};

/* ============================== */
/*      Game Child Tree Table     */
/* ============================== */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::
    GameChildTreeTable(const QString &table_name,
                       const TableIndex table_id,
                       const TableType table_type)
    : GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>(table_name,
                                                                                        table_id,
                                                                                        table_type)
{}

/* ================= */
/*      Children     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::hasChildren(
    const QModelIndex &parent) const
{
    if (!parent.isValid())
        return true; // The root has children: the parent rows

    if (parent.column() != 0)
        return false; // Only parent column 0 should have children

    if (parent.internalId() == static_cast<quintptr>(GameChildTreeTable::NO_PARENT))
        return this->rowCount(parent) > 0; // True if the parent row has any children

    return false; // Parent row has no children
}

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
QModelIndex
GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::sibling(
    int row, int column, const QModelIndex &idx) const
{
    if (!idx.isValid())
        return QModelIndex();

    // For top-level items (i.e. parent)
    if (!idx.parent().isValid()) {
        // Top-level items only have one column.
        // If column != 0 or the row is out of bounds, return an invalid index.
        if (column != 0 || row < 0 || row >= rowCount())
            return QModelIndex();

        return index(row, 0); // Return the top-level index for the specified row
    }

    // For child items
    if (row < 0 || row >= rowCount(idx.parent()) || column < 0
        || column >= columnCount(idx.parent()))
        return QModelIndex();

    return index(row, column, idx.parent());
}

/* ================= */
/*      Get Data     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
QVariant GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::data(
    const QModelIndex &index, qint32 role) const
{
    // Child data
    if (index.internalId() != static_cast<quintptr>(GameChildTreeTable::NO_PARENT))
        return GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::
            data(index, role);

    // Parent data
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return this->parent_table_->text(index.row());
        default:
            break;
        }
    }

    return QVariant();
}

/* ========================== */
/*      Get Data - Counts     */
/* ========================== */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
qint32
GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::columnCount(
    const QModelIndex &parent) const
{
    if (!parent.isValid())
        return this->constColumnData()->columnCount(); // Parent level

    if (parent.internalId() == static_cast<quintptr>(GameChildTreeTable::NO_PARENT)
        && parent.column() == 0)
        return this->constColumnData()->columnCount(); // Child level

    return 0; // Return 0 by default, although this shouldn't typically be reached

    // NOTE previous (working code) was as follows.
    // This however fails QAbstractItemModelTester with the following error
    // FAIL! childIndex != childIndex1 () returned FALSE
    /* Q_UNUSED(parent)
    return this->constColumnData()->columnCount();*/
}

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
qint32 GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::rowCount(
    const QModelIndex &parent) const
{
    // Return number of parent rows
    if (!parent.isValid())
        return this->parent_table_->rowCount();

    // Return number of child rows for a parent
    if (parent.internalId() == static_cast<quintptr>(GameChildTreeTable::NO_PARENT)
        && parent.column() == 0)
        return this->parent_table_->childRowCount(parent.row(), this->attributes()->id());

    return 0; // Child rows do not have their own children
}

/* ================ */
/*      Indexes     */
/* ================ */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::hasIndex(
    int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) // Only parent column 0 should have children
        return false;

    if (column < 0 || column >= this->columnCount(parent)) {
        return false;
    }

    return row >= 0 && row < this->rowCount(parent);
}

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
QModelIndex
GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::index(
    qint32 row, qint32 column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
        return this->createIndex(row, column, static_cast<quintptr>(GameChildTreeTable::NO_PARENT));

    return this->createIndex(row,
                             column,
                             parent.row() + GameChildTreeTable::CHILD_INDEX_PARENT_ROW_MODIFIER);
}

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
QModelIndex
GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::parent(
    const QModelIndex &index) const
{
    if (!index.isValid()
        || index.internalId() == static_cast<quintptr>(GameChildTreeTable::NO_PARENT))
        return QModelIndex();

    return this->createIndex(index.internalId()
                                 - GameChildTreeTable::CHILD_INDEX_PARENT_ROW_MODIFIER,
                             0);
}

/* ================= */
/*      Set Data     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTreeTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::setData(
    const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (index.internalId() == static_cast<quintptr>(GameChildTreeTable::NO_PARENT))
        return false;

    return GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::setData(
        index, value, role);
}

} // namespace ehm_dal::tables
