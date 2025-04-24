#include <stdio.h>
#include <string.h>

#define FILE_ALLOCATE 102400  // 100kb = 100 * 1024

void convertMessageIntoHex(char *message, char *hexString) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        sprintf(&hexString[i * 3], "%02X ", (unsigned char)message[i]); 
    }
    hexString[i * 3 - 1] = '\0'; 
}


int writeBinary(const char *hexData, int length, const char *fileNameBase) {
    char fileName[100];
    snprintf(fileName, sizeof(fileName), "%s.txt", fileNameBase);

    FILE* fp = fopen(fileName, "w+"); 

    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    fseek(fp, 0, SEEK_SET);
    fwrite(hexData, sizeof(char), length, fp);
    fclose(fp);

    return 1;
}

void readFile(const char *fileNameBase) {
    char fileName[100];
    snprintf(fileName, sizeof(fileName), "%s.txt", fileNameBase);

    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return;
    }

    // Read and display file content with space separation
    char buffer[1024];
    printf("File content (hex values separated by spaces):\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);  // Directly print the hex string (already space-separated)
    }

    fclose(fp);
}

void createText(char *fileName) {
    char message[100];
    char hexData[300]; 

    printf("Enter Message: ");
    scanf("%[^\n]", message);  

    convertMessageIntoHex(message, hexData);

    if (writeBinary(hexData, strlen(hexData), fileName)) {
        printf("File writing done.\n");
    } else {
        printf("Error occurred.\n");
    }
}

int main() {
    char *fileName = "allocate"; 
    
    createText(fileName);
    readFile(fileName);

    return 0;
}
