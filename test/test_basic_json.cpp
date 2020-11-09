// Copyright (c) 2019 Nomango

#include <gtest/gtest.h>
#include <jsonxx/json.hpp>
#include <iostream>
#include <optional>

using namespace jsonxx;

TEST(test_basic_json, test_assign)
{
    json j;

    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;

    // add a Boolean that is stored as bool
    j["happy"] = true;

    // add a string that is stored as std::string
    j["name"] = "Nomango";

    // add another null object by passing nullptr
    j["nothing"] = nullptr;

    // add an object inside the object
    j["answer"]["everything"] = 42;

    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = { 1, 0, 2 };

    // add another object (using an initializer list of pairs)
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };
}

class BasicJsonTest : public testing::Test
{
protected:
    void SetUp() override
    {
        j = {
            {"pi", 3.141},
            {"happy", true},
            {"name", "Nomango"},
            {"nothing", nullptr},
            {"answer", {
                    {"everything", 42}
            }},
            {"list", {1, 0, 2}},
            {"object", {
                {"currency", "USD"},
                {"value", 42.99}
            }}
        };
    }

    json j;
};

TEST_F(BasicJsonTest, test_dump)
{
    {
        // for-each
        for (const auto& v : j)
        {
            (void)v.dump();
        }
    }

}

TEST_F(BasicJsonTest, test_iterator_dump)
{
    {
        // iterator
        for (auto iter = j.begin(); iter != j.end(); iter++)
        {
            (void)iter->dump();
        }
    }
}

TEST_F(BasicJsonTest, test_optional)
{
    {
        json j = {
            { "number", 1 },
            { "float", 1.3 },
            { "boolean", false },
            { "string", "test" },
            { "array", { 1, 2, 4, true } },
            { "object", { "key", "value" } }
        };
        
        ASSERT_EQ(std::nullopt, j["number"].get_boolean());
        ASSERT_EQ(std::make_optional<int>(1), j["number"].get_integer());
        ASSERT_EQ(std::make_optional<float>(1.3), j["float"].get_float());
        ASSERT_EQ(std::make_optional<bool>(false), j["boolean"].get_boolean());
        ASSERT_EQ(std::make_optional<std::string>("test"), j["string"].get_string());

        j["array"].get_array();
        j["object"].get_object();
    }
}
