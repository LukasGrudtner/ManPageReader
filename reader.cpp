#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;
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

bool selectWord(std::string word)
{
    // char alfabeto[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t"}
    int i = 0, j = 0;
    while (word[i] != '\0') {
        // if (word[i] == '0' ||word[i] == '&' ||word[i] == '*' ||word[i] == '%' ||word[i] == ':' || word[i] == '<' || word[i] == '>' || word[i] == '_' || word[i] == '=' || word[i] == '[' || word[i] == '(' || word[i] == '-' || word[i] == '.' || word[i] == '/')
        //     return false;
        // if (word[i] != "a" && word[i] != "b" && word[i] != "c" && word[i] != "d" && word[i] != "e" && word[i] != "f" && word[i] != "g" && word[i] != "h" && word[i] != "i" && word[i] != "j" && word[i] != "k" && word[i] != "l" && word[i] != "m" && word[i] != "n" && word[i] != "p" && word[i] != "p" && word[i] != "q" && word[i] != "r" && word[i] != "s" && word[i] != "t" && word[i] != "u" && word[i] != "v" && word[i] != "x" && word[i] != "y")
        for (int j = 33; j <= 64; ++j) {
            if (word[i] == j)
                return false;
        }
        for (int k = 91; k <= 96; ++k) {
            if (word[i] == k)
                return false;
        }
        ++i;
    }
    if (word == "in" || word == "on" || word == "at")
        return false;
    if (word == "and" || word == "but" || word == "or" || word == "so" || word == "althoug" || word == "because" || word == "for" || word == "if" || word == "since" || word == "either" || word == "neither")
        return false;
    if (word == "I" || word == "you" || word == "he" || word == "she" || word == "it" || word == "we" || word == "you" || word == "they" || word == "me" || word == "you" || word == "him" || word == "her" || word == "it" || word == "us" || word == "them"|| word == "my" || word == "your" || word == "his" || word == "her" || word == "its" || word == "our" || word == "their"
        || word == "mine" || word == "yours" || word == "his" || word == "hers" || word == "its" || word == "ours" || word == "yours" || word == "theirs")
        return false;
    if (word == "the" || word == "The" || word == "an" || word == "a")
        return false;

    if (word == "the" || word == "of")
        return false;

    return true;
}

void findSecondaryKeys(int argc, char *argv[])
{
    std::ifstream file;
    std::ofstream output;
    std::string word;
    int counter = 0;

    output.open("output.dat");

    for (int i = 1; i < argc; ++i) {
        file.open(argv[i]);
        while (!file.eof()) {
            file >> word;
            if (selectWord(word)) {
                output << word << std::endl;
                 //std::cout << word << endl;
                counter++;
        }
        }
        file.close();
    }
    output.close();
    cout << "\n\nCounter: " << counter << endl;
}





int main (int argc, char* argv[])
{
    biggerName(argc, argv);
    std::cout << "Bigger File: " << biggerFile(argc, argv) << " bytes.\n";
    findSecondaryKeys(argc, argv);
}
