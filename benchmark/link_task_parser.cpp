#include <benchmark/benchmark.h>
#include <link_task_parser.h>

static void BM_LinkTaskParser(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
  const auto hello_task = LinkTaskParser{"hello_task"}.parse_string(R"(

  type: link
  links:
    this.txt: other.txt

  )");
  }
}
// Register the function as a benchmark
BENCHMARK(BM_LinkTaskParser);