#pragma once

// Qt headers
#include <QtGlobal>
#include <vector>

// --- Schedule generator club item --- //
namespace ehm_dal::tools::schedule_template_generator {
/*!
 * \brief The ScheduleClub class represents a club within ScheduleTemplateGenerator
 */
class ScheduleClub
{
public:
    ScheduleClub(const qint32 generator_club_id = 0, const qint32 encoded_division_club_id = 0);

    // Get data - ids
    inline qint32 clubId() const { return generator_club_id_; }
    inline qint32 clubEncodedId() const { return encoded_division_club_id_; }

    // Get data - scheduling
    bool hasGamesToAllocate() const;
    std::pair<qint32, qint32> take();

    // Home game counts for schedule generation - get data
    qint32 homeGameCount() const;
    qint32 homeGameCount(const qint32 club_id) const;
    void initHomeGameCounts(const qint32 club_count, const qint32 default_games_played);
    void resetUnallocatedHomeGames();
    qint32 unallocatedHomeGameCount() const;

    // Home game counts for schedule generation - set data
    void setHomeGameCount(const qint32 club_id, const qint32 home_game_count);

    // Set data
    inline void setClubEncodedId(const qint32 encoded_division_club_id)
    {
        encoded_division_club_id_ = encoded_division_club_id;
    }

    // Operator overloading
    inline auto operator<=>(const ScheduleClub &rhs) const
    {
        return clubEncodedId() <=> rhs.clubEncodedId();
    }
    inline bool operator==(const ScheduleClub &rhs) const
    {
        return clubEncodedId() == rhs.clubEncodedId();
    }

    enum ENUM_FLAGS { INVALID_CLUB_ID = -1, PAIR_ROAD_CLUB_INDEX = 0, PAIR_HOME_CLUB_INDEX = 1 };

private:
    // Ids
    qint32 generator_club_id_{0};
    qint32 encoded_division_club_id_{0};

    // Get data - scheduling
    std::pair<qint32, qint32> take(const qint32 road_club_id);

    // Home game counts
    std::vector<qint32> game_counts_;       // Total number of home games to play vs each club
    std::vector<qint32> unallocated_games_; // Number of home games remaining to be allocated

    // Scheduling
    qint32 nextClubToTake();
    qint32 next_club_to_take_{0};
};
} // namespace ehm_dal::tools::schedule_template_generator
