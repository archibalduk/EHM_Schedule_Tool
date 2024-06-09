#pragma once

// Application headers
#include "include/database/pointer/pointer.h"
#include "include/database/pointer/pointer_flags.h"

// Qt headers
#include <QString>

namespace ehm_dal::data_types {

// --- Name record pointer with text buffer --- //
class NamePointer : public Pointer
{
public:
    NamePointer();
    NamePointer(const ehm_dal::tables::TableIndex table_id,
                const qint32 record_id = PointerFlags::NULL_POINTER);
    virtual ~NamePointer();

    // Get data
    inline QString text() const override { return name_buffer_; }

    // Initialisation
    void init() override;

private:
    QString name_buffer_;
};
} // namespace ehm_dal::data_types

