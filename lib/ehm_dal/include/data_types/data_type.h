#pragma once

// Qt headers
#include <QDataStream>
#include <QLocale>
#include <QVariant>
#include <type_traits>

namespace ehm_dal::data_types {
template<class T>
concept Number = std::is_integral<T>::value || std::is_floating_point<T>::value;

/*!
 * \brief The DataType class is a template class for all C++ integral and floating point data types.
 */
template<Number T>
class DataType
{
public:
    DataType(const T value = 0);
    // NOTE making DataType virtual in any manner results in vtable corruption
    //virtual ~DataType() = default;

    // Get data
    /*!
     * \brief Returns the data stored under the given `role` for the item.
     * \param role typically `Qt::DisplayRole` or `Qt::EditRole`
     */
    QVariant data(const qint32 role = Qt::DisplayRole) const;
    /*!
     * \brief Returns the raw value which can otherwise be accessed via `QVariant data(const qint32 role)`.
     */
    inline T value() const { return value_; }

    // Get data - decimals
    // TODO <float> results in inaccurate decimal values (see e.g. Continent::RegionalStrength)
    /*!
     * \brief Returns the decimal value to as many decimal places as possible.
     * \param role typically `Qt::DisplayRole` or `Qt::EditRole`
     */
    QVariant accurateDecimal(const qint32 role = Qt::DisplayRole) const;
    /*!
     * \brief Returns the decimal value rounded to 8 decimal places. This is useful when converting a double to a float.
     * \param role typically `Qt::DisplayRole` or `Qt::EditRole`
     */
    QVariant roundedDecimal(const qint32 role = Qt::DisplayRole) const;
    /*!
     * \brief Returns the value as a double.
     */
    double toDouble() const;
    /*!
     * \brief Returns the value as a float.
     */
    float toFloat() const;

    // Operator overloading: Comparators
    // TODO replace with spaceship operator
    inline bool operator==(const DataType &rhs) const { return value() == rhs.value(); }
    inline bool operator==(const qint32 rhs) const { return static_cast<qint32>(value()) == rhs; }
    inline bool operator!=(const DataType &rhs) const { return !operator==(rhs); }
    inline bool operator!=(const qint32 rhs) const { return !operator==(rhs); }
    inline bool operator<(const DataType &rhs) const { return value() < rhs.value(); }
    inline bool operator<(const qint32 rhs) const { return static_cast<qint32>(value()) < rhs; }
    inline bool operator>(const DataType &rhs) const { return rhs < *this; }
    inline bool operator>(const qint32 rhs) const { return rhs < static_cast<qint32>(value()); }

    // Set data
    Q_DECL_DEPRECATED void set(const QVariant &value, const qint32 role = Qt::EditRole);
    // BUG making setData() a virtual function appears to corrupt the vtable
    /*!
     * \brief Sets the `role` data for the item at to `value`.
     * \param value
     * \param role
     */
    void setData(const QVariant &value, const qint32 role = Qt::EditRole);
    /*!
     * \brief Sets the value to `value`
     * \param value
     */
    inline void setValue(const T value) { value_ = value; }

private:
    T value_;

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, DataType<T> &data)
    {
        in.readRawData(reinterpret_cast<char *>(&data.value_), sizeof(T));
        return in;
    }
    friend QDataStream &operator<<(QDataStream &out, const DataType<T> &data)
    {
        out.writeRawData(reinterpret_cast<const char *>(&data.value_), sizeof(T));
        return out;
    }
};

/* ================== */
/*      Data Type     */
/* ================== */

template<Number T>
DataType<T>::DataType(const T value)
    : value_(value)
{}

/* ================= */
/*      Get Data     */
/* ================= */

template<Number T>
QVariant DataType<T>::data(const qint32 role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return value_;
    default:
        return QVariant();
    }
}

/* ============================ */
/*      Get Data - Decimals     */
/* ============================ */

template<Number T>
QVariant DataType<T>::accurateDecimal(const qint32 role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QLocale().toString(value_);

    return QVariant();
}

template<Number T>
QVariant DataType<T>::roundedDecimal(const qint32 role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if constexpr (std::is_floating_point_v<T>)
        return QLocale().toString(value_, 'g', 8);

    return QString::number(0.0);
}

template<Number T>
double DataType<T>::toDouble() const
{
    return static_cast<double>(value_);
}

template<Number T>
float DataType<T>::toFloat() const
{
    return static_cast<float>(value_);
}

/* ================= */
/*      Set Data     */
/* ================= */

// TODO deprecate this function in favour of setData()
template<Number T>
void DataType<T>::set(const QVariant &value, const qint32 role)
{
    setData(value, role);
}

template<Number T>
void DataType<T>::setData(const QVariant &value, const qint32 role)
{
    if (role != Qt::EditRole)
        return;

    if constexpr (std::is_floating_point_v<T>)
        setValue(static_cast<T>(value.toDouble()));
    else if constexpr (std::is_unsigned_v<T>)
        setValue(static_cast<T>(value.toUInt()));
    else
        setValue(static_cast<T>(value.toInt()));
}

} // namespace ehm_dal::data_types
