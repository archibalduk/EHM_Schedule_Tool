#pragma once

// Application headers
#include "include/schema/abstract_uid_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Staff award --- //
class StaffAward : public ehm_dal::schema::AbstractUidTableItem
{
public:
    StaffAward();
    ~StaffAward();

    // Child data
    void addChildItem(std::shared_ptr<AbstractTableItem> item,
                      const ehm_dal::tables::TableIndex child_table) override;
    QVariant childData(const QModelIndex &index,
                       qint32 role,
                       column_data::ColumnData *column_data,
                       const ehm_dal::tables::TableIndex child_table) const override;
    qint32 childRowCount(const ehm_dal::tables::TableIndex child_table) const override;
    bool setChildData(const QModelIndex &index,
                      const QVariant &value,
                      const qint32 role,
                      std::vector<qint32> &modified_columns,
                      ehm_dal::column_data::ColumnData *column_data,
                      const ehm_dal::tables::TableIndex child_table) override;

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QString text() const override;

    // Initialisation
    bool init() override;

    // Operator overloading
    bool operator<(const StaffAward &rhs) const;

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


