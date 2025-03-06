#include <gtest/gtest.h>

#include "ip_filter.h"

//TODO: Правильное оформление тестов с выводом информации, что же не так

TEST(SplitTest, HandlesEmptyStringUsingDot)
{
    std::vector<std::string> result = split("", '.');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "") << "Result value: " << result[0];
}

TEST(SplitTest, HandlesStringWithoutDelimeter)
{
    std::vector<std::string> result = split("11", '.');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "11") << "Result value: " << result[0];
}


TEST(SplitTest, HandlesOnlyMultipleDelimeters)
{
    std::vector<std::string> result = split("..", '.');
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "");
    EXPECT_EQ(result[2], "");

}


TEST(SplitTest, HandlesMultipleDelimeters) 
{
    std::vector<std::string> result = split("11.22.33", '.');
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "11");
    EXPECT_EQ(result[1], "22");
    EXPECT_EQ(result[2], "33");
}


TEST(SorterTest, HandlesZeroElemets)
{
    std::vector<std::vector<std::string>> ips;
    auto result = lexicographically_sort(ips);
    EXPECT_TRUE(result.empty());   
}


TEST(SorterTest, HandlesOneElement)
{
    std::vector<std::vector<std::string>> ips {{"11", "11", "11", "11"}};
    auto result = lexicographically_sort(ips);

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result.front(), ips[0]);
}


TEST(SorterTest, HandlesMultipleElements)
{
    std::vector<std::vector<std::string>> ips {{"12", "11", "11", "11"}, {"11", "11", "11", "11"}};
    auto result = lexicographically_sort(ips);

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result.front(), ips[1]);
    EXPECT_EQ(result.back(), ips[0]);
}


TEST(FilterTest, HandlesOneAtPosOne)
{
    std::list<std::vector<std::string>> ips = {{"1", "11", "11", "11"}, {"23", "11", "11", "11"}};
    auto result = filter(ips, 0, 1);
       
    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result.front(), ips.front());

}

TEST(FilterTest, HandlesAtPosOneAndThree)
{
    std::list<std::vector<std::string>> ips = {{"1", "11", "105", "11"}, {"23", "11", "11", "11"}};
    auto result = filter(filter(ips, 0, 1), 2, 105);

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result.front(), ips.front());

}


TEST(FilterAny, HandlesNumber)
{
    std::list<std::vector<std::string>> ips = {{"1", "11", "46", "11"}, {"23", "11", "11", "11"}};
    auto result = filter_any(ips, 46);

    ASSERT_EQ(result.size(), 1) << "Result length: "<<result.size();

    EXPECT_EQ(result.front(), ips.front());
}

