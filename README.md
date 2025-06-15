# metric_collector

**metric_collector** is a simple multithreaded C++ library for collecting and asynchronously writing metrics to a file.

## Features

- Collect metrics with different value types
- Asynchronous writing of metrics to a file without blocking the main thread
- Example usage in `main.cpp`

## Quick Start

### Build

```bash
cd metric_collector/src
cmake ..
make
```

Or use the provided Makefile:

```bash
cd metric_collector/src
make
```

### Run the Example

```bash
./metric_collector
```

After execution, a file named `metrics.txt` will appear with the recorded metrics.

## Dependencies

- C++11
- CMake