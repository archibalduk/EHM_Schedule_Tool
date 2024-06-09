#pragma once

// Application headers
namespace ehm_dal::database {
class DatabaseVersion;
}

// Qt headers
class QDataStream;
#include <QtGlobal>
#include <memory>

namespace ehm_dal::ehm_extra_rules {

// --- Extra rule item --- //
class ExtraRule
{
public:
    ExtraRule();
    ~ExtraRule();

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version);
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version);

private:
    struct Data;
    std::unique_ptr<Data> data_;
};
} // namespace ehm_dal::ehm_extra_rules

