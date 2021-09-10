
#include "main.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <unistd.h> ///sysconf

//#include "dxf_filter.h"
//#include <dxflib/dl_dxf.h>

#include "svg_gen.h"

#include <string>
///#include <pthread.h>


//#include <boost/filesystem.hpp>
//#include <boost/numeric/ublas/matrix.hpp>

//namespace fs = boost::filesystem;
//using namespace boost::numeric::ublas;

/*#include <dxflib/dl_dxf.h>
#include <dxflib/dl_attributes.h>
#include <dxflib/dl_codes.h>
#include <dxflib/dl_creationadapter.h>
#include <dxflib/dl_creationinterface.h>
#include <dxflib/dl_entities.h>
#include <dxflib/dl_exception.h>
#include <dxflib/dl_extrusion.h>
#include <dxflib/dl_global.h>
#include <dxflib/dl_writer.h>
#include <dxflib/dl_writer_ascii.h>*/

/*FILE* open_file_dxf(char *filename)
{
    struct stat buf;
    int fh, result; ///декскрипторы
    FILE *input = NULL;
    fh=open(filename, O_RDONLY); ///получение свойств файла
    result=fstat(fh, &buf);
    if (result !=0)
        {
            printf("Плох дескриптор файла\n");
            return 0;
        }
    else
    {
        printf("%s",filename);
        printf("Размер файла: %ld\n", buf.st_size);
        printf("Номер устройства: %lu\n", buf.st_dev);
        printf("Время модификации: %s", ctime(&buf.st_atime));
        input = fopen(filename, "r"); ///получение содержимого файла
        if (input == NULL)
        {
            printf("Error opening file");
            return 0;
        }
        else return input;
    }
}*/

#include "dir_explore/catalog_array.h"

/*void* explore_dxf(void* param_)
{
    thread_param *param=(thread_param*) param_;
    catalog_contents *files=param->contents;
    int i=files->files.str_count;

    int thread_num=get_thread_num(param);
    printf("thread_num=%d\n", thread_num);

    for(i-thread_num; i>=0; i=i-param->thread_count)
    {
        svg_gen svg;
        if (!svg.dxf.in(files->files[i], svg.dxf_filter))
        {
            printf("File %s could not be opened\n", files->files[i]);
        }
    }
    return 0;
}*/

//#include <ctype.h>
#include "stats.hpp"
#include <time.h>
#include <boost/asio.hpp>

#include "dir_explore/str_array.h"
int main(int argc, char** argv)
{
    ///find /path -type f
    clock_t start = clock();
    catalog_contents files;   //("/media/alex/7272b60a-d362-4f44-9b82-5de148a183e0/home/alex/Раскладки/", ".dxf");
    files.set_directory("/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/Раскладки/");
    files.set_filter("dxf");
    //files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/Раскладки/Мангал_v2 T12/ножка 4шт.DXF";
    //files.filename="/media/alex/7272b60a-d362-4f44-9b82-5de148a183e0/home/alex/Раскладки/Nakrasi/nakrasnew_s1.2_AntikBeloeZoloto_v2.dxf";
    //files.filename="/media/alex/7272b60a-d362-4f44-9b82-5de148a183e0/home/alex/Раскладки/2021_doors/1,02/ДГ-3_P4(2120x960)ЛЕВАЯ/1.5/KV.DXF";
      //files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/workspace/dxflib_test/dxf_examples/Untitled.dxf";
     //files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/Раскладки/2021_doors/13,03/ДА-14_P7(TP)(965x2050)ПРАВАЯ норд/1.5/KZ2_2052_3TERMO.dxf";
     //files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/workspace/dxflib_test/dxf_examples/polyline.dxf";
    //files.filename="/media/alex/7272b60a-d362-4f44-9b82-5de148a183e0/home/alex/Раскладки/2021_doors/25.01/Логотип на стенд 4шт.dxf";

    //files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/Раскладки/2021_doors/1,04/part2/ДА-16_P7(TP)(2160x1000)ЛЕВАЯ новый_окно s-001/1.5/UGOLOK.DXF";
    files.extracting_directory_and_files();
    files.processing_files(explore_file_body);
    files.print_stat();
    clock_t end = clock();
    printf("time=%lf\n",(end - start)/((double)CLOCKS_PER_SEC));
    return 0;
}
