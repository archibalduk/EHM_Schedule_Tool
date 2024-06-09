#include "club_id_editor_dialog.h"

// Qt headers
#include <QDialogButtonBox>
#include <QTableView>
#include <QVBoxLayout>

using namespace parser_ui;

ClubIdEditorDialog::ClubIdEditorDialog()
    : QDialog()
{
    setWindowTitle(QStringLiteral("Assign club id numbers"));
    init();
}

void ClubIdEditorDialog::init()
{
    auto layout{new QVBoxLayout(this)};

    // Table
    table_ = new QTableView(this);
    layout->addWidget(table_);

    // Model
    model_ = new parser::ClubIdEditorModel(table_);
    table_->setModel(model_);

    // Button box
    auto button_box{new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this)};
    layout->addWidget(button_box);

    QObject::connect(button_box, &QDialogButtonBox::accepted, this, &ClubIdEditorDialog::accept);
}
