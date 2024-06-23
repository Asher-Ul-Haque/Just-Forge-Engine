#pragma once
#include <defines.h>

#define PASS 0
#define FAIL 1
#define BYPASS 2

typedef unsigned char (*testFunction)();

void initializeTestManager();

void testManagerRegisterTest(testFunction, char* DESCRIPTION);

void testManagerRunTests();
