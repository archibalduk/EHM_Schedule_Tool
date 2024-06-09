#pragma once


// Application headers
#include "include/schema/abstract_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {

// --- Staff award history --- //
class StaffAwardHistory : public ehm_dal::schema::AbstractTableItem
{
public:
    StaffAwardHistory();
    ~StaffAwardHistory();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QString text() const override;

    // Initialisation
    bool init() override;

    // Parent data
    qint32 parentItemId() const override;

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

