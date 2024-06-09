#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Club history column data --- //
class ClubHistoryColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    ClubHistoryColumns();

    enum ENUM_COLUMNS {
        Club = FirstIdOnlyDerivedColumnIndex,
        Comp,
        Season,
        Position,
        GamesPlayed,
        Won,
        Tied,
        Lost,
        OvertimeWins,
        OvertimeLosses,
        ShootoutWins,
        ShootoutLosses,
        GoalsScored,
        GoalsAgainst,
        Points,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
