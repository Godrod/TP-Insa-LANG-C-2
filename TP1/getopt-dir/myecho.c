#include <stdio.h>

int main (int argc, char* argv [])
{
    int i;
    for (i = 1; i < argc; ++i)
        printf ("\033[34m%s\033[0m%c" , argv[i],  (i < argc -1) ? ' ' : '\n');

    return 0 ;
}
