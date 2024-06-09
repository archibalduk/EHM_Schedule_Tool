#pragma once

// Application headers
#include "include/database/pointer/pointer_flags.h"

// Qt headers
#include <QDataStream>
#include <QVariant>

namespace ehm_dal::data_types {
// TODO add sanity checks when getting data in case the id is -1
// TODO consider merging Flag and Pointer into a single class. This should be possible if FlagTable derives from AbstractTable.
// --- Abstract pointer base class --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
class AbstractPointer
{
public:
    AbstractPointer();
    AbstractPointer(const T_TableIndex table_id,
                    const T_IdDataType record_id = PointerFlags::NULL_POINTER);

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, AbstractPointer &data)
    {
        in.readRawData(reinterpret_cast<char *>(&data.id_), sizeof(T_IdDataType));
        return in;
    }

    friend QDataStream &operator<<(QDataStream &out, const AbstractPointer &data)
    {
        auto id{data.id()};
        out.writeRawData(reinterpret_cast<char *>(&id), sizeof(T_IdDataType));
        return out;
    }

    // Get data - attributes
    qint32 columnCount() const { return constTable()->columnCount(); }
    inline bool isNone() const { return !isPointer(); }
    inline bool isPointer() const { return id() > PointerFlags::NULL_POINTER; }
    inline bool isValidPointer() const { return isValidTable() && isPointer(); }
    inline bool isValidTable() const
    {
        return table_id_ != static_cast<T_TableIndex>(PointerFlags::NULL_POINTER);
    }

    // Get data - pointer
    QVariant data(const qint32 role) const;
    virtual QVariant data(const qint32 column, const qint32 role) const;
    inline virtual T_IdDataType id() const { return id_; }
    /*!
     * \brief idBuffer returns the buffered id which is generally only
     * useful when first initialising the links between child and parent data. Prefer using
     * `AbstractPointer::id()` wherever possible as the buffered value may be out of date.
     * \return buffered id value
     */
    inline T_IdDataType idBuffer() const { return id_; }
    /*!
     * \brief parentItemId returns the buffered id which is generally only
     * useful when first initialising the links between child and parent data. Prefer using
     * `AbstractPointer::id()` wherever possible as the buffered value may be out of date.
     * \return buffered id value
     */
    inline T_IdDataType parentItemId() const { return idBuffer(); }
    virtual QString text() const;

    // Get data - table
    QString description() const;
    virtual std::shared_ptr<T_Table> constTable() const = 0;
    virtual std::shared_ptr<T_Table> table() = 0;
    T_TableIndex tableId() const { return table_id_; }

    // Operator overloading: Comparators
    inline bool operator==(const AbstractPointer &rhs) const { return id() == rhs.id(); }
    inline bool operator==(const qint32 rhs) const { return id() == rhs; }
    inline bool operator!=(const AbstractPointer &rhs) const { return !operator==(rhs); }
    inline bool operator!=(const qint32 rhs) const { return !operator==(rhs); }
    inline bool operator<(const AbstractPointer &rhs) const { return id() < rhs.id(); }
    inline bool operator<(const qint32 rhs) const { return id() < rhs; }
    inline bool operator>(const AbstractPointer &rhs) const { return rhs < *this; }
    inline bool operator>(const qint32 rhs) const { return rhs < id(); }

    // Set data - pointer
    // TODO deprecate set() in favour of setData()
    Q_DECL_DEPRECATED void set(const QVariant &value, const qint32 role)
    {
        return setData(value, role);
    }
    virtual void setData(const QVariant &value, const qint32 role);
    bool setData(const qint32 column, const QVariant &value, const qint32 role);

protected:
    T_IdDataType id_{static_cast<T_IdDataType>(PointerFlags::NULL_POINTER)};       // Record id
    T_TableIndex table_id_{static_cast<T_TableIndex>(PointerFlags::NULL_POINTER)}; // Table id

    inline void setId(const qint32 id) { id_ = static_cast<T_IdDataType>(id); }
};

/* ============================ */
/*      Pointer Base Class      */
/* ============================ */

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::AbstractPointer()
{}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::AbstractPointer(const T_TableIndex table_id,
                                                                      const T_IdDataType record_id)
    : id_(record_id)
    , table_id_(table_id)
{}

/* =========================== */
/*      Get Data - Pointer     */
/* =========================== */

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QVariant AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::data(const qint32 role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return text();
    case Qt::EditRole:
        return id();
    default:
        return QVariant();
    }
}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QVariant AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::data(const qint32 column,
                                                                    qint32 role) const
{
    return constTable()->index(id(), column).data(role);
}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QString AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::text() const
{
    return constTable()->index(id(), 2).data(Qt::DisplayRole).toString();
}

/* ========================= */
/*      Get Data - Table     */
/* ========================= */

// --- Get table name --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QString AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::description() const
{
    if (tableId() != static_cast<T_TableIndex>(PointerFlags::NULL_POINTER))
        return constTable()->attributes()->name();

    return QStringLiteral("[No table]");
}

/* =========================== */
/*      Set Data - Pointer     */
/* =========================== */

// --- Sets the pointer id value --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
void AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::setData(const QVariant &value,
                                                                   const qint32 role)
{
    if (role == Qt::EditRole)
        id_ = static_cast<T_IdDataType>(value.toInt());
}

// --- Edits the underlying item pointed to --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
bool AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::setData(const qint32 column,
                                                                   const QVariant &value,
                                                                   const qint32 role)
{
    const auto index{table()->index(id(), column)};
    return table()->setData(index, value, role);
}
} // namespace ehm_dal::data_types


