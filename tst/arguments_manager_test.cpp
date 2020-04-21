//
// Created by kirill on 20.04.2020.
//

#include <gtest/gtest.h>
#include "arguments_manager.h"

char *argv[] {"prog_name","qwe","qwer","4"};

TEST(a,b)
{
    EXPECT_EQ(ArgumentsManager(4,argv).GetUnitSize(),4);
}