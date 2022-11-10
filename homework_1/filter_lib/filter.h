#ifndef FILTER_H
#define FILTER_H

typedef struct FilteredLines FilteredLines;
struct FilteredLines {
    int count;
    char **lines;
};

int filter(char **const lines, const int count_lines, char *attr, FilteredLines *filtered_lines);

#endif // FILTER_H