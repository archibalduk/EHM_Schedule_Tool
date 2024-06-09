#include "schedule_generator_ui.h"

// Application headers
#include "src/ui/generator/club_count_dialog.h"
#include "src/ui/generator/schedule_matrix_editor_dialog.h"

// Qt headers
#include <memory>

using namespace generator_ui;

ScheduleGeneratorUi::ScheduleGeneratorUi()
    : schedule_(
        std::make_shared<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>())
{}

/* =================== */
/*      Generator      */
/* =================== */

// --- Show the various user prompts --- //
bool ScheduleGeneratorUi::show()
{
    if (showClubCountEditor() == QDialog::Rejected)
        return false;

    if (showScheduleMatrixEditor() == QDialog::Rejected)
        return false;

    return schedule_->generate(start_date_,
                               end_date_,
                               day_priorities_,
                               exclusion_range_start_date_,
                               exclusion_range_end_date_);
}

// --- Import a schedule matrix and show the matrix editor dialog --- //
bool ScheduleGeneratorUi::showImportMatrixDialog()
{
    ehm_dal::spreadsheet::Spreadsheet sheet;
    if (!sheet.showOpenDialog(QString(), false))
        return false;

    schedule_->matrix(sheet);

    if (showScheduleMatrixEditor() == QDialog::Rejected)
        return false;

    return schedule_->generate(start_date_,
                               end_date_,
                               day_priorities_,
                               exclusion_range_start_date_,
                               exclusion_range_end_date_);
}

// --- Show the division & club count editor --- //
qint32 ScheduleGeneratorUi::showClubCountEditor()
{
    ClubCountDialog dialog;
    const auto result{dialog.exec()};

    if (result == QDialog::Accepted) {
        const auto club_count_data{dialog.clubCountData()};
        const auto division_count{static_cast<qint32>(club_count_data.size())};

        for (auto i = 0; i < division_count; ++i)
            schedule_->addDivision(i, club_count_data[i]);
    }

    return result;
}

// --- Show the schedule matrix generator --- //
qint32 ScheduleGeneratorUi::showScheduleMatrixEditor()
{
    ScheduleMatrixEditorDialog dialog(schedule_->matrix());
    const auto result{dialog.exec()};

    day_priorities_ = dialog.dayPriorities();
    start_date_ = dialog.startDate();
    end_date_ = dialog.endDate();
    exclusion_range_start_date_ = dialog.exclusionRangeStartDate();
    exclusion_range_end_date_ = dialog.exclusionRangeEndDate();

    return result;
}
