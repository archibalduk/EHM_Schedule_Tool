#pragma once


// Application headers
#include "include/data_types/string.h"

// Qt headers
class QDataStream;
#include <QString>

namespace ehm_dal::saved_game {
/*!
 * \brief The SavedGameSubFile class represents a sub-file of a saved game and provides access to the binary data.
 */
class SavedGameSubFile
{
public:
    /*!
     * \brief Default constructor.
     */
    SavedGameSubFile();
    /*!
     * \brief Default destructor.
     */
    ~SavedGameSubFile();

    // File i/o
    /*!
     * \brief Reads the saved game header relating to the SavedGameTable.
     * \param in `QDataStream` attached to the saved game
     */
    void readHeader(QDataStream &in);
    /*!
     * \brief Reads the raw binary data relating to the SavedGameTable.
     * \param in `QDataStream` attached to the saved game
     */
    void readTable(QDataStream &in);

    // Get data - attributes
    /*!
     * \brief Returns whether or not the SavedGameTable is the saved game's Database table (i.e. database.zdb)
     * \return whether or not the SavedGameTable is the saved game's Database table.
     */
    inline bool isDatabaseTable() const { return is_database_table_; }
    /*!
     * \brief Returns the estimated size of each row in bytes. This is based on the estimated record count.
     * \return the estimated size of each row in bytes.
     */
    inline qint32 estimatedBytesPerRow() const { return estimated_bytes_per_row_; }
    /*!
     * \brief Returns the estimated row count based on the integer or short value of the first four or two bytes of the raw data. 
     * Whether or not an integer (4 bytes) or short (2 bytes) is more suitable is automatically detected.
     * \return the estimated row count.
     */
    inline qint32 estimatedRowCount() const { return estimated_row_count_; }
    /*!
     * \brief Returns the file name.
     * \return the file name.
     */
    inline QString fileName() const { return file_name_.get(); }
    /*!
     * \brief Returns the sub-file position (i.e. offset) within the saved game file.
     * \return the file position/offset.
     */
    inline quint32 filePosition() const { return file_position_; }
    /*!
     * \brief Returns the file size in KB (kilobytes). 1 KB = 1024 bytes.
     * \return the file size in KB (kilobytes).
     */
    double fileSizeKilobytes() const;

    // Get data - sub-file data
    /*!
     * \brief Returns a pointer to the raw data of the sub-file.
     * \return a pointer to the `QByteArray` raw data.
     */
    QByteArray *data();

    /*!
     * \brief The ENUM_TEXT_LENGTH enum denotes the fixed length of 8-bit `char` arrays of table names in the saved game header
     */
    enum ENUM_FLAGS {
        TABLE_NAME_LENGTH
        = 260 /*!< fixed length of 8-bit `char` arrays of table names in the saved game header */
    };

private:
    // Attributes
    bool is_database_table_{false};
    data_types::String file_name_;
    quint32 file_position_;
    quint32 file_size_;

    // Data
    QByteArray raw_data_;

    // Estimated attributes
    qint32 estimated_row_count_{0};
    double estimated_bytes_per_row_{0.0};

    // Set data
    void initEstimatedData();
};

} // namespace ehm_dal::saved_game


