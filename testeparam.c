#include <stdio.h>
#include <string.h>

int biggerName(const char* argv[])
{
    unsigned long bigger_name = 0;
    printf("\n Arquivos: %d \n", argc - 1);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
        printf("%ld\n", strlen(argv[i]));
        if (strlen(argv[i]) > bigger_name)
            bigger_name = strlen(argv[i]);
    }
    printf("\nBigger Name: %d chars.\n", bigger_name);
    return bigger_name;
}

int main (int argc, char* argv[])
{
    biggerName(argv[]);
}
