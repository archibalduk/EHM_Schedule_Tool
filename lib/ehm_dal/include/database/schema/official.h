#pragma once


// Application headers
#include "include/database/schema/private/person.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Official --- //
class Official : public ehm_dal::schema::Person
{
public:
    Official();
    ~Official();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Initialisation
    bool initInternalData() override;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


