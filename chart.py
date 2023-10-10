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

    theo_name = f"teórico: {theo_label} * ({mult:.2e})"

    fig, ax = plt.subplots()
    plt.plot(x, measured_avg, label="medições (média)", linewidth=2)
    plt.plot(x, theoretical, label=theo_name, linestyle="dotted", linewidth=2)
    ax.set(
        xlabel="n (tamanho do array)",
        ylabel="tempo (ciclos)",
        title=f"{algo.capitalize()} Sort",
    )

    ax.legend()
    ax.grid()

    # add standard deviation
    std = np.array([np.std(data[i][algo]) for i in data.keys()])
    plt.errorbar(
        x, measured_avg, yerr=std, fmt="none", ecolor="black", capsize=2, linewidth=1
    )

    plt.plot(x, measured, "ro", markersize=1)

    fig.set_size_inches(7, 5)
    fig.savefig(f"out/{algo}.png", dpi=300)
    # fig.savefig(f"out/{algo}-sorted.png", dpi=300)


def plot_together(data, labels, filename):
    plt.clf()
    x = np.array([int(i) for i in data.keys()])

    for label in labels:
        measured_avg = np.array([np.mean(data[i][label]) for i in data.keys()])
        plt.plot(x, measured_avg, label=f"{label} sort", linewidth=2)

        # add standard deviation
        std = np.array([np.std(data[i][label]) for i in data.keys()])
        plt.errorbar(
            x, measured_avg, yerr=std, fmt="none", ecolor="black", capsize=2, linewidth=1
        )

    plt.legend()
    plt.grid()
    plt.savefig(f"out/{filename}.png", dpi=300)


# with open("out/data_sorted.json") as f:
with open("out/data.json") as f:
    data = json.load(f)
    x = np.array([int(i) for i in data.keys()])

    n = x
    n_2 = np.array([i**2 for i in x])
    n_log_n = np.array([i * np.log(i) for i in x])

    plot("insertion", n_2, "n^2", data)
    plot("selection", n_2, "n^2", data)
    plot("merge", n_log_n, "n*log(n)", data)
    plot("heap", n_log_n, "n*log(n)", data)
    plot("quick", n_log_n, "n*log(n)", data)

    plot_together(data, ["insertion", "selection"], "quadratic")
    plot_together(data, ["merge", "heap", "quick"], "nlogn")

    # sorted
    # plot("insertion", n, "n", data)
    # plot("selection", n_2, "n^2", data)
    # plot("merge", n_log_n, "n*log(n)", data)
    # plot("heap", n_log_n, "n*log(n)", data)
    # plot("quick", n_2, "n*log(n)", data)

    # revsorted
    # plot("insertion", n_2, "n^2", data)
    # plot("selection", n_2, "n^2", data)
    # plot("merge", n_log_n, "n*log(n)", data)
    # plot("heap", n_log_n, "n*log(n)", data)
    # plot("quick", n_2, "n*log(n)", data)
