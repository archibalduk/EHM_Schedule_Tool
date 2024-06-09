#include "text_schedule_parser_ui.h"

// Application headers
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "src/ui/parser/club_id_editor_dialog.h"
#include "src/ui/parser/column_selection_dialog.h"

using namespace parser_ui;

TextScheduleParserUi::TextScheduleParserUi() {}

/* ====================== */
/*      Club Editing      */
/* ====================== */

// --- Show the club editor --- //
qint32 TextScheduleParserUi::showClubEditor()
{
    ClubIdEditorDialog ced;
    ced.model()->setSourceData(parser_);
    return ced.exec();
}

/* ================== */
/*      File I/O      */
/* ================== */

// --- Open a text schedule for parsing --- //
bool TextScheduleParserUi::open()
{
    ehm_dal::spreadsheet::Spreadsheet sheet;
    if (!sheet.showOpenDialog(QString(), false))
        return false;

    auto column_selector{std::make_unique<ColumnSelectionDialog>()};

    // Init default values for the column selector
    column_selector->setDateColumnId(parser_.dateColumnId());
    column_selector->setHeaderRowCount(parser_.headerRowCount());
    column_selector->setHomeClubColumnId(parser_.homeClubColumnId());
    column_selector->setRoadClubColumnId(parser_.roadClubColumnId());

    if (column_selector->exec() == QDialog::Rejected)
        return false;

    // Set the parser column values from the column selector
    parser_.setDateColumnId(column_selector->dateColumnId());
    parser_.setHeaderRowCount(column_selector->headerRowCount());
    parser_.setHomeClubColumnId(column_selector->homeClubColumnId());
    parser_.setRoadClubColumnId(column_selector->roadClubColumnId());

    parser_.parse(sheet);

    return true;
}

/* ================= */
/*      Parsing      */
/* ================= */

// --- Show the various ui screens for parsing a text schedule --- //
bool TextScheduleParserUi::parse()
{
    if (!open())
        return false;

    return showClubEditor() == QDialog::Accepted;
}

/* ================== */
/*      Schedule      */
/* ================== */

// --- Get a copy of the schedule --- //
std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
TextScheduleParserUi::schedule()
{
    return parser_.schedule();
}
