#pragma once


// Application headers
#include "include/column_data/column_data.h"
#include "include/tables/game_table.h"
#include "include/tables/table_index.h"
#include "include/tables/table_type.h"

/*!
 * \brief namespace ehm_dal::saved_game
 */
namespace ehm_dal::saved_game {

// --- EHM saved game table template sub-class --- //
/*!
 * \brief The SavedGameTable class is a template sub-class of GameTable and is intended for use as a saved game table.
 */
template<class T_AbstractTableItem, class T_ColumnData = ehm_dal::column_data::ColumnData>
class SavedGameTable : public ehm_dal::tables::GameTable<T_AbstractTableItem, T_ColumnData>
{
public:
    SavedGameTable(const QString &table_name,
                   const ehm_dal::tables::TableType table_type
                   = ehm_dal::tables::TableType::TABLE_WITH_NO_TABLE_ID);

    // Unknown/junk data
    inline qsizetype junkDataPrefixSize() const override { return junk_data_prefix_size_; }
    inline void setJunkDataPrefixSize(const qsizetype size) { junk_data_prefix_size_ = size; }

private:
    // Unknown/junk data
    qsizetype junk_data_prefix_size_{0};
};

template<class T_AbstractTableItem, class T_ColumnData>
SavedGameTable<T_AbstractTableItem, T_ColumnData>::SavedGameTable(
    const QString &table_name, const ehm_dal::tables::TableType table_type)
    : ehm_dal::tables::GameTable<T_AbstractTableItem, T_ColumnData>(
        table_name, ehm_dal::tables::TableIndex::SAVED_GAME_TABLE, table_type)
{}

} // namespace ehm_dal::saved_game

