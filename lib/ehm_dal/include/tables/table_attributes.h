#pragma once

// Application headers
#include "include/tables/table_index.h"
#include "include/tables/table_type.h"

// Qt headers
class QDataStream;
#include <QString>

namespace ehm_dal::tables {
class TableAttributes
{
public:
    TableAttributes(const QString &name = QString(),
                    const TableIndex table_id = TableIndex::NO_TABLE,
                    const TableType type = TableType::STANDARD_TABLE);

    // File i/o
    quint32 readTableHeader(QDataStream &in);
    bool writeTableHeader(QDataStream &out);

    // Get data
    /*!
     * \brief Returns the internal EHM table id of the table.
     * \return the internal EHM table id.
     */
    inline qint16 gameTableId() const { return game_table_id_; }
    /*!
     * \brief Returns the id of the table. The id used to distinguish between tables in EHM DAL. This id is disinct 
     * from any table id used internally by EHM.
     * \return the table id as a ehm_dal::tables::TableIndex.
     */
    inline TableIndex id() const { return ehm_dal_table_id_; }
    /*!
     * \brief Returns the name of the table.
     * \return the table name.
     */
    inline QString name() const { return name_; }

    // Get data - table type
    bool isDatabaseTable() const;
    bool isFlagBitmaskTable() const;
    bool isFlagStandardTable() const;
    bool isFlagTable() const;
    /*!
     * \brief Returns the type of the table.
     * \return the table type as a ehm_dal::tables::TableType.
     */
    inline TableType type() const { return type_; }

private:
    static constexpr qint16 NO_TABLE_ID{-1};

    // File/record attributes
    qint64 file_position_{-1};
    quint32 record_count_{0};

    // Table attributes
    TableIndex ehm_dal_table_id_;       // Internal ehm_db table id
    qint16 game_table_id_{NO_TABLE_ID}; // EHM database id used in database.db
    const QString name_;
    const TableType type_;
};

} // namespace ehm_dal::tables
