//
// Created by Michael Lynch on 21/02/2022.
//

#pragma once


namespace trl
{
    class ReversibleRandomGenerator
    {
    public:
        explicit ReversibleRandomGenerator(unsigned int initialSeed);

        unsigned int next();
        unsigned int previous();

        void reset();
    private:
        unsigned int initialSeed_;
        double currentGenerator_;
    };
}
