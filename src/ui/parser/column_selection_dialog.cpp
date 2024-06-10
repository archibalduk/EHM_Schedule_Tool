#include "column_selection_dialog.h"

// Qt headers
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpinBox>

using namespace parser_ui;

ColumnSelectionDialog::ColumnSelectionDialog()
    : QDialog()
{
    setWindowTitle(QStringLiteral("Import text schedule"));
    init();
}

/* ================== */
/*      Get Data      */
/* ================== */

qint32 ColumnSelectionDialog::dateColumnId() const
{
    return date_column_id_spin_box_->value() - COLUMN_ID_MODIFIER;
}

qint32 ColumnSelectionDialog::headerRowCount() const
{
    return header_row_count_spin_box_->value();
}

qint32 ColumnSelectionDialog::homeClubColumnId() const
{
    return home_club_column_id_spin_box_->value() - COLUMN_ID_MODIFIER;
}

qint32 ColumnSelectionDialog::roadClubColumnId() const
{
    return road_club_column_id_spin_box_->value() - COLUMN_ID_MODIFIER;
}

/* ================== */
/*      Set Data      */
/* ================== */

void ColumnSelectionDialog::setDateColumnId(const qint32 date_column_id)
{
    date_column_id_spin_box_->setValue(date_column_id + COLUMN_ID_MODIFIER);
}

void ColumnSelectionDialog::setHeaderRowCount(const qint32 header_row_count)
{
    header_row_count_spin_box_->setValue(header_row_count + COLUMN_ID_MODIFIER);
}

void ColumnSelectionDialog::setHomeClubColumnId(const qint32 home_club_column_id)
{
    home_club_column_id_spin_box_->setValue(home_club_column_id + COLUMN_ID_MODIFIER);
}

void ColumnSelectionDialog::setRoadClubColumnId(const qint32 road_club_column_id)
{
    road_club_column_id_spin_box_->setValue(road_club_column_id + COLUMN_ID_MODIFIER);
}

/* ======================== */
/*      User Interface      */
/* ======================== */

void ColumnSelectionDialog::init()
{
    auto layout{new QFormLayout(this)};

    // Spin boxes
    date_column_id_spin_box_ = new QSpinBox(this);
    header_row_count_spin_box_ = new QSpinBox(this);
    home_club_column_id_spin_box_ = new QSpinBox(this);
    road_club_column_id_spin_box_ = new QSpinBox(this);

    initSpinBox(QStringLiteral("Header row count:"), header_row_count_spin_box_, layout);
    initSpinBox(QStringLiteral("Date column:"), date_column_id_spin_box_, layout);
    initSpinBox(QStringLiteral("Road club column:"), road_club_column_id_spin_box_, layout);
    initSpinBox(QStringLiteral("Home club column:"), home_club_column_id_spin_box_, layout);

    // Button box
    auto button_box{
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this)};
    layout->addWidget(button_box);

    QObject::connect(button_box, &QDialogButtonBox::accepted, this, &ColumnSelectionDialog::accept);
    QObject::connect(button_box, &QDialogButtonBox::rejected, this, &ColumnSelectionDialog::reject);
}

void ColumnSelectionDialog::initSpinBox(const QString &title,
                                        QSpinBox *spin_box,
                                        QFormLayout *layout)
{
    spin_box->setRange(MINIMUM_COLUMN_ID, MAXIMUM_COLUMN_ID);
    layout->addRow(title, spin_box);
}
