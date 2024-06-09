#pragma once

/*!
 * \brief namespace ehm_dal::tables
 */
namespace ehm_dal::tables {

// Database table indexes
/*!
 * \brief The TableIndex enum represents the id number of each table within the database.
 * \details TableIndex is used by variety of classes in order to access a specific database table. The index values 
 * are used to distinguish between tables in EHM DAL. The values are disinct from any table id used internally by EHM.
 */
enum class TableIndex : char {
    SAVED_GAME_TABLE = -2,    /*!< saved game table */
    NO_TABLE = -1,            /*!< no table */
    GAME_BASIC_DATA = 0,      /*!< game basic data */
    DATABASE_HEADER,          /*!< database header */
    CONTINENTS,               /*!< continents */
    NATIONS,                  /*!< nations */
    CITIES,                   /*!< cities */
    STATES,                   /*!< states */
    ARENAS,                   /*!< arenas */
    COLOURS,                  /*!< colours */
    CLUBS,                    /*!< clubs */
    AFFILIATIONS,             /*!< affiliations */
    RETIRED_NUMBERS,          /*!< retired numbers */
    STAFF,                    /*!< staff (i.e. players & non-players) */
    STAFF_PREFERENCES,        /*!< staff preferences */
    NON_PLAYER_DATA,          /*!< non-player attributes */
    PLAYER_DATA,              /*!< player attributes */
    STAFF_HISTORY,            /*!< player career history */
    CLUB_COMPETITIONS,        /*!< club competitions */
    CLUB_COMPETITION_HISTORY, /*!< club competition history */
    STAFF_AWARDS,             /*!< staff awards */
    STAFF_AWARD_HISTORY,      /*!< staff award history */
    OFFICIALS,                /*!< officials */
    FIRST_NAMES,              /*!< first names (i.e. forenames) */
    SECOND_NAMES,             /*!< second names (i.e. surnames) */
    INJURIES,                 /*!< injuries */
    CURRENCIES,               /*!< currencies */
    STAGE_NAMES,              /*!< stage names */
    DRAFT_HISTORY,            /*!< draft history (i.e. drafted players) */
    DRAFTS,                   /*!< drafts */
    PLAYER_RIGHTS,            /*!< player rights */
    CLUB_HISTORY,             /*!< club history */
    CLUB_RECORDS,             /*!< club records */
    PLAYER_INFO,              /*!< player stats */
    STAFF_INFO                /*!< staff info  (i.e. players & non-players) */
};

} // namespace ehm_dal::tables


