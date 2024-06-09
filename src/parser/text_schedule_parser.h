#pragma once

// Application headers
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

// Qt headers
#include <QHash>
#include <QString>

namespace parser {

class TextScheduleParser
{
public:
    TextScheduleParser();

    // Get data
    inline QHash<QString, qint32> clubNames() const { return club_list_; }

    inline std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
    schedule()
    {
        return schedule_;
    }

    // Parsing
    bool parse(const QString &file_path);
    bool parse(ehm_dal::spreadsheet::Spreadsheet &sheet);

    // Settings - get data
    inline qint32 dateColumnId() const { return date_column_id_; }
    inline qint32 headerRowCount() const { return header_row_count_; }
    inline qint32 homeClubColumnId() const { return home_club_column_id_; }
    inline qint32 roadClubColumnId() const { return road_club_column_id_; }

    // Settings - set data
    inline void setDateColumnId(const qint32 date_column_id) { date_column_id_ = date_column_id; }
    inline void setHeaderRowCount(const qint32 header_row_count)
    {
        header_row_count_ = header_row_count;
    }
    inline void setHomeClubColumnId(const qint32 home_club_column_id)
    {
        home_club_column_id_ = home_club_column_id;
    }
    inline void setRoadClubColumnId(const qint32 road_club_column_id)
    {
        road_club_column_id_ = road_club_column_id;
    }

private:
    // Clubs
    QHash<QString, qint32> club_list_;
    qint32 addClub(const QString &club_name);

    // Flags
    enum ENUM_FLAGS { NO_RESULT = -1 };

    // Parsing
    qint32 parseClub(const QString &club_name);
    void parseRow(const ehm_dal::spreadsheet::Spreadsheet &sheet, const qint32 row);

    // Schedule
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;

    // Settings
    enum ENUM_DEFAULT_SETTINGS {
        DEFAULT_ROAD_CLUB_COLUMN_ID = 0,
        DEFAULT_HOME_CLUB_COLUMN_ID = 1,
        DEFAULT_DATE_COLUMN_ID = 2,
        DEFAULT_HEADER_ROW_COUNT = 1
    };

    qint32 date_column_id_{DEFAULT_DATE_COLUMN_ID};
    qint32 header_row_count_{DEFAULT_HEADER_ROW_COUNT};
    qint32 home_club_column_id_{DEFAULT_HOME_CLUB_COLUMN_ID};
    qint32 road_club_column_id_{DEFAULT_ROAD_CLUB_COLUMN_ID};
};
} // namespace parser
