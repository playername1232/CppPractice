#include "MainTestManger.h"

#include "bitset test/BitsetTest.h"
#include "MemoryPool/MemoryPoolTest.h"

int MainTestManger::testMemory()
{
    return MemoryPoolTest::mainMemoryPoolTest();
}

int MainTestManger::testBitset()
{
    return BitsetTest::mainBitsetTest();
}
