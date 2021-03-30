// gcc -fno-stack-protector -z execstack -no-pie -o vul vul.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vul(char* name) {
        char buf[64] = {};
        strcpy(buf, name);
}

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf ("Usage: %s [Your name]\n", argv[0]);
                exit(-1);
        }

        vul(argv[1]);
        return 0;
}

