#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Person column data base class --- //
class PersonColumns : public ehm_dal::column_data::ColumnData
{
public:
    PersonColumns();

    enum COLUMN_INDEXES {
        FirstName = FirstStandardDerivedColumnIndex,
        SecondName,
        DateOfBirth,
        YearOfBirth,
        Age,
        Birthplace,
        Nation,
        FirstPersonDerivedColumnIndex
    };
};
} // namespace ehm_dal::schema

