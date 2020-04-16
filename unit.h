//
// Created by kirill on 20.03.2020.
//

#ifndef SIGNATURE_UNIT_H
#define SIGNATURE_UNIT_H

#include <fstream>
#include <string>
#include <utility> //move

class Unit
{
public:
    ///
    /// @breif Construct unit.
    ///
    /// @param unit_size Size of unit in bytes.
    ///
    /// @return Constructed
    ///
    explicit Unit(int unit_size = 0);
    ~Unit() = default;

    ///
    /// @brief Fills unit with 0.
    ///
    void Refill();

    ///
    /// @breif Sets hash
    ///
    /// @param hash Hash that will be set
    ///
    void set_hash(size_t hash);

    ///
    /// @breif Returns unit data
    ///
    /// @return unit data
    ///
    std::basic_string<char> Data();

    ///
    /// @breif Reads unit from file
    ///
    /// @param file File stream from where to read
    ///
    /// @return Number of read bytes
    ///
    size_t Read(std::ifstream &file);

    ///
    /// @breif Writes unit and hash in file
    ///
    /// @param file File stream in which to write
    ///
    void Write(std::ofstream &file);

    ///
    /// @brief Insertion operator
    ///
    /// @param[in] out Ostream object
    /// @param[in] unit Unit to output
    ///
    /// @note Outputs unit data
    ///
    /// @return Object ostream with unit data.
    ///
    friend std::ostream& operator<<(std::ostream& out, const Unit& unit);
private:
    std::basic_string<char> unit_;
    int unit_size_;
    size_t hash_;
};

#endif //SIGNATURE_UNIT_H
