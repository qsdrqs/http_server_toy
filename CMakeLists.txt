cmake_minimum_required(VERSION 2.8.12)
project(http)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)
add_executable(http ${DIR_SRC})
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set (FLAGS "-g -O0")
else()
    set (FLAGS "-O2")
endif()
set (CMAKE_C_FLAGS "${FLAGS} -Wall")
set (CMAKE_CXX_FLAGS "${FLAGS} -Wall -Wno-write-strings") # C sources use char* as string

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(http APIS)


# tests
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
enable_testing()
