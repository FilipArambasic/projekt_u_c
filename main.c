#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"

int main() {

    int izbor = 1;

    while (izbor != 999) {
        izbor = izbornik();
    }

    return 0;
}
