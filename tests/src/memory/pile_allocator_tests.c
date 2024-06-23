#include "pile_allocator_tests.h"
#include "../test_manager.h"
#include "../expect.h"
#include <memory/pile_alloc.h>

unsigned char pileAllocatorShouldCreateAndDestroyPile()
{
    PileAllocator pile;
    createPileAllocator(sizeof(unsigned long long), 0, &pile);

    expectShouldNotBe(0, pile.memory);
    expectShouldBe(sizeof(unsigned long long), pile.totalSize);
    expectShouldBe(0, pile.allocatedSize);
    
    destroyPileAllocator(&pile);

    expectShouldBe(0, pile.memory);
    expectShouldBe(0, pile.totalSize);
    expectShouldBe(0, pile.allocatedSize);

    return true;
}

unsigned char pileAllocatorSingleAllocAllSpace()
{
    PileAllocator pile;
    createPileAllocator(sizeof(unsigned long long), 0, &pile);

    //Single allocation
    void* block = pileAlloc(&pile, sizeof(unsigned long long));
    //validation
    expectShouldNotBe(0, block);
    expectShouldBe(sizeof(unsigned long long), pile.allocatedSize);

    destroyPileAllocator(&pile);
    return true;
}

unsigned char pileAllocatorMultiAllocAllSpace()
{
    unsigned long long maxAllocs = 1024;
    PileAllocator pile;
    createPileAllocator(sizeof(unsigned long long) * maxAllocs, 0, &pile);

    //Multiple allocations until full
    void* block;
    for (unsigned long long i = 0; i < maxAllocs; ++i)
    {
        block = pileAlloc(&pile, sizeof(unsigned long long));
        //validation
        expectShouldNotBe(0, block);
        expectShouldBe(sizeof(unsigned long long) * (i + 1), pile.allocatedSize);
    }
    destroyPileAllocator(&pile);
    return true;
}

unsigned char pileAllocationMultiAllocOverAlloc()
{
    unsigned long long maxAllocs = 3;
    PileAllocator pile;
    createPileAllocator(sizeof(unsigned long long) * maxAllocs, 0, &pile);

    //Multiple allocations until full
    void* block;
    for (unsigned long long i = 0; i < maxAllocs; ++i)
    {
        block = pileAlloc(&pile, sizeof(unsigned long long));
        //validation
        expectShouldNotBe(0, block);
        expectShouldBe(sizeof(unsigned long long) * (i + 1), pile.allocatedSize);
    }

    FORGE_LOG_DEBUG("Allocating one more block than possible, Intentional bug");
    block = pileAlloc(&pile, sizeof(unsigned long long));
    //validation
    expectShouldBe(0, block);
    expectShouldBe(sizeof(unsigned long long) * maxAllocs, pile.allocatedSize);
    destroyPileAllocator(&pile);
    return true;
}

unsigned char pileAllocatorMultiAllocAllSpaceThenFree()
{
    unsigned long long maxAllocs = 1024;
    PileAllocator pile;
    createPileAllocator(sizeof(unsigned long long) * maxAllocs, 0, &pile);

    //Multiple allocations until full
    void* block;
    for (unsigned long long i = 0; i < maxAllocs; ++i)
    {
        block = pileAlloc(&pile, sizeof(unsigned long long));
        //validation
        expectShouldNotBe(0, block);
        expectShouldBe(sizeof(unsigned long long) * (i + 1), pile.allocatedSize);
    }

    //Free all allocations
    pileFree(&pile);
    expectShouldBe(0, pile.allocatedSize);
    destroyPileAllocator(&pile);
    return true;
}

void pileAllocatorRegisterTests()
{
    testManagerRegisterTest(pileAllocatorShouldCreateAndDestroyPile, "Pile Allocator should create and destroy a pile");
    testManagerRegisterTest(pileAllocatorSingleAllocAllSpace, "Allocate once in a pile until full");
    testManagerRegisterTest(pileAllocatorMultiAllocAllSpace, "Allocate multiple times in a pile until full");
    testManagerRegisterTest(pileAllocationMultiAllocOverAlloc, "Allocate more than possible in a pile");
    testManagerRegisterTest(pileAllocatorMultiAllocAllSpaceThenFree, "Allocate multiple times in a pile until full, then free all");
}
