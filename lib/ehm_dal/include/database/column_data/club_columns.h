#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Club column data --- //
class ClubColumns : public ehm_dal::column_data::ColumnData
{
public:
ClubColumns();

enum COLUMN_INDEXES {
    Name = FirstStandardDerivedColumnIndex,
    ShortName,
    Nickname,
    Abbreviation,
    League,
    DetailedDivision,
    ReserveDivision,
    LastLeague,
    LastPosition,
    MediaExpectedPosition,
    Nation,
    HomeCity,
    ProfessionalStatus,
    ContinentalLicence,
    Arena,
    PracticeFacilities,
    HomeGameDay,
    AverageAttendance,
    MinimumAttendance,
    MaximumAttendance,
    ClubOwnsArena,
    Reputation,
    YearFounded,
    FanSupport,
    MarketSize,
    Training,
    PublicCompany,
    Cash,
    PlayerBudget,
    Colour1Foreground,
    Colour1Background,
    Colour1Trim,
    Colour2Foreground,
    Colour2Background,
    Colour2Trim,
    Colour3Foreground,
    Colour3Background,
    Colour3Trim,
    FavouriteStaff1,
    FavouriteStaff2,
    FavouriteStaff3,
    DislikedStaff1,
    DislikedStaff2,
    DislikedStaff3,
    Rivals1,
    Rivals2,
    Rivals3,
    GenderName,
    GenderShortName,
    UnusedFlag,
    COLUMN_COUNT
};
};
} // namespace ehm_dal::schema

