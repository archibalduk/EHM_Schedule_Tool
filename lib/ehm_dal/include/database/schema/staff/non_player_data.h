#pragma once

// Application headers
#include "include/schema/abstract_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Non-player attributes --- //
class NonPlayerData : public ehm_dal::schema::AbstractTableItem
{
public:
    NonPlayerData();
    ~NonPlayerData();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QString text() const override;

    // Initialisation
    inline bool init() override { return false; }

    // Operator overloading
    NonPlayerData &operator=(NonPlayerData &&rhs);

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


