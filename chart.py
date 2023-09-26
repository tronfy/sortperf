import json
import matplotlib.pyplot as plt
import numpy as np


def plot(algo, theoretical, theo_label, data):
    plt.clf()
    x = np.array([int(i) for i in data.keys()])

    measured = np.array([data[i][algo] for i in data.keys()])
    measured_avg = np.array([np.mean(data[i][algo]) for i in data.keys()])

    # adjust theoretical to fit measured, consider highest n
    mult = measured_avg[-1] / theoretical[-1]
    theoretical = theoretical * mult

    theo_name = f"theoretical: {theo_label} * ({mult:.2e})"

    fig, ax = plt.subplots()
    plt.plot(x, measured_avg, label="measured (avg)", linewidth=2)
    plt.plot(x, theoretical, label=theo_name, linestyle="dotted", linewidth=2)
    ax.set(xlabel="n", ylabel="time (clock cycles)", title=f"{algo.capitalize()} Sort")

    ax.legend()

    plt.plot(x, measured, "ko", markersize=1)

    ax.grid()

    fig.set_size_inches(7, 5)
    fig.savefig(f"out/{algo}.png", dpi=300)


def plot_together(data, labels, filename):
    plt.clf()
    x = np.array([int(i) for i in data.keys()])

    for label in labels:
        measured_avg = np.array([np.mean(data[i][label]) for i in data.keys()])
        plt.plot(x, measured_avg, label=f"{label} sort", linewidth=2)

    plt.legend()
    plt.grid()
    plt.savefig(f"out/{filename}.png", dpi=300)


with open("out/data.json") as f:
    data = json.load(f)
    x = np.array([int(i) for i in data.keys()])

    n_2 = np.array([i**2 for i in x])
    n_log_n = np.array([i * np.log(i) for i in x])

    plot("insertion", n_2, "n^2", data)
    plot("selection", n_2, "n^2", data)
    plot("merge", n_log_n, "n*log(n)", data)
    plot("heap", n_log_n, "n*log(n)", data)
    plot("quick", n_log_n, "n*log(n)", data)

    plot_together(data, ["insertion", "selection"], "quadratic")
    plot_together(data, ["merge", "heap", "quick"], "nlogn")
