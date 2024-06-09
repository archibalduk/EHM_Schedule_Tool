#pragma once

// Application headers
#include "include/file_io/abstract_file_manager.h"

namespace ehm_dal::file_io {
/*!
 * \brief The DatabaseFileManager class provides simple read and write access to a database
 */
class DatabaseFileManager : public ehm_dal::file_io::AbstractFileManager
{
public:
    DatabaseFileManager();

    // Descriptor
    inline QString descriptor() const override { return QStringLiteral("database"); }
    inline QString fileFilterString() const override
    {
        return QStringLiteral("EHM 1 Database (*.db)");
    }

private:
    // Close database/tables
    void closeAll() override;

    // File i/o - read
    bool read(const QString &path) override;

    // File i/o - write
    bool write(const QString &path) override;
};

} // namespace ehm_dal::file_io
