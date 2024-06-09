#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Arena column data --- //
class StaffAwardColumns : public ehm_dal::column_data::ColumnData
{
public:
    StaffAwardColumns();

    enum COLUMN_INDEXES {
        Name = FirstStandardDerivedColumnIndex,
        NameShort,
        Type,
        Competition,
        DetailedDivision,
        Nation,
        Continent,
        NumberOfPlayersToVote,
        Reputation,
        ColourForeground,
        ColourBackground,
        ColourTrim,
        ExtraRules,
        GenderName,
        GenderNameShort,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

