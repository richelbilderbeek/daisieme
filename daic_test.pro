# General setup
include(any_test.pri)

include(daic.pri)
include(daic_test.pri)

# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += $$PWD/daic_main_test.cpp

