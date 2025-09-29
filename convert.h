// https://github.com/bean8533/C-Advanced-Data-Representation/tree/main

#ifndef CONVERT_H
#define CONVERT_H

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

void oct_to_bin(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void oct_to_hex(const char *oct, char *out);
void to_sign_magnitude(int32_t value, char *out);
void to_ones_complement(int32_t value, char *out);
void to_twos_complement(int32_t value, char *out);

#endif