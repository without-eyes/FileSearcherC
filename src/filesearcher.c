#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void findFile(const char* fileArray[], const int fileArraySize) {
    for (int i = 1; i < fileArraySize; i++) {
        searchInRootFolder(ROOT_DIRECTORY, fileArray[i]);
    }
}

void searchInRootFolder(char* currentDirectoryPath, const char* fileName) {
    DIR *currentDirectory = opendir(currentDirectoryPath);
    if (!currentDirectory) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(currentDirectory)) != NULL) {
        if (isDotDirectory(entry->d_name)) {
            continue;
        }

        if (entry->d_type != DT_DIR && isFileSuitable(fileName, entry->d_name)) {
            printf("%s/%s\n", currentDirectoryPath, entry->d_name);
        } else if (entry->d_type == DT_DIR) {
            char newPath[1000];
            snprintf(newPath, sizeof(newPath), "%s/%s", currentDirectoryPath, entry->d_name);
            searchInRootFolder(newPath, fileName);
        }
    }

    closedir(currentDirectory);
}

void recursiveSearch(char* currentDirectoryPath, const char* fileName) {

}

bool isFileSuitable(const char* searchedFileName, const char* currentFileName) {
    int currentFilePosition = 0, searchedFilePosition = 0;
    while (currentFilePosition < strlen(currentFileName)) {
        if (searchedFileName[searchedFilePosition] == currentFileName[currentFilePosition] || searchedFileName[searchedFilePosition] == '.') {
            searchedFilePosition++;
            currentFilePosition++;
        } else if (searchedFileName[searchedFilePosition] == '*') {
            return true;
        } else {
            return false;
        }
    }
    return searchedFileName[searchedFilePosition] == '\0';
}

bool isDotDirectory(const char* directoryName) {
    return strcmp(directoryName, ".") == 0 || strcmp(directoryName, "..") == 0;
}