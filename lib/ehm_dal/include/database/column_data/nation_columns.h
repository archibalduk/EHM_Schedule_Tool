#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Nation column IDs --- //
class NationColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    NationColumns();

    enum ENUM_COLUMNS {
        Name = FirstStandardDerivedColumnIndex,
        NameShort,
        NameNationality,
        Abbreviation,

        Continent,
        ActualRegion,
        Region,
        GroupMembership,
        CapitalCity,
        NationalArena,
        CitizenshipYears,

        Reputation,
        LeagueStandard,
        FinancialPower,
        GameImportance,
        StateOfDevelopment,

        FirstLanguage,
        SecondLanguage,
        ThirdLanguage,

        IIHFScore,
        MenFinalPosition1YearAgo,
        MenFinalPosition2YearsAgo,
        MenFinalPosition3YearsAgo,
        JnrFinalPosition1YearAgo,
        JnrFinalPosition2YearsAgo,
        JnrFinalPosition3YearsAgo,

        Rivals1,
        Rivals2,
        Rivals3,

        Colour1Foreground,
        Colour1Background,
        Colour1Trim,
        Colour2Foreground,
        Colour2Background,
        Colour2Trim,
        Colour3Foreground,
        Colour3Background,
        Colour3Trim,

        NumberStaff,
        NumberClubs,

        LeagueSelected,
        GamesPlayed,

        GenderName,
        GenderNameShort,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

