#include <iostream>
#include <fstream>
#include <string>

bool test_mode = true;

int main()
{
    std::string file_in_path = "./in.f", file_out_path = "./out.f";
    /*
    std::cout << "Name of in file:";
    std::cin >> file_in_path;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    */

    std::ifstream fin(file_in_path,std::ios::binary);
    std::ofstream fout(file_out_path,std::ios::binary);

    fin.seekg(0,std::ios::end);
    int size = fin.tellg();
    fin.seekg(0,std::ios::beg);

    if(test_mode)
    {
        std::cout << "size of in file: " << size << " byte" << std::endl;
    }

    int unit_size{100};
    char unit[unit_size];

    int j = 1,
    unit_num = size / unit_size;
    if(size % unit_size > 0) ++ unit_num;

    while(unit_num > 0)
    {
        if(unit_num == 1)
        {
            for(int k = 0; k < unit_size; ++k)
                unit[k] = '\0';
        }

        fin.read((char *) unit, sizeof(char) * unit_size);

        // in.f
        if (test_mode)
        {
            std::cout << "----------------in.f " << j << "-----------------" << std::endl;
            for (int i = 0; i < unit_size; ++i)
            {
                std::cout << unit[i];
            }
            std::cout << std::endl;
        }

        //generate hash

        fout.write((char *)unit, sizeof(char) * unit_size);
        --unit_num;
        ++j;
    }

    fout.close();
    fin.close();

    //cat out.f
    if(test_mode)
    {
        std::cout << "\n\n\n";
        std::cout << "----------------out.f-----------------" << std::endl;
        system("cat out.f");
    }

    return 0;
}
/*
Текст задания

Signature

        Требуется написать консольную программу на C++ для генерации сигнатуры указанного файла. Сигнатура генерируется следующим образом: исходный файл делится на блоки равной (фиксированной) длины (если размер файла не кратен размеру блока, последний фрагмент может быть меньше или дополнен нулями до размера полного блока). Для каждого блока вычисляется значение hash функции и дописывается в выходной файл-сигнатуру.

Интерфейс: командная строка, в которой указаны:

* Путь до входного файла

* Путь до выходной файла

* Размер блока (по умолчанию, 1 Мб)

Обязательные требования:

* Следует максимально оптимизировать скорость работы утилиты с учетом работы в многопроцессорной среде

* Нужно реализовать правильную обработку ошибок на основе эксепшенов

* При работе с ресурсами нужно использовать умные указатели

* Не допускается использовать сторонние библиотеки OpenMP, OpenCL, etc

Допущения:

* Размер входного файла может быть много больше размера доступной физической памяти (> 4 Гб)

* В качестве хэш функции можно использовать любую хэш функцию (MD5, CRC и т.д.)
*/