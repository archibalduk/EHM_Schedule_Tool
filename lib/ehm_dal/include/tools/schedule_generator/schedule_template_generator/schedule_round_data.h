#pragma once

// Application headers
#include "include/tools/schedule_generator/schedule_template_generator/dates_generator.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_club.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_game_table.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_round.h"

// Qt headers
#include <vector>

// --- Draft schedule round data --- //
namespace ehm_dal::tools::schedule_template_generator {
/*!
 * \brief The ScheduleRoundData class contains a draft schedule consisting of round data 
 * which can then be converted into a dated schedule template
 */
class ScheduleRoundData
{
public:
    ScheduleRoundData();

    // Add data
    bool add(std::pair<qint32, qint32> &game);

    // Debugging / diagnostics
    void printDiagnosticData() const;

    // Get data
    inline qint32 count() const { return static_cast<qint32>(rounds_.size()); }

    // Scheduling
    bool allocate(ScheduleGameTable &schedule,
                  DatesGenerator &dates,
                  const std::vector<std::shared_ptr<ScheduleClub> > &clubs);

private:
    std::vector<ScheduleRound> rounds_;
};
} // namespace ehm_dal::tools::schedule_template_generator
