//
// Created by kirill on 22.04.2020.
//

#include <gtest/gtest.h>
#include "unit.h"

TEST(unit,constructor_test)
{
    {
        Unit unit;
        EXPECT_EQ(unit.Data().size(), 0);
    }

    {
        Unit unit(1000);
        EXPECT_EQ(unit.Data().size(),1000);
    }

    {
        Unit unit(-10);
        EXPECT_EQ(unit.Data().size(),0);
    }

    {
        Unit unit(0);
        EXPECT_EQ(unit.Data().size(),0);
    }
}

TEST(unit,refill_test)
{
    Unit unit(20);
    unit.Refill();
    for (const auto& symbol : unit.Data())
    {
        EXPECT_EQ(symbol,0);
    }
}