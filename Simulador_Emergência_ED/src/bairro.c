#include <stdio.h>
#include <stdlib.h>
#include "../include/bairro.h"

#define NOME 30
#define TAM 10

typedef struct Bairros_da_cidade{

    char nome[NOME];
    int id;

}Bairros;

typedef struct hash{

    int qtd;
    int tam;
    Bairros **itens;

}Hash;

Bairros bairro1;
Bairros bairro2;
Bairros bairro3;
Bairros bairro4;
Bairros bairro5;
Bairros bairro6;
Bairros bairro7;
Bairros bairro8;
Bairros bairro9;

void confere_alloc(Hash* item){

    if(item == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }
}

Hash* cria_hash_bairros(int tamanho){

    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha != NULL){

        ha->tam = tamanho;
        ha->itens = (Bairros**) malloc(tamanho * sizeof(Bairros*));
        confere_alloc(ha->itens);
        if(ha->itens == NULL){

            free(ha);
            return NULL;

        }
        ha->qtd = 0;
        for(int i=0; i < ha->tam; i++){

            ha->itens[i] = NULL;

        }
    }

    return ha;

}

int chave_divisao(int chave, int tamanho){

    return(chave & 0x7FFFFFFF) % tamanho;

}

int sondagem_linear(int pos, int i, int tamanho){

    return((pos + i) & 0x7FFFFFFF) % tamanho;

}

int insere_hash_ender_aberto(Hash* ha, Bairros bairro){

    if(ha == NULL || ha->qtd == ha->tam){

        confere_alloc(ha);

    }
    int chave = bairro.id;
    int pos;
    int newPos;
    pos = chave_divisao(chave, ha->tam);
    for(int i = 0; i < ha->tam; i++){

        newPos = sondagem_linear(pos, i, ha->tam);
        if(ha->itens[newPos] == NULL){

            Bairros* novo = (Bairros*) malloc(sizeof(Bairros));
            confere_alloc(novo);
            *novo = bairro;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int busca_hash_ender_aberto(Hash* ha, int mat, Bairros* bairro){

    confere_alloc(ha);

    int pos = chave_divisao(mat, ha->tam);
    int newpos;

    for(int i=0; i < ha->tam; i++){

        newpos = sondagem_linear(pos, i, ha->tam);
        confere_alloc(ha->itens[newpos]);
        if(ha->itens[newpos]->id == mat){

            *bairro = *(ha->itens[newpos]);
            return 1;

        }

    }
    return 0;
}

Bairros* rand_bairro(int num){

    switch (num){

        case 1:

            return &bairro1;

        break;
        case 2:

            return &bairro2;

        break;
        case 3:

            return &bairro3;

        break;
        case 4:

            return &bairro4;

        break;
        case 5:

            return &bairro5;

        break;
        case 6:

            return &bairro6;

        break;
        case 7:

            return &bairro7;

        break;
        case 8:

            return &bairro8;

        break;
        case 9:

            return &bairro9;

        break;
        default:

            return NULL;

        break;

    }

}

void preenche_bairros(){

    Hash* ha = cria_hash_bairros(TAM);

    bairro1.nome[NOME] = "Jardim das Anas";
    bairro1.id = 1000;
    insere_hash_ender_aberto(ha, bairro1);

    bairro2.nome[NOME] = "Vila São Pedroso";
    bairro2.id = 2000;
    insere_hash_ender_aberto(ha, bairro2);

    bairro3.nome[NOME] = "Gugarujá";
    bairro3.id = 3000;
    insere_hash_ender_aberto(ha, bairro3);

    bairro4.nome[NOME] = "Igornema";
    bairro4.id = 4000;
    insere_hash_ender_aberto(ha, bairro4);

    bairro5.nome[NOME] = "Miicca";
    bairro5.id = 5000;
    insere_hash_ender_aberto(ha, bairro5);

    bairro6.nome[NOME] = "Nova Olyans";
    bairro6.id = 6000;
    insere_hash_ender_aberto(ha, bairro6);

    bairro7.nome[NOME] = "Fenda dos Parafusos";
    bairro7.id = 7000;
    insere_hash_ender_aberto(ha, bairro7);

    bairro8.nome[NOME] = "Ciriacabana";
    bairro8.id = 8000;
    insere_hash_ender_aberto(ha, bairro8);

    bairro9.nome[NOME] = "Vila Santa Caroline";
    bairro9.id = 9000;
    insere_hash_ender_aberto(ha, bairro9);

}
