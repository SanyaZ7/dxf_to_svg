#ifndef CATALOG_ARRAY_H_INCLUDED
#define CATALOG_ARRAY_H_INCLUDED
#include "str_array.h"
#include <pthread.h>
#include "../svg_gen.h"

#include "../stats.hpp"

class catalog_contents : public stats
{
    public:
    str_array catalogs;//=new str_array;
    str_array files=str_array(sizeof(dxf_handler_funcions));//=new str_array;
    void set_directory(const char *directory); ///обёртка над strdup
    void set_filter(const char *filter); ///обёртка над strdup

    bool extracting_directory_and_files(); ///основа для двух конструкторов с параметрами catalog_contents
    void processing_files(void* (*start_routine)(void*));

    catalog_contents();
    catalog_contents(const char *directory);
    catalog_contents(const char *directory, const char *filter);
    ~catalog_contents();
    //bool is_mouned=false; ///если файл не открывается

    const char *filename=nullptr; ///чтобы
    private:
    char *directory=nullptr; ///каталог, который нужно исследовать и помеcтить данные в класс str_array
    char *filter=nullptr; //фильтр по расширению имён файлов
};

typedef struct
{
    catalog_contents *contents;
    int thread_num;
    int thread_count;
    str_array returns;
    pthread_mutex_t mutex;
} thread_param;

void return_up_dir(char *dir);
int get_thread_num(thread_param *param);
void* explore_file_body(void* param_);

#endif // CATALOG_ARRAY_H_INCLUDED
