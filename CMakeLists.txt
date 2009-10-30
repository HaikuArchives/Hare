cmake_minimum_required(VERSION 2.6)

project(HARE)

#Override the default module naming scheme
#so that we get <encoder> instead of lib<encoder>.so
set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_SHARED_MODULE_SUFFIX "")

set(CMAKE_MODULE_PATH "${HARE_SOURCE_DIR}/CMakeModules")

set(HARE_BUILD_DIR ${HARE_BINARY_DIR}/build)

set(HARE_BUILD_ADDONS_DIR ${HARE_BINARY_DIR}/build/add-ons)

include(UseHaiku)

include_directories("${HARE_SOURCE_DIR}/include/taglib")

add_subdirectory(src)

