#pragma once


// Application headers
#include "include/data_types/date/year.h"
#include "include/schema/abstract_uid_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::data_types {
class Date;
class Pointer;
class NamePointer;
}

namespace ehm_dal::schema {

class Person : public ehm_dal::schema::AbstractUidTableItem
{
public:
    Person();
    ~Person();

    // Bio data - age
    qint32 age() const;

    // Get data
    QString text() const override;

    // Initialisation
    bool init() override;

    // Operator overloading
    bool operator<(const Person &rhs) const;

protected:
    // Bio data - age
    ehm_dal::data_types::Date &dateOfBirth();
    data_types::Year<qint16> &yearOfBirth();
    // Bio data - geography
    ehm_dal::data_types::Pointer &birthplace();
    ehm_dal::data_types::Pointer &nationality();
    // Bio data - name
    ehm_dal::data_types::NamePointer &firstName();
    ehm_dal::data_types::NamePointer &secondName();

    // Get data
    QVariant personData(const qint32 column, qint32 role) const;

    // Set data
    bool setPersonData(const qint32 column,
                       const QVariant &value,
                       qint32 role,
                       std::vector<qint32> &modified_columns);

private:
    struct Data;
    std::unique_ptr<Data> base_data_;

    // Initialisation
    virtual bool initInternalData() = 0;

    // Bio data - age
    bool validateYearOfBirth();
};

} // namespace ehm_dal::schema


