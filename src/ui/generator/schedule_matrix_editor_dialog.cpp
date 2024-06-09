#include "schedule_matrix_editor_dialog.h"

// Application headers
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"

// Qt headers
#include <QCalendarWidget>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableView>
#include <QVBoxLayout>

using namespace generator_ui;

ScheduleMatrixEditorDialog::ScheduleMatrixEditorDialog(
    std::unique_ptr<ehm_dal::tools::schedule_template_generator::ScheduleMatrix> matrix)
    : QDialog(nullptr, Qt::Window)
    , matrix_(std::move(matrix))
{
    setWindowTitle(QStringLiteral("Schedule generator"));
    init();
    showMaximized();
}

/* ================== */
/*      Get Data      */
/* ================== */

std::vector<qint32> ScheduleMatrixEditorDialog::dayPriorities() const
{
    std::vector<qint32> priorities;

    for (const auto &itr : day_priority_spin_boxes_)
        priorities.push_back(itr->value());

    return priorities;
}

QDate ScheduleMatrixEditorDialog::startDate() const
{
    return start_date_->selectedDate();
}

QDate ScheduleMatrixEditorDialog::endDate() const
{
    return end_date_->selectedDate();
}

QDate ScheduleMatrixEditorDialog::exclusionRangeStartDate() const
{
    if (enable_exclusion_range_->isChecked())
        return exclusion_range_start_date_->selectedDate();

    return QDate();
}

QDate ScheduleMatrixEditorDialog::exclusionRangeEndDate() const
{
    if (enable_exclusion_range_->isChecked())
        return exclusion_range_end_date_->selectedDate();

    return QDate();
}

/* ======================== */
/*      User Interface      */
/* ======================== */

void generator_ui::ScheduleMatrixEditorDialog::init()
{
    auto layout{new QGridLayout(this)};

    // Settings
    layout->addWidget(initSettingsWidget(), 0, 0);

    // Table
    table_ = new QTableView(this);
    table_->setModel(matrix_.get());
    layout->addWidget(table_, 0, 1);

    // Button box
    auto button_box{
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this)};
    layout->addWidget(button_box, 1, 0, 1, 2, Qt::AlignRight);

    QObject::connect(button_box,
                     &QDialogButtonBox::accepted,
                     this,
                     &ScheduleMatrixEditorDialog::accept);
    QObject::connect(button_box,
                     &QDialogButtonBox::rejected,
                     this,
                     &ScheduleMatrixEditorDialog::reject);

    // Export matrix button
    auto export_matrix_button{new QPushButton(QStringLiteral("Export matrix"), this)};
    button_box->addButton(export_matrix_button, QDialogButtonBox::ApplyRole);
    QObject::connect(export_matrix_button,
                     &QPushButton::clicked,
                     this,
                     &ScheduleMatrixEditorDialog::exportMatrix);

    // Column stretches
    layout->setColumnStretch(0, 1); // 10%
    layout->setColumnStretch(1, 9); // 90%
}

/* ======================= */
/*      Ui - Settings      */
/* ======================= */

QWidget *ScheduleMatrixEditorDialog::dateWidget(const qint32 default_start_year)
{
    auto w{new QGroupBox(QStringLiteral("Regular season schedule date range"), this)};
    auto layout{new QFormLayout(w)};

    start_date_ = new QCalendarWidget(this);
    start_date_->setSelectedDate({default_start_year, 10, 1});
    layout->addRow(QStringLiteral("Start date:"), start_date_);

    end_date_ = new QCalendarWidget(this);
    end_date_->setSelectedDate({default_start_year + 1, 4, 1});
    layout->addRow(QStringLiteral("End date:"), end_date_);

    return w;
}

QWidget *ScheduleMatrixEditorDialog::dayPrioritiesWidget()
{
    auto w{
        new QGroupBox(QStringLiteral("Day priorities (1 = highest priority / 7 = lowest priority)"),
                      this)};
    auto layout{new QFormLayout(w)};

    constexpr auto day_count{7};
    const std::vector<qint32> priority_values{7, 3, 6, 2, 5, 1, 4};
    const std::vector<QString> week_names{QStringLiteral("Monday:"),
                                          QStringLiteral("Tuesday:"),
                                          QStringLiteral("Wednesday:"),
                                          QStringLiteral("Thursday:"),
                                          QStringLiteral("Friday:"),
                                          QStringLiteral("Saturday:"),
                                          QStringLiteral("Sunday:")};

    for (auto i = 0; i < day_count; ++i) {
        day_priority_spin_boxes_.emplace_back(std::move(new QSpinBox(w)));
        day_priority_spin_boxes_[i]->setRange(1, 7);
        day_priority_spin_boxes_[i]->setValue(priority_values[i]);
        layout->addRow(week_names[i], day_priority_spin_boxes_[i]);
    }

    return w;
}

QWidget *ScheduleMatrixEditorDialog::exclusionDateWidget(const qint32 default_start_year)
{
    auto w{new QGroupBox(QStringLiteral("Excluded date range"), this)};
    auto layout{new QFormLayout(w)};

    enable_exclusion_range_ = new QCheckBox(this);
    layout->addRow(QStringLiteral("Enable:"), enable_exclusion_range_);
    enable_exclusion_range_->setChecked(false);

    exclusion_range_start_date_ = new QCalendarWidget(this);
    exclusion_range_start_date_->setSelectedDate({default_start_year + 1, 2, 9});
    layout->addRow(QStringLiteral("From date:"), exclusion_range_start_date_);

    exclusion_range_end_date_ = new QCalendarWidget(this);
    exclusion_range_end_date_->setSelectedDate({default_start_year + 1, 2, 20});
    layout->addRow(QStringLiteral("Until date:"), exclusion_range_end_date_);

    QObject::connect(enable_exclusion_range_,
                     &QCheckBox::checkStateChanged,
                     this,
                     [&](const Qt::CheckState state) {
                         exclusion_range_start_date_->setEnabled(state == Qt::Checked);
                         exclusion_range_end_date_->setEnabled(state == Qt::Checked);
                     });
    emit enable_exclusion_range_->checkStateChanged(enable_exclusion_range_->checkState());

    return w;
}

QWidget *ScheduleMatrixEditorDialog::initSettingsWidget()
{
    auto w{new QWidget(this)};
    auto layout{new QVBoxLayout(w)};

    // Date settings
    const auto default_start_year{(QDate::currentDate().month() < 5)
                                      ? QDate::currentDate().year() - 1
                                      : QDate::currentDate().year()};

    layout->addWidget(dayPrioritiesWidget());
    layout->addWidget(dateWidget(default_start_year));
    layout->addWidget(exclusionDateWidget(default_start_year));

    return w;
}

void ScheduleMatrixEditorDialog::exportMatrix()
{
    ehm_dal::spreadsheet::Spreadsheet sheet;

    if (!sheet.showSaveDialog(QStringLiteral("schedule_matrix.xlsx")))
        return;

    matrix_->exportMatrix(sheet);
}
