# %%
import customtkinter as ctk
import subprocess
import os

# Set the appearance mode and theme
ctk.set_appearance_mode("Dark")
ctk.set_default_color_theme("blue")


# Function for the "Done" button
def done_action():
    print("Done button clicked")


# Function for the "Ricompile" button
def recompile_action():
    try:
        subprocess.run(["g++", "-o", "main.exe", "main.cpp"], check=True)
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

eta_min_entry = ctk.CTkEntry(grid_tab, placeholder_text="Eta min")
eta_max_entry = ctk.CTkEntry(grid_tab, placeholder_text="Eta max")

eta_min_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
eta_max_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")

lambda_min_entry = ctk.CTkEntry(grid_tab, placeholder_text="Lambda min")
lambda_max_entry = ctk.CTkEntry(grid_tab, placeholder_text="Lambda max")

lambda_min_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
lambda_max_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

alpha_min_entry = ctk.CTkEntry(grid_tab, placeholder_text="Alpha min")
alpha_max_entry = ctk.CTkEntry(grid_tab, placeholder_text="Alpha max")

alpha_min_entry.grid(row=2, column=0, padx=10, pady=5, sticky="w")
alpha_max_entry.grid(row=2, column=3, padx=10, pady=5, sticky="w")

eta_step = ctk.CTkEntry(grid_tab, placeholder_text="Eta steps")
lambda_step = ctk.CTkEntry(grid_tab, placeholder_text="Lambda steps")
alpha_step = ctk.CTkEntry(grid_tab, placeholder_text="Alpha steps")
training_iter = ctk.CTkEntry(grid_tab, placeholder_text="Training iterations")

eta_step.grid(row=3, column=0, padx=10, pady=5, sticky="w")
lambda_step.grid(row=3, column=3, padx=10, pady=5, sticky="w")
alpha_step.grid(row=4, column=0, padx=10, pady=5, sticky="w")
training_iter.grid(row=4, column=3, padx=10, pady=5, sticky="w")

done_button = ctk.CTkButton(grid_tab, text="Done", command=done_action)
done_button.grid(row=5, column=0, columnspan=2, pady=20)

recompile_button = ctk.CTkButton(grid_tab, text="Ricompile", command=recompile_action)
recompile_button.grid(row=5, column=2, columnspan=2, pady=20)

# Single Run Tab
eta = ctk.CTkEntry(single_run_tab, placeholder_text = "Eta [0.01]")
lambda_ = ctk.CTkEntry(single_run_tab, placeholder_text = "Lambda [0.0]")
alpha = ctk.CTkEntry(single_run_tab, placeholder_text = "Alpha [0.0]")
iter = ctk.CTkEntry(single_run_tab, placeholder_text= "Iterations [100]")

eta.grid(row=0, column=0, padx=10, pady=5, sticky="w")
lambda_.grid(row=0, column=3, padx=10, pady=5, sticky="w")
alpha.grid(row=1, column=0, padx=10, pady=5, sticky="w")
iter.grid(row=1, column=3, padx=10, pady=5, sticky="w")

done_button = ctk.CTkButton(single_run_tab, text="Done", command=done_action)
done_button.grid(row=5, column=0, columnspan=2, pady=20)

recompile_button = ctk.CTkButton(
    single_run_tab, text="Ricompile", command=recompile_action
)
recompile_button.grid(row=5, column=2, columnspan=2, pady=20)

# Run the application
root.lift()
root.mainloop()

# %%
