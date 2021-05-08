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

    TEST(3, shouldMakeEmptyOptionalsEqual)
    {
        trl::optional<int> opt1;
        trl::optional<int> opt2;

        ASSERT_EQUALS(opt1, opt2)
    }

    TEST(3, shouldMakeEmptyOptionalLessThanFilled)
    {
        trl::optional<int> empty;
        trl::optional<int> filled = 5;

        ASSERT_TRUE(empty < filled)
    }

    TEST(3, shouldConvertToStringForAutoTestLibrary)
    {
        trl::optional<int> empty;
        ASSERT_EQUALS(auto_test::to_string(empty), "trl::nullopt");

        trl::optional<int> filled = 5;
        ASSERT_EQUALS(auto_test::to_string(filled), "trl::opt(5)");
    }

    class Destructable
    {
    private:
        bool& isAlive;
    public:
        Destructable(bool& aliveFlag):
            isAlive(aliveFlag)
        {
            isAlive = true;
        }

        ~Destructable()
        {
            isAlive = false;
        }
    };

    TEST(3, shouldDestroyOldContentsWhenGivenNewValue)
    {
        bool isAlive = true;
        trl::optional<Destructable> opt = Destructable(isAlive);

        opt = std::nullopt;

        ASSERT_FALSE(isAlive);
    }
}