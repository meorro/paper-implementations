#include <stdio.h>
#include <string.h>

int check_password(const char *pw) {
    if (strcmp(pw, "correctpassword\n") == 0) { return 1; }
    return 0;
}

int main() {
    char buf[100];

    printf("Enter password: ");
    fgets(buf, sizeof(buf), stdin);

    if (check_password(buf)) {
        printf("Access granted!\n");
    } else {
        printf("Access denied!\n");
    }

    return 0;
}