//
// Created by Michael Lynch on 21/02/2022.
//

#include <trlang/ReversibleRandomGenerator.hpp>
#include <cmath>

const double MULTIPLIER = 2553.589304;

trl::ReversibleRandomGenerator::ReversibleRandomGenerator(unsigned int initialSeed)
    : initialSeed_(initialSeed == 0 ? 35894 : initialSeed)
{
    reset();
}

unsigned int trl::ReversibleRandomGenerator::next()
{
    unsigned int nextValue = (int)std::abs(currentGenerator_) % UINT32_MAX;

    currentGenerator_ += std::tan(initialSeed_ * MULTIPLIER);

    return nextValue;
}

unsigned int trl::ReversibleRandomGenerator::previous()
{
    currentGenerator_ -= std::tan(initialSeed_ * MULTIPLIER);

    unsigned int previousValue = (int)std::abs(currentGenerator_) % UINT32_MAX;

    return previousValue;
}

void trl::ReversibleRandomGenerator::reset()
{
    currentGenerator_ = std::tan(initialSeed_ * MULTIPLIER);
}
