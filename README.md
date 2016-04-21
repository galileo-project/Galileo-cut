# Galileo-cut

[![Build Status](https://travis-ci.org/ColeChan/Galileo-cut.svg?branch=dev)](https://travis-ci.org/ColeChan/Galileo-cut)

### Dependency

* elfutils-libelf-devel

Install dependncy:

    sudo yum install -y elfutils-libelf-devel        //for Redhat or CentOS etc.
    sudo apt-get install -y libelf-dev               //for Ubuntu or Debian etc.
    
### Build

    Build:
        cd cut && make
    Test:
        cd cut && make test
    Install:
        cd cut && make install
    
### Usage

    <your_testing_file.c>


    #include <cut/cut.h>

    int main(int argv, char **args) {
        testing_t *testing = testing_new();
        testing_test(testing, argv, args);
        return testing_result(testing);
    }

    int test_mod_name(void) {       // mod_name is your unit mod name
        return 1;                   // return 0 if success else return 1 
    }
    
    int test_use_assert_bool(void) {   // ASSERT_BOOL example
        ASSERT_BOOL(0);
    }

    int test_use_assert_eq(void) {      // ASSERT_EQ example
        ASSERT_EQ(1,4);
    }
    
    gcc test.c -lelf -lcut              //compile
    
**IMPORTANT:**

1. Unit testing function must start with `test_` and follow your testing_mod name
2. Testing function declara like `int test_mod_name(void)`
    
### License

`C/C++ language unit test framework` project release under [MIT LICENSE](https://github.com/tor4z/Galileo-cut/blob/master/LICENSE)