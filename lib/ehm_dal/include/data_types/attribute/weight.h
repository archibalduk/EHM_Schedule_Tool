#pragma once

// Application headers
#include "include/data_types/attribute/attribute.h"

namespace ehm_dal::data_types {
/*!
 * \brief The Weight class stores weight in kilograms
 */
class Weight : public Attribute<quint8>
{
public:
    Weight(quint8 weight_kilograms = 0);

private:
    inline constexpr quint8 upperLimit() const override { return 255; }
};

} // namespace ehm_dal::data_types
