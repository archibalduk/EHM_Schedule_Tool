#pragma once

// Application headers
#include "include/database/schema/club/club_records/club_record_index.h"
#include "include/schema/abstract_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Retired numbers --- //
class ClubRecords : public ehm_dal::schema::AbstractTableItem
{
public:
    ClubRecords();
    ~ClubRecords();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QVariant data(const QModelIndex &index,
                  qint32 role,
                  ehm_dal::column_data::ColumnData *column_data) const override;
    constexpr size_t size() const { return ClubRecordIndex::TOTAL_CLUB_RECORDS_COUNT; }
    QString text() const override;

    // Initialisation
    bool init() override;

    // Operator overloading
    bool operator<(const ClubRecords &rhs) const;

    // Parent data
    qint32 parentItemId() const override;

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role,
                 std::vector<qint32> &modified_columns,
                 ehm_dal::column_data::ColumnData *column_data) override;

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    QVariant internalData(const qint32 column, const qint32 role) const override;
    QVariant nameData(const qint32 row, const qint32 role) const;
    QString name(const qint32 row) const;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema
