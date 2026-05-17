#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <source.c> <output_executable>\n", argv[0]);
        return 1;
    }

    char cmd[1024];
    sprintf(cmd, "gcc %s -o %s", argv[1], argv[2]);

    system(cmd);
 
    return 0;
}