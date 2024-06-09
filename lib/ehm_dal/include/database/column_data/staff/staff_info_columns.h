#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
class StaffInfoColumns : public ehm_dal::column_data::ColumnData
{
public:
    StaffInfoColumns();

    enum ENUM_COLUMNS {
        //Staff = FirstIdOnlyDerivedColumnIndex, // Doesn't add anything to the model as ID serves the same purpose
        LastKnownClub = FirstIdOnlyDerivedColumnIndex,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
