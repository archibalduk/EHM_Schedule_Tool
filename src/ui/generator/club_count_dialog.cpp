#include "club_count_dialog.h"

// Qt headers
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSpinBox>
#include <QTableView>

using namespace generator_ui;

ClubCountDialog::ClubCountDialog()
{
    setWindowTitle(QStringLiteral("Assign division and club counts"));
    init();
}

void ClubCountDialog::init()
{
    auto layout{new QGridLayout(this)};

    // Table
    table_ = new QTableView(this);
    table_->verticalHeader()->hide();
    layout->addWidget(table_, 1, 0, 1, 2);

    // Model
    model_ = new generator::ClubCountEditorModel(table_);
    table_->setModel(model_);

    // Division count
    division_count_ = new QSpinBox(this);
    division_count_->setRange(1, 1000);
    division_count_->setValue(model_->rowCount());
    QObject::connect(division_count_,
                     &QSpinBox::valueChanged,
                     this,
                     &ClubCountDialog::setDivisionCount);

    auto division_count_label{new QLabel(QStringLiteral("Division count:"), this)};
    layout->addWidget(division_count_label, 0, 0);
    layout->addWidget(division_count_, 0, 1);

    // Button box
    auto button_box{
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this)};
    layout->addWidget(button_box);

    QObject::connect(button_box, &QDialogButtonBox::accepted, this, &ClubCountDialog::accept);
    QObject::connect(button_box, &QDialogButtonBox::rejected, this, &ClubCountDialog::reject);
}

void ClubCountDialog::setDivisionCount(const qint32 count)
{
    model_->setDivisionCount(count);
}
