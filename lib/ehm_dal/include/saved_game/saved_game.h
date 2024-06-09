#pragma once


// Application headers
namespace ehm_dal::saved_game {
class SavedGameData;
};

// Qt headers
class QString;
#include <memory>

namespace ehm_dal {
/*!
 * \brief The SavedGame class parses uncompressed EHM .sav saved games.
 * \details The database contained within the saved game is automatically detected and then parsed by the Database class. 
 * The class is compatible uncompressed saved games only. The parsed sub-files are static members of Saved Game, allowing easy access 
 * without the need to continually construct or pass an instantation of Saved Game to functions.
 */
class SavedGame
{
public:
    /*!
     * \brief Default constructor.
     */
    SavedGame();
    /*!
     * \brief Default destructor.
     */
    ~SavedGame();

    // File i/o
    /*!
     * \brief Reads the .sav file at `file_path` and parses the saved game and the Database within.
     * \param file_path file_path Path to the database.db file; e.g. "C:\Users\archibalduk\Desktop\my_saved_game.sav"
     * \return whether the file was successfully opened and parsed.
     */
    bool read(const QString &file_path);

    // Get data
    /*!
     * \brief Returns the saved game data comprising saved game sub-files.
     * \return a `shared_ptr` to the saved game data.
     */
    static std::shared_ptr<ehm_dal::saved_game::SavedGameData> data();

private:
    static std::shared_ptr<ehm_dal::saved_game::SavedGameData> data_;

    // Initialisation
    void init();
};

} // namespace ehm_dal


