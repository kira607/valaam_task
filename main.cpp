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
            case kSuccess:
                break;
            case kNotEnoughArguments:
                std::cout << Color::kRed << "Got " << argc <<
                          " arguments, but 3 or 4 needed\nTerminating..." <<
                          Color::kNone;
                return code;
            case kFileInNotExists:
                std::cout << Color::kRed << "Error: could not open " << Color::kBlue <<
                          manager.GetFileIn() << Color::kRed << "\nTerminating\n" << Color::kNone;
                return code;
            case kFileOutNotExists:
                std::cout << Color::kRed << "Error: could not open " << Color::kBlue <<
                          manager.GetFileOut() << Color::kRed << "\nTerminating\n" << Color::kNone;
                return code;
            case kBadUnitSize:
                std::cout << Color::kRed << "Bad unit_ size. Setting default... (1MB)" << Color::kNone << '\n';
                manager.SetDefaultUnitSize();
                break;
            case kDidNotReceiveUnitSize:
                std::cout << Color::kBlue << "Did not receive unit_ size. Set default... (1MB)" << Color::kNone << '\n';
                break;
        }
    }

    //output parameters information
    std::cout << "file in: " << manager.GetFileIn() << "\n";
    std::cout << "file out: " << manager.GetFileOut() << "\n";
    std::cout << "unit_ size: " << manager.GetUnitSize() << " byte " <<
    "(" << (double)manager.GetUnitSize()/1024 << " KB / " <<
    (double)manager.GetUnitSize()/1024/1024 << " MB)" << "\n";
    std::cout << "Process is running...\n";

    Application application(manager.GetFileIn(),manager.GetFileOut(),manager.GetUnitSize());
    application.Run();
    return kSuccess;
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