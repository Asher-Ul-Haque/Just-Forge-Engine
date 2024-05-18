#pragma once


// - - - | New Data Types and Assertions | - - -


// - - - Boolean Data Types
typedef int bool32;
typedef char bool8;

#define TRUE 1
#define FALSE 0

// - - - Static Assertions
#if defined (__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

//Ensure all types are of the correct size
// - - - Boolean
STATIC_ASSERT(sizeof(bool32) == 4, "boolean32 is not 4 bytes");
STATIC_ASSERT(sizeof(bool8) == 1, "boolean8 is not 1 byte");

// - - - Character
STATIC_ASSERT(sizeof(char) == 1, "char is not 1 byte");
STATIC_ASSERT(sizeof(unsigned char) == 1, "unsigned char is not 1 byte");

// - - - Smol integer
STATIC_ASSERT(sizeof(short) == 2, "short is not 2 bytes");
STATIC_ASSERT(sizeof(unsigned short) == 2, "unsigned short is not 2 bytes");

// - - - Normal integer
STATIC_ASSERT(sizeof(int) == 4, "int is not 4 bytes");
STATIC_ASSERT(sizeof(unsigned int) == 4, "unsigned int is not 4 bytes");

// - - - Beeg integer
STATIC_ASSERT(sizeof(long) == 8, "long is not 8 bytes");
STATIC_ASSERT(sizeof(unsigned long) == 8, "unsigned long is not 8 bytes");

// - - - Too beeg integer
STATIC_ASSERT(sizeof(long long) == 8, "long long is not 8 bytes");
STATIC_ASSERT(sizeof(unsigned long long) == 8, "unsigned long long is not 8 bytes");

// - - - Floating point numbers
STATIC_ASSERT(sizeof(float) == 4, "float is not 4 bytes");
STATIC_ASSERT(sizeof(double) == 8, "double is not 8 bytes");
STATIC_ASSERT(sizeof(long double) == 16, "long double is not 16 bytes");


// - - - | Platform Detection | - - -


// - - - Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define FORGE_PLATFORM_WINDOWS 1

// - - - Linux
#elif defined(__linux__) || defined(__gnu_linux__)
#define FORGE_PLATFORM_LINUX 1

#endif


// - - - | Forge API | - - -


// - - - Export
#ifdef FORGE_EXPORT
#ifdef _MSC_VER
#define FORGE_API __declspec(dllexport)
#else 
#define FORGE_API __attribute__((visibility("default")))
#endif

// - - - Imports
#else 
#ifdef _MSC_VER
#define FORGE_API __declspec(dllimport)
#else 
#define FORGE_API
#endif
#endif


