#include <libelf.h>
#include <gelf.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cut.h"

static _result_t  *_result_new(int, char*);
static void       _result_print(_result_t*);
static char       *_func_name_to_mod(char*);

/*************************
*      Result function   *
**************************/

_result_t _result_new(int code, char *name) {
    _result_t *result = (_result_t*)malloc(sizeof(_result_t));
    if(result == NULL)
        return NULL;
        
    result->mod_name = NULL;
    result->_code     = 0;
    
    return result;
}

static void _result_print(_result_t *result) {
    if(result->_code != 0) {
        LOG_ERROR(result->mod_name);
    } else {
        LOG_SUCCESS(result->mod_name);
    }
}

/*************************
*      Test function     *
**************************/

testing_t *testing_new() {
    testting_t *testing = (testing_t*)malloc(sizeof(testing_t));
    if(testing == NULL)
        return  NULL;
        
    testing->_result = link_new();
    if(testing->_result == NULL) {
        free(testing);
        return NULL;
    }
    
    testing->_code = 0;
    return testing;
}

int testing_test(testing_t *testing, int argc, char** argv) {
    Elf         *elf = NULL;
    Elf_Scn     *scn = NULL;
    GElf_Shdr   shdr;
    Elf_Data    *data = NULL;
    test_f      test_func;    
    int         fd, count;
    int         ret;
    int         index;
    char        *func_name;

    //Read elf file
    elf_version(EV_CURRENT);
    fd = open(argv[0], O_RDONLY);
    elf = elf_begin(fd, ELF_C_READ, NULL);
    if(elf == NULL) {
        close(fd);
        return 1;
    }
    
    //Retrieve symbol table.
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_SYMTAB) {
            break;
        }
    }
    
    data = elf_getdata(scn, NULL);
    count = shdr.sh_size / shdr.sh_entsize;

    //Get testing function
    for (index = 0; index < count; ++index) {
        GElf_Sym sym;
        gelf_getsym(data, index, &sym);
        func_name = elf_strptr(elf, shdr.sh_link, sym.st_name);
        
        if (!strncasecmp(TESTING_KW, func_name, strlen(TESTING_KW))) {
            test_func = (test_f)(sym.st_value);
            ret = test_func();
            
            _result_t *result = _result_new(ret, _func_name_to_mod(func_name);
            link_add_raw(testing->_result, result);
            if(ret != 0)
                testing->_code = 1;
        }
	}
    elf_end(elf);
    close(fd);
    return 0;
}

int testing_result(testing_t *testing) {
    if(testing == NULL)
        return 1
    
    return testing->_code;
}

/************************
*           Utils       *
*************************/

static char *_func_name_to_mod(char *func_name) {
    size_t func_name_len = strlen(func_name);
    size_t mod_name_len  = func_name_len - sizeof(TESTING_KW);
    
    char *mod_name = (char*)malloc(mod_name_len * sizeof(char));
    strncpy(mod_name, func_name + func_name_len, mod_name_len);
    
    return mod_name;
}