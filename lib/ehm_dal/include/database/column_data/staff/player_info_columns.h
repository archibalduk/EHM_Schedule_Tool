#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class PlayerInfoColumns : public ehm_dal::column_data::ColumnData
{
public:
    PlayerInfoColumns();

    enum ENUM_COLUMNS {
        //Staff = FirstIdOnlyDerivedColumnIndex, // Doesn't add anything to the model as ID serves the same purpose
        ClubGamesPlayed = FirstIdOnlyDerivedColumnIndex,
        ClubGoals,
        ClubAssists,
        ClubPIM,
        ClubWins,
        ClubShutouts,
        LeagueTotalGamesPlayed,
        LeagueTotalGoals,
        LeagueTotalAssists,
        LeagueTotalPIM,
        LeagueTotalWins,
        LeagueTotalShutouts,
        ProfessionalGamesPlayedRegularSeason,
        ProfessionalGamesPlayedPlayoff,
        ProfessionalNHLGamesPlayed,
        CanadianJuniorGamesPlayed,
        NHLSeasonsAccrued,
        ProfessionalSeasonsAccrued,
        CanadianMajorJuniorSeasons,
        HasPlayedInCollege,
        HasPlayedInNorthAmericaAsJunior,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
