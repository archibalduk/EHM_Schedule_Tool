#include "schedule_template_parser_ui.h"

// Qt headers
#include <QMessageBox>

using namespace parser_ui;

ScheduleTemplateParserUi::ScheduleTemplateParserUi() {}

/* ================== */
/*      File I/O      */
/* ================== */

// --- Open a schedule template for parsing --- //
bool parser_ui::ScheduleTemplateParserUi::open()
{
    ehm_dal::spreadsheet::Spreadsheet sheet;
    if (!sheet.showOpenDialog(QString(), false))
        return false;

    const auto result{parser_.parse(sheet)};

    if (!result)
        QMessageBox::critical(nullptr,
                              QStringLiteral("Error"),
                              QStringLiteral("Unable to parse schedule template spreadsheet"));

    return result;
}

/* ================== */
/*      Schedule      */
/* ================== */

// --- Get a copy of the schedule --- //
std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
ScheduleTemplateParserUi::schedule()
{
    return parser_.schedule();
}
