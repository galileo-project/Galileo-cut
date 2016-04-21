#include "cut.h"

int main(int argv, char **args) {
    testing_t *testing = testing_new();
    testing_test(testing, argv, args);
    return testing_result(testing);
}

int testing_err(void) {
    return 1;
}

int testing_success(void) {
    return 0;
}