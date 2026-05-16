#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./clean_compiler <source.c> <output_executable>\n");
        return 1;
    }

    char cmd[1024];
    sprintf(cmd, "gcc %s -o %s", argv[1], argv[2]);

    system(cmd);
 
    return 0;
}