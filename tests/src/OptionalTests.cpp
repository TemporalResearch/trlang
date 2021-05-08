//
// Created by Michael Lynch on 08/05/2021.
//

#include <trlang/functional/optional.hpp>
#include <auto_test.hpp>

TEST_SUITE(OptionalTests)
{
    TEST(3, shouldImplicitlyConvertValueToOptional)
    {
        int value = 3;
        trl::optional<int> opt = value;

        ASSERT_EQUALS(opt.value(), value)
    }

    TEST(3, shouldNotHaveValueByDefault)
    {
        trl::optional<int> opt;

        ASSERT_FALSE(opt.has_value());
    }

    TEST(3, shouldImplicitlyConvertStdOptional)
    {
        int value = 3;
        trl::optional<int> opt = std::make_optional<int>(3);

        ASSERT_EQUALS(opt.value(), value);
    }

    TEST(3, shouldAllowOperatorPassThrough)
    {
        int value = 5;
        trl::optional<int> opt(value);
        trl::optional<int> modifiedOpt;

        modifiedOpt = opt + 5;
        ASSERT_EQUALS(modifiedOpt.value(), value + 5);

        modifiedOpt = opt - 5;
        ASSERT_EQUALS(modifiedOpt.value(), value - 5);

        modifiedOpt = opt * 5;
        ASSERT_EQUALS(modifiedOpt.value(), value * 5);

        modifiedOpt = opt / 5;
        ASSERT_EQUALS(modifiedOpt.value(), value / 5);

        modifiedOpt = value;
        ASSERT_TRUE(modifiedOpt == opt);
        ASSERT_TRUE(opt <= modifiedOpt)
        ASSERT_TRUE(opt >= modifiedOpt)

        modifiedOpt = value + 5;
        ASSERT_TRUE(opt < modifiedOpt)
        ASSERT_TRUE(modifiedOpt > opt)
    }
}