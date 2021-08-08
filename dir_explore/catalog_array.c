#include "str_array.h"
#include "catalog_array.h"

#include <stdio.h> //printf
#include <string.h>
#include <unistd.h> //printf
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>

void return_up_dir(char *dir)
{
    int n=strlen(dir);
    dir[n-1]=0;
    int i=n-1;
    while(dir[i]!='/')
    {
        dir[i]=0;
        --i;
    }
}

int get_thread_num(thread_param *param)
{
    pthread_mutex_lock(&(param->mutex));
    static int thread_num=0;
    if(thread_num<param->thread_count) thread_num++;
    pthread_mutex_unlock(&(param->mutex));
    return thread_num;
}

void add_filename_to_current_dir(char *current_dir, char *name)
{
    int len=strlen(current_dir);
    if(current_dir[len-1]=='/')
    strcat(current_dir, name);
    else
    {
        strcat(current_dir, "/");
        strcat(current_dir, name);
    }
}

bool file_expansion_filter(char *name, char *expansion)
{
    if(expansion==nullptr) return true;

    bool result=false;
    char *upper=(char*) calloc(strlen(expansion)+2, sizeof(char));strcpy(upper, expansion);
    char *lower=(char*) calloc(strlen(expansion)+2, sizeof(char));strcpy(upper, expansion);
    int i=0;
    while (expansion[i])                           // пока не конец строки
  {
    int k=0;
    if(expansion[0]!='.')
    {
        k=1;
        upper[0]='.';
        lower[0]='.';
    }
    upper[i+k]=toupper(expansion[i]);
    lower[i+k]=tolower(expansion[i]);
    ++i;                             // инкремент индекса символов строки
  }
    int len=strlen(name);
    int len_exp=strlen(upper);
    i=1;
    while(i<len_exp)
    {
        if(name[len-i]!=upper[len_exp-i]&&name[len-i]!=lower[len_exp-i]) {result=false;break;}
        ++i;
    }
    if(i==len_exp) result=true;

  free(upper);
  free(lower);
  return result;
}

bool catalog_contents::extracting_directory_and_files(void)
{
    bool is_mounted=false;
    if(this->directory&&this->filter)
    {
        DIR *dir=NULL;
        struct dirent *ent;
        char current_dir[1024]= {0};
        strcpy(current_dir, directory);

        catalogs.add_new_string_with_dup(directory);

        for(int i=0; i<catalogs.str_count; ++i)
        {
            strcpy(current_dir, catalogs[i]);
            dir = opendir(catalogs[i]);
            //printf("_______catalogs->array[%d]=%s\n", i,catalogs[i]);
            if(dir)
            {
                is_mounted=true;
                ent=readdir(dir);
                while (ent!=NULL)
                {
                    if(ent->d_type==DT_DIR)
                    {
                        if(strcmp(ent->d_name, ".")&&strcmp(ent->d_name, ".."))
                        {
                            add_filename_to_current_dir(current_dir, ent->d_name);
                            //printf("dir=%s\n", current_dir);
                            catalogs.add_new_string_with_dup(current_dir);
                            return_up_dir(current_dir);
                        }
                    }
                    if(ent->d_type==DT_REG)
                    {
                        add_filename_to_current_dir(current_dir, ent->d_name);
                        //printf("file=%s\n", current_dir);
                        if(file_expansion_filter(ent->d_name, filter))
                            files.add_new_string_with_dup(current_dir);
                        return_up_dir(current_dir);
                        //chdir(current_dir);
                        //unlink(ent->d_name);
                        //printf("file %s is removed\n", current_dir);
                    }
                    ent=readdir(dir);
                }
            }
            else
            {
                printf("Каталог %s не примонтирован или недоступен", directory);
            }
            closedir(dir);
        }
    }
    return is_mounted;
}

catalog_contents::catalog_contents()
{
    if(this->directory&&this->filter)
    catalog_contents(this->directory, this->filter);
}

catalog_contents::catalog_contents(const char *directory,const char *filter)
{
    set_directory(directory);
    set_filter(filter);
    extracting_directory_and_files();
}

catalog_contents::catalog_contents(const char *directory)
{
    catalog_contents(directory, nullptr);
}

catalog_contents::~catalog_contents(void)
{
    if(this->directory) free(this->directory);
    if(this->filter) free(this->filter);
    for(int i=0; i<this->files.str_count; ++i)
    {
        free(this->files.array[i]);
    }
    for(int i=0; i<this->catalogs.str_count; ++i)
    {
        free(this->catalogs.array[i]);
    }
    free(this->files.array);
    free(this->catalogs.array);
}

void catalog_contents::set_directory(const char *directory)
{
    this->directory=strdup(directory);
}

void catalog_contents::set_filter(const char *filter)
{
    this->filter=strdup(filter);
}

void catalog_contents::processing_files(void* (*start_routine)(void*))
{
    if(filename==nullptr)
    {
        int i=0;
        int THREAD_COUNT=10;//sysconf(_SC_NPROCESSORS_ONLN);
        pthread_t id[THREAD_COUNT];
        printf("thread_count=%d\n", THREAD_COUNT);
        pthread_mutex_t mutex;
        pthread_mutex_init(&mutex, NULL);
        //int count=0;
        //создаём рабочие потоки
        for(i = 0; i < THREAD_COUNT; i++)
        {
            thread_param param;
            param.contents=this;
            param.thread_count=THREAD_COUNT;
            param.thread_num=i;
            param.mutex=mutex;
            pthread_create(&id[i], NULL, start_routine, &param);

        }
        pthread_mutex_destroy(&mutex);

        //ждем завершения рабочих потоков
        for(i = 0; i < THREAD_COUNT; i++)
        {
            pthread_join(id[i], NULL);
            pthread_detach(id[i]);
        }
    }
    else
    {
        svg_gen svg;
        if (!svg.dxf.in(filename, svg.dxf_filter))
        {
            printf("File %s could not be opened\n", filename);
        }
        else
        {
            this->evaluate_dxf_stats(svg.func_bit_flags);
            svg.svg_generate();
        }
    }
    //pthread_exit(nullptr);
}

void open_svg_file(catalog_contents *catalog)
{

}

void* explore_file_body(void* param_)
{
    thread_param *param=(thread_param*) param_;
    catalog_contents *files=param->contents;
    int i=files->files.str_count;

    int thread_num=get_thread_num(param);
    printf("thread_num=%d\n", thread_num);
    for(i=i-thread_num; i>=0; i=i-param->thread_count)
    {
        svg_gen svg;
        if (!svg.dxf.in(files->files[i], svg.dxf_filter))
        {
            printf("File %s could not be opened\n", files->files[i]);
        }
        else
        {
            param->contents->evaluate_dxf_stats(svg.func_bit_flags);
            if(svg.func_bit_flags.addSpline==1)
            cout<<"file="<<files->files[i]<<endl;
        }

        /*dxf_handler_funcions flags=svg.func_bit_flags;
        stats stat;
        if(flags.addXRecord==1) {printf("i=%d\n", i); break;}
        files->files.write_additional_data(&flags, sizeof(dxf_handler_funcions),i);*/

    }
    return 0;
}
