#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

// ФІКСАНУТИ ВИВІД ШЛЯХУ КОЛИ ВИКОРИСТОВУЄТЬСЯ . або *
// ФІКСАНУТИ ЩО ПОГАНО ШУКАЄ main.c з . або *
// ДОДАТИ БАГАТОПОТОКОВІСТЬ
// ЗАРЕФАКТОРИТИ КОД ПО ТРЕЛЛО
// ЮНІТ ТЕСТИ
// НАПИСАТИ README

void find(const char* fileArray[], const int fileArraySize) {
    for (int i = 1; i < fileArraySize; i++) {
        printf("\n========================\n%s\n========================\n", fileArray[i]);
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

bool isInFolder(const char* directoryPath, const char* fileName) {
    DIR *directory = opendir(directoryPath);
    if (!directory) {
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        if (isFileSuitable(fileName, entry->d_name)) {
            closedir(directory);
            return true;
        }
    }

    closedir(directory);
    return false;
}

bool isFileSuitable(const char* searchedFileName, const char* currentFileName) {
    int i = 0, j = 0;
    while (i < strlen(currentFileName)) {
        if (searchedFileName[j] == currentFileName[i] || searchedFileName[j] == '.') {
            j++;
            i++;
        } else if (searchedFileName[j] == '8') {
            i++;
        } else {
            return false;
        }
    }
    return searchedFileName[j] == '\0';
}