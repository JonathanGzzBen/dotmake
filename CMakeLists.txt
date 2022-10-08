cmake_minimum_required(VERSION 3.14)
project(dotmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} src/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp/
    GIT_TAG yaml-cpp-0.7.0
)

FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)
