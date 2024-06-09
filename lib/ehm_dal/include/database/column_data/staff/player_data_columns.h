#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class PlayerDataColumns : public ehm_dal::column_data::ColumnData
{
public:
    PlayerDataColumns();

    enum COLUMN_INDEXES {
        // Ability
        CurrentAbility = FirstIdOnlyDerivedColumnIndex,
        PotentialAbility,

        // Reputation
        HomeReputation,
        CurrentReputation,
        WorldReputation,

        // Height/weight
        HeightCentimetres,
        WeightKilograms,
        BodyMassIndex,

        // Jersey numbers
        SquadNumber,
        InternationalSquadNumber,
        FavouriteNumber,

        // Junior preference
        JuniorPreference,

        // Positions
        Goaltender,
        LeftDefense,
        RightDefense,
        LeftWing,
        Center,
        RightWing,

        // Role
        DefensiveRole,
        OffensiveRole,
        PlayerRole,

        // Handedness
        Handedness,

        // Goaltending
        Blocker,
        Glove,
        OneOnOnes,
        Rebounds,
        Recovery,
        Reflexes,

        // Mental
        Aggression,
        Agitation,
        Anticipation,
        Bravery,
        Consistency,
        Creativity,
        Decisions,
        Dirtiness,
        Flair,
        ImportantMatches,
        Leadership,
        Morale,
        PassTendency,
        Teamwork,
        Versatility,
        WorkRate,

        // Physical
        Acceleration,
        Agility,
        Balance,
        InjuryProneness,
        NaturalFitness,
        Pace,
        Stamina,
        Strength,

        // Technical
        Checking,
        Deflections,
        Deking,
        Faceoffs,
        Fighting,
        Hitting,
        Movement,
        Passing,
        Pokecheck,
        Positioning,
        Slapshot,
        Stickhandling,
        Wristshot,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
