#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class DraftHistoryColumns : public ehm_dal::column_data::ColumnData
{
public:
    DraftHistoryColumns();

    enum ENUM_COLUMNS {
        Draft = FirstIdOnlyDerivedColumnIndex,
        DraftYear,
        Overall,
        Round,
        Club,
        ClubComp,
        Staff,
        FirstName,
        SecondName,
        HasPlayerRights,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
