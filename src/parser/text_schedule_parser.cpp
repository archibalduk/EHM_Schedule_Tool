#include "text_schedule_parser.h"

// Qt headers
#include <QDate>

using namespace parser;

TextScheduleParser::TextScheduleParser()
    : schedule_(
        std::make_shared<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>())
{}

// --- Add a club to the club hash table --- //
qint32 TextScheduleParser::addClub(const QString &club_name)
{
    const auto id{static_cast<qint32>(club_list_.size())};
    club_list_.insert(club_name, id);
    schedule_->addClub(id);

    return id;
}

// --- Parse the selected file (QString file path/name) --- //
bool TextScheduleParser::parse(const QString &file_path)
{
    ehm_dal::spreadsheet::Spreadsheet sheet(file_path);
    return parse(sheet);
}

// --- Parse the selected file (Spreadsheet) --- //
bool TextScheduleParser::parse(ehm_dal::spreadsheet::Spreadsheet &sheet)
{
    schedule_->reset();

    sheet.setHeaderCount(header_row_count_);

    if (!sheet.read())
        return false;

    const auto row_count{sheet.rowCount()};
    for (auto i = 0; i < row_count; ++i)
        parseRow(sheet, i);

    return true;
}

// --- Parse/find a club --- //
qint32 TextScheduleParser::parseClub(const QString &club_name)
{
    const auto target_club{club_name.simplified().toLower()};

    if (target_club.isEmpty())
        return NO_RESULT;

    const auto result{club_list_.value(target_club, NO_RESULT)};

    if (result != NO_RESULT)
        return result;

    return addClub(target_club);
}

// --- Parse a spreadsheet row --- //
void TextScheduleParser::parseRow(const ehm_dal::spreadsheet::Spreadsheet &sheet, const qint32 row)
{
    const auto home_club{parseClub(sheet.cell(row, homeClubColumnId()).toString())};
    const auto road_club{parseClub(sheet.cell(row, roadClubColumnId()).toString())};
    const auto date{sheet.cell(row, dateColumnId()).toDate()};

    if (home_club == NO_RESULT || road_club == NO_RESULT) {
        return;
    }

    schedule_->addGame(road_club, home_club, date);
}
