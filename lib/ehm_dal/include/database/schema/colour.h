#pragma once


// Application headers
#include "include/schema/abstract_uid_table_item.h"

// Qt headers
class QColor;
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Colours --- //
class Colour : public ehm_dal::schema::AbstractUidTableItem
{
public:
    Colour();
    ~Colour();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QColor colour() const;
    QString text() const override;

    // Initialisation
    inline bool init() override { return false; }

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


