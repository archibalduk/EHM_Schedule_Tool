#pragma once

// Application headers
#include "include/spreadsheet/private/spreadsheet_file.h"
namespace ehm_dal::data_types {
class Pointer;
}
namespace ehm_dal::settings {
class FolderPath;
}

// Qt headers
class QAbstractTableModel;
#include <QString>
#include <QVariant>
#include <span>
#include <vector>

namespace ehm_dal::spreadsheet {

// --- Spreadsheet --- //
class Spreadsheet
{
public:
    // Constructor
    Spreadsheet(const QString &file_path = QString());
    Spreadsheet(const settings::FolderPath &path);
    ~Spreadsheet();

    // Add data - cells/rows: basic
    inline void add() { add(QVariant()); }
    inline void add(const QString &text) { add(QVariant(text)); }
    void add(const QVariant &data);
    void add(const QVariant &data, const qint32 row);
    void add(const QVariant &data, const qint32 start_row, const qint32 row_count);

    // Add data - cells/rows: model data
    /*!
     * \brief Adds all rows and columns from `model` to the spreadsheet. This is generally used to export a Table using 
     * `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel` or Table
     * \param role Source data role
     */
    void add(QAbstractTableModel *model, const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all rows and the selected columns from `model` to the spreadsheet. This is generally used to export 
     * a Table using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel` or Table
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and all columns from `model` to the spreadsheet. This is generally used to export 
     * a Table using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel` or Table
     * \param row Source row
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const qint32 row,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and selected columns from `model` to the spreadsheet. This is generally used to 
     * export a Table using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel` or Table
     * \param row Source row
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const qint32 row,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all columns of the selected Pointer to the spreadsheet.
     * \param pointer Source pointer
     * \param role Source data role
     */
    void add(const ehm_dal::data_types::Pointer &pointer, const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected columns of the selected Pointer to the spreadsheet.
     * \param pointer Source pointer
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(const ehm_dal::data_types::Pointer &pointer,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all columns of the selected Pointers to the spreadsheet.
     * \param pointer_list Source pointers
     * \param role Source data role
     */
    void add(const std::vector<ehm_dal::data_types::Pointer> &pointer_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected columns of the selected Pointers to the spreadsheet.
     * \param pointer_list Source pointers
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(const std::vector<ehm_dal::data_types::Pointer> &pointer_list,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);

    // Add data - prefix cells
    inline void addPrefix() { addPrefix(QVariant()); }
    inline void addPrefix(const QVariant &data) { prefix_cell_data_.push_back(data); }

    // Add data - header: basic
    inline void addHeader() { add(QVariant()); }
    inline void addHeader(const QString &text) { addHeader(QVariant(text)); }
    void addHeader(const QStringList &text_list);
    void addHeader(const QVariant &data);

    // Add data - header: model data
    /*!
     * \brief Adds a header row of column names of all columns from the 'model'. 
     * This is typically used to add the names of all columns from a Table as a header row to the spreadsheet.
     * \param model Source `QAbstractTableModel` or Table
     */
    void addHeader(QAbstractTableModel *model);
    /*!
     * \brief Adds a header row of column names of the selected columnd from the 'model'. 
     * This is typically used to add the names of the selected columns from a Table as a header row to the spreadsheet.
     * \param model Source `QAbstractTableModel` or Table
     * \param column_index_list Column indexes to be added
     */
    void addHeader(QAbstractTableModel *model, const std::vector<qint32> &column_index_list);

    // Add data - prefix header
    inline void addHeaderPrefix() { addHeaderPrefix(QVariant()); }
    inline void addHeaderPrefix(const QVariant &data) { prefix_header_data_.push_back(data); }

    // Debugging / diagnostics
    void printDiagnosticData() const;

    // File details - get data
    QString file();
    /*!
     * \brief Returns the file path and name of the output spreadsheet.
     * \return the file path and name
     */
    inline QString fileName() { return file_name_; }
    /*!
     * \brief Returns the file type of the output spreadsheet.
     * \return the file type
     */
    QString fileType() const;
    inline QString identifier() { return headerCell(0,0).toString().replace(" ", "_").toLower(); }

    // File details - set data
    void addFileNameSuffix(const QString &suffix);
    bool setFile(const QString &path);

    // File extensions
    static qint32 defaultFileExtension();
    static QString fileExtensionListAsString(const bool merged_list = true);
    static QStringList fileExtensionListAsStringList();
    static void setDefaultFileExtension(const qint32 i);

    // File I/O
    bool open(const QString &file_path);
    bool open(const QString &folder, const QString &file_name);
    bool read();
    bool save(const QString &folder, const QString &file_name);
    /*!
     * \brief Writes/saves the spreadsheet to the output file.
     * \return whether the spreadsheet file was successfully saved
     */
    bool write();

    // File I/O dialog windows
    bool showOpenDialog(QString file_path = QString(), const bool read_data = true);
    bool showOpenDialog(settings::FolderPath &path, const bool read_data = true);
    bool showSaveDialog(const QString &file_name = "output.csv", QString file_path = QString());
    bool showSaveDialog(settings::FolderPath &path);

    // Get data - cells
    QVariant cell(const qint32 row, const qint32 col) const;
    std::span<const QVariant> cells(const qint32 row,
                                    const qint32 col,
                                    const qint32 col_count) const;
    bool columnContainsData(const qint32 column) const;
    qint32 columnCount(const qint32 row) const;
    std::span<const QVariant> row(const qint32 row) const;
    inline qint32 rowCount() const { return static_cast<qint32>(cell_data_.size()); }

    // Get data - prefix cells
    QVariant prefix(const qint32 row) const;
    inline bool hasPrefixData() const { return prefixCount() > 0; }
    inline qint32 prefixCount() const { return static_cast<qint32>(prefix_cell_data_.size()); }

    // Get data - header
    std::span<const QVariant> header(const qint32 row) const;
    QVariant headerCell(const qint32 row, const quint16 col) const;
    inline qint32 headerCount() const
    {
        return std::max(static_cast<qint32>(header_data_.size()), header_count_);
    }

    // Get data - header
    QVariant prefixHeader(const qint32 row) const;
    inline bool hasPrefixHeaderData() const { return prefixHeaderCount() > 0; }
    inline qint32 prefixHeaderCount() const
    {
        return static_cast<qint32>(prefix_header_data_.size());
    }

    // Get settings
    static QString exportPath();
    static QString importPath();

    // Row data: add data
    void addNewHeaderRow();
    void addNewRow();

    // Set header data
    void setHeaderCount(const qint32 header_row_count);

    // Spreadsheet file
    std::unique_ptr<SpreadsheetFile> newSpreadsheet(QFile &f);

private:
    // Data
    std::vector<std::vector<QVariant>> cell_data_;
    std::vector<std::vector<QVariant>> header_data_;
    std::vector<QVariant> prefix_cell_data_;
    std::vector<QVariant> prefix_header_data_;

    // Column data
    std::vector<qint32> columnList(const qint32 column_count) const;

    // File data
    quint8 file_extension_;
    QString file_name_;
    QString path_;

    // File extensions (functions)
    static QHash<QString, quint8> fileExtensions();
    static QString filterText(const qint32 type);

    // File extensions (members)
    enum ENUM_FILE_EXTENSIONS {
        CSV,
        XLSX,
        FILE_EXTENSION_COUNT
    };

    // Header
    qint32 header_count_{2};

    // Progress display
    bool hide_progress_{false};

    // Row data: get data
    std::vector<QVariant> *currentHeaderRow();
    std::vector<QVariant> *currentRow();
};
} // namespace ehm_dal::spreadsheet
