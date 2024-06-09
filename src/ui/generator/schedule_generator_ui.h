#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

// Qt headers
#include <QtGlobal>

namespace generator_ui {
class ScheduleGeneratorUi
{
public:
    ScheduleGeneratorUi();

    // Generator
    bool show();
    bool showImportMatrixDialog();

    // Schedule data
    inline std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
    schedule()
    {
        return schedule_;
    }

private:
    // Schedule data
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;

    // Settings
    std::vector<qint32> day_priorities_;
    QDate start_date_;
    QDate end_date_;
    QDate exclusion_range_start_date_;
    QDate exclusion_range_end_date_;

    // Ui
    qint32 showClubCountEditor();
    qint32 showScheduleMatrixEditor();
};
} // namespace generator_ui
