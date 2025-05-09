#pragma once
#include <cstdlib>    // calloc, free
#include <cstdint>    // uint64_t
#include <climits>    // CHAR_BIT

#if defined(_MSC_VER)
    #include <intrin.h>  // __popcnt64 pro MSVC
#endif

template <size_t N>
class PBitset
{
private:
    size_t count = 0;
    unsigned long long* ptr = nullptr;
    
public:
    PBitset() : count((N + 63) / 64)
    {
        ptr = (unsigned long long*)calloc(count, sizeof(unsigned long long));
    }

    ~PBitset() { free(ptr); }

    void Set(size_t i)
    {
        if (i >= N)
            return;

        size_t idx = i / 64;
        size_t bit = i % 64;

        ptr[idx] |= (1ULL << bit);
    }

    void Reset(size_t i)
    {
        if (i >= N)
            return;

        size_t idx = i / 64;
        size_t bit = i % 64;

        ptr[idx] &= ~(1ULL << bit);
    }

    bool Test(size_t i)
    {
        if (i >= N)
            return false;

        size_t idx = i / 64;
        size_t bit = i % 64;
        
        return (ptr[idx] & (1ULL << bit)) != 0;
    }

    size_t Count()
    {
        size_t total = 0;
        
        for (size_t i = 0; i < count; ++i)
        {
            // MSC
            #if defined(_MSC_VER)
                total += __popcnt64(ptr[i]);
            // GNU or CLANG
            #elif defined(__GNUC__) || defined(__clang__)
                total += __builtin_popcountll(ptr[i]);
            #else
                uint64_t val = ptr[i];
                size_t bitCount = 0;
                while (val)
                {
                    bitCount += val & 1ULL;
                    val >>= 1;
                }
                total += bitCount;
            #endif
        }

        return total;
    }
    
    bool Any() const
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (ptr[i] != 0)
                return true;
        }

        return false;
    }

    bool None() const
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (ptr[i] != 0)
                return false;
        }

        return true;
    }
};
