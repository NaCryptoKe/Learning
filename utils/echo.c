#include "print.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print("Pass an argument");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        print("%s ", argv[i]);
    }

    return 0;
}
