#include <stdio.h>

const char *s = "#include <stdio.h>%c%cconst char *s = %c%s%c;%c%cint main() {%c  printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 10);%c  return 0;%c}";

int main() {
  printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 10);
  return 0;
}