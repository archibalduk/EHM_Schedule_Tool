#include "club_id_editor_model.h"

using namespace parser;

ClubIdEditorModel::ClubIdEditorModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

qint32 ClubIdEditorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMN_COUNT;
}

qint32 ClubIdEditorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<qint32>(club_name_data_.size());
}

QVariant ClubIdEditorModel::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case CLUB_NAME:
            return club_name_data_[index.row()];
        case CLUB_ENCODED_ID:
            if (schedule_)
                return schedule_->club(index.row())->clubEncodedId();
        }
    }

    return QVariant();
}

Qt::ItemFlags ClubIdEditorModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && index.column() == CLUB_ENCODED_ID)
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;

    return Qt::NoItemFlags;
}

QVariant ClubIdEditorModel::headerData(qint32 section,
                                       Qt::Orientation orientation,
                                       qint32 role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section + 1;

    switch (section) {
    case CLUB_NAME:
        return QStringLiteral("Club name");
    case CLUB_ENCODED_ID:
        return QStringLiteral("Club id");
    default:
        return QVariant();
    }
}

bool ClubIdEditorModel::setData(const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    if (index.column() == CLUB_ENCODED_ID && schedule_) {
        schedule_->club(index.row())->setClubEncodedId(value.toInt());
        return true;
    }

    return false;
}

void ClubIdEditorModel::setSourceData(TextScheduleParser &parser)
{
    beginResetModel();

    // Club name data
    const auto club_names{parser.clubNames()};
    const auto size{club_names.size()};
    for (auto i = 0; i < size; ++i)
        club_name_data_.push_back(club_names.key(i));

    // Club id/schedule data
    schedule_ = parser.schedule();

    endResetModel();
}
