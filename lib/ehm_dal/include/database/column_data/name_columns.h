#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Name column data --- //
class NameColumns : public ehm_dal::column_data::ColumnData
{
public:
    NameColumns();

    enum COLUMN_INDEXES {
        NameText = FirstStandardDerivedColumnIndex,
        Nation,
        ExtraFlags,
        Count,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema


