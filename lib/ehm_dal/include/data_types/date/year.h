#pragma once

// Application headers
#include "include/data_types/data_type.h"

// Qt headers
class QString;
#include <type_traits>

namespace ehm_dal::data_types {
template<class T>
concept Short = std::is_same_v<qint16, T> || std::is_same_v<quint16, T>;

/*!
 * \brief The Year class represents a calendar year value. Only qint16 and quint16 are permissible.
 */
template<Short T>
class Year : public DataType<T>
{
public:
    enum ENUM_FLAGS {
        INVALID_YEAR = 1900,
        MINIMUM_YEAR = 0,
        MAXIMUM_YEAR = 2899 // This will prevent typos (e.g. 2900 instead of 1900)
    };

    Year(const T value = INVALID_YEAR);

    // Compare data
    /*!
     * \brief Compares the current value with `year`.
     * \param year the year to be compared with
     */
    bool compare(const QString &year) const;

    // Get data
    /*!
     * \brief Returns whether the year is invalid (i.e. <= 1900). 
     */
    inline bool isInvalid() const { return !isValid(); }
    /*!
     * \brief Returns whether the year is valid (i.e. > 1900). 
     */
    inline bool isValid() const { return (this->value() > INVALID_YEAR); }
    /*!
     * \brief Returns whether the year is >= `min` and <= `max`
     * \param min minimum year value
     * \param max maximum year value
     */
    bool isWithinRange(const qint32 min, const qint32 max) const;

    // Set data
    /*!
     * \brief Adjusts the year by `adjustment amount`.
     * \param adjustment_amount the amount by which to adjust the year
     * \param allow_pre_1901_years allow the year to be adjusted below 1901
     */
    void adjust(const qint32 adjustment_amount, const bool allow_pre_1901_years = false);
    /*!
     * \brief Resets the year to its default invalid value of `ENUM_FLAGS::INVALID_YEAR`.
     */
    inline void reset() { this->setData(INVALID_YEAR, Qt::EditRole); }
    /*!
     * \brief Sets the year to `comparator` if `comparator` is greater than the present value.
     * \param comparator the reference year
     */
    void setIfLater(const Year &comparator);
    /*!
     * \brief Sets the year to `year` if `year` is valid
     * \param year the reference year
     */
    void validate(const qint32 year);
};
} // namespace ehm_dal::data_types
