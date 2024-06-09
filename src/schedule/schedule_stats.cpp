#include "schedule_stats.h"

using namespace schedule;

ScheduleStats::ScheduleStats(QObject *parent)
    : AbstractScheduleStats(parent)
{}

qint32 ScheduleStats::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMN_COUNT;
}

qint32 ScheduleStats::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ROW_COUNT;
}

qint32 ScheduleStats::columnWidth(const qint32 column) const
{
    switch (column) {
    case DESCRIPTION_COLUMN:
    case VALUE_COLUMN:
        return 120;
    default:
        return 0;
    }
}

qint32 ScheduleStats::tableWidth() const
{
    auto size{0};

    const auto column_count{columnCount()};
    for (auto i = 0; i < column_count; ++i)
        size += columnWidth(i);

    return size * static_cast<double>(1.2); // Add 20% for padding/margins
}

QVariant ScheduleStats::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case DESCRIPTION_COLUMN:
            return description(index.row());
        case VALUE_COLUMN:
            return value(index.row(), role);
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QString ScheduleStats::description(const qint32 row) const
{
    switch (row) {
    case START_DATE:
        return QStringLiteral("Start date");
    case START_DAY:
        return QStringLiteral("Start day");
    case END_DATE:
        return QStringLiteral("End date");
    case END_DAY:
        return QStringLiteral("End day");
    case DATE_COUNT:
        return QStringLiteral("Date count");
    case GAME_COUNT:
        return QStringLiteral("Game count");
    case GAME_TO_DATE_RATIO:
        return QStringLiteral("Game : date ratio");
    case CLUB_COUNT:
        return QStringLiteral("Club count");
    default:
        return QString();
    }
}

QVariant ScheduleStats::value(const qint32 row, qint32 role) const
{
    Q_UNUSED(role)

    if (!schedule_)
        return QVariant();

    switch (row) {
    case START_DATE:
        return schedule_->games()->startDate();
    case START_DAY:
        return schedule_->games()->startDate().toString(QStringLiteral("dddd"));
    case END_DATE:
        return schedule_->games()->endDate();
    case END_DAY:
        return schedule_->games()->endDate().toString(QStringLiteral("dddd"));
    case DATE_COUNT:
        return schedule_->games()->dateCount();
    case GAME_COUNT:
        return schedule_->games()->gameCount();
    case GAME_TO_DATE_RATIO:
        return static_cast<double>(schedule_->games()->gameCount())
               / schedule_->games()->dateCount();
    case CLUB_COUNT:
        return schedule_->clubCount();
    default:
        return QVariant();
    }
}

Qt::ItemFlags ScheduleStats::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled;
}

QVariant ScheduleStats::headerData(qint32 section, Qt::Orientation orientation, qint32 role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section + 1;

    switch (section) {
    case DESCRIPTION_COLUMN:
        return QStringLiteral("Description");
    case VALUE_COLUMN:
        return QStringLiteral("Value");
    default:
        return QVariant();
    }
}
