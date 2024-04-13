cmake_minimum_required(VERSION 3.14)
project(dotmake)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp/
        GIT_TAG yaml-cpp-0.7.0
)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG 15460959cbbfa20e66ef0b5ab497367e47fc0a04
)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG d572f4777349d43653b21d6c2fc63020ab326db2
)

if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

FetchContent_MakeAvailable(yaml-cpp googletest googlebenchmark)

set(DotmakeLib ${PROJECT_NAME}lib)
add_library(${DotmakeLib} src/system_caller.cpp
        src/link_task.cpp
        src/shell_task.cpp
        src/specification.cpp
        src/task.cpp
        src/yaml_parser.cpp
        )
set_property(TARGET ${DotmakeLib} PROPERTY CXX_STANDARD 17)
target_link_libraries(${DotmakeLib} PUBLIC yaml-cpp)
target_include_directories(${DotmakeLib} PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DotmakeLib})

# Benchmarking
set(BenchmarkingProject ${CMAKE_PROJECT_NAME}_benchmark)
add_executable(${BenchmarkingProject}
        benchmark/shell_task_parser_benchmark.cpp
        benchmark/link_task_parser_benchmark.cpp
        )
set_property(TARGET ${BenchmarkingProject} PROPERTY CXX_STANDARD 17)
target_link_libraries(${BenchmarkingProject} ${DotmakeLib} benchmark::benchmark benchmark::benchmark_main)

# Testing
enable_testing()
set(TestProject ${PROJECT_NAME}_test)
add_executable(${TestProject}
        test/shell_task_parser_test.cpp
        test/link_task_parser_test.cpp
        )
set_property(TARGET ${TestProject} PROPERTY CXX_STANDARD 17)
target_link_libraries(${TestProject} ${DotmakeLib} GTest::gtest_main GTest::gmock)
include(GoogleTest)
gtest_discover_tests(${TestProject})

