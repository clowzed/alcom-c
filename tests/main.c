#include "../include/alcom.h"

#ifdef ALCOM__TEST

bool test_comment_splitter_position(void);


typedef bool (*test_func)(void);               

bool test_comment_splitter_position(void)
{
    struct test_res
    {
        char * line;
        ssize_t res;
    };

    struct test_res results[] =
    {
        { NULL          , -1 },
        { ""            , 0  },
        {";"            , 0  },
        {";;"           , 0  },
        {"  ;"          , 2  },
        {"mov ax, dx"   , 10 },
        {"a "           , 2  },
        {"    mov    ; ", 11 },

        { NULL, __SIZEOF_SIZE_T__ },
    };

    bool test_passed = true;
    size_t current_test_index = 0;

    while (test_passed)
    {

        struct test_res test_params = results[current_test_index++];
        if (test_params.res == __SIZEOF_SIZE_T__) break;
        info printf("Running inner test comment_splitter_position: line: ->%s|\n", test_params.line);

        ssize_t res = comment_splitter_position(test_params.line);

        test_passed = res == test_params.res;
        if (test_passed)
        {
            info printf("test passed!\n");
        }
        else
        {
            warning printf("expected : %zd got %zd\n", test_params.res, res);
            error printf("test failed!\n");
        }
    }

    if (test_passed)
    {
        done printf("all tests for comment_splitter_position were succesfully passed!\n");
    }
    else
    {
        error printf("tests for comment_splitter_position were not passed!\n");
    }

    return test_passed;
}



int main()
{
    info printf("running tests for alcom program...\n");

    test_func tests[] = {
        test_comment_splitter_position,
        NULL
    };

    size_t current_test_index = 0;
    while (true)
    {
        test_func test = tests[current_test_index++];

        //? If we reached end
        if (!test)
        {
            done printf("All tests were succesfully passed!\n");
            return 0;
        }

        if (test())
        {
            done printf("last test was passed! let's test another!\n");
        }
        else
        {
            error printf("last test was not passed! exiting...\n");
            return 1;
        }
    };
}

#endif
