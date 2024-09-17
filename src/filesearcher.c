#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void find(const char* fileArray[], const int fileArraySize) {
    for (int i = 1; i < fileArraySize; i++) {
        searchInFolder(ROOT_DIRECTORY, fileArray[i]);
    }
}

void searchInFolder(char* currentDirectoryPath, const char* fileName) {
    DIR *currentDirectory = opendir(currentDirectoryPath);
    if (!currentDirectory) return;

    struct dirent *entry;
    while ((entry = readdir(currentDirectory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        if (entry->d_type != DT_DIR && isFileSuitable(fileName, entry->d_name)) {
            printf("%s/%s\n", currentDirectoryPath, entry->d_name);
        }

        if (entry->d_type == DT_DIR) {
            char newPath[1000];
            snprintf(newPath, sizeof(newPath), "%s/%s", currentDirectoryPath, entry->d_name);
            searchInFolder(newPath, fileName);
        }
    }
    closedir(currentDirectory);
}

bool isFileSuitable(const char* searchedFileName, const char* currentFileName) {
    int i = 0, j = 0;
    while (i < strlen(currentFileName)) {
        if (searchedFileName[j] == currentFileName[i] || searchedFileName[j] == '.') {
            j++;
            i++;
        } else if (searchedFileName[j] == '*') {
            return true;
        } else {
            return false;
        }
    }
    return searchedFileName[j] == '\0';
}