//
// Created by kirill on 20.03.2020.
//

#include "color.h"

std::ostream& operator<< (std::ostream &out, color col)
{
    switch(col)
    {
        case color::red  :  out << "\033[31m"; break;
        case color::blue :  out << "\033[34m"; break;
        case color::none :  out << "\033[0m" ; break;
        default          :  out.setstate(std::ios_base::failbit); break;
    }
    return out;
}