#pragma once

// Application headers
#include "include/settings/folder_path.h"

// Qt headers
#include <QTime>
class QDataStream;
class QString;
class QWidget;

namespace ehm_dal::file_io {
/*!
 * \brief The AbstractFileManager class is a base class providing simple read and write file access to database and saved game files
 * \details
 */
class AbstractFileManager
{
public:
    AbstractFileManager(const QString &folder_path_key);

    // Close database/tables
    bool close(const bool show_confirmation_dialog = true);

    // Descriptor
    virtual QString descriptor() const = 0;
    virtual QString fileFilterString() const = 0;

    // File i/o - read
    bool open(const QString &path);
    bool open(QWidget *parent = nullptr);

    // File i/o - write
    bool save();
    bool saveAs(QWidget *parent = nullptr);

    // Get data
    inline bool isOpen() const { return is_open_; }
    inline bool isSaved() const { return has_been_saved_; }

protected:
    // Status
    inline void setOpenStatus(const bool is_open) { is_open_ = is_open; }
    void setSaveStatus(const bool has_been_saved);

private:
    // Close database/tables
    virtual void closeAll() = 0;

    // File i/o - read
    virtual bool read(const QString &path) = 0;

    // File i/o - write
    virtual bool write(const QString &path) = 0;

    // Folder path cache
    settings::FolderPath source_folder_;

    // Status
    bool has_been_saved_{false};
    bool is_open_{false};
    QTime last_saved_time_{QTime::currentTime()};
};
} // namespace ehm_dal::file_io
