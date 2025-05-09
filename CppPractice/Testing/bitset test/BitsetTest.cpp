#include "BitsetTest.h"

#include <iostream>

#include "../../lowsrc/PBitset/PBitset.hpp"

int BitsetTest::mainBitsetTest()
{
    constexpr size_t BIT_COUNT = 128;  // Počet bitů v bitsetu
    PBitset<BIT_COUNT> bits;

    std::cout << "== Initial State ==\n";
    std::cout << "Any: " << bits.Any() << "\n";
    std::cout << "None: " << bits.None() << "\n";
    std::cout << "Count: " << bits.Count() << "\n";

    std::cout << "\n== Setting bits 0, 1, and 127 ==\n";
    bits.Set(0);
    bits.Set(1);
    bits.Set(127);

    std::cout << "Any: " << bits.Any() << "\n";
    std::cout << "None: " << bits.None() << "\n";
    std::cout << "Count: " << bits.Count() << "\n";

    std::cout << "\n== Resetting bit 1 ==\n";
    bits.Reset(1);

    std::cout << "Any: " << bits.Any() << "\n";
    std::cout << "None: " << bits.None() << "\n";
    std::cout << "Count: " << bits.Count() << "\n";

    std::cout << "\n== Testing specific bits ==\n";
    std::cout << "Bit 0: " << bits.Test(0) << "\n";
    std::cout << "Bit 1: " << bits.Test(1) << "\n";
    std::cout << "Bit 127: " << bits.Test(127) << "\n";

    return 0;
}
