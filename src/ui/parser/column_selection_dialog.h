#pragma once

// Qt headers
#include <QDialog>
class QFormLayout;
class QSpinBox;

namespace parser_ui {
class ColumnSelectionDialog : public QDialog
{
public:
    ColumnSelectionDialog();

    // Get data
    qint32 dateColumnId() const;
    qint32 headerRowCount() const;
    qint32 homeClubColumnId() const;
    qint32 roadClubColumnId() const;

    // Sset data
    void setDateColumnId(const qint32 date_column_id);
    void setHeaderRowCount(const qint32 header_row_count);
    void setHomeClubColumnId(const qint32 home_club_column_id);
    void setRoadClubColumnId(const qint32 road_club_column_id);

private:
    QSpinBox *date_column_id_spin_box_;
    QSpinBox *header_row_count_spin_box_;
    QSpinBox *home_club_column_id_spin_box_;
    QSpinBox *road_club_column_id_spin_box_;

    // Ui
    void init();
    void initSpinBox(const QString &title, QSpinBox *spin_box, QFormLayout *layout);

    enum ENUM_FLAGS {
        MINIMUM_COLUMN_ID = 1,
        MAXIMUM_COLUMN_ID = 100,
        COLUMN_ID_MODIFIER = 1 // Spinbox values start at 1 vs internal indexes start at 0
    };
};
} // namespace parser_ui
