#include <iostream>
//#include <chrono>

#include "color.h"
#include "error_codes.h"
#include "ArgumentsManager.h"
#include "Application.h"

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    ArgumentsManager manager(argc, argv);

    try
    {
        manager.init();
    }
    catch(const error_code& code)
    {
        switch (code)
        {
            case SUCCESS:
                break;
            case NOT_ENOUGH_ARGUMENTS:
                std::cout << color::red << "Got " << argc <<
                          " arguments, but 3 or 4 needed\nTerminating..." <<
                          color::none;
                return code;
            case FILE_IN_NOT_EXISTS:
                std::cout << color::red << "Error: could not open " << color::blue <<
                          manager.GetFileIn() << color::red << "\nTerminating\n" << color::none;
                return code;
            case FILE_OUT_NOT_EXISTS:
                std::cout << color::red << "Error: could not open " << color::blue <<
                          manager.GetFileOut() << color::red << "\nTerminating\n" << color::none;
                return code;
            case BAD_UNIT_SIZE:
                std::cout << color::red << "Bad unit size. Setting default... (1MB)" << color::none << '\n';
                manager.SetDefaultUnitSize();
                break;
            case NOT_RECEIVE_UNIT_SIZE:
                std::cout << color::blue << "Did not receive unit size. Setting default... (1MB)" << color::none << '\n';
                manager.SetDefaultUnitSize();
                break;
        }
    }
    ///const unsigned char thread_num = std::thread::hardware_concurrency();
    ///std::cout << "This computer has " << color::blue << (short) thread_num << color::none << " threads\n";

    std::cout << "file in: " << manager.GetFileIn() << "\n";
    std::cout << "file out: " << manager.GetFileOut() << "\n";
    std::cout << "unit size: " << manager.GetUnitSize() << " byte " <<
    "(" << (double)manager.GetUnitSize()/1024 << " KB / " <<
    (double)manager.GetUnitSize()/1024/1024 << " MB)" << "\n";

    Application application(manager.GetFileIn(),manager.GetFileOut(),manager.GetUnitSize());

    auto start = std::chrono::high_resolution_clock::now();

    application.run();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Proccess took " << (end-start).count() << " nanoseconds\n";

    return SUCCESS;
}

//while(18446744073709551615UL == -1)

/*
while(producer.run())
{
    hashGen.run();
    consumer.run();
}
 */