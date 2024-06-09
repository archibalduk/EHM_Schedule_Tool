#pragma once

// Application headers
#include "include/data_types/data_type.h"
#include "include/data_types/date/year.h"
namespace ehm_dal::database {
class DatabaseVersion;
}

// Qt headers
class QDataStream;

namespace ehm_dal::schema {

// --- Abstract club record item --- //
class AbstractClubRecord
{
public:
    AbstractClubRecord();
    virtual ~AbstractClubRecord() = default;

    // File i/o
    virtual bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) = 0;
    virtual bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) = 0;

    // Get data
    QVariant data(const qint32 column, const qint32 role) const;

    // Initialisation
    virtual bool init() { return false; }

    // Set data
    bool setData(const qint32 column,
                 const QVariant &value,
                 const qint32 role,
                 std::vector<qint32> &modified_columns);

protected:
    ehm_dal::data_types::DataType<qint16> record_year_;
    ehm_dal::data_types::Year<qint16> record_value_;

private:
    // Get data
    virtual QVariant internalData(const qint32 column, const qint32 role) const;

    // Set data
    virtual bool setInternalData(const qint32 column,
                                 const QVariant &value,
                                 const qint32 role,
                                 std::vector<qint32> &modified_columns);
};
} // namespace ehm_dal::schema
