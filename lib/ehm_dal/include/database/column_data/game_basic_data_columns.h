#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Game Basic Data column data --- //
class GameBasicDataColumns : public ehm_dal::column_data::ColumnData
{
public:
    GameBasicDataColumns();

    enum COLUMN_INDEXES {
        BaseYear = FirstStandardDerivedColumnIndex,
        TemporaryFlag,
        VerifiedPlayableLeagues,
        ClubsRemapped,
        GameFormatData_1,
        GameFormatData_2,
        NotUsed,
        VirtualsAdded,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

