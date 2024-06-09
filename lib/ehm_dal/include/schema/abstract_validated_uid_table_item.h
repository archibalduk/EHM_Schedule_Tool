#pragma once

// Application headers
#include "include/schema/abstract_uid_table_item.h"

namespace ehm_dal::schema {
/*!
 * \brief The AbstractValidatedUidTableItem is an AbstractUidTableItem with a validator
 */
class AbstractValidatedUidTableItem : public AbstractUidTableItem
{
public:
    AbstractValidatedUidTableItem();
    // TODO implement validator
    // Consider a validation class/pointer which sits as a member of this class in order
    // to avoid masses of duplication between this class and AbstractValidatedTableItem.
    // Alternatively, both classes could inherit from some validation class.
};

} // namespace ehm_dal::schema
