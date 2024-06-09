#pragma once

// Application headers
#include "src/schedule/private/abstract_schedule_stats.h"

namespace schedule {
class ScheduleStats : public AbstractScheduleStats
{
public:
    ScheduleStats(QObject *parent);
    //~ScheduleStats() = default;

    // Counts
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Dimensions
    qint32 columnWidth(const qint32 column) const;
    qint32 tableWidth() const;

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(qint32 section,
                        Qt::Orientation orientation,
                        qint32 role = Qt::DisplayRole) const override;

private:
    enum ENUM_COLUMNS { DESCRIPTION_COLUMN, VALUE_COLUMN, COLUMN_COUNT };
    enum ENUM_ROWS {
        START_DATE,
        START_DAY,
        END_DATE,
        END_DAY,
        DATE_COUNT,
        GAME_COUNT,
        GAME_TO_DATE_RATIO,
        CLUB_COUNT,
        ROW_COUNT
    };

    // Get data
    QString description(const qint32 row) const;
    QVariant value(const qint32 row, qint32 role = Qt::DisplayRole) const;
};
} // namespace schedule
