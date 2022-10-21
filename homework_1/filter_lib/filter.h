#ifndef FILTER_H
#define FILTER_H

typedef struct FilteredLines FilteredLines;
struct FilteredLines {
    int count;
    char **lines;
};

int filter(char **lines, int count_lines, char *attr, FilteredLines *filtered_lines);

#endif // FILTER_H