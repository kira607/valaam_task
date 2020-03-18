#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //convert
#include <cstring>  //strcmp
#include <functional> //hash

namespace colors
{
    char red[]  = "\033[31m";
    char blue[] = "\033[34m";
    char none[] = "\033[0m";
}

bool test_mode = false;

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    //check num of args
    if(argc > 4 || argc < 3)
    {
        std::cout << colors::red <<
                  "Got " << argc << " arguments, but 3 or 4 needed\nTerminating..." <<
                  colors::none << "\n";
        return 1;
    }

    std::string file_in_path = argv[1], file_out_path = argv[2];

    //check diffs btw in & out
    if(file_in_path == file_out_path)
    {
        std::cout << colors::red << "Error: Cannot write incoming file in itself" << colors::none << "\n";
        file_out_path = "out.f";
        std::cout << "File out: " << file_out_path << "\n";
    }

    std::ifstream fin(file_in_path,std::ios::binary);
    std::ofstream fout(file_out_path,std::ios::binary);

    //get size of file
    fin.seekg(0,std::ios::end);
    int file_size = fin.tellg();
    fin.seekg(0,std::ios::beg);

    std::cout << "size of in file: " << file_size << " byte\n";

    //check & set unit size
    int unit_size{};
    try
    {
        std::stringstream convert(argv[3]);
        if (!(convert >> unit_size))
        {
            std::cout << colors::red << "Bad unit size. Setting default... (1MB)\n" << colors::none;
            unit_size = 1024*1024;
        }
        else
        {
            if(unit_size <= 0)
                throw std::exception();
            std::cout << "Unit size: " << unit_size << " byte\n";
        }
    }
    catch(const std::exception &ex)
    {
        if(strcmp(ex.what(),"") == 0)
            std::cout << colors::blue << "Did not receive unit size. Setting default... (1MB)\n" << colors::none;
        else
            std::cout << colors::red << "Bad unit size. Setting default... (1MB)\n" << colors::none;

        unit_size = 1024*1024;
    }

    char unit[unit_size];

    int block_num = 1,
    unit_num = file_size / unit_size;
    if(file_size % unit_size > 0) ++unit_num;

    std::cout << "Units number: " << colors::blue << unit_num << colors::none << "\n";

    //read -> write
    while(unit_num > 0)
    {
        //fill last unit
        if(unit_num == 1)
        {
            for(int k = 0; k < unit_size; ++k)
                unit[k] = '\0';
        }

        //read
        fin.read((char*)unit, sizeof(char) * unit_size);

        // in
        if (test_mode)
        {
            std::cout << "----------------in " << block_num << "-----------------" << std::endl;
            for (int i = 0; i < unit_size; ++i)
            {
                std::cout << unit[i];
            }
            std::cout << std::endl;
        }

        //generate hash
        std::hash<std::string> hash_gen;
        size_t hash = hash_gen(unit);
        std::cout << colors::red << "HASH: " << colors::blue << hash << colors::none << std::endl;

        //write
        fout.write((char*)unit, sizeof(char) * unit_size);
        fout << hash;
        --unit_num;
        ++block_num;
    }

    fout.close();
    fin.close();

    //cat out
    if(test_mode)
    {
        std::cout << "\n\n\n";
        std::cout << "----------------out-----------------" << std::endl;
        system("cat file2.txt");
    }

    return 0;
}