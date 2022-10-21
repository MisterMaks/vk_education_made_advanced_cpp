#include <gtest/gtest.h>

static const int DEFAULT_LEN_STR = 1024;

extern "C" {
    #include "filter.h"
}

typedef struct TestCase TestCase;
struct TestCase {
    int num;
    char **lines;
    int count_lines;
    char *attr;
    FilteredLines *filtered_lines;
    int true_return_value;
};

TestCase *get_test_case(int num, int count_lines, char *text, char *attr, int true_return_value) {
    TestCase *test_case = (TestCase*)malloc(sizeof(TestCase));
    test_case->num = num;
    test_case->count_lines = count_lines;
    test_case->attr = attr;
    test_case->true_return_value = true_return_value;
    test_case->lines = (char**)malloc(count_lines * sizeof(char*));
    test_case->filtered_lines = (FilteredLines*)malloc(sizeof(FilteredLines));
    test_case->filtered_lines->lines = (char**)malloc(count_lines * sizeof(char*));

    int i = 0;
    int j = 0;
    while (text[i+j] != *"\0") {
        test_case->lines[i] = (char*)malloc(DEFAULT_LEN_STR*sizeof(char));
        int z = 0;
        while (text[i+j] != *"\n") {
            test_case->lines[i][z] = text[i+j];
            j++;
            z++;
        }
        i++;
    };

    test_case->count_lines = i;
    
    return test_case;
}

TEST(Filter, TestBasics) {
    TestCase *test_cases[] = {
        get_test_case(1, 1, (char*)"\n", (char*)"good", 0), 
        get_test_case(2, 1, (char*)"bad\n", (char*)"good", 0), 
        get_test_case(3, 1, (char*)"src=\"good\"\n", (char*)"good", 1), 
        get_test_case(4, 3, (char*)"bad\ngood src=\"good\" good\nbad\n", (char*)"good", 1), 
        get_test_case(5, 5, (char*)"aaa\nbbb src=\"ok\" bbb\nccc\nddd src=\"ok\" ddd\neee\n", (char*)"ok", 2), 
    };
    
    for (int i=0; i < sizeof(test_cases)/sizeof(*test_cases); ++i) {
        TestCase *test_case = test_cases[i];
        printf("Test %d ...\n", test_case->num);
        EXPECT_EQ(test_case->true_return_value, filter(test_case->lines, test_case->count_lines, test_case->attr, test_case->filtered_lines));
        printf("\n");
        free(test_case);
    }
}