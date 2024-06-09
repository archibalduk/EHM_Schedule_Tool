#pragma once

// Application headers
namespace ehm_dal::database {
class DatabaseVersion;
}

// Qt headers
class QDataStream;
class QVariant;
#include <QtGlobal>
#include <memory>

namespace ehm_dal::ehm_extra_rules {

// --- Extra rule container --- //
class ExtraRuleData
{
public:
    ExtraRuleData();
    ~ExtraRuleData();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version);
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version);

    // Get data
    QVariant data(const qint32 role) const;
    qint32 rowCount() const;

private:
    struct Data;
    std::unique_ptr<Data> data_;
};
} // namespace ehm_dal::ehm_extra_rules

