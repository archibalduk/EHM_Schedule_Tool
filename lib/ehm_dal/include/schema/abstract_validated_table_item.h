#pragma once

// Application headers
#include "include/schema/abstract_table_item.h"

namespace ehm_dal::schema {
/*!
 * \brief The AbstractValidatedTableItem is an AbstractTableItem with a validator
 */
class AbstractValidatedTableItem : public AbstractTableItem
{
public:
    AbstractValidatedTableItem();
    // TODO implement validator
    // See comments in abstract_validated_uid_table_item.h
};

} // namespace ehm_dal::schema
