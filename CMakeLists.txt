cmake_minimum_required(VERSION 2.8.11)
project(color_operations)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(SOURCE
        ${SOURCE}
        src/main.cpp)

set(HEADERS
        ${HEADERS})

add_executable(color_operations ${SOURCE})

target_link_libraries(color_operations ${OpenCV_LIBS} ${Boost_LIBRARIES})
