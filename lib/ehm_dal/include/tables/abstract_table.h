#pragma once

// Application headers
#include "include/schema/abstract_table_item.h"
#include "include/tables/private/abstract_base_model.h"
#include "include/tables/table_attributes.h"
#include "include/tables/table_index.h"
#include "include/tables/table_type.h"

// Application headers
namespace ehm_dal::data_types {
class Pointer;
}

// Qt headers
#include <QAbstractTableModel>
#include <QString>
#include <memory>
#include <vector>

namespace ehm_dal::tables {

// --- Table base class --- //
/*!
 * \brief The Table class represents a database table and provides access to rows of data.
 * \details Access to each row of data is via `QModelIndex`. Table inherits from `QAbstractTableModel` and is there compatible with Qt's Model/View framework.
 */
class AbstractTable : public AbstractBaseModel
{
    // NOTE: Insert rows, delete rows and move rows functions are entirely untested
public:
    /*!
     * \brief Constructs a new database table.
     * \param table_name Name of the table
     * \param table_id ehm_dal::tables::TableIndex (aka id) of the table
     * \param table_type ehm_dal::tables::TableType of table
     * \param column_data Table column data
     */
    AbstractTable(
        const QString &table_name,
        const ehm_dal::tables::TableIndex table_id,
        const ehm_dal::tables::TableType table_type,
        ehm_dal::column_data::ColumnData *column_data = new ehm_dal::column_data::ColumnData());

    // Child data
    void addChildItem(const qint32 parent_row_id,
                      std::shared_ptr<ehm_dal::schema::AbstractTableItem> item,
                      const ehm_dal::tables::TableIndex child_table);
    QVariant childData(const QModelIndex &index,
                       qint32 role,
                       ehm_dal::column_data::ColumnData *column_data,
                       const ehm_dal::tables::TableIndex child_table);
    qint32 childItemId(const qint32 parent_row_id,
                       const ehm_dal::tables::TableIndex child_table) const;
    virtual qint32 childRowCount(const qint32 parent_row_id,
                                 const ehm_dal::tables::TableIndex child_table) const;
    bool setChildData(const QModelIndex &index,
                      const QVariant &value,
                      const qint32 role,
                      std::vector<qint32> &modified_columns,
                      ehm_dal::column_data::ColumnData *column_data,
                      const ehm_dal::tables::TableIndex child_table);

    // File i/o
    /*!
     * \brief Reads the table data from a `QDataStream` (wrapper for `AbstractTable::readStream`).
     * \param in
     * \return whether parsing was successful.
     */
    bool read(QDataStream &in);
    /*!
     * \brief Reads the table data from a `QByteArray`.
     * \param in
     * \return whether parsing was successful.
     */
    bool readData(QByteArray *data);

    // Find data
    /*!
     * \brief Finds the first row which has a value in the chosen `column` matching `value`.
     * \param value Target value
     * \param column Target column to search
     * \return a Pointer to the search result. A null Pointer indicates that no match was found.
     */
    ehm_dal::data_types::Pointer find(const qint32 value, const quint16 column);
    /*!
     * \brief Finds the first row which has text in the chosen `column` exactly matching `text`. The entirety of the 
     * string much match the `text` to constitute a match.
     * \param text Target text
     * \param column Target column to search
     * \param cs Case sensitivity
     * \return a Pointer to the search result. A null Pointer indicates that no match was found.
     */
    ehm_dal::data_types::Pointer find(const QString &text,
                                      const quint16 column,
                                      const Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    /*!
     * \brief Finds the first row which has text in the chosen `column` containing `text`. This function performs 
     * a sub-string search.
     * \param text Target text
     * \param column Target column to search
     * \param cs Case sensitivity
     * \return a Pointer to the search result. A null Pointer indicates that no match was found.
     */
    ehm_dal::data_types::Pointer findContains(const QString &text,
                                              const quint16 column,
                                              const Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    /*!
     * \brief Finds all rows which have a value in the chosen `column` matching `value`.
     * \param value Target value
     * \param column Target column to search
     * \return a vector of Pointers to each search result. An empty vector indicates that no match was found.
     */
    std::vector<ehm_dal::data_types::Pointer> findAll(const qint32 value, const quint16 column);
    /*!
     * \brief Finds all rows which have text in the chosen `column` exactly matching `text`. The entirety of the
     * string much match the `text` to constitute a match.
     * \param text Target text
     * \param column Target column to search
     * \param cs Case sensitivity
     * \return a vector of Pointers to each search result. An empty vector indicates that no match was found.
     */
    std::vector<ehm_dal::data_types::Pointer> findAll(
        const QString &text,
        const quint16 column,
        const Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    /*!
     * \brief Finds all rows which have text in the chosen `column` containing `text`. This function performs
     * a sub-string search.
     * \param textTarget text
     * \param column Target column to search
     * \param cs Case sensitivity
     * \return a vector of Pointers to each search result. An empty vector indicates that no match was found.
     */
    std::vector<ehm_dal::data_types::Pointer> findAllContains(
        const QString &text,
        const quint16 column,
        const Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    // Get data
    /*!
     * \brief Returns the data stored under the given role for the item referred to by the index.
     * \param index Index of the selected row and column
     * \param role Item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \return a QVariant containing a copy of the data.
     */
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    bool isValidRow(const qint32 row_id) const;
    QString text(const qint32 row) const;

    // Get data - counts
    /*!
     * \brief Returns the number of rows in the table.
     * \param parent Not used
     * \return the row count.
     */
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Get data - pointers
    /*!
     * \brief Returns a shared pointer to the selected row of the table
     * \param row Table row
     * \return shared_ptr to the selected row of the table
     */
    std::shared_ptr<ehm_dal::schema::AbstractTableItem> pointer(const qint32 row);

    // Get data - table attributes
    const TableAttributes *attributes() const { return &table_attributes_; }

    // Initialisation
    /*!
     * \brief Initialises the table
     * \return whether initialisation took place
     */
    bool init();

    // Move data
    //bool moveRow(const QModelIndex &sourceParent, qint32 source_row, const QModelIndex &destination_parent, qint32 destination_child) override;
    bool moveRows(const QModelIndex &source_parent,
                  qint32 source_row,
                  qint32 count,
                  const QModelIndex &destination_parent,
                  qint32 destination_child) override;

    // Parent table
    enum class ParentTableRelationshipType : qint8 {
        TableDoesNotHaveAnyParent,
        ParentTableHasChildIdField,
        ChildTableHasParentIdField
    };
    qint32 parentRowId(const QModelIndex &index) const;
    inline virtual std::shared_ptr<ehm_dal::tables::AbstractTable> parentTable() const
    {
        return nullptr;
    }
    inline virtual ParentTableRelationshipType parentTableRelationship() const
    {
        return ParentTableRelationshipType::TableDoesNotHaveAnyParent;
    }
    inline virtual void setParentTable(
        const std::shared_ptr<ehm_dal::tables::AbstractTable> parent_table,
        const ParentTableRelationshipType relationship)
    {
        Q_UNUSED(parent_table)
        Q_UNUSED(relationship)
        return;
    }

    // Remove data
    bool removeRows(qint32 row, qint32 count, const QModelIndex &parent = QModelIndex()) override;

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;

protected:
    // Table data
    TableAttributes table_attributes_;
    std::vector<std::shared_ptr<ehm_dal::schema::AbstractTableItem>> data_;

private:
    bool is_initialised_{false};

    /*!
     * \brief Reads the table data from a `QDataStream`.
     * \param in
     * \return whether parsing was successful.
     */
    virtual bool readStream(QDataStream &in) = 0;
};

} // namespace ehm_dal::tables


