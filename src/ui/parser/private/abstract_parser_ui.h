#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"

namespace parser_ui {
class AbstractParserUi
{
public:
    AbstractParserUi();
    virtual ~AbstractParserUi() = default;

    // Parsing
    virtual bool parse();

    // Schedule data
    virtual std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator>
    schedule() = 0;

private:
    // File i/o
    virtual bool open() = 0;
};
} // namespace parser_ui
