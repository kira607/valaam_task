//
// Created by kirill on 20.04.2020.
//

#include <gtest/gtest.h>
#include "arguments_manager.h"
#include "error_codes.h"
#include <iostream>
#include <color.h>
#include <cstdlib>

constexpr size_t arguments_buffer_size = 64;
constexpr int default_unit_size = 1024*1024; // == 1024 KB == 1MB

int argc;
char arg1[arguments_buffer_size];
char arg2[arguments_buffer_size];
char arg3[arguments_buffer_size];
char arg4[arguments_buffer_size];
char *argv[] = {arg1,arg2,arg3,arg4};


void SetArgs(char _arg1[], char _arg2[], char _arg3[], char _arg4[], int _argc = 4)
{
    for(auto & i : argv)
    {
        memset(i, 0, arguments_buffer_size);
    }
    strcpy(argv[0],_arg1);
    strcpy(argv[1],_arg2);
    strcpy(argv[2],_arg3);
    strcpy(argv[3],_arg4);
    argc = _argc;
}

TEST(arguments_manager,correct_convert)
{
    SetArgs("prog_name","file_in","file_out","1235");
    ArgumentsManager am(argc,argv);
    am.Init();
    EXPECT_EQ(am.GetUnitSize(),1235);
}

TEST(arguments_manager,exceptions_test)
{
    SetArgs("prog_name","file_in","file_out","0",3);
    ArgumentsManager am1(argc,argv);
    EXPECT_THROW(am1.Init(),ErrorCodes);
    EXPECT_EQ(am1.GetUnitSize(),default_unit_size);

    SetArgs("prog_name","file_in","file_out","0");
    ArgumentsManager am2(argc,argv);
    EXPECT_THROW(am2.Init(),ErrorCodes);
    EXPECT_EQ(am1.GetUnitSize(),default_unit_size);

    SetArgs("prog_name","file_in","file_out","-1");
    ArgumentsManager am3(argc,argv);
    EXPECT_THROW(am3.Init(),ErrorCodes);
    EXPECT_EQ(am1.GetUnitSize(),default_unit_size);

    SetArgs("prog_name","file_in","file_out","q");
    ArgumentsManager am4(argc,argv);
    EXPECT_THROW(am4.Init(),ErrorCodes);
    EXPECT_EQ(am1.GetUnitSize(),default_unit_size);

    SetArgs("prog_name","file_in","file_out","10",10);
    ArgumentsManager am5(argc,argv);
    EXPECT_THROW(am5.Init(),ErrorCodes);

    SetArgs("prog_name","file_in","file_out","10",2);
    ArgumentsManager am6(argc,argv);
    EXPECT_THROW(am6.Init(),ErrorCodes);
}

TEST(arguments_manager,parser_test)
{
    SetArgs("prog_name","file_in","file_out","13q");
    ArgumentsManager am(argc,argv);
    am.Init();
    EXPECT_EQ(am.GetFileIn(),argv[1]);
    EXPECT_EQ(am.GetFileOut(),argv[2]);
    EXPECT_EQ(am.GetUnitSize(),std::stoi(argv[3]));
}

TEST(arguments_manager,default_unit_size_test)
{
    SetArgs("prog_name","file_in","file_out","4");
    ArgumentsManager am(argc,argv);
    am.Init();
    am.SetDefaultUnitSize();
    EXPECT_EQ(am.GetUnitSize(),default_unit_size);
}