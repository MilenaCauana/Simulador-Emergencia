
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../include/bombeiro.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//---------- DEFININDO ESTRUTURAS --------
struct bombeiro{

    //char nome[40]; Ainda n�o definimos se ter� nome
    int id;
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes dispon�veis no momento para atendimento
    bool disponivel; //Se n�o houver ambulancia dispon�vel, ent�o o bombeiro X nao esta dispon�vel
};

struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
};

//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES PRIVADAS---

/*
*---Fun��o de cria��o de posi��o de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posi��o
*
*/
int bombeiro_chave_divisao(int chave, int tamanho){
    return(chave & 0x7FFFFFFF) % tamanho;
}

//---FUN��ES P�BLICAS---

/*
*---Fun��o de cria��o da tabela--
* Recebe: inteiro -> o tamanho da tabela
* Retorna: Um ponteiro para a tabela
*
*/
Bombeiro_Hash *cria_hash_bombeiro(int tamanho){
    Bombeiro_Hash *ha = (Bombeiro_Hash *) malloc(sizeof(Bombeiro_Hash));

    if (ha != NULL){
        int i;
        ha -> tamanho = tamanho;

        ha -> itens = (Bombeiro **)malloc(tamanho * sizeof(Bombeiro *));

        if (ha -> itens == NULL){
            free(ha);
            return NULL;
        }

        ha -> qtd = 0;

        for(int i = 0; i < ha -> tamanho; i++){

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
void bombeiro_libera_hash(Bombeiro_Hash *ha){

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
* Recebe: um ponteiro para a tabela hash e a bombeiro que ser� inserida
* Retorna: inteiro booleano para definir se deu certo a inser��o
*
*/
int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro){

    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = bombeiro.id;
    int pos = bombeiro_chave_divisao(chave, ha -> tamanho);

    Bombeiro *novo;
    novo = (Bombeiro *) malloc(sizeof(Bombeiro));

    if (novo == NULL){
        return 0;
    }

    *novo = bombeiro;
    ha -> itens[pos] = novo;
    ha -> qtd ++;

    return 1;
}

/*
*---Fun��o de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e a bombeiro que ser� buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como par�metro um ponteiro do tipo poliicia, o qual ser� atribuido as informa��es
*
*/
int bombeiro_busca_hash_sem_colisao(Bombeiro_Hash* ha, int id, Bombeiro *bombeiro){

   if (ha == NULL){
    return 0;
   }

   int pos = bombeiro_chave_divisao(id, ha -> tamanho);

   if (ha -> itens[pos] == NULL){
    return 0;
   }

   *bombeiro = *(ha -> itens[pos]);
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
void limpa_hash_bombeiro(Bombeiro_Hash *ha){

    if(ha == NULL){

        return;

    }

    for(int i = 0; i < ha -> tamanho; i++){

        if(ha -> itens[i] != NULL){

            free(ha -> itens[i]);
            ha -> itens[i] = NULL;

        }

    }

    ha -> qtd = 0;

}

/*
*---Fun��o que preenche as informa��es do bairro--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Bombeiro_Hash* preenche_bombeiro(){

    Bombeiro_Hash *ha = cria_hash_bombeiro(TAMANHO);

    Bombeiro bombeiro1;
    bombeiro1.id = 100993;
    bombeiro1.caminhoes = 4;
    bombeiro1.caminhoes_disp= 4;
    bombeiro1.disponivel = true;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro1);

    Bombeiro bombeiro2;
    bombeiro2.id = 100793;
    bombeiro2.caminhoes = 5;
    bombeiro2.caminhoes_disp = 5;
    bombeiro2.disponivel = true;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro2);

    return ha;
}
