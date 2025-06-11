cmake_minimum_required(VERSION 3.28)
project(Chess)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "headers/*.hpp")

add_executable(Chess ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
