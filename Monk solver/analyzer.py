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


if str(sys.argv[1]) == "plot":
    training_loss_path = "NN_results/training_loss.txt"
    tr_loss = np.loadtxt(training_loss_path)
    x_tr = np.linspace(1, len(tr_loss), len(tr_loss))
    plt.errorbar(x_tr, tr_loss, fmt="--", label="Training loss")
    plt.grid(ls="dashed", axis="both")
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.title("Training loss")
    plt.savefig("NN_results/loss_plot.pdf")
    plt.legend(loc="best")
    plt.show()

elif str(sys.argv[1]) == "loss_mean":
    filepath = "NN_results/loss_collection.txt"
    loss = np.loadtxt(filepath)
    mean_loss = loss.mean()
    std_loss = loss.std()
    print(
        f"\nMean loss is: {tronca_decimal(mean_loss, 3)} +/- {tronca_decimal(std_loss,3)}.\n"
    )

elif str(sys.argv[1]) == "iterate":
    exe_path = sys.argv[2]
    number_of_runs = int(sys.argv[3])
    run_exe(exe_path, number_of_runs)

elif str(sys.argv[1]) == "clear":
    filepath = "NN_results/loss_collection.txt"
    lines = np.loadtxt(
        filepath,
    )
    cleaned_lines = [line.strip() for line in lines if line.strip()]
    np.savetxt(filepath)

else:
    print("\nError...\n")
