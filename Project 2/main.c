#include <stdio.h>
#include <string.h>

int main(argc, argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: you must pass to parameters\n");
        fprintf(stderr, "Usage: ./main <word> <file>");
        return 1;
    }

    FILE *file = fopen(argv[2], "r");

    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char buffer[1000];
    char word[strlen(argv[1])];
    int length = 0;
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      for (length; length < strlen(argv[1]); length++) {
        if (buffer[length])
}  
}
    fclose(file);
    return 0;
}
