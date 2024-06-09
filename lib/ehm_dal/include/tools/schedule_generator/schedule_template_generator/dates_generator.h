#pragma once

// Qt headers
#include <QDate>

// --- Schedule template dates generator --- //
namespace ehm_dal::tools::schedule_template_generator {
/*!
 * \brief The DatesGenerator class generates dates for a schedule template
 */
class DatesGenerator
{
public:
    DatesGenerator(const QDate &start_date, const QDate &end_date);

    // Dates
    QDate date(const qint32 index);

    // Day priorities (Mon -> Sun)
    void setDayPriorities(const qint32 mon,
                          const qint32 tue,
                          const qint32 wed,
                          const qint32 thu,
                          const qint32 fri,
                          const qint32 sat,
                          const qint32 sun);
    void setDayPriorities(const std::vector<qint32> &day_priorities);

    // Excluded date range (e.g. Olympics)
    void setExcludedDateRange(const QDate &excluded_start_date, const QDate &excluded_end_date);

    // Generator
    bool generate(const qint32 target_dates_count);

    // Get data
    inline qint32 count() const { return static_cast<qint32>(schedule_dates_.size()); }

private:
    // Dates
    std::vector<QDate> schedule_dates_;

    // Date cache
    std::vector<std::vector<QDate>> date_cache_;
    void populateCache();
    void populateCache(std::vector<QDate> &cache, Qt::DayOfWeek day);
    void tidyUpCache(std::vector<QDate> &cache);

    // Date picking
    void addDate(std::vector<QDate> &cache, const qint32 index);
    bool isValidDate(const QDate &date) const;
    void pickDates(std::vector<QDate> &cache, const qint32 step);

    // Date range
    qint32 target_dates_count_{0};
    QDate start_date_;
    QDate end_date_;
    QDate excluded_start_date_; // Excluded date period (e.g. during the Olympics)
    QDate excluded_end_date_;

    inline bool areMoreDatesRequired() const { return count() < target_dates_count_; }
    inline bool hasSufficientDates() const { return !areMoreDatesRequired(); }

    // Days
    enum ENUM_DAYS {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY,
        DAY_COUNT,
        DAYS_IN_A_WEEK = DAY_COUNT
    };

    inline qint32 dayToIndex(const Qt::DayOfWeek day) const { return static_cast<qint32>(day) - 1; }
    inline Qt::DayOfWeek indexToDay(const ENUM_DAYS index) const
    {
        return static_cast<Qt::DayOfWeek>(index + 1);
    }

    // Day priorities (Mon -> Sun)
    std::vector<std::pair<ENUM_DAYS, qint32>> day_priority_list_;

    // Generator
    bool generateDates(const auto &step_calculation_lambda);
};
} // namespace ehm_dal::tools::schedule_template_generator
