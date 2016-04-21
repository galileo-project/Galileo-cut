#include <libelf.h>
#include <gelf.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "cut.h"

static _result_t  *_result_new(int, char*);
static void       _result_print(_result_t*);
static char       *_func_name_to_mod(char*);

/*************************
*      Result function   *
**************************/

_result_t *_result_new(int code, char *name) {
    _result_t *result = (_result_t*)malloc(sizeof(_result_t));
    if(result == NULL)
        return NULL;
        
    result->_mod_name = name;
    result->_code     = code;
    
    return result;
}

static void _result_print(_result_t *result) {
    if(result->_code != SUCCESS) {
        LOG_ERROR(result->_mod_name);
    } else {
        LOG_SUCCESS(result->_mod_name);
    }
}

/*************************
*      Test function     *
**************************/

testing_t *testing_new() {
    testing_t *testing = (testing_t*)malloc(sizeof(testing_t));
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
    testing_f   test_func;    
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
        return ERROR;
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
            test_func = (testing_f)(sym.st_value);
            ret = test_func();
            
            _result_t *result = _result_new(ret, _func_name_to_mod(func_name));
            link_add_raw(testing->_result, result);
            if(ret != 0) {
                testing->_code = ERROR;
            }
        }
	}
    elf_end(elf);
    close(fd);
    return SUCCESS;
}

int testing_result(testing_t *testing) {
    if(testing == NULL)
        return ERROR;
        
    node_t *node;
    while((node = link_tail(testing->_result)) != NULL) {
        _result_print(node->data);
    }
    
    return testing->_code;
}

/************************
*         Utils         *
*************************/

static char *_func_name_to_mod(char *func_name) {
    size_t func_name_len = strlen(func_name);
    size_t test_kw_len   = sizeof(TESTING_KW) - 1;
    size_t mod_name_len  = func_name_len - test_kw_len;
    
    char *mod_name = (char*)malloc(mod_name_len * sizeof(char));
    strncpy(mod_name, func_name + test_kw_len, mod_name_len);
    
    return mod_name;
}