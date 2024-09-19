#include "../include/find.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t print_mutex;

void findFile(const char* fileArray[], const int fileArraySize) {
    pthread_t threads[MAX_THREADS];
    int threadCount = 0;

    for (int i = 1; i < fileArraySize; i++) {
        FilePath* filePath = malloc(sizeof(FilePath));
        snprintf(filePath->path, sizeof(filePath->path), "%s", ROOT_DIRECTORY);
        filePath->fileName = fileArray[i];

        pthread_create(&threads[threadCount++], NULL, threadedSearch, filePath);

        if (threadCount >= MAX_THREADS) {
            for (int j = 0; j < threadCount; j++) {
                pthread_join(threads[j], NULL);
            }
            threadCount = 0;
        }
    }

    for (int j = 0; j < threadCount; j++) {
        pthread_join(threads[j], NULL);
    }
}

void* threadedSearch(void* params) {
    FilePath* filePath = params;
    recursiveSearch(filePath->path, filePath->fileName);
    free(params);
    return NULL;
}

void recursiveSearch(char* currentDirectoryPath, const char* fileName) {
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
            pthread_mutex_lock(&print_mutex);
            printf("%s/%s\n", currentDirectoryPath, entry->d_name);
            pthread_mutex_unlock(&print_mutex);
        } else if (entry->d_type == DT_DIR) {
            char newPath[1000];
            if (currentDirectoryPath[strlen(currentDirectoryPath) - 1] == '/') {
                snprintf(newPath, sizeof(newPath), "%s%s", currentDirectoryPath, entry->d_name);
            } else {
                snprintf(newPath, sizeof(newPath), "%s/%s", currentDirectoryPath, entry->d_name);
            }
            recursiveSearch(newPath, fileName);
        }
    }

    closedir(currentDirectory);
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