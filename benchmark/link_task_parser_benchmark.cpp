#include <benchmark/benchmark.h>
#include <dotmake/yaml_parser.h>

static void BenchmarkLinkTaskParser(benchmark::State& state) {
  // Perform setup here
  for (auto ignore : state) {
    // This code gets timed
    const auto hello_task =
        dotmake::yaml_parser::ParseString<dotmake::LinkTask>(
            R"(
  type: link
  links:
    this.txt: other.txt
  )");
  }
}
// Register the function as a benchmark
BENCHMARK(BenchmarkLinkTaskParser);
