#pragma once

// Application headers
#include "include/schema/abstract_uid_table_item.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::data_types {
class Pointer;
}

namespace ehm_dal::schema {

// --- Clubs --- //
class Club : public ehm_dal::schema::AbstractUidTableItem
{
public:
    Club();
    ~Club();

    // Child data
    void addChildItem(std::shared_ptr<AbstractTableItem> item,
                      const ehm_dal::tables::TableIndex child_table) override;
    QVariant childData(const QModelIndex &index,
                       qint32 role,
                       column_data::ColumnData *column_data,
                       const ehm_dal::tables::TableIndex child_table) const override;
    qint32 childRowCount(const ehm_dal::tables::TableIndex child_table) const override;
    bool setChildData(const QModelIndex &index,
                      const QVariant &value,
                      const qint32 role,
                      std::vector<qint32> &modified_columns,
                      ehm_dal::column_data::ColumnData *column_data,
                      const ehm_dal::tables::TableIndex child_table) override;

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

    // Get data
    QString text() const override;

    // Initialisation
    bool init() override;

    // Validation
    void fixErrors() override;

    enum class ClubRosterSizes : quint8 {
        ASSISTANT_MANAGER_SIZE = 1,
        CAPTAIN_SIZE = 3,
        CHAIRMAN_SIZE = 1,
        COACH_SIZE = 5,
        DIRECTOR_SIZE = 3,
        HEAD_COACH_SIZE = 1,
        HEAD_SCOUT_SIZE = 1,
        MANAGER_SIZE = 1,
        PHYSIO_SIZE = 3,
        SCOUT_SIZE = 15,
        SQUAD_SIZE = 75
    };

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // File i/o
    void readRoster(QDataStream &in,
                    std::vector<ehm_dal::data_types::Pointer> &data,
                    const ClubRosterSizes max_size);
    void writeRoster(QDataStream &out,
                     std::vector<ehm_dal::data_types::Pointer> &data,
                     const ClubRosterSizes max_size);

    // Get data
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Initialisation
    void initRoster(std::vector<ehm_dal::data_types::Pointer> &roster_container);

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


