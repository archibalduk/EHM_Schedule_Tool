#pragma once

// Application headers
#include "include/tables/private/abstract_base_model.h"

// Qt headers
#include <QHash>

namespace ehm_dal::flags {
class FlagTable : public ehm_dal::tables::AbstractBaseModel
{
public:
    FlagTable();

    // Add data
    void add(const qint32 value, const QString &text);
    void addNoneValue(const qint32 value);

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    QString text(const qint32 id);

    // Get data - counts
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    QHash<QString, qint32> data_;
};
} // namespace ehm_dal::flags


