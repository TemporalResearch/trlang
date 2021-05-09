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
        ASSERT_TRUE(modifiedOpt != opt);
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

    struct InstantiationCounter
    {
        static int instantiationCounter;

        InstantiationCounter()
        {
            instantiationCounter++;
        }

        InstantiationCounter(const InstantiationCounter& other):
            InstantiationCounter()
        {

        }

        static void resetCounter()
        {
            instantiationCounter = 0;
        }
    };

    int InstantiationCounter::instantiationCounter = 0;

    TEST(3, shouldCopyContentsOfOtherOptionalNotShare)
    {
        InstantiationCounter::resetCounter();
        ASSERT_EQUALS(InstantiationCounter::instantiationCounter, 0);

        trl::optional<InstantiationCounter> opt1 = InstantiationCounter();
        // Extra stack object created in assignment
        ASSERT_EQUALS(InstantiationCounter::instantiationCounter, 2);

        trl::optional<InstantiationCounter> opt2 = opt1;
        ASSERT_EQUALS(InstantiationCounter::instantiationCounter, 3);
    }

    TEST(3, shouldMapFromOneTypeToAnother)
    {
        int value = 5;
        trl::optional<int> opt = value;
        trl::optional<double> dOpt = opt.map<double>([&](auto i) {
            double dValue = i + 0.5;

            return dValue;
        });

        ASSERT_TRUE(dOpt > 5);
        ASSERT_TRUE(dOpt < 6);
    }

    TEST(3, shouldMapTypeOfEmpty)
    {
        trl::optional<int> opt;
        trl::optional<std::string> dOpt = opt.map<std::string>([&](auto i) {
            return "Hello world";
        });

        ASSERT_FALSE(opt.has_value());
        ASSERT_FALSE(dOpt.has_value());
    }

    TEST(3, shouldFlatMapFromOneTypeToAnotherEmptyType)
    {
        int value = 5;
        trl::optional<int> opt = value;
        trl::optional<double> dOpt = opt.flatMap<double>([&](auto i) {
            return trl::optional<double>();
        });

        ASSERT_FALSE(dOpt.has_value());
    }

    TEST(3, shouldFlatMapFromOneTypeToAnotherType)
    {
        int value = 5;
        trl::optional<int> opt = value;
        trl::optional<std::string> dOpt = opt.flatMap<std::string>([&](auto i) {
            trl::optional<std::string> dVal = std::string(i, '#');
            return dVal;
        });

        ASSERT_EQUALS(dOpt.value().size(), value);
    }
}