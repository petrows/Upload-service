cmake_minimum_required(VERSION 2.6)
set(PROJECT "upload-service")

project(${PROJECT})

file(GLOB APP_H "src/*.h")
file(GLOB APP_SRC "src/*.c*")

add_executable(${PROJECT} ${APP_H} ${APP_SRC})

find_library(LIB_CGI fcgi)

if ("LIB_CGI-NOTFOUND" STREQUAL ${LIB_CGI})
	message(FATAL_ERROR "Cant find fcgi, install with: sudo apt install libfcgi-dev")
endif()

find_library(LIB_PTHREAD pthread)

if ("LIB_PTHREAD-NOTFOUND" STREQUAL ${LIB_PTHREAD})
	message(FATAL_ERROR "Cant find pthread, install with: sudo apt install libpthread-dev")
endif()

target_compile_options(${PROJECT} PUBLIC -Wall)
target_link_libraries(${PROJECT} ${LIB_CGI} ${LIB_PTHREAD})
