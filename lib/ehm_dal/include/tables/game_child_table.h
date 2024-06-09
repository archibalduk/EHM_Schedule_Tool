#pragma once

// Application headers
#include "include/column_data/column_data.h"
#include "include/tables/game_table.h"

// Qt headers
#include <QDataStream>

namespace ehm_dal::tables {
/*!
 * \brief The GameChildTable class is a model for child data of a parent table. Each parent
 * item has a single child item (such as `Staff` which each has a single related `StaffInfo`
 * entry).
 */
template<class T_ChildAbstractTableItem,
         class T_ParentAbstractTableItem,
         class T_ColumnData = ehm_dal::column_data::ColumnData>
class GameChildTable : public GameTable<T_ChildAbstractTableItem, T_ColumnData>
{
public:
    GameChildTable(const QString &table_name,
                   const ehm_dal::tables::TableIndex table_id,
                   const TableType table_type);

    // File i/o
    bool readStream(QDataStream &in) override;

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;

    // Get data - counts
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Parent table - attributes
    std::shared_ptr<ehm_dal::tables::AbstractTable> parentTable() const override
    {
        return parent_table_;
    }
    ehm_dal::tables::AbstractTable::ParentTableRelationshipType parentTableRelationship()
        const override
    {
        return parent_table_relationship_;
    }
    void setParentTable(
        const std::shared_ptr<ehm_dal::tables::AbstractTable> parent_table,
        const ehm_dal::tables::AbstractTable::ParentTableRelationshipType relationship) override
    {
        parent_table_ = std::move(parent_table);
        parent_table_relationship_ = std::move(relationship);
    }

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;

    // Table model type
    inline QString modelName() const override { return QStringLiteral("Game child table"); }
    inline constexpr AbstractBaseModel::AbstractTableModelType modelType() const override
    {
        return AbstractBaseModel::AbstractTableModelType::GameChildTable;
    }

protected:
    // Parent table
    std::shared_ptr<ehm_dal::tables::AbstractTable> parent_table_;
    ehm_dal::tables::AbstractTable::ParentTableRelationshipType parent_table_relationship_{
        ehm_dal::tables::AbstractTable::ParentTableRelationshipType::ParentTableHasChildIdField};

    // Parent table - transfer
    bool transferChildDataToParent();

    enum ENUM_FLAGS { NO_PARENT = 0, CHILD_INDEX_PARENT_ROW_MODIFIER = 1 };

    // Modified columns
    virtual bool emitModifiedColumns(const qint32 row,
                                     const std::vector<qint32> &modified_columns,
                                     const QModelIndex &parent,
                                     const QList<qint32> &modified_roles = QList<qint32>())
    {
        for (const auto &itr : modified_columns) {
            const auto parent_index{this->index(parent.row(), 0, QModelIndex())};
            const auto modified_index{this->index(row, itr, parent_index)};

            emit this->dataChanged(modified_index, modified_index, modified_roles);
        }

        return !modified_columns.empty();
    }
};

/* ========================= */
/*      Game Child Table     */
/* ========================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::GameChildTable(
    const QString &table_name, const TableIndex table_id, const TableType table_type)
    : GameTable<T_ChildAbstractTableItem, T_ColumnData>(table_name, table_id, table_type)
{}

/* ================= */
/*      File i/o     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::readStream(
    QDataStream &in)
{
    const auto read_result{GameTable<T_ChildAbstractTableItem, T_ColumnData>::readStream(in)};

    const auto transfer_result{transferChildDataToParent()};

    return read_result && transfer_result;
}

/* ================= */
/*      Get Data     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
QVariant GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::data(
    const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    return this->parent_table_->childData(index,
                                          role,
                                          this->constColumnData(),
                                          this->attributes()->id());
}

/* ========================== */
/*      Get Data - Counts     */
/* ========================== */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
qint32 GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::rowCount(
    const QModelIndex &parent) const
{
    if (parent.isValid() || !this->parent_table_) // No children
        return 0;

    return this->parent_table_->rowCount();
}

/* ==================== */
/*      Parent Data     */
/* ==================== */

// --- Transfer a child item to the parent --- //
template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::
    transferChildDataToParent()
{
    if (!parent_table_) {
        qWarning().noquote() << QStringLiteral("No parent table assigned to '%1' child table")
                                    .arg(this->table_attributes_.name());
        return false;
    }

    const auto parent_size{parent_table_->rowCount()};
    const auto child_table_index{this->attributes()->id()};

    // Parent items have a child id
    if (parent_table_relationship_
        == ehm_dal::tables::AbstractTable::ParentTableRelationshipType::ParentTableHasChildIdField) {
        for (auto parent_id = 0; parent_id < parent_size; ++parent_id) {
            const auto child_id{parent_table_->childItemId(parent_id, child_table_index)};
            if (this->isValidRow(child_id))
                parent_table_->addChildItem(parent_id, this->data_[child_id], child_table_index);
        }
    }
    // Child items have a parent id
    else if (parent_table_relationship_
             == ehm_dal::tables::AbstractTable::ParentTableRelationshipType::
                 ChildTableHasParentIdField) {
        for (auto &itr : this->data_) {
            const auto parent_id{itr->parentItemId()};
            parent_table_->addChildItem(parent_id, itr, child_table_index);
        }
    }

    // Clear the buffer
    this->data_.clear();

    return true;
}

/* ================= */
/*      Set Data     */
/* ================= */

template<class T_ChildAbstractTableItem, class T_ParentAbstractTableItem, class T_ColumnData>
bool GameChildTable<T_ChildAbstractTableItem, T_ParentAbstractTableItem, T_ColumnData>::setData(
    const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    std::vector<qint32> modified_columns{index.column()};

    const auto result{parent_table_->setChildData(index,
                                                  value,
                                                  role,
                                                  modified_columns,
                                                  this->constColumnData(),
                                                  this->attributes()->id())};

    if (result && this->emitModifiedColumns(index.row(), modified_columns, index.parent()))
        return true;

    return false;
}

} // namespace ehm_dal::tables
