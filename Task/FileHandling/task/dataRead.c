#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "../Output/data.bin"
#define FILE_SIZE (100 * 1024) 

int main() {
    FILE *fp = fopen(FILE_NAME, "rb");  // Open for reading in binary mode

    if (fp == NULL) {
        printf("Error: File '%s' not found.\n", FILE_NAME);
        return 1;
    }

    // Allocate buffer to read file contents
    unsigned char *buffer = (unsigned char *)malloc(FILE_SIZE);
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    // Read file into buffer
    size_t bytesRead = fread(buffer, 1, FILE_SIZE, fp);
    if (bytesRead != FILE_SIZE) {
        printf("Warning: Expected to read %d bytes, but read %zu bytes.\n", FILE_SIZE, bytesRead);
    } else {
        int i;
        for (i = 0; i < FILE_SIZE; i++) {
            printf("0x%02X ", buffer[i]);
        }
        printf("\n");

        printf("%d",i);
    }

    // Clean up
    fclose(fp);
    free(buffer);

    return 0;
}
