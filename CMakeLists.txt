cmake_minimum_required(VERSION 3.10)

project(flowy)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-4.0)
pkg_check_modules(GST gstreamer-1.0)

set (source_dir "${PROJECT_SOURCE_DIR}/src")
file(GLOB source_files "${source_dir}/*.cpp")

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${GST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES})
