#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- States & provinces column data --- //
class StateColumns : public ehm_dal::column_data::ColumnData
{
public:
    StateColumns();

    enum COLUMN_INDEXES {
        Abbreviation = FirstStandardDerivedColumnIndex,
        Name,
        ShortName,
        Nation,
        Gender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

