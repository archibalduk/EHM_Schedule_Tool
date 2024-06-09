#include "abstract_parser_ui.h"

using namespace parser_ui;

AbstractParserUi::AbstractParserUi() {}

/* ================= */
/*      Parsing      */
/* ================= */

// --- Default parsing function to be sub-classed where there are multiple screens/prompts --- //
bool AbstractParserUi::parse()
{
    return open();
}
