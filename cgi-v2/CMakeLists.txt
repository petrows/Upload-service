cmake_minimum_required(VERSION 2.6)
set(PROJECT "upload-service")

project(${PROJECT})

file(GLOB APP_H "src/*.h")
file(GLOB APP_SRC "src/*.c*")

add_executable(${PROJECT} ${APP_H} ${APP_SRC})

find_library(LIB_CGI fcgi)
find_library(LIB_PTHREAD pthread)

target_compile_options(${PROJECT} PUBLIC -Wall)
target_link_libraries(${PROJECT} ${LIB_CGI} ${LIB_PTHREAD})
