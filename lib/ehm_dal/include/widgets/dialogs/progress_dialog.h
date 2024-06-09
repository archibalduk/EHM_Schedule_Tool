#pragma once

// Qt headers
#include <QProgressDialog>

namespace ehm_dal::widgets {

// --- Progress dialog wrapper --- //
class ProgressDialog : public QProgressDialog
{
public:
    // Constructor
    ProgressDialog(const QString &window_title_text,
                   const qint32 minimum,
                   const qint64 maximum,
                   QWidget *parent = nullptr,
                   const bool silent = false);
    ~ProgressDialog();

    // Set data
    void complete();
    void increaseRange(const qint32 i);
    void increment(const qint64 i = 1);
    void increment(const QString &label_text);
    void set(const QString &text, const qint64 maximum);
    void setText(const QString &text);

    // Silent
    void setSilent(const bool silent);
};
} // namespace ehm_dal::widgets
