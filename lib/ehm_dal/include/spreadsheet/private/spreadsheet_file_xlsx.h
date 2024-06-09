#pragma once

// Application headers
#include "xlsxdocument.h"
#include "include/spreadsheet/private/spreadsheet_file.h"

namespace ehm_dal::spreadsheet {

// --- Excel XLSX spreadsheet --- //
class SpreadsheetFileXlsx : public SpreadsheetFile
{
public:
    // Constructor
    SpreadsheetFileXlsx();
    SpreadsheetFileXlsx(QFile &file, const QString &file_name);

    // Excel functions
    qint64 dateToExcelNumber(const QDate &d) const;

    // File I/O
    bool read(std::vector<std::vector<QVariant>> &header,
              std::vector<std::vector<QVariant>> &cells,
              const qint32 header_count = 0) override;
    bool writeCells(std::vector<QVariant> &prefix,
                    std::vector<std::vector<QVariant>> &cells) override;
    bool writeHeader(std::vector<QVariant> &prefix,
                     std::vector<std::vector<QVariant>> &header) override;

private:
    // File path (for QXlsx which cannot use the device)
    QString file_name_;

    // File I/O
    void readRow(std::vector<std::vector<QVariant>> &data,
                 const qint32 row,
                 const qint32 column_count);
    bool write(std::vector<QVariant> &prefix,
               std::vector<std::vector<QVariant>> &data,
               const QXlsx::Format &format,
               const bool silent_progress_dialog = false);
    void writeCell(qint32 row,
                   qint32 column,
                   const QVariant &data,
                   QXlsx::Worksheet *w,
                   const QXlsx::Format &standard_format,
                   const QXlsx::Format &date_format);

    // Row offset counter
    qint32 row_offset_{0};

    // Xlsx document
    std::unique_ptr<QXlsx::Document> xlsx_;

    static const QDate excel_epoch_;
};
} // namespace ehm_dal::spreadsheet
