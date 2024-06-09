#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"
#include "src/schedule/schedule_stats_matrix.h"
#include "src/schedule/schedule_stats.h"
#include "src/schedule/schedule_tools.h"

// Qt headers
class QMenuBar;
#include <QAction>
#include <QMainWindow>

namespace app {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Menu
    QMenuBar *menu_bar_;
    std::unique_ptr<QAction> import_schedule_template_action_;
    std::unique_ptr<QAction> import_text_schedule_action_;
    std::unique_ptr<QAction> export_ehm_schedule_action_;
    std::unique_ptr<QAction> generate_new_schedule_template_action_;
    std::unique_ptr<QAction> generate_new_schedule_template_from_matrix_action_;
    std::unique_ptr<QAction> help_about_application_action_;
    std::unique_ptr<QAction> help_about_qt_action_;

    // Schedule
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;
    schedule::ScheduleStatsMatrix *schedule_matrix_;
    schedule::ScheduleStats *schedule_stats_;
    schedule::ScheduleTools schedule_tools_;

    void setSchedule(
        std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
            schedule);

    // Ui
    void init();
    void initMenu();

private slots:
    // Export data
    void onExportSchedule();

    // Generator
    void onGenerateNewSchedule();
    void onGenerateNewScheduleFromMatrix();

    // Help
    qint32 showHelpAboutApplication();

    // Import data
    void onImportScheduleTemplate();
    void onImportTextSchedule();
};
} // namespace app
