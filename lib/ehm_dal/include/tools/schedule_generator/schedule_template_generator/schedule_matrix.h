#pragma once

// Application headers
#include "include/spreadsheet/spreadsheet.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_club.h"

// Qt headers
#include <QAbstractTableModel>

// --- Schedule matrix --- //
namespace ehm_dal::tools::schedule_template_generator {
/*!
 * \brief The ScheduleMatrix class provides the interface for viewing 
 * and editing the numbers of games to be played by each team
 */
class ScheduleMatrix : public QAbstractTableModel
{
public:
    ScheduleMatrix(const std::vector<std::shared_ptr<ScheduleClub>> &sorted_clubs_list);

    // Counts
    qint32 cellCount(const QModelIndex &parent = QModelIndex()) const;
    inline qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return cellCount(parent);
    }
    inline qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return cellCount(parent);
    }

    // File i/o
    bool exportMatrix(ehm_dal::spreadsheet::Spreadsheet &sheet);
    bool importMatrix(ehm_dal::spreadsheet::Spreadsheet &sheet);

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(qint32 section,
                        Qt::Orientation orientation,
                        qint32 role = Qt::DisplayRole) const override;
    bool isDataCell(const qint32 cell_position) const;
    bool isDataCell(const QModelIndex &index) const;
    inline bool isTotalCell(const qint32 cell_position) const { return !isDataCell(cell_position); }
    bool isTotalCell(const QModelIndex &index) const { return !isDataCell(index); }

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;

    // Totals cells
    qint32 columnTotal(const qint32 column) const;
    qint32 rowTotal(const qint32 row) const;
    qint32 totalCellPosition() const;

private:
    std::vector<std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleClub>> clubs_;
};
} // namespace ehm_dal::tools::schedule_template_generator
