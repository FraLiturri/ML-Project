file_name = "C:/Users/franc/OneDrive/Desktop/ML-Project/ML-Project/Monk solver/eigen_path.hpp"


def create_hpp_file(include_path):
    try:
        # Apri il file in modalità scrittura
        with open(file_name, "w") as file:
            # Scrivi la direttiva #include con il percorso specificato
            file.write(f'#include "{include_path}"\n')
        print(f"File '{file_name}' created with success!")
    except Exception as e:
        print(f"Error: {e}")
