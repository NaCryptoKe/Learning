#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 2) {
        write(2, "Argument needed.\n", 17);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int fd = open (argv[i], O_RDONLY);

        if (fd == -1) {
            write(2, "Error opening file\n", 19);
            close(fd);
            return 1;
        }
        
        char buffer[BUFFER_SIZE];

        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            ssize_t bytes_written = write(1, buffer, bytes_read);
        }

        if (bytes_read == -1)   write(2, "Error reading from source file\n", 31);

        close(fd);
    }

    return 0;
}
