#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <list>
#include "linked_list.h"

using namespace std;

/* Retorna o Comando com o maior nome */
int biggerName(int argc, char* argv[])
{
    unsigned long bigger_name = 0;
    for (int i = 0; i < argc; i++) {
        if (strlen(argv[i]) > bigger_name)
            bigger_name = strlen(argv[i]);
    }
    return bigger_name;
}

/* Retorna a ManPage com o maior conteúdo */
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

/* Faz a filtragem das palavras, retirando as que caem em categorias léxicas */
bool selectWord(std::string word)
{
    if(word[1] == '\0')
        return false;
    if(word[0] == '{' || word[0] == '}')
        return false;

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

    string preposicoes[] = {"in", "on", "at", "of"};
    string conjuncoes[] = {"and", "but", "or", "so", "althoug", "because",
                            "for", "if", "since", "either", "neither"};
    string pronomes[] = {"I", "you", "he", "she", "it", "we", "you", "they",
                        "me", "him", "her", "us", "them", "my", "your", "his",
                        "her", "its", "out", "their", "mine", "hers", "ours",
                        "yours", "theirs", "somebody", "someone", "something",
                        "nobody", "nothing", "nowhere", "who", "which", "that",
                        "this", "these", "that", "those"};
    string artigos[] = {"the", "an", "a"};


    for (int i = 0; i < (sizeof(preposicoes)/sizeof(string)); i++) {
        if (word == preposicoes[i])
            return false;
    }

    for (int i = 0; i < (sizeof(conjuncoes)/sizeof(string)); i++) {
        if (word == conjuncoes[i])
            return false;
    }

    for (int i = 0; i < (sizeof(pronomes)/sizeof(string)); i++) {
        if (word == pronomes[i])
            return false;
    }

    for (int i = 0; i < (sizeof(artigos)/sizeof(string)); i++) {
        if (word == artigos[i])
            return false;
    }

    return true;
}

/* Encontra as chaves secundárias e as escreve em arquivo */
void findSecondaryKeys(int argc, char *argv[])
{
    std::ifstream file;
    std::ofstream output;
    std::string word;
    int counter = 0;

    output.open("words.dat");

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

/* Cria os registros das ManPages */
void createRegisters(int argc, char *argv[])
{
    int nameSize = biggerName(argc, argv);
    int contentsSize = biggerFile(argc, argv);

    cout << "Bigger Name: " << nameSize << " bytes.\n";
    cout << "Bigger File: " << contentsSize << " bytes.\n\n";

    struct manpages {
        char name[52];
        char contents[139715];
    };

    struct manpages registro;

    ifstream file;
    ofstream manpage;
    manpage.open("manpage.dat");

    for (int i = 1; i < argc; i++) {
        struct manpages registro;
        file.open(argv[i]);

        int k = 0;
        while (argv[i][k] != '\0') {
            registro.name[k] = argv[i][k];
            k++;
        }

        file.read((char *) &registro.contents, sizeof(struct manpages));

        file.close();
        manpage.write((char *) &registro, sizeof(struct manpages));

        /* Gambiarra pura. Deve ter um jeito melhor pra resolver isso. */
        int m = 0;
        while (registro.name[m] != '\0') {
            registro.name[m] = '\0';
            m++;
        }

        int n = 0;
        while (registro.contents[n] != '\0') {
            registro.contents[n] = '\0';
            n++;
        }

    }
    manpage.close();

}

/* Exemplo de como ler um arquivo para uma struct, não é utilizado */
void ler(int argc, char *argv[])
{
    struct manpages {
        char name[52];
        char contents[139715];
    };
    struct manpages registro;
    ifstream file;
    file.open("manpage.dat");

    file.seekg(139767*0);

    file.read((char *) &registro, sizeof(struct manpages));

    int posicao, counter;
    string teste = registro.contents;

    while (posicao > -1) {
        posicao = teste.find("file");
        cout << posicao << endl;
        if (posicao > -1) {
            teste[posicao] = 'c';
            counter++;
        }
    }

    cout << "Counter: " << counter << endl;

    file.close();
}

/* Lê o arquivo de Chaves Secundárias e retorna o número de chaves */
unsigned long numWords(string destino)
{
    ifstream file;
    string word;
    unsigned long counter = 0;
    file.open(destino);

    while (!file.eof()) {
        getline(file, word);
        counter++;
    }

    return counter;
}

/* Lê o arquivo bruto e escreve um arquivo retirando as palavras repetidas */
void removeRepeatedWords(int argc, char *argv[]) {
    fstream input, output;
    LinkedList* lista = new LinkedList();

    input.open("words.dat");
    output.open("secondaryKeys.dat");
    string word, word2;
    bool teste = false;
    int cont;

    while (!input.eof()) {
        input >> word;

        if (!lista->contains(word)) {
            lista->push_back(word);
            cont++;
            cout << "Lista: " << lista->size() << endl;
        }
    }

    int size = lista->size();
    for (int i = 0; i < size; i++) {
        cout << "File: " << lista->size() << endl;
        output << lista->pop_front() << endl;
    }

    cout << "Depois: " << numWords("secondaryKeys.dat") << endl;

    input.close();
    output.close();
}


int main (int argc, char* argv[])
{
    findSecondaryKeys(argc, argv);
    createRegisters(argc, argv);

    removeRepeatedWords(argc, argv);
}
