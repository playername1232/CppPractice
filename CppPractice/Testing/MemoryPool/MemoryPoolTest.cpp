#include "MemoryPoolTest.h"
#include "../../lowsrc/MemoryPool/MemoryPool.h"

#include <iostream>

int MemoryPoolTest::mainMemoryPoolTest()
{
    MemoryPool<int> pool(5);

    int* a = pool.AllocateMemory();
    int* b = pool.AllocateMemory();
    int* c = pool.AllocateMemory();

    if (a) *a = 10;
    if (b) *b = 20;
    if (c) *c = 30;

    pool.VisualizeMemory();

    std::cout << "\nFreeing b..." << std::endl;
    pool.FreeMemory(b);
    pool.VisualizeMemory();

    std::cout << "\nReallocating to size 7..." << std::endl;
    int* ptrs[] = { a, c };
    pool.ReallocateMemory(ptrs, 7);

    if (ptrs[0]) *ptrs[0] += 1;
    if (ptrs[1]) *ptrs[1] += 1;

    pool.VisualizeMemory();

    return 0;
}
