#include "cut.h"

int main(int argv, char **args) {
    testing_t *testing = testing_new();
    if(testing == NULL)
        return 1;
    testing_test(testing, argv, args);
    return testing_result(testing);
}

int test_err(void) {
    return 1;
}

int test_success(void) {
    return 0;
}