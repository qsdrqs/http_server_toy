/*
 * test/test_log.cc: tests for logging functions
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */

extern "C" {
#include "log/log_output.h"
#include <stdio.h>
#include "global.h"
}

#include <gtest/gtest.h>
class TestLog : public ::testing::Test {
protected:
    TestLog()
    {
        InitLogFile();
    }

    ~TestLog() override
    {
        EndLogFile();
    }
};

TEST_F(TestLog, test_console)
{
    Logging(true, "abc/def/ghi.html", 500, GET, CONSOLE_ONLY);
}

TEST_F(TestLog, test_file)
{
    ASSERT_NE(log_file, nullptr);
    Logging(true, "abc/def/ghi.html", 500, GET, FILE_ONLY);
}

TEST_F(TestLog, test_all)
{
    ASSERT_NE(log_file, nullptr);
    Logging(true, "abc/def/ghi.html", 500, GET, ALL);
}
