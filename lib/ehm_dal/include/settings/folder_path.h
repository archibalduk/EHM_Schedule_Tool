#pragma once

// Qt headers
#include <QFileDialog>
#include <QString>
class QWidget;

namespace ehm_dal::settings {
// --- Folder path convenience functions --- //
class FolderPath
{
public:
    // Default constructor
    FolderPath(const QString &key, const QString &file_name = QString());

    // File dialogs
    QString fileOpenDialog(QWidget *parent = nullptr,
                           const QString &caption = QString(),
                           const QString &filter = QString(),
                           QString selected_filter = QString(),
                           QFileDialog::Options options = QFileDialog::ReadOnly);
    QString fileSaveDialog(QWidget *parent = nullptr,
                           const QString &caption = QString(),
                           const QString &filter = QString(),
                           QString selected_filter = QString(),
                           QFileDialog::Options options = QFileDialog::Options());
    QString folderDialog(QWidget *parent = nullptr,
                         const QString &caption = QStringLiteral("Open folder"),
                         QFileDialog::Options options = QFileDialog::ShowDirsOnly);

    // Get data
    QString defaultPath();
    inline QString fileName() const { return file_name_; }
    inline QString key() const { return key_; }
    QString path(const QString &file_name = QString()) const;
    bool useNativeFileDialog();

    // Initialisation
    void init(const QString &key);

    // Set data
    inline void setFileName(const QString &file_name) { file_name_ = file_name; }
    void setPath(const QString &path);

private:
    // File dialogs
    enum ENUM_FILE_DIALOG_TYPE { FILE_OPEN_DIALOG, FILE_SAVE_DIALOG, FOLDER_OPEN_DIALOG };

    QString dialog(const ENUM_FILE_DIALOG_TYPE &dialog_type,
                   QWidget *parent,
                   const QString &caption,
                   const QString &filter,
                   QString &selected_filter,
                   QFileDialog::Options &options);

    // Registry key
    QString key_;

    // Path cache
    QString file_name_;
    QString path_;
};
} // namespace ehm_dal::settings
