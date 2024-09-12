#include <stdio.h>
#include "../include/filesearcher.h"

int main(const int argc, const char * argv[]) {
    if (argc != 2) {
        printf("Error: Wrong number of arguments\n");
        return 0;
    }

    find(argv[1]);
}
