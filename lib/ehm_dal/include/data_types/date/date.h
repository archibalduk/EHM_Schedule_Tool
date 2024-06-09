#pragma once

// Application headers
#include "include/data_types/private/abstract_data_type.h"

// Qt headers
class QDataStream;
#include <QDate>

namespace ehm_dal::data_types {

// --- SI_Date wrapper --- //
/*!
 * \brief The Date class acts as a `QDate` wrapper for EHM format `SI_Date`.
 */
class Date : public AbstractDataType
{
public:
    /*!
     * \brief Default constructor
     */
    Date();

    // File i/o
    /*!
     * \brief Reads an `SI_Date` from a saved game which does not include a `bool` leap year value
     * \param in
     */
    void readFromSavedGame(QDataStream &in);

    // Get data
    /*!
     * \brief Returns the date.
     * \return the date
     */
    inline QDate get() const { return date_; }
    /*!
     * \brief Converts the Date to `SI_Date` format. The `day`, `year` and `is_leap_year` must be passed 
     * by reference. Each of these variables will be populated with the relevant `SI_Date` values.
     * \param day Reference to `SI_Date` day of the year index to be set by the function
     * \param year Reference to `SI_Date` year to be set by the function
     * \param is_leap_year Reference to `SI_Date` leap year value to be set by the function
     */
    void toSiDate(qint16 &day, qint16 &year, bool &is_leap_year) const; // Must pass by reference
    /*!
     * \brief Returns the year
     */
    inline qint32 year() const { return date_.year(); }

    // Set data
    /*!
     * \brief Sets the Date from an `SI_Date` format date
     * \param day `SI_Date` day of the year index
     * \param year `SI_Date` year
     */
    void set(qint16 day, qint16 year);

    // Thresholds
    /*!
     * \brief The ENUM_THRESHOLDS enum denotes certain date thresholds.
     */
    enum ENUM_THRESHOLDS {
        MINIMUM_YEAR = 1900,      /*!< minimum year in EHM (denotes a random year) */
        FEBRUARY_28TH = 59,       /*!< `SI_Date` day of the year index representing 29 February */
        FIRST_DAY_OF_THE_YEAR = 0 /*!< denotes the first day of the year */
    };

private:
    QDate date_{1900, 2, 1};

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, Date &data);
    friend QDataStream &operator<<(QDataStream &out, const Date &data);

    // Get data
    /*!
     * \brief Returns the date (for compatibility with QAbstractTableModel).
     * \return the date
     */
    inline QVariant value(const qint32 role = Qt::DisplayRole) const override
    {
        Q_UNUSED(role)
        return date_;
    }

    // Set data
    void setValue(const QVariant &value) override;
};

// File i/o
QDataStream &operator>>(QDataStream &in, Date &data);
QDataStream &operator<<(QDataStream &out, const Date &data);

} // namespace ehm_dal::data_types


