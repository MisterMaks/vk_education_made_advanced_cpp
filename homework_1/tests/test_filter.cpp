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
    TestCase *test_case = (TestCase*)calloc(1, sizeof(TestCase));
    test_case->num = num;
    test_case->count_lines = count_lines;
    test_case->attr = attr;
    test_case->true_return_value = true_return_value;
    test_case->filtered_lines = (FilteredLines*)calloc(1, sizeof(FilteredLines));
    if (count_lines <= 0) {
        return test_case;
    }
    test_case->filtered_lines->lines = (char**)calloc(count_lines, sizeof(char*));
    if (!text) {
        test_case->lines = NULL;
        return test_case;
    } 
    test_case->lines = (char**)calloc(count_lines, sizeof(char*));

    int i = 0;
    int j = 0;
    int z = 0;
    while (text[z] != *"\0") {
        if (j == 0) {
            test_case->lines[i] = (char*)calloc(DEFAULT_LEN_STR, sizeof(char));
        }
        if (text[z] != *"\n") {
            test_case->lines[i][j] = text[z];
            j++;
        } else {
            j = 0;
            i++;
        }
        z++; 
    }
    
    return test_case;
}

TEST(Filter, TestBasics) {
    TestCase *test_cases[] = {
        get_test_case(1, 1, (char*)"\n", (char*)"good", 0), 
        get_test_case(2, 1, (char*)"bad\n", (char*)"good", 0), 
        get_test_case(3, 1, (char*)"src=\"good\"\n", (char*)"good", 1), 
        get_test_case(4, 3, (char*)"bad\ngood src=\"good\" good\nbad\n", (char*)"good", 1), 
        get_test_case(5, 5, (char*)"aaa\nbbb src=\"ok\" bbb\nccc\nddd src=\"ok\" ddd\neee\n", (char*)"ok", 2), 
        get_test_case(6, -1, (char*)"aaa\nbbb src=\"ok\" bbb\nccc\nddd src=\"ok\" ddd\neee\n", (char*)"ok", -1), 
        get_test_case(7, 1, NULL, (char*)"ok", -1), 
        get_test_case(8, 1, (char*)"bad\n", NULL, -1),
    };
    
    for (int i=0; i < sizeof(test_cases)/sizeof(*test_cases); ++i) {
        TestCase *test_case = test_cases[i];
        printf("Test %d ...\n", test_case->num);
        EXPECT_EQ(test_case->true_return_value, filter(test_case->lines, test_case->count_lines, test_case->attr, test_case->filtered_lines));
        printf("\n");
        if (test_case->lines) {
            for (int i = 0; i < test_case->count_lines; ++i) {
                free(test_case->lines[i]);
            }
            free(test_case->lines);
        }
        free(test_case->filtered_lines->lines);
        free(test_case->filtered_lines);
        free(test_case);
    }

    TestCase *test_case_9 = (TestCase*)calloc(1, sizeof(TestCase));
    test_case_9->num = 9;
    test_case_9->count_lines = 1;
    test_case_9->lines = (char**)calloc(test_case_9->count_lines, sizeof(char*));
    test_case_9->lines[0] = (char*)"aaa\n";
    test_case_9->attr = (char*)"a";
    test_case_9->true_return_value = -1;
    test_case_9->filtered_lines = NULL;
    printf("Test %d ...\n", test_case_9->num);
    EXPECT_EQ(test_case_9->true_return_value, filter(test_case_9->lines, test_case_9->count_lines, test_case_9->attr, test_case_9->filtered_lines));
    printf("\n");
    if (test_case_9->lines) {
        free(test_case_9->lines);
    }
    free(test_case_9);
}
