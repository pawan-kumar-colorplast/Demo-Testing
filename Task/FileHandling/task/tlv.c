#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    char final[512] = "63"; 
    char value[512] = "820278218302"; 
    char value2[] = "8A01058B";
    char default_ARR[] = "2F0601";
    char value3[] = "81";
    char value4[] = "C6";


    char fid[] = "7FAB";
    char fileSize[] = "0000";
    char pin[] = "83010A";

    // Compute lengths of hex values (each 2 chars = 1 byte)
    int byte_len = strlen(default_ARR) / 2;
    int byte_len2 = strlen(fileSize) / 2;
    int byte_len3 = strlen(pin) / 2;

    char len_hex[3];
    snprintf(len_hex, sizeof(len_hex), "%02X", byte_len);

    char len_hex2[3];
    snprintf(len_hex2, sizeof(len_hex2), "%02X", byte_len2);

    char len_hex3[3];
    snprintf(len_hex3, sizeof(len_hex3), "%02X", byte_len3);

    // Append values in proper TLV structure
    strcat(value, fid);
    strcat(value, value2);
    strcat(value, len_hex);
    strcat(value, default_ARR);
    strcat(value, value3);
    strcat(value, len_hex2);
    strcat(value, fileSize);
    strcat(value, value4);
    strcat(value, len_hex3);
    strcat(value, pin);

    // Calculate total length
    int byte_len4 = strlen(value) / 2;
    char len_hex4[3];
    snprintf(len_hex4, sizeof(len_hex4), "%02X", byte_len4);

    // Append length and value to final TLV
    strcat(final, len_hex4);
    strcat(final, value);

    printf("Final TLV: %s\n", final);

    return 0;
}


