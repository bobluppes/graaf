from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

"""
This script can be used to visualize benchmark results. The script assumes multiple benchmark
results in csv files under the build directory. These results can be generated with the
Graaf_perf executable:

build/perf/Graaf_perf --benchmark_out=benchmark_results.csv --benchmark_out_format=csv
"""


def read_benchmark_files_into_df(dir=Path("../build"), skiprows=10):
    df = pd.DataFrame()
    for file in dir.glob("*.csv"):
        df_new = pd.read_csv(file, skiprows=skiprows)
        df_new["filename"] = Path(file).stem
        df = pd.concat([df, df_new], ignore_index=True)

    assert not df.empty, "Reading into df failed. Check dir and skiprows parameters!"

    df[["bm_name", "variable"]] = df["name"].str.split(pat="/", n=1, expand=True)
    df["variable"] = df["variable"].astype(int)
    df["time (s)"] = df["real_time"].apply(lambda x: x * 1e-9)
    df["ID"] = df["filename"] + " - " + df["bm_name"]
    return df


def plot_benchmarks_from_df(df, ax=None, save_plot=False):
    if ax is None:
        _, ax = plt.subplots(figsize=(7, 5))
        ax.set(xscale="log", xlabel="No. of Additions", ylabel="Runtime (s)")

    sns.lineplot(df, x="variable", y="time (s)", hue="ID", legend="full", ax=ax)
    plt.savefig("plot.png") if save_plot else plt.show()


if __name__ == "__main__":
    df = read_benchmark_files_into_df()
    plot_benchmarks_from_df(df)
