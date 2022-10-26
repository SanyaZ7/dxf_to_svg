dir_explore/catalog_array.c
В этом файле расположена основная функция, которая запускается в большом количестве потоков (потоки реализованы посредством pthread, обход каталогов посредством Си, но вообще существуют std::thread и std::filesystem).
Смотрим на функцию void* explore_file_body(void* param_)
     Видим строки, которые выполняют основную работу
        svg_gen svg;
        if (!svg.dxf.in(files->files[i], svg.dxf_filter))
        {
            printf("File %s could not be opened\n", files->files[i]);
        }
       В проект встроены исходники библиотеки dxflib-3.17.0-src, она нужна для базового парсинга
           В файле main.cpp видим:
           files.filename="/media/alex/015d3c8f-8a5e-46de-b792-c278081e088a/Раскладки/2021_doors/1,04/part2/ДА-16_P7(TP)(2160x1000)ЛЕВАЯ новый_окно s-001/1.5/UGOLOK.DXF";
    //files.extracting_directory_and_files();
    Так как в стандарте DXF количество примитивов немаленькое, а программы, как например SolidWorks генерирует какое-то небольшое подмножество,
то я внедрил режим сбора статистики, который можно отключить посредством закомментирования строки files.extracting_directory_and_files();
files.filename получается тот самый DXF файл, на который генерируется SVG.
files.filename по умолчанию NULL и SVG не генерируется, если его не указывать явно.
Сплайны 3-го порядка аппроксимируются линиями, так как формула получается очень длинная
Получить эту длинную формулу можно посредством Maple
> xydata7 := [[x[0], 1], [x[1], 1], [x[2], 1], [x[3], 1], [x[4], 1], [x[5], 1], [x[6], 1]];
> c7 := BSplineCurve(xydata7, t, order = 3, knots = [0, 0, 0, k1, k2, k3, k4, 1, 1, 1]);

Используется среда CodeBlocks 20.03
Makefile можно получить посредством утилиты cbp2make синтаксиса вида
cbp2make -in dxflib_test.cbp
Сгенерированный файл dxflib_test.cbp.mak слудует переименовать в Makefile

Email for contacts: SanyaZ7@mail.ru
