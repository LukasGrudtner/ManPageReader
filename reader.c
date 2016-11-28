#include <stdio.h>
#include <string.h>

int contaChar(const char *str)
{
    int i = 0;
    for(;str[i] != 0; ++i)
    return i;
}

int main (int argc, char* argv[])
{
    int bigger_name = 0;
    int i;
    printf("\n Arquivos: %d \n", argc - 1);
    for (i=1; i < argc; i++) {
        printf("--> %s\n", argv[i]);
        printf("%ld\n", strlen(argv[i]));
        if (strlen(argv[i]) > bigger_name)
            bigger_name = strlen(argv[i]);
    }
    printf("\nBigger Name: %d chars.\n", bigger_name);
}
