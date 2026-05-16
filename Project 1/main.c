#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Error: Missing filename argument.\n");
        fprintf(stderr, "Usage: %s <filename>", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    
    char buffer[100];
    char long_line = 0;
    int line = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        ssize_t len = strlen(buffer);
        
        if(!long_line) {
            printf("%d. ", line);
            line++;
        }
        printf("%s", buffer);
    
        if (len > 0 && buffer[len-1] == '\n') {
            long_line = 0;
        } else {
            long_line = 1;
        }
    }
    
    fclose(file);
    return 0;
}
