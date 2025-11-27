cmake_minimum_required(VERSION 3.24)
project(ctensors VERSION 1.0.0 LANGUAGES C)

include(FetchContent)

option(CTENSORS_BUILD_EXAMPLES "Build the provided examples" OFF)

set(CTENSORS_HEADERS
        lib/ctensors.h
        lib/ctensors_types.h
        lib/ctensors_fopen.h
        lib/ctensors_fclose.h
        lib/ctensors_fread_table.h
        lib/ctensors_header_parse.h
        lib/ctensors_mmap.h
        lib/ctensors_mmap_table.h
        lib/ctensors_table_read.h
        lib/ctensors_table_get_tensor.h)

set(CTENSORS_SOURCES
        lib/ctensors_fopen.c
        lib/ctensors_fclose.c
        lib/ctensors_fread_table.c
        lib/ctensors_header_parse.c
        lib/ctensors_mmap.c
        lib/ctensors_mmap_table.c
        lib/ctensors_types.c
        lib/ctensors_table_read.c
        lib/ctensors_table_get_tensor.c)

add_library(ctensors ${CTENSORS_HEADERS} ${CTENSORS_SOURCES})
set_property(TARGET ctensors PROPERTY C_STANDARD 23)
target_include_directories(ctensors PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
    $<INSTALL_INTERFACE:include>
)


# Let CMake download yyjson
fetchcontent_declare(
        yyjson
        GIT_REPOSITORY https://github.com/ibireme/yyjson.git
        GIT_TAG master # master, or version number, e.g. 0.6.0
)
fetchcontent_getproperties(yyjson)
fetchcontent_makeavailable(yyjson)

# Link yyjson to your target
target_link_libraries(ctensors PRIVATE yyjson)

if(${CTENSORS_BUILD_EXAMPLES})
    add_executable(ctensors_read_example examples/read.c)
    target_link_libraries(ctensors_read_example PRIVATE ctensors)

    add_executable(ctensors_mmap_example examples/mmap.c)
    target_link_libraries(ctensors_mmap_example PRIVATE ctensors)
endif()