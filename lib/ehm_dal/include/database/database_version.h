#pragma once

// Qt headers
#include <QtGlobal>

namespace ehm_dal::database {
// --- Database version control --- //
class DatabaseVersion
{
public:
    // Constructor
    DatabaseVersion();

    // Debugging / diagnostics
    void printDiagnosticData() const;

    // Get data
    inline qint16 version() const {return version_number_;}

    // Set data
    inline void setVersion(const qint16 version_number) { version_number_ = version_number; }

    enum ENUM_VERSION_FLAGS { NO_VERSION = -1, NO_MINIMUM_VERSION = NO_VERSION, EHM_1033 = 1033 };

    // Operator overloading
    inline bool operator==(const qint16 rhs) const { return version() == rhs; }
    inline bool operator!=(const qint16 rhs) const { return !operator==(rhs); }
    inline bool operator<(const qint16 rhs) const { return version() < rhs; }
    inline bool operator>(const qint16 rhs) const { return rhs < version(); }

private:
    qint16 version_number_ {NO_VERSION};
};
} // namespace ehm_dal::database
