#pragma once

// Application headers
#include "src/parser/text_schedule_parser.h"
#include "src/ui/parser/private/abstract_parser_ui.h"

namespace parser_ui {

class TextScheduleParserUi : public AbstractParserUi
{
public:
    TextScheduleParserUi();

    // Parsing
    bool parse() override;

    // Schedule data
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule()
        override;

private:
    // Club editing
    qint32 showClubEditor();

    // File i/o
    bool open() override;

    // Parsing
    parser::TextScheduleParser parser_;
};
} // namespace parser_ui
