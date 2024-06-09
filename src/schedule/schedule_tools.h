#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

// Qt headers
#include <QAction>
#include <QObject>
class QMenuBar;

namespace schedule {
class ScheduleTools : public QObject
{
public:
    ScheduleTools();

    // Set data
    void setSourceData(
        std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
            schedule);

    // Ui
    void addToMenu(QMenuBar *menu_bar);

private:
    // Actions
    std::unique_ptr<QAction> add_days_action_;
    std::unique_ptr<QAction> set_start_year_action_;

    // Data
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;

    // Ui
    QWidget *parent_{nullptr};

    enum FLAGS { MAX_DAYS_IN_A_YEAR = 366, MINIMUM_YEAR = 1900, MAXIMUM_YEAR = 2899 };

private slots:
    void onAddDays();
    void onSetStartYear();
};
} // namespace schedule
