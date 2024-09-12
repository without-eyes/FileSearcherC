#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <stdbool.h>

#ifdef __unix__
    #define ROOT_FOLDER "/"
#elif defined(_WIN32) || defined(WIN32)/
    #define ROOT_FOLDER "C:/"
#endif

void find(const char* fileName);

bool isInFolder(char* filePath, const char* fileName);

void goToSubdirectory(char* directory);

#endif //FILESEARCHER_H
