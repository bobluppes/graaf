import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path
import os

benchmark_dir = Path("../build")
benchmark_filter = "bm_"
google_benchmark_skiprows = 10

plt.figure()

for benchmark_results in benchmark_dir.glob("*.csv"):
    filename = os.path.basename(benchmark_results)
    benchmarks_df = pd.read_csv(benchmark_results, skiprows=google_benchmark_skiprows)

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
