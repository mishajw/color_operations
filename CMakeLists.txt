cmake_minimum_required(VERSION 2.8.11)
project(color_operations)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(SOURCE
        ${SOURCE}
        src/main.cpp
        src/color_operation.cpp
        src/matrix_operation.cpp
        src/brightness_operation.cpp)

set(HEADERS
        ${HEADERS}
        src/color_operation.hpp
        src/matrix_operation.hpp
        src/brightness_operation.hpp)

add_executable(color_operations ${SOURCE})

target_link_libraries(color_operations ${OpenCV_LIBS} ${Boost_LIBRARIES})
