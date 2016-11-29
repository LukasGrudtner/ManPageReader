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
    for (int i = 0; i < argc; i++) {
        if (strlen(argv[i]) > bigger_name)
            bigger_name = strlen(argv[i]);
    }
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
    int i = 0;
    while (word[i] != '\0') {
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
                counter++;
        }
        }
        file.close();
    }
    output.close();
}

/* Método para deletar as palavras repetidas no arquivo.
    Aparentemente não funciona... */
// void deleteRepeatedWords(int argc, char *argv[])
// {
//     std::string pivo, word = "";
//     int posicao;
//     std::ifstream input1, input2;
//     ofstream output;
//
//     input1.open("output.dat");
//     input2.open("output.dat");
//
//     while (!input1.eof()) {
//         input1 >> pivo;
//         cout << "Pivô: " << pivo << endl;
//         while (!input2.eof()) {
//             //cout << "Word: " << word << endl;
//             input2 >> word;
//             if (pivo == word) {
//                 posicao = input2.tellg();
//                 //cout << posicao << endl;
//                 input1.seekg(posicao);
//                 input1 >> word;
//                 getline(input1, word);
//                 //cout << word << endl;
//             }
//         }
//         input2.close();
//         input2.open("output.dat");
//     }
//     input1.close();
//     input2.close();
// }

void createRegisters(int argc, char *argv[])
{
    int nameSize = biggerName(argc, argv);
    int contentsSize = biggerFile(argc, argv);

    cout << "Bigger Name: " << nameSize << " bytes.\n";
    cout << "Bigger File: " << contentsSize << " bytes.\n\n";

    struct manpages {
        char name[17];          /* Valores para apenas 2 manpages */
        char contents[4700];
    };

    struct manpages registro;

    ifstream file;
    ofstream manpage;
    manpage.open("manpage.dat");

    for (int i = 1; i < argc; i++) {
        file.open(argv[i]);

        int k = 0;
        while (argv[i][k] != '\0') {
            registro.name[k] = argv[i][k];
            k++;
        }
        cout << "Registro.nome: " << registro.name << "\n";

        file.read((char *) &registro.contents, sizeof(struct manpages));

        file.close();
        manpage.write((char *) &registro, sizeof(struct manpages));
    }
    manpage.close();

}

int main (int argc, char* argv[])
{
    findSecondaryKeys(argc, argv);
    createRegisters(argc, argv);
}
