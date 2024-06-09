#pragma once

/*!
 * \brief namespace ehm_dal::tables
 */
namespace ehm_dal::tables {

// Database table types
/*!
 * \brief The TableType enum denotes different types of database table.
 */
enum class TableType : unsigned char {
    // Database tables
    STANDARD_TABLE,         /*!< standard table */
    TABLE_HEADER,           /*!< table header */
    TABLE_WITH_NO_TABLE_ID, /*!< table with no EHM table id */
    TABLE_WITH_NO_HEADER,   /*!< table with no record count or EHM table id */
    // Flag tables
    BITMASK_FLAG_TABLE, /*!< table containing `ehm_dal::flags::Flag` data (bitmask format) */
    FLAG_TABLE,         /*!< table containing `ehm_dal::flags::Flag` data (non-bitmask format) */
};

} // namespace ehm_dal::tables


