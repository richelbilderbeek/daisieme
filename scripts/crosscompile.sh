#!/bin/sh
#
# Crosscompiles daisieme C++GUI to the Windows operating system
#
# Usage:
#
#   ./crosscompile.sh
#
DESKTOP_PRO=elly_gui.pro

# To daisieme/cpp
cd ../cpp

if [ ! -e $DESKTOP_PRO ]
then
  echo "ERROR: Cannot find "$DESKTOP_PRO
  exit
fi
i686-w64-mingw32.static-qmake-qt5 $DESKTOP_PRO
make

# To daisieme
cd ..

DESKTOP_EXE=cpp/release/elly_gui.exe

if [ ! -e $DESKTOP_EXE ]
then
  echo "ERROR: Cannot find "$DESKTOP_EXE
else
  echo "OK: Can find "$DESKTOP_EXE
fi


mv $DESKTOP_EXE daisieme.exe

zip daisieme_exe.zip daisieme.exe