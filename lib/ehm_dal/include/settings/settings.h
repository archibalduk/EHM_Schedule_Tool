#pragma once

// Qt headers
#include <QHash>
#include <QString>
#include <QVariant>

namespace ehm_dal::settings {

// --- Application settings cache/manager --- //
class Settings
{
public:
    // Constructor
    Settings();

    // Get data
    static bool debugMode();
    QVariant value(const QString &key, const QVariant &default_value = QVariant());

    // Registry i/o
    void writeAll() const;

    // Set data
    void remove(const QString &key);
    void setValue(const QString &key, const QVariant &value);

private:
    // Registry i/o
    QVariant read(const QString &key, const QVariant &default_value = QVariant()) const;

    // Settings cache
    static QHash<QString, QVariant> cache_;
};
} // namespace ehm_dal::settings
