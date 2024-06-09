#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator/schedule_club.h"
#include "src/schedule/private/abstract_schedule_stats.h"

namespace schedule {
class ScheduleStatsMatrix : public AbstractScheduleStats
{
public:
    ScheduleStatsMatrix(QObject *parent);
    //~ScheduleStatsMatrix() = default;

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
    void setSourceData(
        std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
            schedule) override;

    // Totals cells
    qint32 totalCellPosition() const;

private:
    std::vector<std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleClub>> clubs_;
};
} // namespace schedule
