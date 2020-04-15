//
// Created by kirill on 13.04.2020.
//

#ifndef SIGNATURE_ARGUMENTS_MANAGER_H
#define SIGNATURE_ARGUMENTS_MANAGER_H

#include <sstream>
#include <string>
#include <fstream>

#include "error_codes.h"

class ArgumentsManager
{
public:
    ArgumentsManager(int argc, char*argv[]);
    void Init();
    void SetDefaultUnitSize();
    [[nodiscard]] std::string GetFileIn() const;
    [[nodiscard]] std::string GetFileOut() const;
    [[nodiscard]] int GetUnitSize() const;
private:
    int argc_;
    char** argv_;
    std::string file_in_name_;
    std::string file_out_name_;
    int unit_size_;
    static constexpr int kDefaultUnitSize = 1048576; // == 1024*1024 == 1 MB
};


#endif //SIGNATURE_ARGUMENTS_MANAGER_H
