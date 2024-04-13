# Results

## Before

```
Running C:\Users\jonat\Documents\Programming\dotmake\build\dotmake_benchmark.exe
Run on (12 X 2927.78 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
BM_ShellTaskParser_mean        15456 ns        15461 ns           10
BM_ShellTaskParser_median      15122 ns        15346 ns           10
BM_ShellTaskParser_stddev        582 ns          573 ns           10
BM_ShellTaskParser_cv           3.77 %          3.71 %            10
BM_LinkTaskParser_mean         16148 ns        16152 ns           10
BM_LinkTaskParser_median       15971 ns        16113 ns           10
BM_LinkTaskParser_stddev         402 ns          459 ns           10
BM_LinkTaskParser_cv            2.49 %          2.84 %            10
```

## After

```
2023-01-14T21:22:19-06:00
Running C:\Users\jonat\Documents\Programming\dotmake\build\Release\dotmake_benchmark.exe
Run on (12 X 2930.78 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
--------------------------------------------------------------------------
Benchmark                                Time             CPU   Iterations
--------------------------------------------------------------------------
BenchmarkShellTaskParser_mean        14603 ns        14627 ns           10
BenchmarkShellTaskParser_median      14577 ns        14753 ns           10
BenchmarkShellTaskParser_stddev        126 ns          162 ns           10
BenchmarkShellTaskParser_cv           0.86 %          1.11 %            10
BenchmarkLinkTaskParser_mean         15095 ns        15032 ns           10
BenchmarkLinkTaskParser_median       15080 ns        14997 ns           10
BenchmarkLinkTaskParser_stddev        64.5 ns          110 ns           10
BenchmarkLinkTaskParser_cv            0.43 %          0.73 %            10
```