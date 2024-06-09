#pragma once


// Application headers
#include "include/database/column_data/private/person_columns.h"

namespace ehm_dal::column_data {
// --- Staff column data --- //
class StaffColumns : public ehm_dal::column_data::PersonColumns
{
public:
    StaffColumns();

    enum COLUMN_INDEXES {
        SecondNation = FirstPersonDerivedColumnIndex,
        DeclaredNation,
        Classification,
        ExtraFlags,

        // Club Contract
        ClubContracted,
        ClubPlaying,
        SquadSelectedFor,
        JobForClub,
        DateJoinedClub,
        ContractExpiresClub,
        EstimatedWage,
        EstimatedWageWeekly,
        EstimatedValue,

        // Nation Contract
        NationContracted,
        JobForNation,
        DateJoinedNation,
        ContractExpiresNation,

        // Stats
        FirstNHLContract,
        StanleyCupsWon,
        InternationalApps,
        InternationalGoals,
        InternationalAssists,

        // Draft
        NHLDraftEligible,
        ClubsDraftedBy,
        ClubCompsDraftedBy,
        IsNhlDrafted,
        RightsHeldByClubs,
        RightsHeldByClubComps,

        // Staff attributes
        Adaptability,
        Ambition,
        Determination,
        Loyalty,
        Pressure,
        Professionalism,
        Sportsmanship,
        Temperament,

        // Pointers
        PlayerData,
        PlayerInfoData,
        StaffInfoData,
        StaffPreferencesData,
        NonPlayerData,
        PlayerRightsData,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data

