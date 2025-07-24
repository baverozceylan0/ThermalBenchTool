A lightweight experimental framework for running C-based microbenchmarks (basic math, square root), capturing system metrics (CPU frequency, temperature, utilization), and visualizing results using Python.  

## 🧠 Overview

This repo enables you to:

1. **Compile** benchmark programs (`basicmath`, `sqrt_task`).
2. **Run** benchmarks while **recording** system metrics.
3. **Plot** metric time-series to analyze performance and thermal behavior.

`compile_all.sh`: compiles both project benchmarks.
`start_recording.sh`: kicks off sensor data capture (temperature, CPU freq, etc.).
`start_task.sh` / `start_task_basicmath.sh`: executes benchmarks.
`sample_experiment.sh`: orchestrates full runs—compiling, logging, running task, ending logging.

## 🛠 Prerequisites

Install the following tools:

- GCC (or compatible C compiler)
- `make`
- Python 3 + Matplotlib (or your plotting library)
- Linux sysfs access for metrics (e.g., `/sys/class/thermal`, `cpufreq`)

- ## 🚀 Quick Start

Run a full experiment (build → execute → record → plot):

```bash
./compile_all.sh
./sample_experiment.sh
# Output plots saved in the current working directory
