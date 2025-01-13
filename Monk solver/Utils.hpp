/* #include <iostream>
#include <fstream>
#include <fcntl.h>   // Per open, flock
//#include <sys/file.h> // Per flock
//#include <unistd.h>  // Per close
#include <cstring>   // Per strerror
#include <stdexcept> // Per std::runtime_error

void writeToFileSafely(const std::string &filename, const std::string &content) {
    // Apri il file in modalità append
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        throw std::runtime_error("Errore nell'apertura del file: " + std::string(strerror(errno)));
    }

    // Acquisisce il lock...
    if (flock(fd, LOCK_EX) == -1) {
        close(fd);
        throw std::runtime_error("Errore nell'acquisire il lock: " + std::string(strerror(errno)));
    }

    // Scrivi il contenuto nel file
    ssize_t written = write(fd, content.c_str(), content.size());
    if (written == -1) {
        flock(fd, LOCK_UN); // Rilascia il lock prima di uscire in errore
        close(fd);
        throw std::runtime_error("Errore nella scrittura nel file: " + std::string(strerror(errno)));
    }

    // Rilascia il lock
    if (flock(fd, LOCK_UN) == -1) {
        close(fd);
        throw std::runtime_error("Errore nel rilascio del lock: " + std::string(strerror(errno)));
    }

    // Chiudi il file
    close(fd);
}
 */