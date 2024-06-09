#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class StaffHistoryColumns : public ehm_dal::column_data::ColumnData
{
public:
    StaffHistoryColumns();

    enum COLUMN_INDEXES {
        // Ability
        Staff = FirstIdOnlyDerivedColumnIndex,
        OnLoan,
        Playoff,
        Season,
        Club,
        Comp,
        GamesPlayed,
        Goals,
        Assists,
        PenaltiesInMinutes,
        PlusMinus,
        Wins,
        Losses,
        Ties,
        Minutes,
        Conceded,
        Saves,
        Shutouts,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
