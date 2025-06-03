#include <stdio.h>
#include <stdlib.h>
#include "../include/bairro.h"

//Definindo alguns tamanhos
#define NOME 30
#define TAMANHO 11


//---------- DEFININDO ESTRUTURAS --------
struct Bairros_da_cidade{

    char nome[NOME];
    int id;

};

struct bairros_hash{

    int qtd, tamanho;//qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Bairros **itens;

};

//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES PRIVADAS---

/*
*---Fun��o de cria��o de  primeira posi��o de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posi��o
*
*/
int bairro_chave_divisao(int chave, int tamanho){

    return(chave & 0x7FFFFFFF) % tamanho;

}

//---FUN��ES P�BLICAS---

/*
*---Fun��o de cria��o da tabela--
* Recebe: um tamanho
* Retorna: Um ponteiro para a tabela
*
*/
Bairros_Hash* cria_hash_bairros(int tamanho){

    Bairros_Hash* ha = (Bairros_Hash*) malloc(sizeof(Bairros_Hash));

    if(ha != NULL){

        int i;
        ha -> tamanho = tamanho;

        ha -> itens = (Bairros**) malloc(tamanho * sizeof(Bairros*));

        if(ha -> itens == NULL){

            free(ha);
            return NULL;

        }

        ha -> qtd = 0;

        for(int i=0; i < ha -> tamanho; i++){

            ha -> itens[i] = NULL;

        }
    }

    return ha;

}

/*
*---Fun��o de libera��o da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
*/
void bairro_libera_hash(Bairros_Hash *ha){

    if (ha != NULL){
        int i;

        for (i = 0; i < ha -> tamanho; i++){
            if (ha -> itens[i] != NULL){
                free (ha -> itens[i]);
            }
        }

        free(ha -> itens);
        free (ha);
    }

}

/*
*---Fun��o de inser��o da tabela--
* Recebe: um ponteiro para a tabela hash e a policia que ser� inserida
* Retorna: inteiro booleano para definir se deu certo a inser��o
*
*/
int bairro_insere_hash_sem_colisao(Bairros_Hash *ha, Bairros bairro){

    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = bairro.id;
    int pos = bairro_chave_divisao(chave, ha -> tamanho);

    Bairros *novo;
    novo = (Bairros *) malloc(sizeof(Bairros));

    if (novo == NULL){
        return 0;
    }

    *novo = bairro;
    ha -> itens[pos] = novo;
    ha -> qtd ++;

    return 1;
}

/*
*---Fun��o de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e o bairro que ser� buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como par�metro um ponteiro do tipo bairro, o qual ser� atribuido as informa��es
*
*/
int bairro_busca_hash_sem_colisao(Bairros_Hash* ha, int id, Bairros *bairro){

   if (ha == NULL){
    return 0;
   }

   int pos = bairro_chave_divisao(id, ha -> tamanho);

   if (ha -> itens[pos] == NULL){
    return 0;
   }

   *bairro = *(ha -> itens[pos]);
   return 1;
}

/*
*---Fun��o que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
*  "Esvaziar" a tabela hash sem destru�-la completamente.
*
*/
void limpa_hash_bairros(Bairros_Hash *ha){

    if(ha == NULL){

        return;

    }

    for(int i=0; i < ha->tamanho; i++){

        if(ha->itens[i] != NULL){

            free(ha->itens[i]);
            ha->itens[i] = NULL;

        }

    }

    ha->qtd = 0;

}

/*
*---Fun��o que preenche as informa��es do bairro--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Bairros_Hash* preenche_bairros(){

    Bairros_Hash *ha = cria_hash_bairros(TAMANHO);

    Bairros bairro1;
    strcpy (bairro1.nome, "Jardim das Anas");
    bairro1.id = 1001;
    bairro_insere_hash_sem_colisao(ha, bairro1);

    Bairros bairro2;
    strcpy (bairro2.nome, "Vila S�o Pedroso");
    bairro2.id = 1002;
    bairro_insere_hash_sem_colisao(ha, bairro2);

    Bairros bairro3;
    strcpy (bairro3.nome, "Gugaruj�");
    bairro3.id = 1003;
    bairro_insere_hash_sem_colisao(ha, bairro3);

    Bairros bairro4;
    strcpy (bairro4.nome, "Igornema");
    bairro4.id = 1004;
    bairro_insere_hash_sem_colisao(ha, bairro4);

    Bairros bairro5;
    strcpy (bairro5.nome, "Miicca");
    bairro5.id = 1005;
    bairro_insere_hash_sem_colisao(ha, bairro5);

    Bairros bairro6;
    strcpy (bairro6.nome, "Nova Olyans");
    bairro6.id = 1006;
    bairro_insere_hash_sem_colisao(ha, bairro6);

    Bairros bairro7;
    strcpy (bairro7.nome, "Fenda dos Parafusos");
    bairro7.id = 1007;
    bairro_insere_hash_sem_colisao(ha, bairro7);

    Bairros bairro8;
    strcpy (bairro8.nome, "Ciriacabana");
    bairro8.id = 1008;
    bairro_insere_hash_sem_colisao(ha, bairro8);

    Bairros bairro9;
    strcpy (bairro9.nome, "Vila Santa Caroline");
    bairro9.id = 1009;
    bairro_insere_hash_sem_colisao(ha, bairro9);

    return ha;
}
