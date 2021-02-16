cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_C_COMPILER clang)
project(http)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)
add_executable(http ${DIR_SRC})
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set (CMAKE_C_FLAGS "-g -O0 -Wall")
else()
    set (CMAKE_C_FLAGS "-O2 -Wall")
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(http APIS)


# tests
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
enable_testing()
