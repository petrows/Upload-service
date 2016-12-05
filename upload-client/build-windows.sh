#!/bin/bash

# Exit on error
set -e 

QT_DIR="C:\\Qt\\5.7\\mingw53_32"
MINGW_DIR="c:\\Qt\\Tools\\mingw530_32"

export CMAKE_PREFIX_PATH="$QT_DIR"

MINGW_QT=$(/bin/cygpath -u "$QT_DIR")"/bin"
MINGW_BIN=$(/bin/cygpath -u "$MINGW_DIR")"/bin"

export PATH=$MINGW_BIN:$PATH
export QTDIR="$MINGW_QT"

/bin/rm -rf build_win32
/bin/mkdir build_win32
cd build_win32
/bin/mkdir bin
cmake.exe -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX="./" -DCMAKE_BUILD_TYPE=Release ..
"$MINGW_BIN/mingw32-make.exe" all install -j4

cd bin
"$MINGW_QT/windeployqt.exe" --release *.exe

