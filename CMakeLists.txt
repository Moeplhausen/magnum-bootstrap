cmake_minimum_required(VERSION 2.8.12)
project(EmscriptenIssues)


set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/emscripten-dst/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")
set(WITH_SDL2APPLICATION ON)


add_subdirectory(libs/corrade)
add_subdirectory(libs/magnum)
add_subdirectory(src)
