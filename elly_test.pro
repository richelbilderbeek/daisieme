include(any_test.pri)
include(daic.pri)
#DEFINES += ELLY_DO_RUN_DAISIE
include(daic_test.pri)
include(elly.pri)
include(elly_test.pri)

# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += elly_main_test.cpp
