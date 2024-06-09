#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class StaffPreferencesColumns : public ehm_dal::column_data::ColumnData
{
public:
    StaffPreferencesColumns();

    enum COLUMN_INDEXES {
        FavouriteClub1 = FirstIdOnlyDerivedColumnIndex,
        FavouriteClub2,
        FavouriteClub3,
        DislikedClub1,
        DislikedClub2,
        DislikedClub3,
        FavouriteStaff1,
        FavouriteStaff2,
        FavouriteStaff3,
        DislikedStaff1,
        DislikedStaff2,
        DislikedStaff3,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
