cmake_minimum_required(VERSION 3.1.0)
set (CMAKE_CXX_STANDARD 14)
project(color_operations)

find_package(OpenCV 3.2 REQUIRED)
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

set(SOURCE
        ${SOURCE}
        src/main.cpp
        src/operation.cpp
        src/matrix_operation.cpp
        src/brightness_operation.cpp
        src/color_operations.cpp)

set(HEADERS
        ${HEADERS}
        src/operation.hpp
        src/matrix_operation.hpp
        src/brightness_operation.hpp
        src/color_operations.hpp)

add_executable(color_operations ${SOURCE})

target_link_libraries(color_operations ${OpenCV_LIBS} ${Boost_LIBRARIES})
