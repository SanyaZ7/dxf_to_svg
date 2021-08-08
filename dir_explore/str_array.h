#ifndef STR_ARRAY_H_INCLUDED
#define STR_ARRAY_H_INCLUDED

char* str_dup(char *str);

class str_array
{
public:
 char **array;
 int arrlen=0; ///счёт arrlen и str_count идёт с нуля
 int str_count=0;
 int disp=0; ///смещение для хранения дополнительных данных
 void add_new_string_with_dup(char *str);
 char* str_dup(char *str);
 char* operator [] (int index) {if(index<str_count) return array[index]+disp; else return array[0]+disp;}
 str_array(int keysize);
 str_array();
 void write_additional_data(void *data, int size, int i);
};

#endif // STR_ARRAY_H_INCLUDED
