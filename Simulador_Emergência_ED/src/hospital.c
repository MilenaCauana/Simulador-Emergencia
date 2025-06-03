#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../include/hospital.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//---------- DEFININDO ESTRUTURAS --------
struct hospital{

    //char nome[40]; Ainda n�o definimos se ter� nome
    int id;
    int ambulancias; //Total de ambulancias no hospital
    int ambulancias_disp; //Quantidade de ambulancias dispon�veis no momento para atendimento
    bool disponivel; //Se n�o houver ambulancia dispon�vel, ent�o o hospital X nao esta dispon�vel
};

struct hospital_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Hospital **itens;
};

//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES PRIVADAS---

/*
*---Fun��o de cria��o de posi��o de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posi��o
*
*/
int hospital_chave_divisao(int chave, int tamanho){
    return(chave & 0x7FFFFFFF) % tamanho;
}

//---FUN��ES P�BLICAS---

/*
*---Fun��o de cria��o da tabela--
* Recebe: inteiro -> o tamanho da tabela
* Retorna: Um ponteiro para a tabela
*
*/
Hospital_Hash *cria_hash_hospital(int tamanho){
    Hospital_Hash *ha = (Hospital_Hash *) malloc(sizeof(Hospital_Hash));

    if (ha != NULL){
        int i;
        ha -> tamanho = tamanho;

        ha -> itens = (Hospital **)malloc(tamanho * sizeof(Hospital *));

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
void hospital_libera_hash(Hospital_Hash *ha){

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
* Recebe: um ponteiro para a tabela hash e a Hospital que ser� inserida
* Retorna: inteiro booleano para definir se deu certo a inser��o
*
*/
int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital){

    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = hospital.id;
    int pos = hospital_chave_divisao(chave, ha -> tamanho);

    Hospital *novo;
    novo = (Hospital *) malloc(sizeof(Hospital));

    if (novo == NULL){
        return 0;
    }

    *novo = hospital;
    ha -> itens[pos] = novo;
    ha -> qtd ++;

    return 1;
}

/*
*---Fun��o de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e a Hospital que ser� buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como par�metro um ponteiro do tipo poliicia, o qual ser� atribuido as informa��es
*
*/
int hospital_busca_hash_sem_colisao(Hospital_Hash* ha, int id, Hospital *hospital){

   if (ha == NULL){
    return 0;
   }

   int pos = hospital_chave_divisao(id, ha -> tamanho);

   if (ha -> itens[pos] == NULL){
    return 0;
   }

   *hospital = *(ha -> itens[pos]);
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
void limpa_hash_hospital(Hospital_Hash *ha){

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
Hospital_Hash* preenche_hospital(){

    Hospital_Hash *ha = cria_hash_hospital(TAMANHO);

    Hospital hospital1;
    hospital1.id = 100392;
    hospital1.ambulancias = 4;
    hospital1.ambulancias_disp= 4;
    hospital1.disponivel = true;
    hospital_insere_hash_sem_colisao(ha, hospital1);

    Hospital hospital2;
    hospital2.id = 100592;
    hospital2.ambulancias = 5;
    hospital2.ambulancias_disp = 5;
    hospital2.disponivel = true;
    hospital_insere_hash_sem_colisao(ha, hospital2);

    return ha;
}
