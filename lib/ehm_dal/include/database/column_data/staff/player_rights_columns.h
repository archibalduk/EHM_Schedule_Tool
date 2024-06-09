#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class PlayerRightsColumns : public ehm_dal::column_data::ColumnData
{
public:
    PlayerRightsColumns();

    enum ENUM_COLUMNS {
        Staff = FirstIdOnlyDerivedColumnIndex,
        Club,
        ClubCompetition,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
