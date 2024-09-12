#include "../include/filesearcher.h"

#include <stdio.h>
#include <string.h>

void find(char* fileName) {
    printf("%s\n", fileName);
    char* currentFolder = ROOT_FOLDER;
    while (!isInFolder(currentFolder, fileName)) {
        printf("%s\n", currentFolder);
        goToSubdirectory(currentFolder);
    }
    printf("%s/%s\n", currentFolder, fileName);
}

bool isInFolder(char* filePath, const char* fileName) {
    FILE *file = fopen(strcat(filePath, fileName), "r");
    if (file == NULL) return false;
    fclose(file);
    return true;
}

void goToSubdirectory(char* directory) {

}
