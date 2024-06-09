#include "schedule_template_parser.h"

// Qt headers
#include <QDate>

using namespace parser;
ScheduleTemplateParser::ScheduleTemplateParser()
    : schedule_(
        std::make_shared<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>())
{}

qint32 ScheduleTemplateParser::defaultStartYear() const
{
    const auto date{QDate::currentDate()};

    // If the current date is earlier than May (i.e. mid-season) then use the previous year as the start year
    if (date.month() < MAY_MONTH_NUMBER)
        return date.year() - 1;

    return date.year();
}

bool ScheduleTemplateParser::parse(const QString &file_path)
{
    ehm_dal::spreadsheet::Spreadsheet sheet(file_path);
    return parse(sheet);
}

bool ScheduleTemplateParser::parse(ehm_dal::spreadsheet::Spreadsheet &sheet)
{
    schedule_->reset();
    schedule_->setStartYear(defaultStartYear());

    sheet.setHeaderCount(HEADER_ROW_COUNT);

    if (!sheet.read())
        return false;

    sheet.printDiagnosticData();

    const auto row_count{sheet.rowCount()};
    for (auto i = 0; i < row_count; ++i) {
        if (sheet.columnCount(i) < COLUMN_COUNT)
            continue;

        schedule_->addGameFromEncodedId(sheet.cell(i, ROAD_TEAM).toInt(),
                                        sheet.cell(i, HOME_TEAM).toInt(),
                                        sheet.cell(i, DAY_OF_MONTH).toInt(),
                                        sheet.cell(i, MONTH).toInt(),
                                        sheet.cell(i, YEAR_OFFSET).toInt());
    }

    return true;
}
