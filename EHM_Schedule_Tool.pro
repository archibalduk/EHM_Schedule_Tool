QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# C++20 support
CONFIG += c++latest

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Enable as many compiler warnings as possible
CONFIG += warn_on

# Enable parallel building
*msvc* { # visual studio spec filter
     QMAKE_CXXFLAGS += -MP
}

# Application version
VERSION = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# External project libraries
include($$PWD/lib/ehm_dal/ehm_dal.pri)
include($$PWD/lib/qxlsx/qxlsx.pri)

SOURCES += \
    src/generator/club_count_editor_model.cpp \
    src/main.cpp \
    src/parser/club_id_editor_model.cpp \
    src/parser/schedule_template_parser.cpp \
    src/parser/text_schedule_parser.cpp \
    src/schedule/private/abstract_schedule_stats.cpp \
    src/schedule/schedule_stats.cpp \
    src/schedule/schedule_stats_matrix.cpp \
    src/schedule/schedule_tools.cpp \
    src/ui/generator/club_count_dialog.cpp \
    src/ui/generator/schedule_generator_ui.cpp \
    src/ui/generator/schedule_matrix_editor_dialog.cpp \
    src/ui/main_window.cpp \
    src/ui/parser/club_id_editor_dialog.cpp \
    src/ui/parser/column_selection_dialog.cpp \
    src/ui/parser/private/abstract_parser_ui.cpp \
    src/ui/parser/schedule_template_parser_ui.cpp \
    src/ui/parser/text_schedule_parser_ui.cpp

HEADERS += \
    src/generator/club_count_editor_model.h \
    src/parser/club_id_editor_model.h \
    src/parser/schedule_template_parser.h \
    src/parser/text_schedule_parser.h \
    src/schedule/private/abstract_schedule_stats.h \
    src/schedule/schedule_stats.h \
    src/schedule/schedule_stats_matrix.h \
    src/schedule/schedule_tools.h \
    src/ui/generator/club_count_dialog.h \
    src/ui/generator/schedule_generator_ui.h \
    src/ui/generator/schedule_matrix_editor_dialog.h \
    src/ui/main_window.h \
    src/ui/parser/club_id_editor_dialog.h \
    src/ui/parser/column_selection_dialog.h \
    src/ui/parser/private/abstract_parser_ui.h \
    src/ui/parser/schedule_template_parser_ui.h \
    src/ui/parser/text_schedule_parser_ui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
