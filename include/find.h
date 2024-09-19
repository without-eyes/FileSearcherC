#ifndef FIND_H
#define FIND_H

#include <stdbool.h>

#define ROOT_DIRECTORY "/"
#define MAX_THREADS 16

typedef struct {
    char path[1000];
    const char* fileName;
} FilePath;

void findFile(const char* fileArray[], int fileArraySize);

void* threadedSearch(void* params);

void recursiveSearch(char* currentDirectoryPath, const char* fileName);

bool isFileSuitable(const char* searchedFileName, const char* currentFileName);

bool isDotDirectory(const char* directoryName);

#endif //FIND_H
