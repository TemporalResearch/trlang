//
// Created by Michael Lynch on 11/04/2021.
//

#ifndef AUTO_HARMONY_CHUNKGENERATOR_HPP
#define AUTO_HARMONY_CHUNKGENERATOR_HPP

#include <vector>

namespace trl
{
/**
 * A generator for a chunk of data.
 * @tparam T Type of the data being generated
 */
    template<class T>
    class ChunkGenerator
    {
    private:
        bool _initialized;
        unsigned int _currentSeed;
        unsigned int _currentChunk;

    protected:
        std::vector<T> _data;

    public:
        ChunkGenerator() :
                _initialized(false),
                _currentSeed(0),
                _currentChunk(0),
                _data()
        {

        }

        virtual ~ChunkGenerator() = default;

        /**
         * Regenerates the chunk at a specific chunk id and seed.
         * @param seed The seed that the chunk should use to generate data with.
         * @param chunkId The id of the chunk which is to be generated.
         */
        void withSeedAndPosition(const unsigned int &seed, const unsigned int chunkId)
        {
            if (!_initialized
                || (seed != _currentSeed && chunkId != _currentChunk))
            {
                regenerateData(seed, chunkId);
                _initialized = true;
                _currentChunk = chunkId;
                _currentSeed = seed;
            }
        }

        /**
         * Access part of the chunk data.
         * @param dataPosition The position in the chunk to access.
         * @return A const reference to the piece of data in the chunk.
         */
        const T& operator[](const int &dataPosition) const
        {
            return at(dataPosition);
        }

        /**
         * Access part of the chunk data.
         * @param dataPosition The position in the chunk to access.
         * @return A const reference to the piece of data in the chunk.
         */
        const T& at(const int &dataPosition) const
        {
            return _data.at(dataPosition);
        }

        /**
         * The number of elements of data present in a chunk of data.
         */
        [[nodiscard]] unsigned int size() const
        {
            return _data.size();
        }

        /**
         * Implemented by sub-classes, this will regenerate the data based on the current seed and chunkId.
         */
        virtual void regenerateData(const unsigned int &seed, const unsigned int &chunkId) = 0;

    };
}

#endif //AUTO_HARMONY_CHUNKGENERATOR_HPP
