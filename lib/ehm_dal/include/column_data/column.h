#pragma once

// Application headers
namespace ehm_dal::tables {
class AbstractTable;
enum class TableIndex : char;
}

// Qt headers
#include <QString>

namespace ehm_dal::column_data {

// --- Column index/data --- //
/*!
 * \brief The Column class represents a column of data in a `Table`.
 */
class Column
{
public:
    // Settings
    /*!
     * \brief The COLUMN_SETTINGS enum represents settings for a `Column`.
     */
    enum COLUMN_SETTINGS {
        NO_SETTINGS = 1 << 0,
        HIDE_EVERYWHERE = 1 << 1,   /*!< Hide from filters, ui and tables */
        HIDE_FROM_FILTERS = 1 << 2, /*!< Hide from filters, but visible on ui and tables */
        HIDE_FROM_TABLES = 1 << 3,  /*!< Hide from tables, but visible on filters */
        HIDE_FROM_UI = 1 << 4,      /*!< Hide from the UI, but visible on filters and tables */
        HIDE_FROM_UI_AND_TABLES = 1 << 5, /*!< Hide from the UI and tables, but visible on filters */
        READ_ONLY = 1 << 6,               /*!< Read only */
        COLOUR_POINTER = 1 << 7,          /*!< Colour pointer */
        NAME_STRING_POINTER = 1 << 8,     /*!< Name string pointer */
        POINTER_LIST = 1 << 9,            /*!< QSet<qint32> of pointers */
        RAW_POINTER = 1 << 10,            /*!< Raw pointer */
        CACHED_COLUMN = 1 << 11           /*!< Uses a Cached Column Manager to generate data */
    };

    // Column types
    /*!
     * \brief The ColumnType enum represents the data type of the `Column`.
     */
    enum class ColumnType : quint8 {
        // Bool
        BOOL,
        // Containers
        CONTAINER,
        // Date
        DATE,
        YEAR,
        // Numerical
        ATTRIBUTE_20,
        ATTRIBUTE_99,
        ATTRIBUTE_200,
        ATTRIBUTE_POTENTIAL,
        CHAR,
        UCHAR,
        CURRENCY,
        DOUBLE,
        FLOAT,
        INT,
        UINT,
        SHORT,
        USHORT,
        // Pointer
        FLAG,
        POINTER,
        POINTER_BITMASK_FLAG_TABLE,
        POINTER_COLOUR_TABLE,
        POINTER_DATABASE_TABLE,
        POINTER_FLAG_TABLE,
        POINTER_LIST,
        RAW_POINTER,
        // Primary key
        PRIMARY_KEY_ID,
        PRIMARY_KEY_UID,
        // Special
        EXTRA_RULES,
        // Text
        STRING
    };

    Column();
    // Non-pointer constructor
    /*!
     * \brief Constructs a Column representing a data type other than an `ehm_dal::data_types::AbstractPointer`.
     * \param position Position index of the column within the table (starting at zero)
     * \param name Name of the column
     * \param type Type of data held by the column
     * \param settings The `Column::COLUMN_SETTINGS` of the column
     */
    Column(const qint32 position,
           const QString &name,
           const ColumnType type,
           const quint16 settings = NO_SETTINGS);
    // Pointer constructor
    /*!
     * \brief Constructs a Column representing an `ehm_dal::data_types::AbstractPointer` data type.
     * \param position Position index of the column within the table (starting at zero)
     * \param name Name of the column
     * \param table The source `ehm_dal::tables::AbstractTable` to which the column points
     * \param settings The `Column::COLUMN_SETTINGS` of the column
     */
    Column(const qint32 position,
           const QString &name,
           std::shared_ptr<ehm_dal::tables::AbstractTable> table,
           const quint16 settings = NO_SETTINGS);

    // Get data - basic attributes
    /*!
     * \brief Returns the `Qt::ItemFlags` in respect of the column.
     */
    Qt::ItemFlags flags() const;
    /*!
     * \brief Returns the column position/index
     */
    inline qint32 id() const { return position_; } // Column position/index
    /*!
     * \brief Returns the column name
     */
    inline QString name() const { return name_; }  // Column name
    Q_DECL_DEPRECATED inline qint32 position() const
    {
        return id();
    } // Column position/index (to be deprecated)

    // Get data - general attributes
    /*!
     * \brief Returns whether the column is cached
     */
    inline bool isCached() const { return (settings_ & CACHED_COLUMN); }
    /*!
     * \brief Returns whether the column is checkable
     */
    inline bool isCheckable() const { return type_ == ColumnType::BOOL; }
    /*!
     * \brief Returns whether the column represents a container
     */
    inline bool isContainer() const { return type_ == ColumnType::CONTAINER; }
    /*!
     * \brief Returns whether the column contains read only data
     */
    inline bool isReadOnly() const { return (settings_ & READ_ONLY); }

    // Get data - table pointer
    /*!
     * \brief Returns whether the column points to a `ehm_dal::schema::Colour`.
     * This is only applicable to columns representing an `ehm_dal::data_types::AbstractPointer` data type.
     */
    inline bool isColourPointer() const { return (settings_ & COLOUR_POINTER); }
    /*!
     * \brief Returns whether the column points to a `ehm_dal::Database` table.
     * This is only applicable to columns representing an `ehm_dal::data_types::AbstractPointer` data type.
     */
    bool isDatabaseTablePointer() const;
    /*!
     * \brief Returns whether the column points to a `ehm_dal::flag::FlagDatabase` table.
     * This is only applicable to columns representing an `ehm_dal::data_types::AbstractPointer` data type.
     */
    bool isFlagTablePointer() const;
    /*!
     * \brief Returns whether the column points to a `ehm_dal::data_types::NamePointer`.
     * This is only applicable to columns representing an `ehm_dal::data_types::AbstractPointer` data type.
     */
    inline bool isNameStringPointer() const { return (settings_ & NAME_STRING_POINTER); }
    /*!
     * \brief Returns whether the column represents a list of pointers.
     */
    inline bool isPointerList() const { return (settings_ & POINTER_LIST); }
    /*!
     * \brief Returns whether the column represents a raw pointer to point to data.
     */
    inline bool isRawPointer() const { return (settings_ & RAW_POINTER); }
    /*!
     * \brief Returns the `ehm_dal::tables::TableIndex` of the source `ehm_dal::tables::AbstractTable`.
     */
    ehm_dal::tables::TableIndex relatedTableIndex() const;
    /*!
     * \brief Returns the table name of the source `ehm_dal::tables::AbstractTable`.
     */
    QString relatedTableName() const;

    // Get data - visibility
    /*!
     * \brief Returns whether the column is hidden everywhere.
     */
    inline bool hiddenEverywhere() const { return (settings_ & HIDE_EVERYWHERE); }
    /*!
     * \brief Returns whether the column is hidden from filters.
     */
    inline bool hiddenFromFilters() const
    {
        return (settings_ & HIDE_FROM_FILTERS) || hiddenEverywhere();
    }
    /*!
     * \brief Returns whether the column is hidden from tables.
     */
    inline bool hiddenFromTables() const
    {
        return (settings_ & HIDE_FROM_TABLES) || (settings_ & HIDE_FROM_UI_AND_TABLES)
               || hiddenFromFilters();
    }
    /*!
     * \brief Returns whether the column is hidden from the user interface.
     */
    inline bool hiddenFromUi() const
    {
        return (settings_ & HIDE_FROM_UI_AND_TABLES) || (settings_ & HIDE_FROM_UI)
               || hiddenEverywhere();
    }
    /*!
     * \brief Returns whether the column is visible to filters.
     */
    inline bool visibleToFilters() const { return !hiddenFromFilters(); }

private:
    enum ENUM_FLAGS { NO_COLUMN_INDEX = -1 };

    // Attributes
    qint32 position_{NO_COLUMN_INDEX};
    QString name_{QStringLiteral("No column name")};
    quint16 settings_{NO_SETTINGS};
    ColumnType type_;

    // Table pointer
    std::shared_ptr<ehm_dal::tables::AbstractTable> table_;
    void initTablePointer();

    // Settings
    void initSettings();
};

} // namespace ehm_dal::column_data

