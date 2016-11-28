#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>

// Procura a palavra com maior número de caracteres
int biggerName(int argc, char* argv[])
{
    unsigned long bigger_name = 0;
    printf("\n Arquivos: %d \n", argc - 1);
    for (int i = 0; i < argc; i++) {
        //printf("%s\n", argv[i]);
        //printf("%ld\n", strlen(argv[i]));
        if (strlen(argv[i]) > bigger_name)
            bigger_name = strlen(argv[i]);
    }
    printf("\nBigger Name: %ld chars.\n", bigger_name);
    return bigger_name;
}

int biggerFile(int argc, char* argv[])
{
    unsigned long biggerFile = 0, counter = 0;
    std::string word;
    std::ifstream file;

    int i, t;
    FILE *arq;

    for (i = 1; i < argc; ++i) {
        if(!(arq = fopen(argv[i], "r"))) {
            fprintf(stderr, "Erro ao tentar abrir %s\n", argv[i]);
            continue;
        }
        fseek(arq, 0, SEEK_END);
        t = ftell(arq);
        fclose(arq);

        if (t > biggerFile) biggerFile = t;
    }
    return biggerFile;

}

int main (int argc, char* argv[])
{
    biggerName(argc, argv);
    std::cout << "Bigger File: " << biggerFile(argc, argv) << " bytes.\n";
}
