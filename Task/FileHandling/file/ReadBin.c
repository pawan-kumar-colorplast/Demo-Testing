#include <stdio.h>
#define FILE_SIZE 102400 

int main() {
    FILE *fp = fopen("Output/allocated.bin", "rb");
    char data[100];

    if (fp == NULL) {
        printf("Error in Reading File\n");
        return 1;
    }

    fseek(fp,FILE_SIZE - 20, SEEK_SET);

    fread(data, sizeof(data) - 1, 1, fp);
    data[99] = '\0';  
    fclose(fp);

    printf("File Read completed\n");
    printf("%s\n", data);
    return 0;
}
