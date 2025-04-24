#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void concat_hex(char *dest, int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        const char *hex = va_arg(args, const char*);
        strcat(dest, hex);
    }
    va_end(args);
}

int main() {
    char final[512] = "62";
    char value[512] = "8202782183";
    char fid[100];

    char len_hex[3];

    // user input
    printf("Enter File Id : ");
    scanf("%s",fid);

    // TLV for FID
    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen(fid) / 2));
    concat_hex(value, 2, len_hex, fid);

    concat_hex(value, 1, "8A01058B");

    // TLV for Security
    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen("2F0601") / 2));
    concat_hex(value, 2, len_hex, "2F060181");

    printf("File Size : ");
    scanf("%s",fid);

    // TLV for file Size
    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen(fid) / 2));
    concat_hex(value, 2, len_hex, fid);

    // TLV Pin Tag
    concat_hex(value, 1, "C6");

    printf("Pin's: ");
    scanf("%s",fid);

    // Values of Pin
    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen(fid) / 2));
    concat_hex(value, 2, len_hex, fid);

    // ADD 8500
    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen("8500") / 2));
    concat_hex(value, 1, "8500");

    snprintf(len_hex, sizeof(len_hex), "%02X", (int)(strlen(value) / 2));
    concat_hex(final, 2, len_hex, value);

    printf("%s",final);
    return 0;
}
