#include <stdio.h>
#include <stdlib.h>
#include "include\bairro.h"

#define NOME 30

typedef struct Bairros_da_cidade{

    char nome[NOME];
    int id;

}Bairros;

typedef struct hash{

    int qtd;
    int tam;
    Bairros **itens;

}Hash;

void confere_alloc(Bairros *item){

    if(item == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }
}

void preenche_bairros(){

    Bairros bairro1;
    bairro1.nome[NOME] = "Jardim das Anas";
    bairro1.id = 1000;

    Bairros bairro2;
    bairro2.nome[NOME] = "Vila São Pedroso";
    bairro2.id = 2000;

    Bairros bairro3;
    bairro3.nome[NOME] = "Gugarujá";
    bairro3.id = 3000;

    Bairros bairro4;
    bairro4.nome[NOME] = "Igornema";
    bairro4.id = 4000;

    Bairros bairro5;
    bairro5.nome[NOME] = "Miicca";
    bairro5.id = 5000;

    Bairros bairro6;
    bairro6.nome[NOME] = "Nova Olyans";
    bairro6.id = 6000;

    Bairros bairro7;
    bairro7.nome[NOME] = "Fenda dos Parafusos";
    bairro7.id = 7000;

    Bairros bairro8;
    bairro8.nome[NOME] = "Ciriacabana";
    bairro8.id = 8000;

    Bairros bairro9;
    bairro9.nome[NOME] = "Vila Santa Caroline";
    bairro9.id = 9000;

}


