#include <stdio.h>
#include <string.h>

#define FILE_SIZE 102400 // 100 KB = 100 * 1024 bytes

int main() {
    FILE *fp;
    const char *message = "this is pawan"; 
    size_t message_len = strlen(message);

    fp = fopen("Output/allocated.bin", "wb");
    
    if (fp == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    fseek(fp, FILE_SIZE - 1, SEEK_SET);
    fwrite(message, 1, message_len, fp);
    fclose(fp);

    printf("File created\n");

    return 0;
}
