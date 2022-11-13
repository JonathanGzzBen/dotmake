#include <benchmark/benchmark.h>
#include <shell_task_parser.h>

static void BM_ShellTaskParser(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
  const auto hello_task = ShellTaskParser{"hello_task"}.parse_string(R"(

  type: shell
  commands:
    - echo "hello"

  )");
  }
}
// Register the function as a benchmark
BENCHMARK(BM_ShellTaskParser);