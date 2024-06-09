#pragma once

// Application headers
#include "lib/ehm_dal/include/tools/schedule_generator/schedule_template_generator.h"
#include "src/parser/text_schedule_parser.h"

// Qt headers
#include <QAbstractTableModel>

namespace parser {
class ClubIdEditorModel : public QAbstractTableModel
{
public:
    ClubIdEditorModel(QObject *parent);

    // Counts
    qint32 columnCount(const QModelIndex &parent = QModelIndex()) const override;
    qint32 rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Get data
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(qint32 section,
                        Qt::Orientation orientation,
                        qint32 role = Qt::DisplayRole) const override;

    // Set data
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 qint32 role = Qt::EditRole) override;
    void setSourceData(TextScheduleParser &parser);

private:
    // Data
    std::vector<QString> club_name_data_;
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule_;

    enum ENUM_COLUMNS { CLUB_NAME, CLUB_ENCODED_ID, COLUMN_COUNT };
};
} // namespace parser
