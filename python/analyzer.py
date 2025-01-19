# %%
import numpy as np
import subprocess
from matplotlib import pyplot as plt
import sys
from decimal import Decimal, ROUND_DOWN


def tronca_decimal(numero, cifre_decimali):
    formato = f"1.{'0' * cifre_decimali}"  # Crea il formato, ad esempio "1.00"
    return Decimal(numero).quantize(Decimal(formato), rounding=ROUND_DOWN)


def run_exe(file_path, n):
    for i in range(n):
        try:
            print(f"Running {i + 1} of {n}")
            result = subprocess.run(file_path, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error executing {i + 1}: {e}")
        except FileNotFoundError:
            print(f"File not found: {file_path}")
            break


def plot():
    training_loss_path = "Monk_solver/NN_results/training_loss.txt"
    val_loss_path = "Monk_solver/NN_results/val_loss.txt"
    test_loss_path = "Monk_solver/NN_results/test_loss.txt"

    tr_loss = np.loadtxt(training_loss_path)
    val_loss = np.loadtxt(val_loss_path)
    x_tr = np.linspace(1, len(tr_loss), len(tr_loss))
    x_val = np.linspace(1, len(val_loss), len(val_loss))
    plt.errorbar(x_tr, tr_loss, fmt="--", label="Training loss")
    plt.errorbar(x_val, val_loss, fmt ="--", label = "Validation loss")
    plt.grid(ls="dashed", axis="both")
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.title("Training loss")
    plt.savefig("Monk_solver/NN_results/loss_plot.pdf")
    plt.legend(loc="best")
    plt.show()


def iterate():
    exe_path = sys.argv[2]
    number_of_runs = int(sys.argv[3])
    run_exe(exe_path, number_of_runs)
