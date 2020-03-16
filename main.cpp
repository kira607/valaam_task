#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

namespace colors
{
    char red[] = "\033[31m";
    char blue[] = "\033[34m";
    char none[] = "\033[0m";
}

bool test_mode = false;

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    if(argc > 4 || argc < 3)
    {
        std::cout << colors::red << "Got " << argc << " arguments, but 3 or 4 needed" <<
        std::endl << "Terminating" << colors::none << std::endl;
        return 1;
    }
    std::string file_in_path = argv[1], file_out_path = argv[2];

    if(file_in_path == file_out_path)
    {
        std::cout << colors::red << "AAAA Fuck!" << colors::none << std::endl;
        file_out_path = "out.f";
        std::cout << "FILE OUT: " << file_out_path << std::endl;
    }

    std::ifstream fin(file_in_path,std::ios::binary);
    std::ofstream fout(file_out_path,std::ios::binary);

    fin.seekg(0,std::ios::end);
    int file_size = fin.tellg();
    fin.seekg(0,std::ios::beg);

    std::cout << "size of in file: " << file_size << " byte" << std::endl;

    int unit_size;
    try
    {
        std::stringstream convert(
                argv[3]); // создаём переменную stringstream с именем convert, инициализируя её значением argv[1]
        if (!(convert >> unit_size)) // выполняем конвертацию
        {
            std::cout << colors::red << "Bad unit size. Setting default... (1MB)" << colors::none << std::endl;
            unit_size = 1024 * 1024; // если конвертация терпит неудачу, то задаём myint значение по умолчанию
        }
        else
        {
            std::cout << "Unit size: " << unit_size << " byte" << std::endl;
        }
    }
    catch(const std::logic_error &)
    {
        std::cout << colors::blue << "Did not receive unit size. Setting default... (1MB)" << colors::none << std::endl;
        unit_size = 1024*1024;
    }

    char unit[unit_size];

    int j = 1,
    unit_num = file_size / unit_size;
    if(file_size % unit_size > 0) ++ unit_num;

    std::cout << "Units number: " << colors::blue << unit_num << colors::none << std::endl;

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
        system("cat file2.txt");
    }

    return 0;
}