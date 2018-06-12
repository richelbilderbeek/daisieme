include(any_profiling.pri)
include(elly.pri)
include(daic.pri)

# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += elly_main.cpp
