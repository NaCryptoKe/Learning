#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void write_int(int fd, int n);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        write(1, "Argument needed.\n", 17);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int fd = open (argv[i], O_RDONLY);

        if (fd == -1) {
            write(1, "Error opening file\n", 19);
            return 1;
        }

        int newline = 0;
        int wordcount = 0;
        int bytecount = 0;
        int inword = 0;

        int ch;
        while (read(fd, &ch, 1) > 0) {
            bytecount++;
            if (ch == '\n') newline++;

            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') inword = 0;
            else if (!inword) {
                inword = 1;
                wordcount++;
            }
        }

        int len = 0;
        while (argv[i][len]) len++;

        write_int(1, newline);
        write(1, " ", 1);
        write_int(1, wordcount);
        write(1, " ", 1);
        write_int(1, bytecount);
        write(1, " ", 1);
        write (1, argv[i], len);
        write(1, "\n", 1);

        close(fd);
    }
    return 0;
}

void write_int(int fd, int n) {
    char buf[12];
    int i = 11;
    if (n == 0) { write(fd, "0", 1); return; }
    while (n > 0) {
        buf[--i] = '0' + (n % 10);
        n /= 10;
    }
    write(fd, buf + i, 11 - i);
}
