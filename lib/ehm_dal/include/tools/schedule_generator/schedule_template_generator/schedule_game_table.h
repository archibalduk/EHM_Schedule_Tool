#pragma once

// Application headers
#include "include/tools/schedule_generator/schedule_template_generator/schedule_game.h"

// Qt headers
#include <QAbstractTableModel>
#include <QDate>
#include <memory>

// --- Schedule generator game table --- //
namespace ehm_dal::tools::schedule_template_generator {

class ScheduleClub;

/*!
 * \brief The ScheduleGameTable class is a container for `ScheduleGame`s
 */
class ScheduleGameTable : public QAbstractTableModel
{
public:
    ScheduleGameTable();

    // Add data
    void addGame(const std::shared_ptr<ScheduleClub> road_club,
                 const std::shared_ptr<ScheduleClub> home_club,
                 const QDate &date);

    // Get data - counts
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Get data - dates
    qint32 dateCount() const;
    QDate endDate() const;
    QDate startDate() const;

    // Get data - game counts
    inline qint32 gameCount() const { return rowCount(); } // Convenience function
    qint32 gameCount(const std::shared_ptr<ScheduleClub> &road_club,
                     const std::shared_ptr<ScheduleClub> &home_club) const;
    qint32 gameCount(const qint32 road_club_encoded_id, const qint32 home_club_encoded_id) const;
    qint32 gameCountAllMatchups(const std::shared_ptr<ScheduleClub> &club_a,
                                const std::shared_ptr<ScheduleClub> &club_b) const;
    qint32 gameCountAllMatchups(const qint32 club_a_encoded_id,
                                const qint32 club_b_encoded_id) const;
    qint32 gameCountAllMatchups(const std::shared_ptr<ScheduleClub> &club) const;
    qint32 gameCountAllMatchups(const qint32 club_encoded_id) const;
    qint32 gameCountHome(const std::shared_ptr<ScheduleClub> &home_club) const;
    qint32 gameCountHome(const qint32 home_club_encoded_id) const;
    qint32 gameCountRoad(const std::shared_ptr<ScheduleClub> &road_club) const;
    qint32 gameCountRoad(const qint32 road_club_encoded_id) const;

    // Get data - games
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;

    // Reset
    void reset();

    // Set data
    void addDays(const qint32 days);
    void setStartYear(const qint32 start_year);
    // bool setData(const QModelIndex &index, const QVariant &value, qint32 role = Qt::EditRole) override;

    // Start year
    inline qint32 startYear() const { return start_year_; }

    // Column flags
    enum ENUM_COLUMNS {
        ROAD_TEAM_ENCODED_ID,
        HOME_TEAM_ENCODED_ID,
        DATE,
        DAY_OF_MONTH,
        MONTH,
        YEAR_OFFSET,
        COLUMN_COUNT
    };

private:
    std::vector<ScheduleGame> data_;

    // Start year
    enum ENUM_FLAGS { DEFAULT_START_YEAR };
    qint32 start_year_{DEFAULT_START_YEAR};

    void validateYear(const qint32 year);
};
} // namespace ehm_dal::tools::schedule_template_generator
