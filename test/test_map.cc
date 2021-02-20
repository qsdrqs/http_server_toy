/*
 * test/test_map.cc: tests for string map functions
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */

extern "C" {
#include "global.h"
#include "util/map.h"
#include <string.h>
}
#include <gtest/gtest.h>

class TestMap : public ::testing::Test
{
protected:
    Map* map;
    TestMap()
    {
        this->map = init_map();
    }
    ~TestMap() override
    {
        free_map(this->map);
    }
};

TEST_F(TestMap, test_basic_find)
{
    add_key_value("a", "1", this->map);
    add_key_value("b", "2", this->map);
    add_key_value("c", "3", this->map);
    add_key_value("d", "4", this->map);

    char result[5];
    ASSERT_EQ(2, find("c", this->map, result));
    ASSERT_EQ(0, strcmp(result, "3"));

    // can't find
    ASSERT_EQ(-1, find("e", this->map, result));
}

TEST_F(TestMap, test_replace_add)
{
    char result[5];
    add_key_value("a", "1", this->map);
    ASSERT_EQ(0, find("a", this->map, result));
    ASSERT_EQ(0, strcmp(result, "1"));

    add_key_value("a", "2", this->map);
    ASSERT_EQ(0, find("a", this->map, result));
    ASSERT_EQ(0, strcmp(result, "2"));

    add_key_value("a", "3", this->map);
    ASSERT_EQ(0, find("a", this->map, result));
    ASSERT_EQ(0, strcmp(result, "3"));
}

TEST_F(TestMap, too_long_key_value)
{

    ASSERT_EQ(-1, add_key_value("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", "test", this->map));
    ASSERT_EQ(-1, add_key_value("test", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", this->map));
}

TEST_F(TestMap, test_expand)
{
    add_key_value("1", "1", this->map);
    add_key_value("2", "2", this->map);
    add_key_value("3", "3", this->map);
    add_key_value("4", "4", this->map);
    add_key_value("5", "1", this->map);
    add_key_value("6", "2", this->map);
    add_key_value("7", "3", this->map);
    add_key_value("8", "4", this->map);
    add_key_value("9", "1", this->map);
    add_key_value("10", "2", this->map);
    add_key_value("11", "3", this->map);
    add_key_value("12", "4", this->map);
    add_key_value("13", "1", this->map);
    add_key_value("14", "2", this->map);
    add_key_value("15", "3", this->map);
    add_key_value("16", "4", this->map);
    add_key_value("17", "1", this->map);
    add_key_value("18", "2", this->map);
    add_key_value("19", "3", this->map);
    add_key_value("20", "4", this->map);
    add_key_value("21", "1", this->map);
    add_key_value("22", "2", this->map);
    add_key_value("23", "3", this->map);
    add_key_value("24", "4", this->map);
    add_key_value("25", "1", this->map);
    add_key_value("26", "2", this->map);
    add_key_value("27", "3", this->map);
    add_key_value("28", "4", this->map);
    add_key_value("29", "1", this->map);
    add_key_value("30", "2", this->map);
    add_key_value("31", "3", this->map);
    add_key_value("32", "4", this->map);

    char result[5];
    ASSERT_EQ(15, find("16", this->map, result));
    ASSERT_EQ(0, strcmp(result, "4"));

    ASSERT_EQ(31, find("32", this->map, result));
    ASSERT_EQ(0, strcmp(result, "4"));

    ASSERT_EQ(18, find("19", this->map, result));
    ASSERT_EQ(0, strcmp(result, "3"));
}
