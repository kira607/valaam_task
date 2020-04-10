//
// Created by kirill on 20.03.2020.
//

#ifndef UNTITLED_COLOR_H
#define UNTITLED_COLOR_H

#include <ostream>

enum class color
{
    red,
    blue,
    none,
};

std::ostream& operator<< (std::ostream &out, color col);

#endif //UNTITLED_COLOR_H
