#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../include/hospital.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//---------- DEFININDO ESTRUTURAS --------
struct hospital{

    //char nome[40]; Ainda não definimos se terá nome
    int id;
    int ambulancias; //Total de ambulancias no hospital
    int ambulancias_disp; //Quantidade de ambulancias disponíveis no momento para atendimento
    bool disponivel; //Se não houver ambulancia disponível, então o hospital X nao esta disponível
};

struct hospital_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Hospital **itens;
};

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PRIVADAS---

/*
*---Função de criação de posição de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posição
*
*/
int hospital_chave_divisao(int chave, int tamanho){
    return(chave & 0x7FFFFFFF) % tamanho;
}

//---FUNÇÕES PÚBLICAS---

/*
*---Função de criação da tabela--
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
*---Função de liberação da tabela--
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
*---Função de inserção da tabela--
* Recebe: um ponteiro para a tabela hash e a Hospital que será inserida
* Retorna: inteiro booleano para definir se deu certo a inserção
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
*---Função de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e a Hospital que será buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como parâmetro um ponteiro do tipo poliicia, o qual será atribuido as informações
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
*---Função que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
*  "Esvaziar" a tabela hash sem destruí-la completamente.
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
*---Função que preenche as informações do bairro--
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
