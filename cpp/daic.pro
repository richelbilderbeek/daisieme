include(any_profiling_qtcore.pri)

include(daic.pri)

# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += daic_main.cpp

HEADERS +=
