#pragma once


// Application headers
namespace ehm_dal::tables {
class AbstractTable;
enum class TableIndex : char;
} // namespace ehm_dal::tables

// Qt headers
class QByteArray;
class QDataStream;
#include <QtGlobal>
#include <memory>
class QString;

namespace ehm_dal {
/*!
 * \brief The Database class parses the database.db file and provides access to its tables.
 * \details The parsed tables are static members of Database, allowing easy access via the 
 * static table(const TableIndex table_id) function without the need to continually construct or pass an 
 * instantation of Database to functions.
 * 
 * A database is typically parsed by passing the file path of the database.db file to read(const QString &file_path). 
 * Alternatively, a `QDataStream` attached to a database.db file can be parsed using read(QDataStream &in).
 */
class Database
{
public:
    /*!
     * \brief Default constructor.
     */
    Database();

    // Close database
    /*!
     * \brief Clear all of the database tables
     */
    void clearAll();

    // File i/o
    /*!
     * \brief Reads a database.db from the `file_path` and parses each of the tables.
     * \param file_path Path to the database.db file; e.g. "C:\Users\archibalduk\Desktop\database.db"
     * \return whether the file was successfully opened and parsed.
     */
    bool read(const QString &file_path);
    /*!
     * \brief Reads a database.db file from `QDataStream` and parses each of the tables. 
     * The `QDataStream` is parsed from the current position of the stream until the end of the stream is reached.
     * \param in `QDataStream` attached to database.db file
     * \return whether the file was successfully opened and parsed.
     */
    bool read(QDataStream &in);
    /*!
     * \brief Reads `file_size` bytes a database.db file from `QDataStream` and parses each of the tables. 
     * The `QDataStream` is parsed from the current position of the stream until until `file_size` bytes are parsed.
     * \param in `QDataStream` attached to database.db file
     * \param file_size File size in bytes to be read.
     * \return 
     */
    bool read(QDataStream &in, const qsizetype file_size);

    // Get data
    /*!
     * \brief Returns a shared pointer to a Table with a ehm_dal::tables::TableIndex of `table_id`.
     * \param table_id ehm_dal::tables::TableIndex of the desired Table.
     * \return a `shared_ptr` to the Table or `nullptr` if the ehm_dal::tables::TableIndex is invalid.
     */
    static std::shared_ptr<ehm_dal::tables::AbstractTable> table(const ehm_dal::tables::TableIndex table_id);
    /*!
     * \brief Returns the number of database tables
     * \return the number of database tables
     */
    qint32 tableCount() const;

private:
    // Tables
    struct TableData;
    static TableData table_data_;

    // End of the file
    static QByteArray end_of_file_data_;

    // File i/o
    qsizetype remainingBytes(QDataStream &in,
                             const qsizetype file_start_pos,
                             const qsizetype file_size);
    bool readEndOfFile(QDataStream &in, const qsizetype bytes_to_read);

    // Initialisation
    void init();
    void initChildTables();
};

} // namespace ehm_dal


