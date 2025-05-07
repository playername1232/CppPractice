#include "MainTestManger.h"

#include "MemoryPool/MemoryPoolTest.h"

int MainTestManger::testMemory()
{
    return MemoryPoolTest::mainMemoryPoolTest();
}
