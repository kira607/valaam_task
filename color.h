//
// Created by kirill on 20.03.2020.
//

#ifndef SIGNATURE_COLOR_H
#define SIGNATURE_COLOR_H

#include <ostream>

enum class Color
{
    red,
    blue,
    none,
};

///
/// @brief Insertion operator
///
/// @param[in] out Ostream object
/// @param[in] color Color to set
///
/// @note Outputs control character that sets color of text in terminal.
/// @warning If you don't reset color, all text that goes further in terminal will be colored with last set color
///
/// @return object ostream with color.
///
std::ostream& operator<< (std::ostream &out, Color color);

#endif //SIGNATURE_COLOR_H
