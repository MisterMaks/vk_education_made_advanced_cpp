#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"

const int DEFAULT_LEN_STR = 1024;
const int ASCII_CODE_LINE_BREAK = 10;

int main() {
    int count_lines;
    printf("Input count lines of text: ");
    scanf("%d", &count_lines);

    char *attr = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));;
    printf("Input attr value in 'src' tag: ");
    scanf("%s", attr);

    while ((getchar()) != '\n');

    char **lines = (char**)calloc(count_lines, sizeof(char*));
    printf("Input text line by line:\n");
    for (int i = 0; i < count_lines; ++i) {
        lines[i] = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));
        char ch;
        int j = 0;
        int num_line = i + 1;
        printf("%d. ", num_line);
        while ((ch = getchar()) != *"\n") {
            lines[i][j] = ch;
            j++;
        }
    }

    FilteredLines *filtered_lines = calloc(1, sizeof(FilteredLines));
    filtered_lines->lines = (char**)calloc(count_lines, sizeof(char*));

    int count_filtered_lines = filter(lines, count_lines, attr, filtered_lines);

    printf("\nCount filtered lines: %d\n", count_filtered_lines);

    // DEBUG
    // for (int i = 0; i < count_filtered_lines; ++i) {
    //     printf("%s\n", filtered_lines->lines[i]);
    // }

    for (int i = 0; i < count_lines; ++i) {
        free(lines[i]);
    }
    free(lines);
    free(filtered_lines->lines);
    free(filtered_lines);
    free(attr);

    return 0;
}
