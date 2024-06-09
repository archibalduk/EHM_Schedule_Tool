#pragma once

// Application headers
#include "include/database/pointer/pointer_flags.h"
#include "include/database/pointer/private/abstract_pointer.h"
#include "include/tables/abstract_table.h"
#include "include/tables/table_index.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::data_types {

// --- Database/AbstractTableItem record pointer --- //
class Pointer : public ehm_dal::data_types::
                AbstractPointer<qint32, ehm_dal::tables::TableIndex, ehm_dal::tables::AbstractTable>
{
public:
    Pointer();
    Pointer(const ehm_dal::tables::TableIndex table_id,
            const qint32 record_id = PointerFlags::NULL_POINTER);
    virtual ~Pointer();

    // File i/o
    void readFromShort(QDataStream &in);
    void writeToShort(QDataStream &out) const;

    // Get data - pointer
    using AbstractPointer::data;
    QVariant data(const qint32 column, qint32 role) const override;
    qint32 id() const override;
    QString text() const override;

    // Get data - table
    std::shared_ptr<ehm_dal::tables::AbstractTable> constTable() const override;
    std::shared_ptr<ehm_dal::tables::AbstractTable> table() override;

    // Initialisation
    virtual void init();

    // Set data
    void setData(const QVariant &value, const qint32 role) override;

private:
    std::weak_ptr<ehm_dal::schema::AbstractTableItem> ptr_;

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, Pointer &data);
    friend QDataStream &operator<<(QDataStream &out, const Pointer &data);

    // Initialisation
    void initPointer();
};

// File i/o
QDataStream &operator>>(QDataStream &in, Pointer &data);
QDataStream &operator<<(QDataStream &out, const Pointer &data);

} // namespace ehm_dal::data_types


