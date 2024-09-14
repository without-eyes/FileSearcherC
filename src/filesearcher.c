#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

// ДОДАТИ ПОШУК З * і .
// ДОДАТИ БАГАТОПОТОКОВІСТЬ
// ЗАРЕФАКТОРИТИ КОД ПО ТРЕЛЛО
// ЮНІТ ТЕСТИ

void find(const char* fileArray[], const int fileArraySize) {
    for (int i = 1; i < fileArraySize; i++) {
        searchInFolder(ROOT_DIRECTORY, fileArray[i]);
    }
}

void searchInFolder(char* currentDirectoryPath, const char* fileName) {
    if (isInFolder(currentDirectoryPath, fileName)) {
        printf("%s/%s\n", currentDirectoryPath, fileName);
        return;
    }

    DIR *currentDirectory = opendir(currentDirectoryPath);
    if (!currentDirectory) return;

    struct dirent *entry;
    while ((entry = readdir(currentDirectory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        if (entry->d_type == DT_DIR) {
            char newPath[1000];
            snprintf(newPath, sizeof(newPath), "%s/%s", currentDirectoryPath, entry->d_name);
            searchInFolder(newPath, fileName);
        }
    }
    closedir(currentDirectory);
}

bool isInFolder(char* directoryPath, const char* fileName) {
    char filePath[1000];
    if (snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, fileName) >= sizeof(filePath)) return false;
    FILE *file = fopen(filePath, "r");
    if (file == NULL) return false;
    fclose(file);
    return true;
}