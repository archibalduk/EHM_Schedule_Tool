#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Arena column data --- //
class StaffAwardHistoryColumns : public ehm_dal::column_data::ColumnData
{
public:
    StaffAwardHistoryColumns();

    enum COLUMN_INDEXES {
        Award = FirstIdOnlyDerivedColumnIndex,
        CompYear,
        FirstPlacedClub,
        FirstPlacedIndex,
        FirstPlacedFirstName,
        FirstPlacedSecondName,
        SecondPlacedClub,
        SecondPlacedIndex,
        SecondPlacedFirstName,
        SecondPlacedSecondName,
        ThirdPlacedClub,
        ThirdPlacedIndex,
        ThirdPlacedFirstName,
        ThirdPlacedSecondName,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

