#pragma once

// Application headers
#include "include/data_types/data_type.h"

namespace ehm_dal::data_types {
/*!
 * \brief The Attribute class is a template class for attribute-like values with lower and upper limit values.
 */
template<class T>
class Attribute : public DataType<T>
{
public:
    Attribute(const T value = 0);

    // Set data
    // CRASH making DataType:: setData() a virtual function appears to corrupt the vtable
    // TODO consider how to implement Attribute::setData in light of the above crash given that
    // attributes need to have a lowerLimit() and an upperLimit()
    // void setData(const QVariant &value, const qint32 role = Qt::EditRole) override;

private:
    inline virtual constexpr T lowerLimit() const { return static_cast<T>(0); }
    inline virtual constexpr T upperLimit() const { return static_cast<T>(20); }
};

/* ========================= */
/*      Attribute (0-20)     */
/* ========================= */

template<class T>
Attribute<T>::Attribute(const T value)
    : DataType<T>(value)
{}

/* ================= */
/*      Set Data     */
/* ================= */
/*
template<class T>
void Attribute<T>::setData(const QVariant &value, const qint32 role)
{
    if (role != Qt::EditRole)
        return;

    // Convert to qint64 to ensure the underlying value is not truncated
    const auto new_value{static_cast<T>(value.toLongLong())};

    if (new_value < lowerLimit())
        this->setValue(lowerLimit());
    else if (new_value > upperLimit())
        this->setValue(upperLimit());
    else
        this->setValue(new_value);
}
*/
} // namespace ehm_dal::data_types
