#include <stdio.h>
#include "config.h"

int main() {
    printf("Program compiled with: %s\n", CONFIGURE_ARGS);
    return 0;
}
