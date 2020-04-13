//
// Created by kirill on 13.04.2020.
//

#include "ArgumentsManager.h"

//struct exception : std::exception
//{
//    error_code code_;
//    explicit exception(error_code code)
//    {
//        code_ = code;
//    }
//};

ArgumentsManager::ArgumentsManager(int argc, char *argv[])
:unit_size_{0}
{
    argc_ = argc;
    argv_ = argv;
}

void ArgumentsManager::init()
{
    if(argc_ > 4 || argc_ < 3)
    {
        throw error_code::NOT_ENOUGH_ARGUMENTS;
    }

    file_in_name_  = argv_[1];
    file_out_name_ = argv_[2];

    if(!std::ifstream(file_in_name_).is_open())
    {
        throw error_code::FILE_IN_NOT_EXISTS;
    }
    if(!std::ofstream(file_out_name_).is_open())
    {
        throw error_code::FILE_OUT_NOT_EXISTS;
    }
    if(argc_ == 3)
    {
        throw error_code::NOT_RECEIVE_UNIT_SIZE;
    }
    else
    {
        std::stringstream convert(argv_[3]);
        if (!(convert >> unit_size_))
        {
            throw error_code::BAD_UNIT_SIZE;

        }
        if (unit_size_ <= 0)
        {
            throw error_code::BAD_UNIT_SIZE;
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
    unit_size_ = default_unit_size_;
}




