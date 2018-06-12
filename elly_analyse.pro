include(any_normal.pri)
include(elly.pri)
include(daic.pri)
include(elly_analyse.pri)

# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += elly_analyse_main.cpp
