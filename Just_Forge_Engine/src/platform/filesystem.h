#pragma once
#include "defines.h"

typedef struct File 
{
    void* handle;
    bool8 isValid;
} File;

typedef enum fileModes
{
    FILE_MODE_READ = 0x1,
    FILE_MODE_WRITE = 0x2,
} fileModes;

FORGE_API bool8 fileExists(const char* PATH);

FORGE_API bool8 openFile(const char* PATH, fileModes MODE, bool8 BINARY_MODE, File* OUTPUT_FILE);

FORGE_API void closeFile(File* INPUT_FILE);

FORGE_API bool8 readFileLine(File* INPUT_FILE, char** BUFFER);

FORGE_API bool8 writeFileLine(File* INPUT_FILE, const char* TEXT);

FORGE_API bool8 readFile(File* INPUT_FILE, unsigned long long DATA_SIZE, void* BUFFER, unsigned long long* READ_BYTES);

FORGE_API bool8 readAllBytes(File* INPUT_FILE, unsigned char** OUTPUT, unsigned long long* READ_BYTES);

FORGE_API bool8 writeFile(File* INPUT_FILE, unsigned long long DATA_SIZE, const void* DATA, unsigned long long* WRITE_BYTES);
