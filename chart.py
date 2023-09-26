
import os
import json
import matplotlib.pyplot as plt
import numpy as np

if not os.path.exists('charts'):
    os.makedirs('charts')


def plot(algo, theoretical, theo_label, data):
    x = np.array([int(i) for i in data.keys()])

    measured = np.array([data[i][algo] for i in data.keys()])
    measured_avg = np.array([np.mean(data[i][algo]) for i in data.keys()])
    
    # adjust theoretical to fit measured, consider lowest and highest n
    mult = (measured_avg[-1] / theoretical[-1])
    theoretical = theoretical * mult

    theo_name = f"teórico ({theo_label} * {mult:.2e})"

    fig, ax = plt.subplots()
    plt.plot(x, measured_avg, label='medido (média)', linewidth=2)
    plt.plot(x, theoretical, label=theo_name, linestyle=':')
    ax.set(xlabel='n', ylabel='tempo (clocks)',
           title=f"{algo.capitalize()} Sort")
    
    ax.legend()

    plt.plot(x, measured, 'ko', label='medido', markersize=1)

    ax.grid()

    fig.savefig(f"out/{algo}.png")


with open('out/data.json') as f:
    data = json.load(f)
    x = np.array([int(i) for i in data.keys()])

    n_2 = np.array([i**2 for i in x])
    n_log_n = np.array([i*np.log(i) for i in x])

    plot('insertion', n_2, 'n^2', data)
    plot('selection', n_2, 'n^2', data)
    plot('merge', n_log_n, 'n*log(n)', data)
    plot('heap', n_log_n, 'n*log(n)', data)
    plot('quick', n_log_n, 'n*log(n)', data)
