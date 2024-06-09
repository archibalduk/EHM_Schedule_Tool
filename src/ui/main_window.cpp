#include "main_window.h"

// Application headers
#include "src/ui/generator/schedule_generator_ui.h"
#include "src/ui/parser/schedule_template_parser_ui.h"
#include "src/ui/parser/text_schedule_parser_ui.h"

// Qt headers
#include <QApplication>
#include <QCoreApplication>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMenuBar>
#include <QTableView>

using namespace app;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("%L1 v%2").arg(QCoreApplication::applicationName(),
                                                 QCoreApplication::applicationVersion()));
    setMinimumSize(1066, 600);

    init();
}

MainWindow::~MainWindow() {}

/* ===================== */
/*      Export Data      */
/* ===================== */

// --- Export the schedule template --- //
void MainWindow::onExportSchedule()
{
    if (schedule_)
        schedule_->exportSchedule();
    else
        qInfo() << "No schedule to export";
}

/* =================== */
/*      Generator      */
/* =================== */

// --- Show the schedule template generator dialogs --- //
void MainWindow::onGenerateNewSchedule()
{
    auto generator{std::make_unique<generator_ui::ScheduleGeneratorUi>()};
    const auto result{generator->show()};

    if (result) {
        qInfo() << "Generator success";
        setSchedule(generator->schedule());
    }
    showNormal(); // In case the user has minimised the main window whilst using the generator dialogs
}

// --- Show the schedule template generator dialogs using an existing matrix spreadsheet file --- //
void MainWindow::onGenerateNewScheduleFromMatrix()
{
    auto generator{std::make_unique<generator_ui::ScheduleGeneratorUi>()};
    const auto result{generator->showImportMatrixDialog()};

    if (result) {
        qInfo() << "Generator success";
        setSchedule(generator->schedule());
    }
    showNormal(); // In case the user has minimised the main window whilst using the generator dialogs
}

/* ============== */
/*      Help      */
/* ============== */

void MainWindow::showHelpAboutApplication() {}

/* ===================== */
/*      Import Data      */
/* ===================== */

// --- Import a schedule template spreadsheet --- //
void MainWindow::onImportScheduleTemplate()
{
    auto parser{std::make_unique<parser_ui::ScheduleTemplateParserUi>()};

    if (parser->parse()) {
        qInfo() << "Import success";
        setSchedule(parser->schedule());
    }
}

// --- Import a text schedule --- //
void MainWindow::onImportTextSchedule()
{
    auto parser{std::make_unique<parser_ui::TextScheduleParserUi>()};

    if (parser->parse()) {
        qInfo() << "Import success";
        setSchedule(parser->schedule());
    }
}

/* ================== */
/*      Schedule      */
/* ================== */

// --- Set source schedule --- //
void MainWindow::setSchedule(
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule)
{
    schedule_ = std::move(schedule);
    schedule_matrix_->setSourceData(schedule_);
    schedule_stats_->setSourceData(schedule_);
    schedule_tools_.setSourceData(schedule_);
}

/* ======================== */
/*      User Interface      */
/* ======================== */

// --- Initialise the user interface --- //
void MainWindow::init()
{
    initMenu();

    // Schedule stats
    schedule_stats_ = new schedule::ScheduleStats(this);
    auto schedule_stats_table_view{new QTableView(this)};
    schedule_stats_table_view->setModel(schedule_stats_);
    schedule_stats_table_view->horizontalHeader()->hide();
    schedule_stats_table_view->verticalHeader()->hide();

    const auto schedule_stats_column_count{schedule_stats_->columnCount()};
    for (auto i = 0; i < schedule_stats_column_count; ++i)
        schedule_stats_table_view->setColumnWidth(i, schedule_stats_->columnWidth(i));

    // Schedule stats widget
    auto stats_group_widget{new QGroupBox(QStringLiteral("Schedule stats"), this)};
    stats_group_widget->setFixedWidth(schedule_stats_->tableWidth());
    auto stats_layout{new QVBoxLayout(stats_group_widget)};
    stats_layout->addWidget(schedule_stats_table_view);

    // Schedule matrix
    schedule_matrix_ = new schedule::ScheduleStatsMatrix(this);
    auto schedule_matrix_table_view{new QTableView(this)};
    schedule_matrix_table_view->setModel(schedule_matrix_);

    // Schedule matrix widget
    auto matrix_group_widget{new QGroupBox(QStringLiteral("Schedule stats matrix"), this)};
    auto matrix_layout{new QVBoxLayout(matrix_group_widget)};
    matrix_layout->addWidget(schedule_matrix_table_view);

    // Central widget
    auto central_widget{new QWidget(this)};
    setCentralWidget(central_widget);

    // Layout
    auto layout{new QHBoxLayout(central_widget)};
    layout->addWidget(stats_group_widget);
    layout->addWidget(matrix_group_widget);
}

// --- Initialise the user menu --- //
void MainWindow::initMenu()
{
    // Menu bar
    menu_bar_ = new QMenuBar(this);
    setMenuBar(menu_bar_);

    // Menu bar: File
    auto file_menu{menu_bar_->addMenu(QStringLiteral("&File"))};

    // File -> open
    import_schedule_template_action_ = std::make_unique<QAction>(QStringLiteral(
                                                                     "&Open schedule template..."),
                                                                 file_menu);
    QObject::connect(import_schedule_template_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::onImportScheduleTemplate);
    file_menu->addAction(import_schedule_template_action_.get());

    import_text_schedule_action_ = std::make_unique<QAction>(QStringLiteral(
                                                                 "Open &text schedule..."),
                                                             file_menu);
    QObject::connect(import_text_schedule_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::onImportTextSchedule);
    file_menu->addAction(import_text_schedule_action_.get());

    // File -> export
    file_menu->addSeparator();

    export_ehm_schedule_action_ = std::make_unique<QAction>(QStringLiteral(
                                                                "&Save schedule template as..."),
                                                            file_menu);
    QObject::connect(export_ehm_schedule_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::onExportSchedule);
    file_menu->addAction(export_ehm_schedule_action_.get());

    // Menu bar: Generate
    auto generate_menu{menu_bar_->addMenu(QStringLiteral("&Generate"))};

    // File -> new / generate
    generate_new_schedule_template_action_
        = std::make_unique<QAction>(QStringLiteral("&New schedule template..."), generate_menu);
    QObject::connect(generate_new_schedule_template_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::onGenerateNewSchedule);
    generate_menu->addAction(generate_new_schedule_template_action_.get());

    generate_new_schedule_template_from_matrix_action_
        = std::make_unique<QAction>(QStringLiteral(
                                        "&New schedule template from matrix spreadsheet..."),
                                    generate_menu);
    QObject::connect(generate_new_schedule_template_from_matrix_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::onGenerateNewScheduleFromMatrix);
    generate_menu->addAction(generate_new_schedule_template_from_matrix_action_.get());

    // Menu bar: Tools
    schedule_tools_.addToMenu(menu_bar_);

    // Menu bar: Generate
    auto help_menu{menu_bar_->addMenu(QStringLiteral("&Help"))};

    // Help -> About application
    help_about_application_action_ = std::make_unique<QAction>(QStringLiteral("&About..."),
                                                               help_menu);
    QObject::connect(help_about_application_action_.get(),
                     &QAction::triggered,
                     this,
                     &MainWindow::showHelpAboutApplication);
    help_menu->addAction(help_about_application_action_.get());

    // Help -> About Qt
    help_about_qt_action_ = std::make_unique<QAction>(QStringLiteral("About &Qt..."), help_menu);
    QObject::connect(help_about_qt_action_.get(), &QAction::triggered, this, &QApplication::aboutQt);
    help_menu->addAction(help_about_qt_action_.get());
}
