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


def plot_random_sorted_rev(algo, data, data_sorted, data_revsorted):
    plt.clf()
    x = np.array([int(i) for i in data_sorted.keys()])

    # sorted and revsorted have shape (15,) but data has shape (30,)
    # so we need to take only the first 15 elements
    data_15 = {k: v for k, v in data.items() if int(k) <= 150000}

    fig, ax = plt.subplots()

    measured_avg = np.array([np.mean(data_15[i][algo]) for i in data_15.keys()])
    plt.plot(x, measured_avg, label="array aleatória", linewidth=2)
    std = np.array([np.std(data_15[i][algo]) for i in data_15.keys()])
    plt.errorbar(
        x, measured_avg, yerr=std, fmt="none", ecolor="black", capsize=2, linewidth=1
    )

    measured_avg = np.array([np.mean(data_sorted[i][algo]) for i in data_sorted.keys()])
    plt.plot(x, measured_avg, label="array ordenada (asc)", linewidth=2)
    std = np.array([np.std(data_sorted[i][algo]) for i in data_sorted.keys()])
    plt.errorbar(
        x, measured_avg, yerr=std, fmt="none", ecolor="black", capsize=2, linewidth=1
    )

    measured_avg = np.array([np.mean(data_revsorted[i][algo]) for i in data_revsorted.keys()])
    plt.plot(x, measured_avg, label="array ordenada (desc)", linewidth=2)
    std = np.array([np.std(data_revsorted[i][algo]) for i in data_revsorted.keys()])
    plt.errorbar(
        x, measured_avg, yerr=std, fmt="none", ecolor="black", capsize=2, linewidth=1
    )

    ax.set(
        xlabel="n (tamanho do array)",
        ylabel="tempo (ciclos)",
        title=f"{algo.capitalize()} Sort",
    )
    ax.legend()
    ax.grid()

    fig.set_size_inches(7, 5)
    fig.savefig(f"out/{algo}-all3.png", dpi=300)

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

# data = json.load(open("out/data.json"))
# data_sorted = json.load(open("out/data_sorted.json"))
# data_revsorted = json.load(open("out/data_revsorted.json"))

# plot_random_sorted_rev("insertion", data, data_sorted, data_revsorted)
# plot_random_sorted_rev("selection", data, data_sorted, data_revsorted)
# plot_random_sorted_rev("merge", data, data_sorted, data_revsorted)
# plot_random_sorted_rev("heap", data, data_sorted, data_revsorted)
# plot_random_sorted_rev("quick", data, data_sorted, data_revsorted)
