cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_C_COMPILER clang)
project(http)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)
add_executable(http ${DIR_SRC})
set(CMAKE_C_FLAGS "-Wall -O2 -std=c2x")
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(http APIS)


# tests
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
enable_testing()
