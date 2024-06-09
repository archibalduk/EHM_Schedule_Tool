#pragma once

// Application headers
#include "src/parser/schedule_template_parser.h"
#include "src/ui/parser/private/abstract_parser_ui.h"

namespace parser_ui {
class ScheduleTemplateParserUi : public AbstractParserUi
{
public:
    ScheduleTemplateParserUi();

    // Schedule data
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule()
        override;

private:
    // File i/o
    bool open() override;

    // Parsing
    parser::ScheduleTemplateParser parser_;
};
} // namespace parser_ui
