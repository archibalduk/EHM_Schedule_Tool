#include "club_count_editor_model.h"

using namespace generator;

ClubCountEditorModel::ClubCountEditorModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

qint32 ClubCountEditorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMN_COUNT;
}

qint32 ClubCountEditorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<qint32>(club_count_data_.size());
}

QVariant ClubCountEditorModel::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case DIVISION_ID:
            return index.row();
        case CLUB_COUNT:
            return club_count_data_[index.row()];
        default:
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags ClubCountEditorModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && index.column() == CLUB_COUNT)
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;

    return Qt::NoItemFlags;
}

QVariant ClubCountEditorModel::headerData(qint32 section,
                                          Qt::Orientation orientation,
                                          qint32 role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section + 1;

    switch (section) {
    case DIVISION_ID:
        return QStringLiteral("Division id");
    case CLUB_COUNT:
        return QStringLiteral("Club count");
    default:
        return QVariant();
    }
}

bool ClubCountEditorModel::setData(const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    if (index.column() == CLUB_COUNT) {
        const auto count{value.toInt()};

        if (count > 0)
            club_count_data_[index.row()] = count;

        return true;
    }

    return false;
}

void ClubCountEditorModel::setDivisionCount(const qint32 count)
{
    if (count == rowCount() || count < 1)
        return;

    beginResetModel();
    club_count_data_.resize(count, 2);
    endResetModel();
}
