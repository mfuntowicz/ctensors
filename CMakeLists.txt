cmake_minimum_required(VERSION 3.24)
project(libsafetensors VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)

include(FetchContent)

option(SAFETENSORS_BUILD_EXAMPLES "Build the provided examples" OFF)

set(SAFETENSORS_HEADERS
        lib/safetensors.h
        lib/safetensors_errors.h
        lib/safetensors_types.h
#        lib/safetensors_fopen.h
#        lib/safetensors_fclose.h
#        lib/safetensors_fread_table.h
        lib/safetensors_header_parse.h
        lib/safetensors_mmap.h
        lib/safetensors_mmap_table.h
        lib/safetensors_mmap_unix.h
        lib/safetensors_table_read.h
        lib/safetensors_table_get_tensor.h)

set(SAFETENSORS_SOURCES
        lib/safetensors_errors.c
#        lib/safetensors_fopen.c
#        lib/safetensors_fclose.c
#        lib/safetensors_fread_table.c
        lib/safetensors_header_parse.c
        lib/safetensors_mmap_table.c
        lib/safetensors_mmap_unix.c
        lib/safetensors_types.c
        lib/safetensors_table_read.c
        lib/safetensors_table_get_tensor.c)

add_library(safetensors ${SAFETENSORS_HEADERS} ${SAFETENSORS_SOURCES})
set_property(TARGET safetensors PROPERTY C_STANDARD 23)
target_include_directories(safetensors PUBLIC
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
target_link_libraries(safetensors PRIVATE yyjson)

if(${SAFETENSORS_BUILD_EXAMPLES})
    add_executable(safetensors_read_example examples/read.c)
    target_link_libraries(safetensors_read_example PRIVATE safetensors)

    add_executable(safetensors_mmap_example examples/mmap.c)
    target_link_libraries(safetensors_mmap_example PRIVATE safetensors)
endif()