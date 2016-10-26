#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int getbin(char*,FILE*);
void bf_interpret(char*);

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr,"Usage: binary file.b\n");
        return -1;
    }

    FILE *in = fopen(argv[1],"r");

    if (!in) {
        fprintf(stderr,"Error opening file %s: %s\n",argv[1],strerror(errno));
        return -1;
    }

    int i = 0;
    char buf[4], bf[100000] = {0};
    while (getbin(buf,in))
    {
        if (!strcmp(buf,"010"))
            bf[i] = '>';
        else if (!strcmp(buf,"011"))
            bf[i] = '<';
        else if (!strcmp(buf,"000"))
            bf[i] = '+';
        else if (!strcmp(buf,"001"))
            bf[i] = '-';
        else if (!strcmp(buf,"100"))
            bf[i] = '.';
        else if (!strcmp(buf,"101"))
            bf[i] = ',';
        else if (!strcmp(buf,"110"))
            bf[i] = '[';
        else if (!strcmp(buf,"111"))
            bf[i] = ']';
        else
            bf[i] = ' ';
        i++;
    }

    bf_interpret(bf);
}

int getbin(char *buf, FILE *in)
{
    int c, i = 0;
    while (i < 3) {
        if ((c = getc(in)) == EOF)
            return 0;
        else
            buf[i] = c;
        i++;
    }
    buf[3] = 0;

    return 1;
}

//thx m8 https://gist.github.com/maxcountryman/1699708
// initialize the tape with 30,000 zeroes
unsigned char tape[30000] = {0};

// set the pointer to point at the left-most cell of the tape
unsigned char* ptr = tape;

void bf_interpret(char* input) {
    char current_char;
    size_t i;
    size_t loop;

    for (i = 0; input[i] != 0; i++) {
        current_char = input[i];
        if (current_char == '>') {
            ++ptr;
        } else if (current_char == '<') {
            --ptr;
        } else if (current_char == '+') {
            ++*ptr;
        } else if (current_char == '-') {
            --*ptr;
        } else if (current_char == '.' ) {
            putchar(*ptr);
        } else if (current_char == ',') {
            *ptr = getchar();
        } else if (current_char == '[') {
            continue;
        } else if (current_char == ']' && *ptr) {
            loop = 1;
            while (loop > 0) {
                current_char = input[--i];
                if (current_char == '[') {
                    loop--;
                } else if (current_char == ']') {
                    loop++;
                }
            }
        }
    }
}
