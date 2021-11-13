//
// Created by Michael Lynch on 08/05/2021.
//

#include <trlang/functional/optional.hpp>
#include <auto_test.hpp>

#include <catch2/catch.hpp>

TEST_CASE("shouldImplicitlyConvertValueToOptional", "[3]")
{
    int value = 3;
    trl::optional<int> opt = value;

    REQUIRE(opt.value() == value);
}

TEST_CASE("shouldNotHaveValueByDefault", "[3]")
{
    trl::optional<int> opt;

    REQUIRE_FALSE(opt.has_value());
}

TEST_CASE("shouldImplicitlyConvertStdOptional", "[3]")
{
    int value = 3;
    trl::optional<int> opt = std::make_optional<int>(3);

    REQUIRE(opt.value() == value);
}

TEST_CASE("shouldAllowOperatorPassThrough", "[3]")
{
    int value = 5;
    trl::optional<int> opt(value);
    trl::optional<int> modifiedOpt;

    modifiedOpt = opt + 5;
    REQUIRE(modifiedOpt.value() == value + 5);

    modifiedOpt = opt - 5;
    REQUIRE(modifiedOpt.value() == value - 5);

    modifiedOpt = opt * 5;
    REQUIRE(modifiedOpt.value() == value * 5);

    modifiedOpt = opt / 5;
    REQUIRE(modifiedOpt.value() == value / 5);

    modifiedOpt = value;
    REQUIRE(modifiedOpt == opt);
    REQUIRE(opt <= modifiedOpt);
    REQUIRE(opt >= modifiedOpt);

    modifiedOpt = value + 5;
    REQUIRE(modifiedOpt != opt);
    REQUIRE(opt < modifiedOpt);
    REQUIRE(modifiedOpt > opt);
}

TEST_CASE("shouldMakeEmptyOptionalsEqual", "[3]")
{
    trl::optional<int> opt1;
    trl::optional<int> opt2;

    REQUIRE(opt1 == opt2);
}

TEST_CASE("shouldMakeEmptyOptionalLessThanFilled", "[3]")
{
    trl::optional<int> empty;
    trl::optional<int> filled = 5;

    REQUIRE(empty < filled);
}

TEST_CASE("shouldConvertToStringForAutoTestLibrary", "[3]")
{
    trl::optional<int> empty;
    REQUIRE(auto_test::to_string(empty) == "trl::nullopt");

    trl::optional<int> filled = 5;
    REQUIRE(auto_test::to_string(filled) == "trl::opt(5)");
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

TEST_CASE("shouldDestroyOldContentsWhenGivenNewValue", "[3]")
{
    bool isAlive = true;
    trl::optional<Destructable> opt = Destructable(isAlive);

    opt = std::nullopt;

    REQUIRE_FALSE(isAlive);
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

TEST_CASE("shouldCopyContentsOfOtherOptionalNotShare", "[3]")
{
    InstantiationCounter::resetCounter();
    REQUIRE(InstantiationCounter::instantiationCounter == 0);

    trl::optional<InstantiationCounter> opt1 = InstantiationCounter();
    // Extra stack object created in assignment
    REQUIRE(InstantiationCounter::instantiationCounter == 2);

    trl::optional<InstantiationCounter> opt2 = opt1;
    REQUIRE(InstantiationCounter::instantiationCounter == 3);
}

TEST_CASE("shouldMapFromOneTypeToAnother", "[3]")
{
    int value = 5;
    trl::optional<int> opt = value;
    trl::optional<double> dOpt = opt.map<double>([&](auto i) {
        double dValue = i + 0.5;

        return dValue;
    });

    REQUIRE(dOpt > 5);
    REQUIRE(dOpt < 6);
}

TEST_CASE("shouldMapTypeOfEmpty", "[3]")
{
    trl::optional<int> opt;
    trl::optional<std::string> dOpt = opt.map<std::string>([&](auto i) {
        return "Hello world";
    });

    REQUIRE_FALSE(opt.has_value());
    REQUIRE_FALSE(dOpt.has_value());
}

TEST_CASE("shouldFlatMapFromOneTypeToAnotherEmptyType", "[3]")
{
    int value = 5;
    trl::optional<int> opt = value;
    trl::optional<double> dOpt = opt.flatMap<double>([&](auto i) {
        return trl::optional<double>();
    });

    REQUIRE_FALSE(dOpt.has_value());
}

TEST_CASE("shouldFlatMapFromOneTypeToAnotherType", "[3]")
{
    int value = 5;
    trl::optional<int> opt = value;
    trl::optional<std::string> dOpt = opt.flatMap<std::string>([&](auto i) {
        trl::optional<std::string> dVal = std::string(i, '#');
        return dVal;
    });

    REQUIRE(dOpt.value().size() == value);
}

TEST_CASE("shouldRunForEachFunction", "[3]")
{
    int value = 5;
    int otherNumber = 0;

    trl::optional<int> opt = value;
    opt.forEach([&otherNumber](auto i) {
        otherNumber = i;
    });

    REQUIRE(otherNumber == value);
}
