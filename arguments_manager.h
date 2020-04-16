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
    ///
    /// @brief Constructs arguments manager.
    ///
    /// @param[in] argc number of parameters.
    /// @param[in] argv values of parameters.
    ///
    /// @return Constructed arguments manager object.
    ///
    ArgumentsManager(int argc, char* argv[]);

    ///
    /// @brief Initializes application.
    ///
    /// @note Sets fields of arguments manager.
    ///       if not enough arguments or has bad arguments
    ///       throws exception with error code
    ///       \see ErrorCodes for more details
    ///
    void Init();

    ///
    /// @brief Sets default unit size
    ///
    void SetDefaultUnitSize();

    ///
    /// @brief Returns name of in file.
    ///
    /// @return Name of in file.
    ///
    [[nodiscard]] std::string GetFileIn() const;

    ///
    /// @brief Returns name of out file.
    ///
    /// @return Name of out file.
    ///
    [[nodiscard]] std::string GetFileOut() const;

    ///
    /// @brief Returns unit size in bytes.
    ///
    /// @return Unit size.
    ///
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
