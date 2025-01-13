def create_hpp_file(filename, include_path):
    try:
        # Apri il file in modalità scrittura
        with open(filename, "w") as file:
            # Scrivi la direttiva #include con il percorso specificato
            file.write(f'#include "{include_path}"\n')
        print(f"File '{filename}' created with success!")
    except Exception as e:
        print(f"Error: {e}")
