#pragma once

// Qt headers
#include <QDate>
#include <memory>

// --- Schedule generator game item --- //
namespace ehm_dal::tools::schedule_template_generator {

class ScheduleClub;

/*!
 * \brief The ScheduleGame class represents a game within ScheduleTemplateGenerator
 */
class ScheduleGame
{
public:
    ScheduleGame();

    // Get data
    inline QDate date() const { return date_; }
    qint32 homeClubEncodedId() const;
    qint32 roadClubEncodedId() const;

    // Set data
    inline void addDays(const qint32 days) { date_ = date_.addDays(days); }
    void set(const std::shared_ptr<ScheduleClub> road_club,
             const std::shared_ptr<ScheduleClub> home_club,
             const QDate &date);
    inline void setDate(const QDate &date) { date_ = date; }
    inline void setYear(const qint32 year) { date_.setDate(year, date_.month(), date_.day()); }

private:
    // Clubs
    std::shared_ptr<ScheduleClub> home_club_;
    std::shared_ptr<ScheduleClub> road_club_;

    // Date
    QDate date_;

    enum ENUM_FLAGS { INVALID = -1 };
};
} // namespace ehm_dal::tools::schedule_template_generator
