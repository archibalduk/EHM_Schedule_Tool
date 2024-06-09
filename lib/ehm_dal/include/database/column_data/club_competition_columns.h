#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- ClubCompetition column data --- //
class ClubCompetitionColumns : public ehm_dal::column_data::ColumnData
{
public:
    ClubCompetitionColumns();

    enum COLUMN_INDEXES {
        Name = FirstStandardDerivedColumnIndex,
        ShortName,
        Abbreviation,
        RegularSeasonTrophyName,
        PlayoffTrophyName,
        Nation,
        Continent,
        Classification,
        ParentClubCompetition,
        DivisionLevel,
        Reputation,
        UpperAgeLimit,
        Clubs,
        ClubCount,
        ForegroundColour,
        BackgroundColour,
        TrimColour,
        SelectedFlag,
        GenderName,
        GenderShortName,
        GenderPlayoffTrophy,
        GenderRegularSeasonTrophy,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

