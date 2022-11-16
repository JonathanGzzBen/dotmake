# Results

## Before
```
Running C:\Users\jonat\Documents\Programming\dotmake\build\Release\dotmake_benchmark.exe
Run on (12 X 2937.03 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_ShellTaskParser      16055 ns        16044 ns        44800
BM_LinkTaskParser       16915 ns        17090 ns        44800
```

## After
```
Running C:\Users\jonat\Documents\Programming\dotmake\build\Release\dotmake_benchmark.exe
Run on (12 X 2921.77 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_ShellTaskParser      15786 ns        15695 ns        44800
BM_LinkTaskParser       16437 ns        16497 ns        40727
```