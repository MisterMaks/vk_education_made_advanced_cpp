#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"

static const int DEFAULT_LEN_STR = 1024;

int filter(char **lines, int count_lines, char *attr, FilteredLines *filtered_lines) {
    char *search_line = (char*)malloc(DEFAULT_LEN_STR*sizeof(char));
    sprintf(search_line, "src=\"%s\"", attr);
    for (int i = 0; i < count_lines; ++i) {
        if (strstr(lines[i], search_line) != NULL) {
            int count = filtered_lines->count;
            filtered_lines->lines[count] = (char*)malloc(DEFAULT_LEN_STR*sizeof(char));
            filtered_lines->lines[count] = lines[i];
            filtered_lines->count++;
        } 
    }
    return filtered_lines->count;
}
