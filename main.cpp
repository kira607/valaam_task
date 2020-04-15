#include <iostream>

#include "color.h"
#include "error_codes.h"
#include "arguments_manager.h"
#include "application.h"

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    ArgumentsManager manager(argc, argv);

    try
    {
        manager.Init();
    }
    catch(const ErrorCodes& code)
    {
        switch (code)
        {
            case SUCCESS:
                break;
            case NOT_ENOUGH_ARGUMENTS:
                std::cout << Color::red << "Got " << argc <<
                          " arguments, but 3 or 4 needed\nTerminating..." <<
                          Color::none;
                return code;
            case FILE_IN_NOT_EXISTS:
                std::cout << Color::red << "Error: could not open " << Color::blue <<
                          manager.GetFileIn() << Color::red << "\nTerminating\n" << Color::none;
                return code;
            case FILE_OUT_NOT_EXISTS:
                std::cout << Color::red << "Error: could not open " << Color::blue <<
                          manager.GetFileOut() << Color::red << "\nTerminating\n" << Color::none;
                return code;
            case BAD_UNIT_SIZE:
                std::cout << Color::red << "Bad unit_ size. Setting default... (1MB)" << Color::none << '\n';
                manager.SetDefaultUnitSize();
                break;
            case DID_NOT_RECEIVE_UNIT_SIZE:
                std::cout << Color::blue << "Did not receive unit_ size. Setting default... (1MB)" << Color::none << '\n';
                manager.SetDefaultUnitSize();
                break;
        }
    }

    //output parameters information
    std::cout << "file in: " << manager.GetFileIn() << "\n";
    std::cout << "file out: " << manager.GetFileOut() << "\n";
    std::cout << "unit_ size: " << manager.GetUnitSize() << " byte " <<
    "(" << (double)manager.GetUnitSize()/1024 << " KB / " <<
    (double)manager.GetUnitSize()/1024/1024 << " MB)" << "\n";

    Application application(manager.GetFileIn(),manager.GetFileOut(),manager.GetUnitSize());
    application.Run();
    return SUCCESS;
}

/// NOTES

/// How to know number of threads on computer
//const unsigned char thread_num = std::thread::hardware_concurrency();
//std::cout << "This computer has " << Color::blue << (short) thread_num << Color::none << " threads\n";

/// 18446744073709551615UL == -1 is true condition
//while(18446744073709551615UL == -1) //true

///How to detect Run time
//auto start = std::chrono::high_resolution_clock::now();
//something to detect
//auto end = std::chrono::high_resolution_clock::now();
//std::cout << "Proccess took " << (end-start).count() << " nanoseconds\n";