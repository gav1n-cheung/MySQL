cmake_minimum_required(VERSION 3.10)
project(SQLTest)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP QUIET)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   ${OpenMP_C_FLAGS}")


add_executable(SQLTest main.cpp)
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
target_link_libraries(SQLTest ${PCL_LIBRARIES} libmysqlclient.so)




