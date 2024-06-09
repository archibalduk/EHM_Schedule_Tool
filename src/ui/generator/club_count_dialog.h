#pragma once

// Application headers
#include "src/generator/club_count_editor_model.h"

// Qt headers
#include <QDialog>
class QSpinBox;
class QTableView;

namespace generator_ui {
class ClubCountDialog : public QDialog
{
public:
    ClubCountDialog();

    // Get data
    inline std::vector<qint32> clubCountData() const { return model_->clubCountData(); }

private:
    // Data
    generator::ClubCountEditorModel *model_;

    // Ui
    QSpinBox *division_count_;
    QTableView *table_;
    void init();

private slots:
    void setDivisionCount(const qint32 count);
};
} // namespace generator_ui
