#pragma once

// Qt headers
#include <QAbstractTableModel>

namespace generator {
class ClubCountEditorModel : public QAbstractTableModel
{
public:
    ClubCountEditorModel(QObject *parent);

    // Counts
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Get data
    inline std::vector<qint32> clubCountData() const { return club_count_data_; }
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(qint32 section,
                        Qt::Orientation orientation,
                        qint32 role = Qt::DisplayRole) const override;

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;
    void setDivisionCount(const qint32 count);

private:
    // Data
    std::vector<qint32> club_count_data_{2};

    enum ENUM_COLUMNS { DIVISION_ID, CLUB_COUNT, COLUMN_COUNT };
};
} // namespace generator
