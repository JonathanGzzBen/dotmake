#include <benchmark/benchmark.h>
#include <dotmake/yaml_parser.h>

static void BenchmarkShellTaskParser(benchmark::State& state) {
  // Perform setup here
  for (auto ignore : state) {
    // This code gets timed
    const auto hello_task =
        dotmake::yaml_parser::ParseString<dotmake::ShellTask>(R"(

  type: shell
  commands:
    - echo "hello"

  )");
  }
}
// Register the function as a benchmark
BENCHMARK(BenchmarkShellTaskParser);
