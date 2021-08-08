#include <stdio.h>
#include <stdlib.h>
#include "str_array.h"
#include <string.h>

str_array::str_array()
{
    arrlen=8;
    str_count=0;
    array=(char**)calloc(arrlen, sizeof(char*));
}

str_array::str_array(int keysize)
{
    arrlen=8;
    str_count=0;
    array=(char**)calloc(arrlen, sizeof(char*));
    disp=keysize;
}

char* str_array::str_dup(char *str)
{
    char *res=(char*) calloc(strlen(str)+1+disp, sizeof(char));
    strcpy(res+disp,str);
    return res;
}

char* strdup(char *str)
{
    char *res=(char*) calloc(strlen(str)+1, sizeof(char));
    strcpy(res,str);
    return res;
}

void str_array::add_new_string_with_dup(char *str)
{
    if(arrlen<=str_count)
    {
        arrlen=arrlen+256;
        array=(char**) realloc(array, arrlen*sizeof(char*));
        goto start;
    }
    else
    {
        start:
        array[str_count]=str_dup(str);
        str_count++;
    }
}

#include <cstring>
 void str_array::write_additional_data(void *data, int size, int i)
 {
    if(disp!=0)
    {
        memcpy(this->array[i], data, size);
    }
 }


