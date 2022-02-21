//
// Created by Michael Lynch on 21/02/2022.
//

#include <trlang/ReversibleRandomGenerator.hpp>
#include <cmath>

const double DIVISOR = 2553;

trl::ReversibleRandomGenerator::ReversibleRandomGenerator(unsigned int initialSeed)
    : initialSeed_(initialSeed)
{
    currentGenerator_ = std::sin(initialSeed * 1.0 / DIVISOR);
}

unsigned int trl::ReversibleRandomGenerator::next()
{
    unsigned int nextValue = std::floor(
            (currentGenerator_ * std::pow(10, 10))
                - (currentGenerator_ * std::pow(10, 4)));

    currentGenerator_ += std::sin(initialSeed_ * 1.0 / DIVISOR);

    return nextValue;
}

unsigned int trl::ReversibleRandomGenerator::previous()
{
    currentGenerator_ -= std::sin(initialSeed_ * 1.0 / DIVISOR);

    unsigned int previousValue = std::floor(
            (currentGenerator_ * std::pow(10, 10))
                - (currentGenerator_ * std::pow(10, 4)));

    return previousValue;
}

void trl::ReversibleRandomGenerator::reset()
{
    currentGenerator_ = std::sin(initialSeed_ * 1.0 / DIVISOR);
}
