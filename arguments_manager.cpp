//
// Created by kirill on 13.04.2020.
//

#include "arguments_manager.h"

ArgumentsManager::ArgumentsManager(int argc, char *argv[])
:unit_size_{kDefaultUnitSize}
{
    argc_ = argc;
    argv_ = argv;
}

void ArgumentsManager::Init()
{
    if(argc_ > 4 || argc_ < 3)
    {
        throw ErrorCodes::kNotEnoughArguments;
    }

    file_in_name_  = argv_[1];
    file_out_name_ = argv_[2];

    if(!std::ifstream(file_in_name_).is_open())
    {
        throw ErrorCodes::kFileInNotExists;
    }
    if(!std::ofstream(file_out_name_).is_open())
    {
        throw ErrorCodes::kFileOutNotExists;
    }
    if(argc_ == 3)
    {
        throw ErrorCodes::kDidNotReceiveUnitSize;
    }
    else
    {
        std::stringstream convert(argv_[3]);
        if (!(convert >> unit_size_))
        {
            throw ErrorCodes::kBadUnitSize;

        }
        if (unit_size_ <= 0)
        {
            throw ErrorCodes::kBadUnitSize;
        }
    }
}

std::string ArgumentsManager::GetFileIn() const
{
    return file_in_name_;
}

std::string ArgumentsManager::GetFileOut() const
{
    return file_out_name_;
}

int ArgumentsManager::GetUnitSize() const
{
    return unit_size_;
}

void ArgumentsManager::SetDefaultUnitSize()
{
    unit_size_ = kDefaultUnitSize;
}

/// Note: It is possible to use struct like below to avoid warnings
//struct ExceptionCode : std::exception
//{
//    ErrorCodes code;
//    explicit ExceptionCode(ErrorCodes code)
//    {
//        code = code;
//    }
//};



