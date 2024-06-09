#pragma once

// Application headers
#include "include/data_types/attribute/attribute.h"

namespace ehm_dal::data_types {
/*!
 * \brief The Reputation200 class is a template class for 0-200 reputation attribute ranges.
 */
template<class T>
class Reputation200 : public Attribute<T>
{
public:
    Reputation200(const T value = 0)
        : Attribute<T>(value)
    {}

private:
    inline constexpr T upperLimit() const override { return static_cast<T>(200); }
};

} // namespace ehm_dal::data_types
