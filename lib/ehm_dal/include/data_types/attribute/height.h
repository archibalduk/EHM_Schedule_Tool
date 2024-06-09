#pragma once

// Application headers
#include "include/data_types/attribute/attribute.h"

namespace ehm_dal::data_types {
/*!
 * \brief The Height class stores height in centimetres
 */
class Height : public Attribute<quint8>
{
public:
    Height(quint8 height_centimetres = 0);

    /*!
     * \brief Returns the height in metres.
     */
    double toMetres() const;

private:
    inline constexpr quint8 upperLimit() const override { return 255; }
};

} // namespace ehm_dal::data_types
