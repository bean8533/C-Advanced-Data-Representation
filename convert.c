// https://github.com/bean8533/C-Advanced-Data-Representation/tree/main

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void div_convert(uint32_t n, int base, char *out) {
    char temp[65]; // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Extract digits from right to left
    while (n > 0) {
        const int remainder = n % base;
        n = n / base;

        // Convert digit to character
        if (remainder < 10)
            temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A' + (remainder - 10);
    }
    temp[pos] = '\0';

    // Reverse the result
    int start = 0;
    int end = strlen(temp) - 1;

    while (start < end) {
        const char temp_character = temp[start];

        temp[start] = temp[end];
        temp[end] = temp_character;

        start++;
        end--;
    }

    strcpy(out, temp);
}

void sub_convert(uint32_t n, int base, char *out) {
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // find highest power
    uint32_t power = 1;
    while (power <= n / base)
        power *= base;

    // subtract multiples to convert
    while (power > 0) {
        const int digit = n / power;

        // Convert digit to character
        if (digit < 10)
            out[pos++] = '0' + digit;
        else
            out[pos++] = 'A' + (digit - 10);

        n %= power;
        power /= base;
    }
    out[pos] = '\0';
}

void print_tables(uint32_t n) {
    const uint32_t original = n;
    const uint32_t left_shifted = n << 3;
    const uint32_t and = n & 0xFF;

    // create variables to store results
    char bin_str[33];
    char oct_str[12];
    char dec_str[11];
    char hex_str[9];

    div_convert(original, 2, bin_str);
    div_convert(original, 8, oct_str);
    div_convert(original, 10, dec_str);
    div_convert(original, 16, hex_str);
    printf("Original: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin_str, oct_str, dec_str, hex_str);

    div_convert(left_shifted, 2, bin_str);
    div_convert(left_shifted, 8, oct_str);
    div_convert(left_shifted, 10, dec_str);
    div_convert(left_shifted, 16, hex_str);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin_str, oct_str, dec_str, hex_str);

    div_convert(and, 2, bin_str);
    div_convert(and, 8, oct_str);
    div_convert(and, 10, dec_str);
    div_convert(and, 16, hex_str);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin_str, oct_str, dec_str, hex_str);
}


// -------------------Assignment 2 functions-------------------


void oct_to_bin(const char *oct, char *out) {
    const char *oct_as_bin[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    out[0] = '\0';

    for (int i = 0; oct[i] != '\0'; i++) {
        if (oct[i] >= '0' && oct[i] <= '7') {
            strcat(out, oct_as_bin[oct[i] - '0']);
        }
    }
}

void oct_to_hex(const char *oct, char *out) {
    // skip rest of function if input is 0
    if (strcmp(oct, "0") == 0) {
        strcpy(out, "0");
        return;
    }

    char binary_str[100];
    oct_to_bin(oct, binary_str);

    char grouped_binary[104];
    grouped_binary[0] = '\0';

    const int len = strlen(binary_str);
    const int extra_zeros = (4 - (len % 4)) % 4;

    for (int i = 0; i < extra_zeros; i++) {
        strcat(grouped_binary, "0");
    }
    strcat(grouped_binary, binary_str);

    int out_pos = 0;
    int leading_zero = 1; // check if at beginning

    for (int i = 0; i < strlen(grouped_binary); i += 4) {
        char chunk[5];
        strncpy(chunk, grouped_binary + i, 4);
        chunk[4] = '\0';

        char hex_digit = '\0';
        if (strcmp(chunk, "0000") == 0) hex_digit = '0';
        else if (strcmp(chunk, "0001") == 0) hex_digit = '1';
        else if (strcmp(chunk, "0010") == 0) hex_digit = '2';
        else if (strcmp(chunk, "0011") == 0) hex_digit = '3';
        else if (strcmp(chunk, "0100") == 0) hex_digit = '4';
        else if (strcmp(chunk, "0101") == 0) hex_digit = '5';
        else if (strcmp(chunk, "0110") == 0) hex_digit = '6';
        else if (strcmp(chunk, "0111") == 0) hex_digit = '7';
        else if (strcmp(chunk, "1000") == 0) hex_digit = '8';
        else if (strcmp(chunk, "1001") == 0) hex_digit = '9';
        else if (strcmp(chunk, "1010") == 0) hex_digit = 'A';
        else if (strcmp(chunk, "1011") == 0) hex_digit = 'B';
        else if (strcmp(chunk, "1100") == 0) hex_digit = 'C';
        else if (strcmp(chunk, "1101") == 0) hex_digit = 'D';
        else if (strcmp(chunk, "1110") == 0) hex_digit = 'E';
        else if (strcmp(chunk, "1111") == 0) hex_digit = 'F';
        else printf("Error in function: oct_to_hex");

        // skip leading zeros
        if (leading_zero && hex_digit == '0') {
            continue;
        }

        leading_zero = 0;
        out[out_pos] = hex_digit;
        out_pos++;
    }

    out[out_pos] = '\0';
}

void hex_to_bin(const char *hex, char *out) {
    out[0] = '\0';

    for (int i = 0; hex[i] != '\0'; i++) {
        switch (hex[i]) {
            case '0':
                strcat(out, "0000");
                break;
            case '1':
                strcat(out, "0001");
                break;
            case '2':
                strcat(out, "0010");
                break;
            case '3':
                strcat(out, "0011");
                break;
            case '4':
                strcat(out, "0100");
                break;
            case '5':
                strcat(out, "0101");
                break;
            case '6':
                strcat(out, "0110");
                break;
            case '7':
                strcat(out, "0111");
                break;
            case '8':
                strcat(out, "1000");
                break;
            case '9':
                strcat(out, "1001");
                break;
            case 'A': case 'a':
                strcat(out, "1010");
                break;
            case 'B': case 'b':
                strcat(out, "1011");
                break;
            case 'C': case 'c':
                strcat(out, "1100");
                break;
            case 'D': case 'd':
                strcat(out, "1101");
                break;
            case 'E': case 'e':
                strcat(out, "1110");
                break;
            case 'F': case 'f':
                strcat(out, "1111");
                break;
            default:
                printf("Error in function: hex_to_bin");
        }
    }
}

void dec_to_32bit_binary_str(const uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0'; // null terminator
}

void to_sign_magnitude(const int32_t value, char *out) {
    const uint32_t magnitude = (uint32_t)abs(value); // get absolute value
    dec_to_32bit_binary_str(magnitude, out);

    // set sign bit
    if (value < 0) {
        out[0] = '1';
    }
}

void to_ones_complement(const int32_t value, char *out) {
    if (value >= 0) {
        dec_to_32bit_binary_str((uint32_t)value, out);
    }
    else {
        const uint32_t magnitude = (uint32_t)abs(value); // get absolute value
        dec_to_32bit_binary_str(magnitude, out);

        // flip bits
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }
}

void to_twos_complement(const int32_t value, char *out) {
    if (value >= 0) {
        dec_to_32bit_binary_str((uint32_t)value, out);
        return;
    }

    const uint32_t magnitude = (uint32_t)abs(value); // get absolute value
    dec_to_32bit_binary_str(magnitude, out);

    // flip bits
    for (int i = 0; i < 32; i++) {
        out[i] = (out[i] == '0') ? '1' : '0';
    }

    // add 1
    for (int i = 31; i >= 0; i--) {
        if (out[i] == '0') {
            out[i] = '1';
            break;
        }

        out[i] = '0';
    }
}