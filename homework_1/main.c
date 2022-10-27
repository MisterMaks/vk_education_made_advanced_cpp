#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"

#define STR2(x) #x
#define STR(X) STR2(X)

const int DEFAULT_LEN_STR = 1024;
const int ASCII_CODE_LINE_BREAK = 10;

typedef struct InputLines InputLines;
struct InputLines {
    int count;
    char *attr;
    char **lines;
};

InputLines *input() {
    InputLines *input_lines = calloc(1, sizeof(FilteredLines));

    printf("Input count lines of text: ");
    scanf("%" STR(DEFAULT_LEN_STR) "s", input_lines->count);

    printf("Input attr value in 'src' tag: ");
    input_lines->attr = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));
    scanf("%" STR(DEFAULT_LEN_STR) "s", input_lines->attr);

    printf("Input text line by line:\n");
    input_lines->lines = (char**)calloc(input_lines->count, sizeof(char*));
    for (int i = 0; i < input_lines->count; ++i) {
        printf("%d. ", i+1);
        input_lines->lines[i] = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));
        scanf("%" STR(DEFAULT_LEN_STR) "[^\n]", input_lines->lines[i]);
    } 
}

int main() {
    InputLines *input_lines = input();

    FilteredLines *filtered_lines = calloc(1, sizeof(FilteredLines));
    filtered_lines->lines = (char**)calloc(input_lines->count, sizeof(char*));

    int count_filtered_lines = filter(input_lines->lines, input_lines->count, input_lines->attr, filtered_lines);

    printf("\nCount filtered lines: %d\n", count_filtered_lines);

    // DEBUG
    // for (int i = 0; i < count_filtered_lines; ++i) {
    //     printf("%s\n", filtered_lines->lines[i]);
    // }

    for (int i = 0; i < input_lines->count; ++i) {
        free(input_lines->lines[i]);
    }
    free(input_lines->lines);
    free(filtered_lines->lines);
    free(filtered_lines);
    free(input_lines->attr);

    return 0;
}
