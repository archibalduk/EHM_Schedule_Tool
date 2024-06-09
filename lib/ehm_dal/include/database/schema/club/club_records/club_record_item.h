#pragma once

// Application headers
#include "include/database/schema/club/club_records/abstract_club_record.h"

// Qt headers
class QDataStream;

namespace ehm_dal::schema {

// --- Club record item --- //
class ClubRecordItem : public AbstractClubRecord
{
public:
    ClubRecordItem();
    ~ClubRecordItem() = default;

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;
};
} // namespace ehm_dal::schema
