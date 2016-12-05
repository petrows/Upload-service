#!/bin/bash

# Exit on error
set -e 

QT_DIR="C:\\Qt\\5.7\\mingw53_32"
MINGW_DIR="c:\\Qt\\Tools\\mingw530_32"

ROOT_PATH=$(pwd)

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

# Make portable installer
/bin/zip -r -9 $ROOT_PATH/../upload-client.zip *

# Make exe installer 
makensis.exe /NOCD $(/bin/cygpath -w $ROOT_PATH/installer.nsi)
/bin/mv upload-client-setup.exe $ROOT_PATH/../upload-client-setup.exe
