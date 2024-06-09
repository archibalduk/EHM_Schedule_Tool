#pragma once

// Application headers
#include "include/column_data/column_data.h"

// Qt headers
#include <QAbstractTableModel>

namespace ehm_dal::tables {

// --- Abstract base class for model classes --- //
// --- Formerly known as ContainerModelBaseClass --- //
class AbstractBaseModel : public QAbstractTableModel
{
public:
    AbstractBaseModel(
        ehm_dal::column_data::ColumnData *column_data = new ehm_dal::column_data::ColumnData(),
        QObject *parent = nullptr);
    virtual ~AbstractBaseModel() override;

    // Column data
    /*!
     * \brief Returns the `ehm_dal::column_data::ColumnData`.
     * \return a raw pointer to the `ehm_dal::column_data::ColumnData`.
     */
    ehm_dal::column_data::ColumnData *columnData();
    ehm_dal::column_data::ColumnData *constColumnData() const;

    // Get data - counts
    /*!
     * \brief Returns the number of columns in the table.
     * \param parent Not used
     * \return the column count.
     */
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    inline qint32 size() const { return rowCount(); }

    // Get data - flags
    /*!
     * \brief Returns the item flags for the given index.
     * \param index Index of the selected row and column
     * \return the `Qt::ItemFlags`.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Get data - header
    /*!
     * \brief Returns the data for the given role and section in the header with the specified orientation. 
     * For horizontal headers, the section number corresponds to the column number. Similarly, for vertical headers, 
     * the section number corresponds to the row number.
     * \param section Row or column, depending on orientation
     * \param orientation Horizontal or vertical orientation
     * \param role Item data role. Typically `Qt::DisplayRole`
     * \return the header data.
     */
    QVariant headerData(qint32 section,
                        Qt::Orientation orientation,
                        qint32 role = Qt::DisplayRole) const override;

    // Table model type
    enum class AbstractTableModelType : quint8 {
        AbstractClass,
        GameTable,
        GameChildTable,
        GameChildTreeTable
    };

    inline virtual QString modelName() const { return QStringLiteral("Abstract class"); }
    inline virtual constexpr AbstractTableModelType modelType() const
    {
        return AbstractTableModelType::AbstractClass;
    }

protected:
    // Modified columns
    bool emitModifiedColumns(const qint32 row,
                             const std::vector<qint32> &modified_columns,
                             const QList<qint32> &modified_roles = QList<qint32>());

private:
    // Column data
    std::unique_ptr<ehm_dal::column_data::ColumnData> column_data_;
    enum ENUM_FLAGS { LARGE_TABLE_THRESHOLD = 100 };

    // Reset
    inline virtual bool clearAllData() { return false; }
};

} // namespace ehm_dal::tables
