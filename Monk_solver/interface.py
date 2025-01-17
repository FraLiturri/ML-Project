# %%
import numpy as np
import multiprocessing as mp
import Monk_solver.parameters as param
import sys
import subprocess
from itertools import product
from loguru import logger
import tkinter as tk
from tkinter import messagebox
import multiprocessing as mp
import os
from customtkinter import *
import customtkinter as ctk

IsCompilationGood = False
NomeFileDaCompilare = "main.cpp"
run_command = "main.exe"

# Standard parameters for grid search;
Eta_Min_Default = 0.01
Eta_Max_Default = 0.5
Lambda_Min_Default = 0
Lambda_Max_Default = 0
Alpha_Min_Default = 0
Alpha_Max_Default = 0
Step1_Default = 10
Step2_Default = 1
Step3_Default = 1
Training_Steps_Default = 200
CPU_Number = os.cpu_count()


# Standard parameters for single run;
Eta_single = 0.2
Lambda_single = 0.0
Alpha_single = 0.0


def CallMain(Inputs):
    command = [
        run_command,
        str(Inputs[0]),
        str(Inputs[1]),
        str(Inputs[2]),
        str(Inputs[3]),
    ]
    result = subprocess.run(command, capture_output=True, text=True)
    print(result.stdout)


def Compile():
    global IsCompilationGood
    try:
        process = subprocess.run(
            ["cd Monksolver; g++", "-o", "main.exe; cd..", NomeFileDaCompilare],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True,
        )
        IsCompilationGood = True
    except FileNotFoundError:
        logger.error("Fatal error: main.exe not found.")
        messagebox.showerror(
            "Error.",
            "Push Ok and read error in python console.",
        )
        IsCompilationGood = False
    except subprocess.CalledProcessError as e:
        logger.error("Fatal Error: main compilation failed.")
        messagebox.showerror(
            "Error.",
            "Push Ok and read error in python console.",
        )
        IsCompilationGood = False
        print(e.stderr)


def BuildGrid(eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3):
    MyGrid = param.Grid(
        eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3
    )
    return MyGrid


if __name__ == "__main__":

    def submit_values():

        global IsCompilationGood
        if IsCompilationGood:
            subprocess.run(
                ["rm", "grid_results.txt"], capture_output=True, text=True
            )
            try:
                if (
                    (not eta_min_entry.get())
                    & (not eta_max_entry.get())
                    & (not lambda_min_entry.get())
                    & (not lambda_max_entry.get())
                    & (not alpha_min_entry.get())
                    & (not alpha_max_entry.get())
                    & (not steps_eta_entry.get())
                    & (not steps_lambda_entry.get())
                    & (not steps_alpha_entry.get())
                    & (not training_steps_entry.get())
                ):
                    MyGrid = BuildGrid(
                        Eta_Min_Default,
                        Eta_Max_Default,
                        Lambda_Min_Default,
                        Lambda_Max_Default,
                        Alpha_Min_Default,
                        Alpha_Max_Default,
                        Step1_Default,
                        Step2_Default,
                        Step3_Default,
                    )
                    Inputs = [
                        [x.Eta, x.Lambda, x.Alpha, Training_Steps_Default]
                        for x in MyGrid.Grid
                    ]
                    with mp.Pool(processes=CPU_Number) as pool:
                        results = pool.map(CallMain, Inputs)
                else:
                    eta_min = float(eta_min_entry.get())
                    eta_max = float(eta_max_entry.get())
                    lambda_min = float(lambda_min_entry.get())
                    lambda_max = float(lambda_max_entry.get())
                    alpha_min = float(alpha_min_entry.get())
                    alpha_max = float(alpha_max_entry.get())
                    step1 = int(steps_eta_entry.get())
                    step2 = int(steps_lambda_entry.get())
                    step3 = int(steps_alpha_entry.get())
                    training_steps = int(training_steps_entry.get())

                    if (
                        (eta_min > eta_max)
                        | (lambda_min > lambda_max)
                        | (alpha_min > alpha_max)
                    ):
                        raise ValueError
                    if (step1 <= 0) | (step2 <= 0) | (step3 <= 0):
                        raise ValueError
                    if training_steps < 0:
                        raise ValueError
                    MyGrid = param.Grid(
                        eta_min,
                        eta_max,
                        lambda_min,
                        lambda_max,
                        alpha_min,
                        alpha_max,
                        step1,
                        step2,
                        step3,
                    )
                    Inputs = [
                        [x.Eta, x.Lambda, x.Alpha, training_steps] for x in MyGrid.Grid
                    ]
                    with mp.Pool(processes=CPU_Number) as pool:
                        results = pool.map(CallMain, Inputs)

            except ValueError:
                messagebox.showerror("Error", "Please insert valid values.")
        else:
            messagebox.showinfo("Compilation filed.")

    def submit_values_for_single_training():
        global IsCompilationGood
        if IsCompilationGood:
            subprocess.run(
                ["rm", "grid_results.txt"], capture_output=True, text=True
            )
            try:
                if (
                    (not single_eta_entry.get())
                    & (not single_lambda_entry.get())
                    & (not single_alpha_entry.get())
                    & (not single_training_steps_entry.get())
                ):
                    Inputs = [
                        Eta_single,
                        Lambda_single,
                        Alpha_single,
                        Training_Steps_Default,
                    ]
                    print(
                        "---% Single run %---",
                    )
                    CallMain(Inputs)

                else:
                    etaH = float(single_eta_entry.get())
                    lambdaH = float(single_lambda_entry.get())
                    alphaH = float(single_alpha_entry.get())
                    training_Steps = float(single_training_steps_entry.get())
                    Inputs = [etaH, lambdaH, alphaH, training_Steps]
                    if training_Steps < 0:
                        raise ValueError
                    if etaH < 0:
                        raise ValueError
                    CallMain(Inputs)
            except ValueError:
                messagebox.showerror("Error", "Insert valid values.")

        else:
            messagebox.showinfo("Compilation failed.")
        return 1

    try:
        process = subprocess.run(
            ["cd Monk_solver; g++", "-o", "main.exe; cd..", NomeFileDaCompilare],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True,
        )
        IsCompilationGood = True
    except FileNotFoundError:
        logger.error("Fatal error: main not found.")
        messagebox.showerror("Error")
        IsCompilationGood = False
    except subprocess.CalledProcessError as e:
        logger.error("Errore fatale: la compilazione del main ha prodotto un errore.")
        messagebox.showerror(
            "Errore",
            "La compilazione non ha avuto buon fine: leggi l'errore da terminale dopo aver premuto Ok.",
        )
        IsCompilationGood = False
        print(e.stderr)

    # Set the appearance mode and theme
    ctk.set_appearance_mode("Dark")
    ctk.set_default_color_theme("blue")

    # Function for the "Done" button
    def done_action():
        print("Done button clicked")

    # Function for the "Ricompile" button
    def recompile_action():
        try:
            subprocess.run(
                ["cd Monk_solver; g++", "-o", "main.exe; cd..", "Monk_solver/main.cpp"],
                check=True,
            )
            print("Compilation successful.")
        except subprocess.CalledProcessError as e:
            print("Compilation failed:", e)

    # Create the main application window
    root = ctk.CTk()
    root.title("Grid Search and Single Run")

    # Create a tab view
    tab_view = ctk.CTkTabview(root)
    tab_view.pack(expand=True, fill="both", padx=20, pady=20)

    grid_tab = tab_view.add("Grid Search")
    single_run_tab = tab_view.add("Single Run")

    eta_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta min [{Eta_Min_Default}]"
    )
    eta_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta max [{Eta_Max_Default}]"
    )

    eta_min_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
    eta_max_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")

    lambda_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda min [{Lambda_Min_Default}]"
    )
    lambda_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda max [{Lambda_Max_Default}]"
    )

    lambda_min_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
    lambda_max_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

    alpha_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha min [{Alpha_Min_Default}]"
    )
    alpha_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha max [{Alpha_Max_Default}]"
    )

    alpha_min_entry.grid(row=2, column=0, padx=10, pady=5, sticky="w")
    alpha_max_entry.grid(row=2, column=3, padx=10, pady=5, sticky="w")

    steps_eta_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta steps [{Step1_Default}]"
    )
    steps_lambda_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda steps [{Step2_Default}]"
    )
    steps_alpha_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha steps [{Step3_Default}]"
    )
    training_steps_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Epochs [{Training_Steps_Default}]"
    )

    steps_eta_entry.grid(row=3, column=0, padx=10, pady=5, sticky="w")
    steps_lambda_entry.grid(row=3, column=3, padx=10, pady=5, sticky="w")
    steps_alpha_entry.grid(row=4, column=0, padx=10, pady=5, sticky="w")
    training_steps_entry.grid(row=4, column=3, padx=10, pady=5, sticky="w")

    done_button = ctk.CTkButton(grid_tab, text="Done", command=submit_values)
    done_button.grid(row=5, column=0, columnspan=2, pady=20)

    recompile_button = ctk.CTkButton(grid_tab, text="Ricompile", command=Compile)
    recompile_button.grid(row=5, column=2, columnspan=2, pady=20)

    # Single Run Tab
    single_eta_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Eta [{Eta_single}]"
    )
    single_lambda_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Lambda [{Lambda_single}]"
    )
    single_alpha_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Alpha [{Alpha_single}]"
    )
    single_training_steps_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Epochs [{Training_Steps_Default}]"
    )

    single_eta_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
    single_lambda_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")
    single_alpha_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
    single_training_steps_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

    done_button_single = ctk.CTkButton(
        single_run_tab, text="Done", command=submit_values_for_single_training
    )
    done_button_single.grid(row=5, column=0, columnspan=2, pady=20)

    recompile_button_single = ctk.CTkButton(
        single_run_tab, text="Ricompile", command=Compile
    )
    recompile_button_single.grid(row=5, column=2, columnspan=2, pady=20)

    root.lift()
    root.mainloop()

# %%
