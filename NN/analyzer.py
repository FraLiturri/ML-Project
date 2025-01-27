# %%
import numpy as np
import subprocess
from matplotlib import pyplot as plt
import sys
from decimal import Decimal, ROUND_DOWN

plt.rc("axes", titlesize=14)  # Dimensione titolo degli assi
plt.rc("axes", labelsize=14)  # Dimensione etichette degli assi
plt.rc("xtick", labelsize=14)  # Dimensione etichette tick sull'asse X
plt.rc("ytick", labelsize=14)  # Dimensione etichette tick sull'asse Y
plt.rc("legend", fontsize=14)  # Dimensione legenda
plt.rc("font", size=14)  # Dimensione generale del font


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
    val_loss_path = "NN_results/val_loss.txt"
    test_loss_path = "NN_results/test_loss.txt"

    with open(test_loss_path, "r") as file:
        test_loss = file.readline().strip()

    val_loss = np.loadtxt(val_loss_path)
    tr_loss = np.loadtxt(training_loss_path)

    print(f"Training loss converges to: {tr_loss[len(tr_loss)-1]}.")
    print(f"Validation loss converges to: {val_loss[len(val_loss)-1]}.")
    print(f"Test loss is: {test_loss}.\n")

    x_val = np.linspace(1, len(val_loss), len(val_loss))
    x_tr = np.linspace(1, len(tr_loss), len(tr_loss))

    plt.errorbar(x_tr, tr_loss, fmt="--", label="Training loss")
    plt.errorbar(x_val, val_loss, fmt="--", label="Validation loss")

    plt.grid(ls="dashed", axis="both")
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.title("Training and validation loss")
    plt.legend(loc="best")
    plt.savefig("NN_results/no_nest.pdf")
    plt.show()


elif str(sys.argv[1]) == "loss_mean":
    filepath = "NN_results/loss_collection.txt"
    loss = np.loadtxt(filepath)
    mean_loss = loss.mean()
    std_loss = loss.std()
    print(f"\nMean loss is: {mean_loss} +/- {std_loss}.\n")

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
