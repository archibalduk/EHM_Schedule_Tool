#pragma once

// Application headers
#include "include/tools/schedule_generator/schedule_template_generator/schedule_matrix.h"

// Qt headers
#include <QDialog>
class QCalendarWidget;
class QCheckBox;
class QSpinBox;
class QTableView;

namespace generator_ui {
class ScheduleMatrixEditorDialog : public QDialog
{
public:
    ScheduleMatrixEditorDialog(
        std::unique_ptr<ehm_dal::tools::schedule_template_generator::ScheduleMatrix> matrix);

    // Settings
    std::vector<qint32> dayPriorities() const;
    QDate startDate() const;
    QDate endDate() const;
    QDate exclusionRangeStartDate() const;
    QDate exclusionRangeEndDate() const;

private:
    // Settings - members
    std::vector<QSpinBox *> day_priority_spin_boxes_;
    QCalendarWidget *start_date_;
    QCalendarWidget *end_date_;
    QCheckBox *enable_exclusion_range_;
    QCalendarWidget *exclusion_range_start_date_;
    QCalendarWidget *exclusion_range_end_date_;

    // Ui
    void init();
    QTableView *table_;
    std::unique_ptr<ehm_dal::tools::schedule_template_generator::ScheduleMatrix> matrix_;

    // Ui - settings
    QWidget *dateWidget(const qint32 default_start_year);
    QWidget *dayPrioritiesWidget();
    QWidget *exclusionDateWidget(const qint32 default_start_year);
    QWidget *initSettingsWidget();

private slots:
    void exportMatrix();
};
} // namespace generator_ui
