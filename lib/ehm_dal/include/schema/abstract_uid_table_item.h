#pragma once

// Application headers
#include "include/schema/abstract_table_item.h"

namespace ehm_dal::schema {
/*!
 * \brief The AbstractUidTableItem class represents a row in a Table with id and uid fields.
 */
class AbstractUidTableItem : public AbstractTableItem
{
public:
    AbstractUidTableItem();

    // Get data
    inline qint32 uid() const override { return uid_; }

protected:
    qint32 uid_; // Unique id
};

} // namespace ehm_dal::schema
