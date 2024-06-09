#include "abstract_schedule_stats.h"

using namespace schedule;

AbstractScheduleStats::AbstractScheduleStats(QObject *parent)
    : QAbstractTableModel(parent)
{}

void AbstractScheduleStats::setSourceData(
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule)
{
    beginResetModel();
    schedule_ = std::move(schedule);
    endResetModel();
}
