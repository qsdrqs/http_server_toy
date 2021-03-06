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
#include "global.h"
#include "log/log_output.h"
#include <stdio.h>
}

#include <gtest/gtest.h>
class TestLog : public ::testing::Test
{
protected:
    TestLog()
    {
        char log_root_path[256] = "var/log/http.log";
        init_log_file(log_root_path);
    }

    ~TestLog() override
    {
        if (log_file != 0)
            end_log_file();
    }
};

TEST_F(TestLog, test_console)
{
    logging(true, "abc/def/ghi.html", 500, GET, CONSOLE_ONLY);
}

TEST_F(TestLog, test_file)
{
    ASSERT_NE(log_file, nullptr);
    logging(true, "abc/def/ghi.html", 500, GET, FILE_ONLY);
}

TEST_F(TestLog, test_all)
{
    ASSERT_NE(log_file, nullptr);
    logging(true, "abc/def/ghi.html", 500, GET, ALL);
}

//test path
TEST(TestLogPath, test_path_1)
{
    char log_root_path[256] = "/var/log/http.log";
    /* should cause permission denied */
    ASSERT_NE(init_log_file(log_root_path), 0);
}
TEST(TestLogPath, test_path_2)
{
    char log_root_path[256] = "///////////";
    ASSERT_NE(init_log_file(log_root_path), 0);
}
TEST(TestLogPath, test_path_3)
{
    char log_root_path[256] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    ASSERT_NE(init_log_file(log_root_path), 0);
}
