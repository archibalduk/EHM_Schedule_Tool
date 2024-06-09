#pragma once

// Application headers
#include "include/tools/schedule_generator/schedule_template_generator/schedule_club.h"
#include "include/tools/schedule_generator/schedule_template_generator/schedule_game_table.h"

// Qt headers
#include <QtGlobal>
#include <vector>

// --- Schedule round --- //
namespace ehm_dal::tools::schedule_template_generator {
/*!
 * \brief The ScheduleRound class represents a single round of games
 */
class ScheduleRound
{
public:
    ScheduleRound();

    // Add data
    bool add(std::pair<qint32, qint32> &game);

    // Debugging / diagnostics
    void printDiagnosticData() const;

    // Get data
    bool contains(const qint32 club_id) const;
    qint32 count() const;

    // Scheduling
    void allocate(ScheduleGameTable &schedule,
                  const QDate &date,
                  const std::vector<std::shared_ptr<ScheduleClub>> &clubs);

    // Operator overloading
    inline auto operator<=>(const ScheduleRound &rhs) const { return count() <=> rhs.count(); }
    inline bool operator==(const ScheduleRound &rhs) const { return count() == rhs.count(); }

private:
    std::vector<std::pair<qint32, qint32>> games_;
};
} // namespace ehm_dal::tools::schedule_template_generator
