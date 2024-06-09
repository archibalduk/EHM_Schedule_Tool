#pragma once

// Application headers
#include "include/data_types/attribute/attribute.h"

namespace ehm_dal::data_types {
/*!
 * \brief The Reputation10000 class is a template class for 0-10,000 reputation attribute ranges.
 */
template<class T>
class Reputation10000 : public Attribute<T>
{
public:
    Reputation10000(const T value = 0)
        : Attribute<T>(value)
    {}

private:
    inline constexpr T upperLimit() const override { return static_cast<T>(10000); }
};

} // namespace ehm_dal::data_types
