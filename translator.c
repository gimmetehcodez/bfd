#include <stdio.h>

int main(void)
{
    int c;
    while ((c = getchar()) != EOF)
    {
        switch (c) {
          case '>': printf("010"); break;
          case '<': printf("011"); break;
          case '+': printf("000"); break;
          case '-': printf("001"); break;
          case '.': printf("100"); break;
          case ',': printf("101"); break;
          case '[': printf("110"); break;
          case ']': printf("111"); break;
        }
    }
}
