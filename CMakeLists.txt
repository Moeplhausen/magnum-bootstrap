cmake_minimum_required(VERSION 2.8.12)
project(EmscriptenIssues)


set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/emscripten-dst/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")
set(WITH_SDL2APPLICATION ON)

# CMake policies: enable MACOSX_RPATH by default
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
# Don't treat imported targets with :: as files
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()



#add_subdirectory(libs/corrade)
#add_subdirectory(libs/magnum)
add_subdirectory(src)
