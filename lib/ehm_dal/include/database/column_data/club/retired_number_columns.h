#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Retired numbers column data --- //
class RetiredNumberColumns : public ehm_dal::column_data::ColumnData
{
public:
    RetiredNumberColumns();

    enum ENUM_COLUMNS { Club = FirstIdOnlyDerivedColumnIndex, PlayerName, Number, COLUMN_COUNT };
};
} // namespace ehm_dal::column_data
