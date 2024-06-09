#pragma once

// Qt headers
#include <QtGlobal>
class QString;

// Library information
namespace ehm_dal::library_info {
// Author
QString libraryAuthor();
QString libraryWebsite();
// Name
QString libraryLongName();
QString libraryShortName();
// Version
QString libraryVersion();
quint64 libraryVersionIdentifier();
} // namespace ehm_dal::library_info
