#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

// Qt headers
#include <QAbstractTableModel>

namespace schedule {
class AbstractScheduleStats : public QAbstractTableModel
{
public:
    // Set data
    virtual void setSourceData(
        std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
            schedule);

protected:
    AbstractScheduleStats(QObject *parent);

    // Data
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;
};
} // namespace schedule
