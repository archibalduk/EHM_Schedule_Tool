#pragma once

// Qt headers
#include <QVariant>

namespace ehm_dal::data_types {
/*!
 * \brief The AbstractDataType class provides common virtual functions for all integral game data types.
 */
class AbstractDataType
{
public:
    AbstractDataType();

    // Get data
    /*!
     * \brief Returns the data stored under the given `role` for the item.
     * \param role typically `Qt::DisplayRole` or `Qt::EditRole`
     */
    QVariant data(const qint32 role = Qt::DisplayRole) const;

    // Set data
    Q_DECL_DEPRECATED void set(const QVariant &value,
                               const qint32 role = Qt::EditRole); // TODO to be deprecated
    /*!
     * \brief Sets the `role` data for the item at to `value`.
     * \param value
     * \param role
     */
    void setData(const QVariant &value, const qint32 role = Qt::EditRole);

private:
    virtual QVariant value(const qint32 role = Qt::DisplayRole) const = 0;
    virtual void setValue(const QVariant &value) = 0;
};

} // namespace ehm_dal::data_types
