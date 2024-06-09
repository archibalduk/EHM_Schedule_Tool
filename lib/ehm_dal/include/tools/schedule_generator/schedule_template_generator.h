#pragma once

// Application headers
#include "include/spreadsheet/spreadsheet.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_club.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_game_table.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_matrix.h"

// Qt headers
class QDate;
#include <memory>
#include <vector>

namespace ehm_dal::tools::schedule_template_generator {

// --- Schedule template generator --- //
/*!
 * \brief The ScheduleTemplateGenerator class generates EHM schedule templates
 */
class ScheduleTemplateGenerator
{
public:
    ScheduleTemplateGenerator();

    // Clubs
    qint32 addClub(const qint32 encoded_division_club_id);
    void addDivision(const qint32 division_id,
                     const qint32 club_count,
                     const qint32 first_club_id = 0);
    std::shared_ptr<ScheduleClub> club(const qint32 club_id);
    std::shared_ptr<ScheduleClub> clubFromEncodedId(const qint32 club_encoded_id);
    inline qint32 clubCount() const { return static_cast<qint32>(clubs_.size()); }
    std::shared_ptr<ScheduleClub> findOrAddClub(const qint32 club_encoded_id);
    bool isValidClubId(const qint32 club_id) const;
    std::vector<std::shared_ptr<ScheduleClub>> sortedClubList();

    // Dates
    inline void addDays(const qint32 days) { games_.addDays(days); }
    inline qint32 generatedDateCount() const { return generated_date_count_; }
    inline qint32 generatedRoundCount() const { return generated_round_count_; }

    // Export data
    bool exportSchedule();
    bool exportSchedule(ehm_dal::spreadsheet::Spreadsheet &sheet);

    // Games
    void addGame(const qint32 road_club_id, const qint32 home_club_id, const QDate &date);
    void addGame(const qint32 road_club_id,
                 const qint32 home_club_id,
                 const qint32 day_of_month,
                 const qint32 month,
                 const qint32 year_offset);
    void addGameFromEncodedId(const qint32 road_club_encoded_id,
                              const qint32 home_club_encoded_id,
                              const qint32 day_of_month,
                              const qint32 month,
                              const qint32 year_offset);
    inline const ScheduleGameTable *games() { return &games_; };
    void printGame(const qint32 game_id);

    // Generator
    bool generate(const QDate &start_date,
                  const QDate &end_date,
                  const std::vector<qint32> &day_priorities,
                  const QDate &exclusion_range_start_date = QDate(),
                  const QDate &exclusion_range_end_date = QDate());
    std::unique_ptr<ScheduleMatrix> matrix(const qint32 default_games_played_count = 1);
    std::unique_ptr<ScheduleMatrix> matrix(spreadsheet::Spreadsheet &sheet);

    // Reset
    void reset();

    // Start year
    inline void setStartYear(const qint32 start_year) { games_.setStartYear(start_year); }
    inline qint32 startYear() const { return games_.startYear(); }

private:
    std::vector<std::shared_ptr<ScheduleClub>> clubs_;
    ScheduleGameTable games_;
    qint32 generated_date_count_{0};
    qint32 generated_round_count_{0};

    // Clubs
    qint32 toEncodedDivisionClubId(const qint32 division_id, const qint32 club_id) const;

    // Generator
    void initClubGameCounts(const qint32 default_games_played_count);
    void resetClubUnallocatedGames();
    qint32 unallocatedGameCount() const;

    // Settings
    qint32 generate_iteration_limit_{2000};
};
} // namespace ehm_dal::tools::schedule_template_generator
