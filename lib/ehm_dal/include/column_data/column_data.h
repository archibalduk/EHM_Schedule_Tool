#pragma once

// Qt headers
#include <QModelIndex> // TODO This could be forward-declared if another Qt source is included here
class QSize;
#include <vector>

namespace ehm_dal::column_data {

class Column;

// --- Column index data container --- //
/*!
 * \brief The ColumnData class represents a container of `ehm_dal::column_data::Column` 
 * and attributes relating to the columns as a whole (e.g. column count).
 */
class ColumnData
{
public:
    // Settings
    /*!
     * \brief The COLUMN_DATA_SETTINGS enum represents settings for `ColumnData`.
     */
    enum COLUMN_DATA_SETTINGS {
        NO_SETTINGS = 1 << 0,
        //CHILD_TABLE = 1 << 1,              // Is a child table
        //FLAGS_TABLE = CHILD_TABLE,         // Both tables are treated the same
        DO_NOT_USE_EXTRA_COLUMNS = 1 << 2, /*!< No validation status, display text, etc columns */
        HAS_NO_ID_COLUMN = 1 << 3,         /*!< Has no id column */
        HAS_UID_COLUMN = 1 << 4,           /*!< Has a uid column */
        FORCE_CACHING = 1 << 5,    /*!< Force caching where a table wouldn't otherwise be cached */
        REBUILD_PRIORITY = 1 << 6, /*!< Table should be rebuilt prior to other tables */
        SORTABLE_TABLE = 1 << 7,   /*!< Table can be sorted */
        USES_IDENTIFIER_SINGLE_STRING = 1 << 8, /*!< Single identifier string */
        USES_IDENTIFIER_STRING_LIST = 1 << 9,   /*!< String list of identifiers */
    };

    // Base column indexes
    /*!
     * \brief The COLUMN_DATA_INDEXES enum sets out the base `Column` indexes within the `ColumnData`.
     * Derived class `ColumnData` indexes commence from `FirstStandardDerivedColumnIndex`
     * or `FirstIdOnlyDerivedColumnIndex` as applicable.
     */
    enum COLUMN_DATA_INDEXES {
        FirstColumn = 0,
        Id = FirstColumn,                       /*!< Item id */
        Uid,                                    /*!< Item unique id */
        DisplayText,                            /*!< Display text */
        SubHeadingText,                         /*!< Sub-heading text */
        ValidationStatus,                       /*!< Validation status */
        IsModifiedByDbXfer,                     /*!< Has been modified by a DB xfer/import */
        DbXferImportId,                         /*!< DB xfer/import id */
        FirstStandardDerivedColumnIndex,        /*!< For tables with all of the above fields */
        FirstIdOnlyDerivedColumnIndex = Id + 1, /*!< For tables with an id column only */
        Text = DisplayText                      /*!< For backwards compatibility */
    };

    // Constructor
    /*!
     * \brief Default constructor
     * \param settings The `ColumnData::COLUMN_DATA_SETTINGS` to apply
     */
    ColumnData(const quint16 settings = NO_SETTINGS);
    ~ColumnData();

    // Add column data
    /*!
     * \brief Adds the `column` to the column data. Note this moves `column`.
     * \param column to be added to the column data.
     */
    void add(const Column &column);
    /*!
     * \brief Adds all of the columns from `data` to the column data.
     * \param data containing the columns to be added.
     */
    void add(const ColumnData &data);

    // Cache status
    /*!
     * \brief Returns whether any cached columns are present.
     */
    inline bool isCached() const { return is_cached_; }
    /*!
     * \brief Sets the cached status of any cached columns
     * \param is_cached whether or not the underlying data has been cached
     */
    inline void setCacheComplete(const bool is_cached) { is_cached_ = is_cached; }

    // Get data
    /*!
     * \brief Returns the number of columns
     */
    qint32 columnCount() const;
    /*!
     * \brief Returns a raw pointer to the `Column` with a column index of `column_id`.
     * \param column_id column index
     */
    const Column *column(const qint32 column_id) const;
    /*!
     * \brief Returns the dimensions of the `Column` with a column index of `column_id`.
     * \param column_id column index
     */
    QSize dimensions(const qint32 column_id) const;
    /*!
     * \brief Returns the first column index of the class derived from `ColumnData`.
     */
    inline qint32 firstDerivedColumnIndex() const { return first_derived_column_index_; }
    /*!
     * \brief Returns the `Qt::ItemFlags` in respect of the column from `index`.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /*!
     * \brief Returns whether or not any columns have been added to the column data.
     */
    inline bool isInitialised() const { return is_initialised_; }
    /*!
     * \brief Returns the name of the `Column` with a column index of `column_id`.
     */
    QString name(const qint32 column_id) const;

    // Get data - settings
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::DO_NOT_USE_EXTRA_COLUMNS` is `false`.
     */
    inline bool hasExtraColumns() const { return (settings_ & DO_NOT_USE_EXTRA_COLUMNS) == 0; }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::HAS_NO_ID_COLUMN` is `false`.
     */
    inline bool hasIdColumn() const { return (settings_ & HAS_NO_ID_COLUMN) == 0; }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::REBUILD_PRIORITY` is true.
     */
    inline bool hasRebuildPriority() const { return (settings_ & REBUILD_PRIORITY); }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::HAS_UID_COLUMN` is true.
     */
    inline bool hasUidColumn() const { return (settings_ & HAS_UID_COLUMN); }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::SORTABLE_TABLE` is true.
     */
    inline bool isSortable() const { return (settings_ & SORTABLE_TABLE); }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::USES_IDENTIFIER_SINGLE_STRING` is true.
     */
    inline bool usesIdentifierSingleString() const
    {
        return settings_ & USES_IDENTIFIER_SINGLE_STRING;
    }
    /*!
     * \brief Returns whether or not `COLUMN_DATA_SETTINGS::USES_IDENTIFIER_STRING_LIST` is true.
     */
    inline bool usesIdentifierStringList() const { return settings_ & USES_IDENTIFIER_STRING_LIST; }

    // Identifier
    /*!
     * \brief Validates the identifier setting in order to ensure it is correctly set
     */
    void validateIdentifierSetting();

    // Operator overloading
    bool operator==(const ColumnData &rhs) const;
    inline bool operator!=(const ColumnData &rhs) const { return !(*this == rhs); }

    // Set data
    /*!
     * \brief Clear all column data (including any default columns).
     */
    void clearAll();

    // Sanity checking
    /*!
     * \brief Checks whether a 'Column' is present with a column index equal to `column_id`
     * \param column_id the selected column index
     */
    bool isValid(const qint32 column_id) const;

private:
    std::vector<Column> columns_;
    qint32 first_derived_column_index_{0};

    // Cached status
    bool is_cached_{true}; // Indicates whether initial caching is complete

    // Initialisation
    bool is_initialised_{false};
    void init();

    // Settings
    quint16 settings_{NO_SETTINGS};
};

} // namespace ehm_dal::column_data


