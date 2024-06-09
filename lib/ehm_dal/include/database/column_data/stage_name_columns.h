#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Stage name column data --- //
class StageNameColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    StageNameColumns();

    enum ENUM_COLUMNS {
        LongName = FirstStandardDerivedColumnIndex,
        ShortName,
        PluralName,
        StageGenericType,
        GroupGenericType,
        LongNameGender,
        ShortNameGender,
        PluralNameGender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
