QT += concurrent

INCLUDEPATH += $$PWD/
Debug:LIBS += -L"$$PWD/" -lehm_dal_debug
Release:LIBS += -L"$$PWD/" -lehm_dal
