#pragma once

// Application headers
#include "include/column_data/column_data.h"
#include "include/database/database_version.h"
#include "include/tables/abstract_table.h"

// Qt headers
#include <QDataStream>

namespace ehm_dal::tables {

// --- EHM database table template sub-class --- //
/*!
 * \brief The GameTable class is a template sub-class of Table and is intended for use as a database table.
 */
template<class T_ColumnData>
concept ColumnData = std::derived_from<T_ColumnData, ehm_dal::column_data::ColumnData>
                     || std::is_same_v<ehm_dal::column_data::ColumnData, T_ColumnData>;

template<class T_AbstractTableItem, ColumnData T_ColumnData = ehm_dal::column_data::ColumnData>
class GameTable : public AbstractTable
{
public:
    GameTable(const QString &table_name,
              const ehm_dal::tables::TableIndex table_id,
              const TableType table_type);

    // File i/o
    bool readStream(QDataStream &in) override;

    // Insert data
    bool insertRows(qint32 row, qint32 count, const QModelIndex &parent = QModelIndex()) override;

    // Table model type
    inline QString modelName() const override { return QStringLiteral("Game standard table"); }
    inline constexpr AbstractBaseModel::AbstractTableModelType modelType() const override
    {
        return AbstractBaseModel::AbstractTableModelType::GameTable;
    }

    // Unknown/junk data
    inline virtual qsizetype junkDataPrefixSize() const { return junk_data_prefix_.size(); }
    //inline qsizetype junkDataSuffixSize() const { return junk_data_suffix_.size(); }

private:
    // Unknown/junk data
    QByteArray junk_data_prefix_; // Start of file junk
    //QByteArray junk_data_suffix_; // End of file junk
};

/* =================== */
/*      Game Table     */
/* =================== */

template<class T_AbstractTableItem, ColumnData T_ColumnData>
GameTable<T_AbstractTableItem, T_ColumnData>::GameTable(const QString &table_name,
                                                        const TableIndex table_id,
                                                        const TableType table_type)
    : AbstractTable(table_name, table_id, table_type, new T_ColumnData())
{}

/* ================= */
/*      File i/o     */
/* ================= */

template<class T_AbstractTableItem, ColumnData T_ColumnData>
bool GameTable<T_AbstractTableItem, T_ColumnData>::readStream(QDataStream &in)
{
    // Junk data (for saved game tables)
    const auto junk_data_prefix_size{junkDataPrefixSize()};
    if (junk_data_prefix_size > 0) {
        junk_data_prefix_.resize(junk_data_prefix_size);
        in.readRawData(junk_data_prefix_.data(), junk_data_prefix_size);
    }

    // Table header
    auto error_count{0};
    const auto record_count{table_attributes_.readTableHeader(in)};

    ehm_dal::database::DatabaseVersion database_version;

    qDebug().noquote() << QStringLiteral("Reading table:") << table_attributes_.name()
                       << QString("-> %L1 record(s)").arg(record_count);

    // Table items/records
    for (quint32 i = 0; i < record_count; ++i) {
        auto item{std::make_unique<T_AbstractTableItem>()};
        item->read(in, database_version);
        item->fixErrors();
        data_.emplace_back(std::move(item));
    }

    if (error_count)
        qWarning().noquote() << QStringLiteral("%L1 error(s) encountered when reading %2")
                                    .arg(error_count)
                                    .arg(table_attributes_.name());

    return error_count == 0;
}

/* ==================== */
/*      Insert Data     */
/* ==================== */

template<class T_AbstractTableItem, ColumnData T_ColumnData>
bool GameTable<T_AbstractTableItem, T_ColumnData>::insertRows(qint32 row,
                                                              qint32 count,
                                                              const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || row > static_cast<qint32>(this->data_.size()))
        return false;

    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        auto new_item{std::make_shared<T_AbstractTableItem>()};
        new_item->alloc(static_cast<qint32>(this->data_.size()));
        this->data_.insert(this->data_.begin() + row, std::move(new_item));
    }

    endInsertRows();
    return true;
}

} // namespace ehm_dal::tables
