#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void find(const char* fileName) {
    char* currentDirectoryPath = ROOT_DIRECTORY;
    searchInFolder(currentDirectoryPath, fileName);
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