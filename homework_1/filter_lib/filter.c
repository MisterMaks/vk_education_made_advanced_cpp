#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"

static const int DEFAULT_LEN_STR = 1024;

int filter(char **const lines, const int count_lines, char *attr, FilteredLines *filtered_lines) {
    if (count_lines <= 0) {
        return -1;
    }
    if (!lines[count_lines-1]) {
        return -1;
    }
    if (!attr[0]) {
        return -1;
    }
    if (!filtered_lines) {
        return -1;
    }
    filtered_lines->lines = realloc(filtered_lines->lines, count_lines*sizeof(char*));
    char *search_line = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));
    snprintf(search_line, DEFAULT_LEN_STR*sizeof(char), "src=\"%s\"", attr);
    for (int i = 0; i < count_lines; ++i) {
        if (strstr(lines[i], search_line) != NULL) {
            int count = filtered_lines->count;
            filtered_lines->lines[count] = lines[i];
            filtered_lines->count++;
        } 
    }
    free(search_line);
    return filtered_lines->count;
}
