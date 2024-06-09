#pragma once


// Application headers
#include "saved_game_sub_file.h"

// Qt headers
class QDataStream;
#include <QtGlobal>
#include <memory>
#include <vector>

namespace ehm_dal::saved_game {
/*!
 * \brief The SavedGameData class contains the individual binary sub-files comprising the saved game.
 */
class SavedGameData
{
public:
    /*!
     * \brief Default constructor.
     */
    SavedGameData();
    /*!
     * \brief Default destructor.
     */
    ~SavedGameData();

    // File i/o
    /*!
     * \brief Reads the saved game file from the `QDataStream`.
     * \param in `QDataStream` attached to the saved game
     * \return whether the file was successfully opened and parsed.
     */
    bool read(QDataStream &in);

    // Find data
    /*!
     * \brief Finds all sub-files containing `sub_file_name` and returns all results in a vector.
     * \param sub_file_name Target sub-file name
     * \param cs Case sensitivity
     * \return a vector of shared pointers to the relevant sub-files.
     */
    std::vector<std::shared_ptr<SavedGameSubFile>> find(
        const QString &sub_file_name, const Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    // Get data - header
    /*!
     * \brief Returns whether the saved game is compressed.
     * \return whether the saved game is compressed.
     */
    inline bool isCompressed() const { return compressed_flag_ != 0; }

private:
    // Header
    qint32 compressed_flag_{0};
    qint32 header_flag_{22};
    qint32 table_count_{0};

    // Tables
    std::vector<std::shared_ptr<SavedGameSubFile>> tables_;
};

} // namespace ehm_dal::saved_game


