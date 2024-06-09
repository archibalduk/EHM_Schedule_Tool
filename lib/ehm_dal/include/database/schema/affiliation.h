#pragma once

// Application headers
#include "include/schema/abstract_validated_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Affiliations --- //
class Affiliation : public ehm_dal::schema::AbstractValidatedTableItem
{
public:
    Affiliation();
    ~Affiliation();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QString text() const override;

    // Initialisation
    bool init() override;

    // Operator overloading
    bool operator<(const Affiliation &rhs) const;

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    bool deletable() const override;
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


