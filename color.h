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

std::ostream& operator<< (std::ostream &out, Color color);

#endif //SIGNATURE_COLOR_H
