#include "schedule_stats_matrix.h"

using namespace schedule;

ScheduleStatsMatrix::ScheduleStatsMatrix(QObject *parent)
    : AbstractScheduleStats(parent)
{}

qint32 ScheduleStatsMatrix::cellCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (schedule_)
        return totalCellPosition() + 1;

    return 0;
}

QVariant ScheduleStatsMatrix::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    if (index.row() == index.column()) {
        if (role == Qt::BackgroundRole)
            return QColor(30, 30, 30);

        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (isDataCell(index))
            return schedule_->games()->gameCount(clubs_[index.column()], clubs_[index.row()]);

        if (isTotalCell(index.row()))
            return schedule_->games()->gameCountRoad(clubs_[index.column()]);

        return schedule_->games()->gameCountHome(clubs_[index.row()]);
    }

    return QVariant();
}

Qt::ItemFlags ScheduleStatsMatrix::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)

    if (index.row() != index.column())
        return Qt::ItemIsEnabled;

    return Qt::NoItemFlags;
}

QVariant ScheduleStatsMatrix::headerData(qint32 section,
                                         Qt::Orientation orientation,
                                         qint32 role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (isDataCell(section)) {
        const auto club_encoded_id{clubs_[section]->clubEncodedId()};

        if (orientation == Qt::Vertical)
            return QStringLiteral("@ %1").arg(club_encoded_id);

        return club_encoded_id;
    }

    return QStringLiteral("Total");
}

bool ScheduleStatsMatrix::isDataCell(const qint32 cell_position) const
{
    if (schedule_ && cell_position < totalCellPosition())
        return true;

    return false;
}

bool ScheduleStatsMatrix::isDataCell(const QModelIndex &index) const
{
    return isDataCell(index.row()) && isDataCell(index.column());
}

void ScheduleStatsMatrix::setSourceData(
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule)
{
    beginResetModel();
    schedule_ = std::move(schedule);
    clubs_ = schedule_->sortedClubList();
    endResetModel();
}

qint32 ScheduleStatsMatrix::totalCellPosition() const
{
    if (schedule_)
        return static_cast<qint32>(clubs_.size());

    return 0;
}
