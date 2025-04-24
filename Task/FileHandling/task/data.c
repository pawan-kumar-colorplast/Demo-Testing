#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FILE_NAME "../Output/data.bin"
#define FILE_SIZE (100 * 1024) 

typedef enum {
    MF = 0x01,
    DF = 0x02,
    EF = 0x03
} FileType;

typedef struct {
    unsigned char sw1;
    unsigned char sw2;
} StatusWord;

typedef struct {
    uint16_t file_id;
    FileType file_type;
    uint32_t file_size;
} FileHeader;

typedef struct {
    uint16_t cls;
    uint16_t ins;
    uint16_t p1;
    uint16_t p2;
} Header;

StatusWord sw_table[] = {
    {0x90, 0x00},
    {0x6A, 0x80},
    {0x6A, 0x82},
    {0x6A, 0x83},
    {0x62, 0x83},
    {0x69, 0x82},
    {0x67, 0x00},
    {0x6F, 0x00},
    {0x00, 0x00}
};

// Helper
const char* fileTypeToString(FileType type) {
    switch (type) {
        case MF: return "MF";
        case DF: return "DF";
        case EF: return "EF";
        default: return "Unknown";
    }
}

// Helper
void print_Data(FileHeader mf) {
    printf("File ID: 0x%04X\n",  mf.file_id);
    printf("File Type (Hex): 0x%02X\n", mf.file_type); 
    printf("File Type: %s\n", fileTypeToString(mf.file_type));
    printf("File Size: %u bytes\n", mf.file_size);
}

void concat_hex(char *dest, int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        const char *hex = va_arg(args, const char*);
        strcat(dest, hex);
    }
    va_end(args);
}

int isHeaderValidForCreate(Header h) {
    // Expected values
    const uint16_t exp_cls = 0x00;
    const uint16_t exp_ins = 0xE0;
    const uint16_t exp_p1 = 0x00;
    const uint16_t exp_p2 = 0x00;

    // Check if all values match the expected ones
    if (h.cls == exp_cls && h.ins == exp_ins && h.p1 == exp_p1 && h.p2 == exp_p2) {
        return 1;
    } else {
        return 0;
    }
}


int create_binary_file(const char *filename, size_t size) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Failed to create file.\n");
        return 1;
    }

    // Seek to the last byte to allocate space
    
    // SEEK_SET -> position is Beginning of the File Pointer
    // SEEK_CUR -> position is current of the file Pointer
    // SEEK_END -> position is end of the file Pointer

    // Ending pr SEEK_SET point na kr rha hu tb ye error aaega
    if (fseek(fp, size - 1, SEEK_SET) != 0) {
        printf("Failed to seek in file.\n");
        fclose(fp);
        return 1;
    }

    unsigned char zero = 0x00;
    fwrite(&zero, 1, 1, fp);

    fclose(fp);
    return 0;
}

int read_binary_file(const char *filename, size_t size) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error: File '%s' not found.\n", filename);
        return 1;
    }

    unsigned char *buffer = (unsigned char *)malloc(size);
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, size, fp);
    if (bytesRead != size) {
        printf("Warning: Expected %zu bytes, but read %zu bytes.\n", size, bytesRead);
    } else {
        printf("File read successfully. First 16 bytes:\n");
        for (int i = 0; i < 16 && i < bytesRead; i++) {
            printf("0x%02X ", buffer[i]);
        }
        printf("\n");
    }

    free(buffer);
    fclose(fp);
    return 0;
}

int create_file(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("File not found.\n");
        return 1;
    }

    FileHeader mf;
    mf.file_id = 0x3F00;
    mf.file_type = MF;
    mf.file_size = FILE_SIZE;

    char *fci = "63";
    char *value = "820278218302";
    char *fid = "";
    char *value2 = "8A01058B03";
    char *defaultARR = "2F06" ;
    char *value3 = "018102";
    char *fsize = "0000";
    char *pin = "C6";
    
    print_Data(mf);
}

int main() {
    
    // if(create_binary_file(FILE_NAME, FILE_SIZE) == 0) {
    //     printf("Binary file created Successfully");
    // }

    // read_binary_file(FILE_NAME, FILE_SIZE);

    // create_file(FILE_NAME);

    Header h;

    h.cls = 0x00;
    h.ins = 0xE0;
    h.p1 = 0x00;
    h.p2 = 0x00;

    if(isHeaderValidForCreate(h)) {
        create_file(FILE_NAME);
    }else {
        printf("Header values are different. create_file function will not be called.\n");
    }

    return 0;
}
