#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../include/policia.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//---------- DEFININDO ESTRUTURAS --------

//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES PRIVADAS---

/*
*---Fun��o de cria��o de posi��o de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posi��o
*
*/
int policia_chave_divisao(int chave, int tamanho){
    return(chave & 0x7FFFFFFF) % tamanho;
}

//---FUN��ES P�BLICAS---

/*
*---Fun��o de cria��o da tabela--
* Recebe: inteiro -> o tamanho da tabela
* Retorna: Um ponteiro para a tabela
*
*/
Policia_Hash *cria_hash_policia(int tamanho){
    Policia_Hash *ha = (Policia_Hash *) malloc(sizeof(Policia_Hash));

    if (ha != NULL){
        int i;
        ha -> tamanho = tamanho;

        ha -> itens = (Policia **)malloc(tamanho * sizeof(Policia *));

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
void policia_libera_hash(Policia_Hash *ha){

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
int policia_insere_hash_sem_colisao(Policia_Hash *ha, Policia policia){

    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = policia.id;
    int pos = policia_chave_divisao(chave, ha -> tamanho);

    Policia *novo;
    novo = (Policia *) malloc(sizeof(Policia));

    if (novo == NULL){
        return 0;
    }

    *novo = policia;
    ha -> itens[pos] = novo;
    ha -> qtd ++;

    return 1;
}

/*
*---Fun��o de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e a policia que ser� buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como par�metro um ponteiro do tipo poliicia, o qual ser� atribuido as informa��es
*
*/
int policia_busca_hash_sem_colisao(Policia_Hash* ha, int id, Policia *policia){

   if (ha == NULL){
    return 0;
   }

   int pos = policia_chave_divisao(id, ha -> tamanho);

   if (ha -> itens[pos] == NULL){
    return 0;
   }

   *policia = *(ha -> itens[pos]);
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
void limpa_hash_policia(Policia_Hash *ha){

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
Policia_Hash* preenche_policia(){

    Policia_Hash *ha = cria_hash_policia(TAMANHO);

    Policia policia1;
    policia1.id = 100190;
    policia1.viaturas = 3;
    policia1.viaturas_disp = 3;
    policia1.disponivel = true;
    policia_insere_hash_sem_colisao(ha, policia1);

    Policia policia2;
    policia2.id = 100590;
    policia2.viaturas = 2;
    policia2.viaturas_disp = 2;
    policia2.disponivel = true;
    policia_insere_hash_sem_colisao(ha, policia2);

    Policia policia3;
    policia3.id = 100790;
    policia3.viaturas = 4;
    policia3.viaturas_disp = 4;
    policia3.disponivel = true;
    policia_insere_hash_sem_colisao(ha, policia3);

    return ha;
}
