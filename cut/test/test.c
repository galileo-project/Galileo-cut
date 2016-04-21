#include "cut.h"

int main(int argv, char **args) {
    testing_t *testing = testing_new();
    if(testing == NULL)
        return 1;
    testing_test(testing, argv, args);
    int ret = testing_result(testing);
    
    if(ret != 0)
        return 0;
}

int test_err(void) {
    return 1;
}

int test_success(void) {
    return 0;
}

int test_assert_bool(void) {
    ASSERT_BOOL(0);
}

int test_assert_eq(void) {
    ASSERT_EQ(1,4);
}