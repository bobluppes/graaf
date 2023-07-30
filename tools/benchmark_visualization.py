import os
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd

"""
This script can be used to visualize benchmark results. The script assumes multiple benchmark 
results in csv files under the build directory. These results can be generated with the 
Graaf_perf executable:

build/perf/Graaf_perf --benchmark_out=benchmark_results.csv --benchmark_out_format=csv
"""


def plot_benchmarks_from_csv(
    benchmark_dir=Path("../build"), benchmark_filter="bm_", google_benchmark_skiprows=10
):
    plt.figure()

    for benchmark_results in benchmark_dir.glob("*.csv"):
        filename = os.path.basename(benchmark_results)
        benchmarks_df = pd.read_csv(
            benchmark_results, skiprows=google_benchmark_skiprows
        )

        # The benchmark name and variable are recorded as 'bm_name/variable'
        benchmarks_df[["bm_name", "variable"]] = benchmarks_df["name"].str.split(
            pat="/", n=1, expand=True
        )
        benchmarks_df["variable"] = benchmarks_df["variable"].astype(int)

        # Google benchmark records the time in ns
        benchmarks_df["time (s)"] = benchmarks_df["real_time"].apply(lambda x: x * 1e-9)

        # Filter
        benchmarks_df = benchmarks_df[
            benchmarks_df["bm_name"].apply(lambda x: x.find(benchmark_filter) != -1)
        ]

        for benchmark_df in [x for _, x in benchmarks_df.groupby("bm_name")]:
            benchmark_label = "{} - {}".format(
                os.path.splitext(filename)[0], benchmark_df["bm_name"].iloc[0]
            )

            plt.plot(
                benchmark_df["variable"],
                benchmark_df["time (s)"],
                label=benchmark_label,
                marker=".",
            )

    plt.xlabel("number of additions")
    plt.ylabel("runtime (s)")
    plt.xscale("log")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot_benchmarks_from_csv()
