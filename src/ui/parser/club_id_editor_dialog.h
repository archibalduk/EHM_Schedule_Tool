#pragma once

// Application headers
#include "src/parser/club_id_editor_model.h"

// Qt headers
#include <QDialog>
class QTableView;

namespace parser_ui {
class ClubIdEditorDialog : public QDialog
{
public:
    ClubIdEditorDialog();

    // Get data
    inline parser::ClubIdEditorModel *model() { return model_; }

private:
    // Data
    parser::ClubIdEditorModel *model_;

    // Ui
    QTableView *table_;
    void init();
};
} // namespace parser_ui
