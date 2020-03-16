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