#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class NonPlayerDataColumns : public ehm_dal::column_data::ColumnData
{
public:
    NonPlayerDataColumns();

    enum COLUMN_INDEXES {
        // Ability
        CurrentAbility = FirstIdOnlyDerivedColumnIndex,
        PotentialAbility,

        // Reputation
        HomeReputation,
        CurrentReputation,
        WorldReputation,

        // Business Management
        Business,
        Interference,
        Patience,
        Resources,

        // Mental
        Discipline,
        ManHandling,
        Motivating,
        Youngsters,

        // Tactics
        Attacking,
        Directness,
        FreeRoles,
        LineMatching,
        PenaltyKill,
        Physical,
        PowerPlay,
        Tactics, // aka Tactical Knowledge
        PreferredJob,

        // Technical
        CoachingGoaltenders,
        CoachingDefensemen,
        CoachingForwards,
        CoachingTechnique, // aka Coaching Style
        Judgement,         // aka Judging Ability
        JudgingPotential,
        Physiotherapy,

        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
