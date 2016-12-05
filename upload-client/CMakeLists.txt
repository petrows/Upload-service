cmake_minimum_required(VERSION 2.8.11)
set(PROJECT upload-client)

# Project
project(${PROJECT})

# Detect the OS and set proper var
set(OS_MAC 0)
set(OS_WIN 0)
set(OS_LINUX 0)
set(OS_NAME 0)
set(LIBS "")

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(OS_MAC 1)
	set(OS_NAME "macos")
	set(LIBS ${LIBS} z)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(OS_LINUX 1)
	set(OS_NAME "linux")
	set(LIBS ${LIBS} z)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(OS_WIN 1)
	set(OS_NAME "windows")
endif()

if(NOT OS_NAME)
	message(FATAL_ERROR "Unknown build target platform!")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Xml)

# Single App
SET(SE_SRC 3dpatry/qtsingleapplication/src/qtsingleapplication.cpp 3dpatry/qtsingleapplication/src/qtlocalpeer.cpp)
SET(SE_H 3dpatry/qtsingleapplication/src/qtsingleapplication.h 3dpatry/qtsingleapplication/src/qtlocalpeer.h)
include_directories(3dpatry/qtsingleapplication/src)

# ZIP
add_definitions(-DQUAZIP_STATIC)
include_directories(3dpatry/quazip)
file(GLOB_RECURSE ZIP_SRCS "3dpatry/quazip/*.c*" "3dpatry/quazip/*.h")
if (OS_WIN)
	link_directories(3dpatry/zlib-win32)
	include_directories(3dpatry/zlib-win32/include)
	set(LIBS ${LIBS} zlib1 ${CMAKE_CURRENT_SOURCE_DIR}/3dpatry/zlib-win32/zdll.lib)
	install (FILES 3dpatry/zlib-win32/zlib1.dll DESTINATION bin)
endif()

# Source files
file(GLOB_RECURSE SRCS "src/*.cpp" "src/*.h")

# Res files
FILE (GLOB_RECURSE RESOURCES "res/*.qrc")
qt5_add_resources(RESOURCES_RCC ${RESOURCES})

# UI files
file(GLOB_RECURSE SRCS_UI "src/*.ui")
qt5_wrap_ui(SRCS_UI_MOC ${SRCS_UI})

# Tell CMake to create the helloworld executable
add_executable(${PROJECT} WIN32 ${SRCS} ${SRCS_UI_MOC} ${SE_SRC} ${ZIP_SRCS} ${RESOURCES_RCC})

# Install targets for different platforms
if (OS_WIN OR OS_LINUX)
	install (TARGETS ${PROJECT} DESTINATION bin)
endif()
if (OS_MAC)
	install (TARGETS ${PROJECT} DESTINATION ${PROJECT}.app/Contents/MacOS/)
endif()

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT} ${LIBS} Qt5::Core Qt5::Widgets Qt5::Network Qt5::Xml)

# Use special libs
