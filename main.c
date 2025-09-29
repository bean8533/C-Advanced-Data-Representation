// https://github.com/bean8533/C-Advanced-Data-Representation/tree/main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "convert.h"


int main() {
    int tests_total = 0;
    int tests_passed = 0;

    FILE *file = fopen("a2_test.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file a2_test.txt\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // ignores comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;

        // removes newline character at end of string
        line[strcspn(line, "\r\n")] = '\0';

        char function_name[50];
        char input_str[100];
        char expected_output[100];

        const int items = sscanf(line, "%s %s %s", function_name, input_str, expected_output);

        if (items != 3) continue;

        char output[100] = "";
        char test_description[200];
        tests_total++;

        if (strcmp(function_name, "oct_to_bin") == 0) {
            sprintf(test_description, "%s(\"%s\")", function_name, input_str);
            oct_to_bin(input_str, output);
        }
        else if (strcmp(function_name, "oct_to_hex") == 0) {
            sprintf(test_description, "%s(\"%s\")", function_name, input_str);
            oct_to_hex(input_str, output);
        }
        else if (strcmp(function_name, "hex_to_bin") == 0) {
            sprintf(test_description, "%s(\"%s\")", function_name, input_str);
            hex_to_bin(input_str, output);
        }
        else if (strcmp(function_name, "to_sign_magnitude") == 0) {
            const int32_t value = strtol(input_str, NULL, 10);
            sprintf(test_description, "%s(%d)", function_name, value);
            to_sign_magnitude(value, output);
        } else if (strcmp(function_name, "to_ones_complement") == 0) {
            const int32_t value = strtol(input_str, NULL, 10);
            sprintf(test_description, "%s(%d)", function_name, value);
            to_ones_complement(value, output);
        } else if (strcmp(function_name, "to_twos_complement") == 0) {
            const int32_t value = strtol(input_str, NULL, 10);
            sprintf(test_description, "%s(%d)", function_name, value);
            to_twos_complement(value, output);
        }
        else {
            printf("error unknown function: %s\n", function_name);
            tests_total--;
            continue;
        }

        if (strcmp(output, expected_output) == 0) {
            printf("Test %d: %s -> Expected: \"%s\", Got: \"%s\" [PASS]\n", tests_total, test_description, expected_output, output);
            tests_passed++;
        }
        else {
            printf("Test %d: %s -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", tests_total, test_description, expected_output, output);
        }
    }

    fclose(file);

    printf("\nSummary: %d/%d tests passed\n", tests_passed, tests_total);

    return 0;
}