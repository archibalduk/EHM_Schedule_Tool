#pragma once

// Application headers
#include "include/widgets/dialogs/progress_dialog.h"

// Qt headers
#include <vector>
#include <QFile>
#include <QObject>
#include <QRegularExpression>
#include <QVariant>

namespace ehm_dal::spreadsheet {

// --- Spreadsheet file base class --- //
class SpreadsheetFile
{
public:
    // Constructor
    SpreadsheetFile() { progress_dialog_.setSilent(hide_progress_); }
    SpreadsheetFile(QFile &file)
        : file_(&file)
    {
        progress_dialog_.setSilent(hide_progress_);
    }

    // Destructor
    virtual ~SpreadsheetFile() { progress_dialog_.complete(); }

    // File I/O
    virtual bool read(std::vector<std::vector<QVariant>> &header,
                      std::vector<std::vector<QVariant>> &cells,
                      const qint32 header_count = 0)
        = 0;
    virtual bool writeCells(std::vector<QVariant> &prefix, std::vector<std::vector<QVariant>> &cells)
        = 0;
    virtual bool writeHeader(std::vector<QVariant> &prefix,
                             std::vector<std::vector<QVariant>> &header)
        = 0;

    // Get data
    QString dateFormat() const;

    // Set silent
    void setSilent(const bool silent) {hide_progress_ = silent;}

protected:
    // A digit (\d), zero or more times (*)
    const QRegularExpression numerical_{"\\d*"};

    // Stream
    QFile *file_{nullptr};

    // Header row count
    qint32 header_count_ {2};

    // Progress dialog
    bool hide_progress_ {false};
    widgets::ProgressDialog progress_dialog_{QStringLiteral("Spreadsheet File"), 0, 1};
};
} // namespace ehm_dal::spreadsheet
