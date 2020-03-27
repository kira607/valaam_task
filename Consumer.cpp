//
// Created by kirill on 27.03.2020.
//

#include "Consumer.h"

Consumer::Consumer(std::vector<Unit> &buff, std::ofstream &fout)
{
    unit = buff.front();
    buff.erase(buff.begin());
    unit.write(fout);
}
