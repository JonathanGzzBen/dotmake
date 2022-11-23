# Results

## Before
```
Running C:\Users\jonat\Documents\Programming\dotmake\build\dotmake_benchmark.exe
Run on (12 X 2912.83 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
BM_ShellTaskParser_mean        14980 ns        14962 ns           10
BM_ShellTaskParser_median      15204 ns        15346 ns           10
BM_ShellTaskParser_stddev        511 ns          556 ns           10
BM_ShellTaskParser_cv           3.41 %          3.72 %            10
BM_LinkTaskParser_mean         15900 ns        15904 ns           10
BM_LinkTaskParser_median       16202 ns        16044 ns           10
BM_LinkTaskParser_stddev         535 ns          574 ns           10
BM_LinkTaskParser_cv            3.37 %          3.61 %            10
```

## After
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
