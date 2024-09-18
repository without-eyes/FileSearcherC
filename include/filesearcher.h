#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <stdbool.h>

#ifdef __unix__
    #define ROOT_DIRECTORY "/"
#elif defined(_WIN32) || defined(WIN32)/
    #define ROOT_DIRECTORY "C:/"
#endif

void findFile(const char* fileArray[], int fileArraySize);

void searchInRootFolder(char* currentDirectoryPath, const char* fileName);

void recursiveSearch(char* currentDirectoryPath, const char* fileName);

bool isFileSuitable(const char* searchedFileName, const char* currentFileName);

bool isDotDirectory(const char* directoryName);

#endif //FILESEARCHER_H
