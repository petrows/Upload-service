#!/bin/bash

# Exit on error
set -e 

QT_DIR="C:\\Qt\\5.7\\msvc2015"
COMPILER_DIR="C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\bin"

export CMAKE_PREFIX_PATH="$QT_DIR"

QT_BIN=$(/bin/cygpath -u "$QT_DIR")"/bin"
COMPILER_BIN=$(/bin/cygpath -u "$COMPILER_DIR")"/bin"

export PATH=$COMPILER_BIN:$PATH
export QTDIR="$QT_BIN"

/bin/rm -rf build_win32
/bin/mkdir build_win32
cd build_win32
/bin/mkdir bin
cmake.exe -G "Visual Studio 14" -DCMAKE_INSTALL_PREFIX="./" -DCMAKE_BUILD_TYPE=Release ..
MSBuild.exe /p:Configuration=Release upload-client.sln

cd bin
"$QT_BIN/windeployqt.exe" --release *.exe

