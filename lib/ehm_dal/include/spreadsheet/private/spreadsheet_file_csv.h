#pragma once

// Application headers
#include "include/spreadsheet/private/spreadsheet_file.h"

namespace ehm_dal::spreadsheet {

// --- CSV spreadsheet --- //
class SpreadsheetFileCsv : public SpreadsheetFile
{
public:
    // Constructor
    SpreadsheetFileCsv();
    SpreadsheetFileCsv(QFile &file);

    // Delimiter
    static QString systemDelimiterDescription();

    // File I/O
    bool read(std::vector<std::vector<QVariant>> &header,
              std::vector<std::vector<QVariant>> &cells,
              const qint32 header_count = 0) override;
    bool writeCells(std::vector<QVariant> &prefix,
                    std::vector<std::vector<QVariant>> &cells) override;
    bool writeHeader(std::vector<QVariant> &prefix,
                     std::vector<std::vector<QVariant>> &header) override;

    // Get data
    bool isAsciiEnabled() const { return !utf_8_enabled_; }
    bool isUtfEnabled() const { return utf_8_enabled_; }

private:
    // Delimiter
    QChar system_delimiter_{systemDelimiter()};
    static QChar systemDelimiter();

    // File I/O
    void readRow(std::vector<std::vector<QVariant>> &data, QChar &delimiter);
    bool write(std::vector<QVariant> &prefix,
               std::vector<std::vector<QVariant>> &data,
               const bool silent_progress_dialog = false);

    // Get data
    QByteArray bom() const;

    // Settings
    bool utf_8_enabled_{false};

    // Validation
    void validate(std::vector<QVariant> &cells);
};
} // namespace ehm_dal::spreadsheet
