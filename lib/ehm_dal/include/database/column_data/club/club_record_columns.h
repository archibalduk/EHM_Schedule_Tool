#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Club record column data --- //
class ClubRecordColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    ClubRecordColumns();

    enum ENUM_COLUMNS {
        // Record information columns
        RecordTypeName = FirstIdOnlyDerivedColumnIndex,
        // Record data
        Year,
        Value,
        // Player record data
        RecordHolder,
        RecordHolderFirstNameString,
        RecordHolderSecondNameString,
        RecordHolderFirstNameIndex,
        RecordHolderSecondNameIndex,
        COLUMN_COUNT,
        FIRST_RECORD_DATA_COLUMN = Year,
        FIRST_PLAYER_RECORD_DATA_COLUMN = RecordHolder
    };
};
} // namespace ehm_dal::column_data
