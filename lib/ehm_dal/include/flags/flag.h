#pragma once


// Application headers
#include "flag_index.h"
#include "include/database/pointer/private/abstract_pointer.h"
#include "include/flags/flag_database.h"
#include "include/flags/flag_table.h"

namespace ehm_dal::flags {

// --- Flag pointer base class --- //
template<typename T_DataType>
class Flag : public ehm_dal::data_types::
                 AbstractPointer<T_DataType, ehm_dal::flags::FlagIndex, ehm_dal::flags::FlagTable>
{
public:
    Flag(); // TODO fix magic number -1 below
    Flag(const ehm_dal::flags::FlagIndex flag_table_id, const qint32 record_id = -1);

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, ehm_dal::flags::Flag<T_DataType> &data)
    {
        in >> data.id_;
        return in;
    }

    friend QDataStream &operator<<(QDataStream &out, const ehm_dal::flags::Flag<T_DataType> &data)
    {
        out << data.id();
        return out;
    }

    // Get data
    QString text() const override;

    // Get data - table
    std::shared_ptr<ehm_dal::flags::FlagTable> constTable() const override;
    std::shared_ptr<ehm_dal::flags::FlagTable> table() override;
};

} // namespace ehm_dal::flags


