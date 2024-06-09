#pragma once

// Application headers
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

namespace parser {
class ScheduleTemplateParser
{
public:
    ScheduleTemplateParser();

    // Get data
    inline std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
    schedule()
    {
        return schedule_;
    }

    // Parsing
    bool parse(const QString &file_path);
    bool parse(ehm_dal::spreadsheet::Spreadsheet &sheet);

private:
    // Get data
    qint32 defaultStartYear() const;

    // Schedule
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;

    enum ENUM_COLUMNS { ROAD_TEAM, HOME_TEAM, DAY_OF_MONTH, MONTH, YEAR_OFFSET, COLUMN_COUNT };
    enum ENUM_FLAGS { HEADER_ROW_COUNT = 2, MAY_MONTH_NUMBER = 5 };
};
} // namespace parser
