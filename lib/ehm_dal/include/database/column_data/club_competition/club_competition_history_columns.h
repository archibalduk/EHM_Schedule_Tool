#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Club competition history column data --- //
class ClubCompetitionHistoryColumns : public ehm_dal::column_data::ColumnData
{
public:
    ClubCompetitionHistoryColumns();

    enum COLUMN_INDEXES {
        ClubCompetition = FirstIdOnlyDerivedColumnIndex,
        Winners,
        RunnersUp,
        ThirdPlaced,
        Hosts,
        RegularSeasonChampions,
        Year,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

