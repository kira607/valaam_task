//
// Created by kirill on 13.04.2020.
//

#ifndef UNTITLED_ARGUMENTSMANAGER_H
#define UNTITLED_ARGUMENTSMANAGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "error_codes.h"
#include "color.h"

class ArgumentsManager
{
private:
    int argc_;
    char** argv_;
    std::string file_in_name_;
    std::string file_out_name_;
    int unit_size_;
    static constexpr int default_unit_size_ = 1048576; // == 1024*1024 == 1 MB
public:
    ArgumentsManager(int argc, char*argv[]);
    void init();
    void SetDefaultUnitSize();
    [[nodiscard]] std::string GetFileIn() const;
    [[nodiscard]] std::string GetFileOut() const;
    [[nodiscard]] int GetUnitSize() const;
};


#endif //UNTITLED_ARGUMENTSMANAGER_H
