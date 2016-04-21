# Galileo-cut

[![Build Status](https://travis-ci.org/ColeChan/Galileo-cut.svg?branch=dev)](https://travis-ci.org/ColeChan/Galileo-cut)

### Dependency

* elfutils-libelf-devel

install dependncy:

    yum install -y elfutils-libelf-devel
    
### Build

build:
    
    make
    
test:

    make test
    
install:
    
    make install
    
### Usage

    #include "cut.h"

    int main(int argv, char **args) {
        testing_t *testing = testing_new();
        testing_test(testing, argv, args);
        return testing_result(testing);
    }

    int test_mod_name(void) {       // mod_name is you unit mod name
        return 1;                   // return 0 if success else return 1 
    }
    
    int test_use_assert_bool(void) {   // ASSERT_BOOL example
        ASSERT_BOOL(0);
    }

    int test_use_assert_eq(void) {      // ASSERT_EQ example
        ASSERT_EQ(1,4);
    }
    
### License

`C language unit test lib` project release under [MIT LICENSE](https://github.com/tor4z/Galileo-cut/blob/master/LICENSE)