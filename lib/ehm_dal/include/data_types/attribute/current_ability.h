#pragma once

// Application headers
#include "include/data_types/attribute/reputation_200.h"

namespace ehm_dal::data_types {
/*!
 * \brief The CurrentAbility class is a qint16 class for 0-200 current ability ranges.
 * \details This inherits from `Reputation200` as they are essentially the same and simply have separate class names for clarity 
 */
class CurrentAbility : public Reputation200<qint16>
{
public:
    CurrentAbility(const qint16 value = 0)
        : Reputation200<qint16>(value)
    {}
};

} // namespace ehm_dal::data_types
