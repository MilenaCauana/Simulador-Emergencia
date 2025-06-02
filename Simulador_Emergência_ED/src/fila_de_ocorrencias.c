#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../include/fila_de_ocorrencias.h"
#include "../include/ocorrencias.h"

#define NOME 40

typedef struct Bairros_da_cidade{

    char nome[NOME];
    int id;

}Bairros;

typedef struct pessoa{

    int id;
    char nome[NOME];
    Bairros *reside;

}Morador;

typedef struct emergencias{

    int id;
    char tipo[NOME];
    int servico[3];
    Morador *vitima;

}Ocorrencia;

typedef struct no{

    Ocorrencia *incidente;
    struct no *ant;
    struct no *prox;

}No;

typedef struct descritor_fila{

    int qtd_elem;
    No *primeiro;
    No *ultimo;

}Descritor;

Descritor cria_fila(){

    Descritor no_descritor;

    no_descritor.primeiro = NULL;
    no_descritor.ultimo = NULL;
    no_descritor.qtd_elem = 0;

    return no_descritor;

}

void confere_aloc(No *novo){

    if(novo == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }
}

void exibe_ocorrencia(No *novo){

    printf("\n====================================\n");
    printf("Ocorrencia: %s\n", novo->incidente->tipo);
    printf("ID da ocorrencia: %d\n", novo->incidente->id);
    printf("Bairro: %s", novo->incidente->vitima->reside->nome);
    if(novo->incidente->servico[0] == 1){

        printf("Serviço Requisitado: Polícia\n");

    }
    if(novo->incidente->servico[1] == 1){

        printf("Serviço Requisitado: Bombeiro\n");

    }
    if(novo->incidente->servico[2] == 1){

        printf("Serviço Requisitado: Ambulancia\n");

    }
    printf("\n");
    printf("\n------------------------------------\n");
    printf("\n\jDados da vítima\j\n");
    printf("Nome: %s\n", novo->incidente->vitima->nome);
    printf("ID: %d\n", novo->incidente->vitima->id);

}

No* cria_no(Descritor *D){

    No* novo = malloc(sizeof(No));
    confere_alloc(&novo);
    novo->incidente = cria_ocorrencia();
    novo->ant = NULL;
    novo->prox = NULL;

    exibe_ocorrencia(&novo);

    return novo;
}

void adiciona_fim_fila(No* novo, Descritor *D){

    if(D->qtd_elem == 0){

        D->primeiro = novo;
        D->ultimo = novo;
        D->qtd_elem++;

    }else{

        D->ultimo->ant = novo;
        novo->prox = D->ultimo;
        D->ultimo = novo;
        novo->ant = NULL;
        novo->prox = D->ultimo;
        D->qtd_elem++;

    }

}

void exibe_fila(No *ultimo, Descritor *D){

    printf("\n*********************************************\n");
    printf("\n\jFILA DE OCORRENCIAS POR ID: \j\n");
    printf("Quantidade de ocorrencias: %d", D->qtd_elem);

    No *aux = ultimo;

    while(aux != NULL){

        aux = ultimo;

        printf("[%d]->", aux->incidente->id);

        ultimo = ultimo->prox;

    }
    printf("NULL\n");
    printf("\n*********************************************\n");

}

void free_fila(No* ultimo){

    No *aux = ultimo;

    while(aux != NULL){

        aux = ultimo;

        ultimo = ultimo->prox;

        free(aux);

    }
}

int gera_tempo(){

    srand(time(NULL));
    return 20000 + (rand() % (200000 - 20000 + 1));

}

int gera_qtd_no(){

    srand(time(NULL));
    return 5 + (rand() % (20 - 5 + 1));

}

void enfileirando(){

    Descritor fila = cria_fila();

    int qtd_nos = gera_qtd_no();

    for(int i = 0; i < qtd_nos; i++){

        Sleep(gera_tempo());
        printf("\nNova ocorrencia chegando...\n");
        adiciona_fim_fila(cria_no(&fila), &fila);
        Sleep(gera_tempo());

    }

    exibe_fila(&fila, fila.ultimo);
    free_fila(fila.ultimo);

}
