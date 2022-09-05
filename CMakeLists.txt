cmake_minimum_required(VERSION 3.11)
project(dotmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(libs/yaml-cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE libs/yaml-cpp/include)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)
