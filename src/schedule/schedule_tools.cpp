#include "schedule_tools.h"

// Qt headers
#include <QDate>
#include <QInputDialog>
#include <QMenuBar>

using namespace schedule;

ScheduleTools::ScheduleTools()
{
    add_days_action_ = std::make_unique<QAction>(QStringLiteral("Adjust &days..."));
    QObject::connect(add_days_action_.get(), &QAction::triggered, this, &ScheduleTools::onAddDays);

    set_start_year_action_ = std::make_unique<QAction>(QStringLiteral("Set start &year..."));
    QObject::connect(set_start_year_action_.get(),
                     &QAction::triggered,
                     this,
                     &ScheduleTools::onSetStartYear);
}

void ScheduleTools::setSourceData(
    std::shared_ptr<ehm_dal::tools::schedule_template_generator::ScheduleTemplateGenerator> schedule)
{
    schedule_ = std::move(schedule);
}

void ScheduleTools::onAddDays()
{
    if (!schedule_)
        return;

    bool ok;
    const auto value{QInputDialog::getInt(parent_,
                                          QStringLiteral("Adjust days"),
                                          QStringLiteral("Days to add:"),
                                          0,
                                          -MAX_DAYS_IN_A_YEAR,
                                          MAX_DAYS_IN_A_YEAR,
                                          1,
                                          &ok)};

    if (ok)
        schedule_->addDays(value);
}

void ScheduleTools::onSetStartYear()
{
    if (!schedule_)
        return;

    bool ok;
    const auto value{QInputDialog::getInt(parent_,
                                          QStringLiteral("Set start year"),
                                          QStringLiteral("Start year:"),
                                          QDate::currentDate().year(),
                                          MINIMUM_YEAR,
                                          MAXIMUM_YEAR,
                                          1,
                                          &ok)};

    if (ok)
        schedule_->setStartYear(value);
}

void schedule::ScheduleTools::addToMenu(QMenuBar *menu_bar)
{
    parent_ = menu_bar;
    auto menu{menu_bar->addMenu(QStringLiteral("&Tools"))};

    menu->addAction(add_days_action_.get());
    menu->addAction(set_start_year_action_.get());
}
