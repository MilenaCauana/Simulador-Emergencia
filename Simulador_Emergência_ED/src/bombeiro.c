
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../include/bombeiro.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//---------- DEFININDO ESTRUTURAS --------
struct bombeiro{

    //char nome[40]; Ainda não definimos se terá nome
    int id;
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes disponíveis no momento para atendimento
    bool disponivel; //Se não houver ambulancia disponível, então o bombeiro X nao esta disponível
};

struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
};

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PRIVADAS---

/*
*---Função de criação de posição de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posição
*
*/
int bombeiro_chave_divisao(int chave, int tamanho){
    return(chave & 0x7FFFFFFF) % tamanho;
}

//---FUNÇÕES PÚBLICAS---

/*
*---Função de criação da tabela--
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
*---Função de liberação da tabela--
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
*---Função de inserção da tabela--
* Recebe: um ponteiro para a tabela hash e a bombeiro que será inserida
* Retorna: inteiro booleano para definir se deu certo a inserção
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
*---Função de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e a bombeiro que será buscada
* Retorna: inteiro booleano para definir se deu certo a busca
*
* Para receber o aluno, mandar como parâmetro um ponteiro do tipo poliicia, o qual será atribuido as informações
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
*---Função que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
*  "Esvaziar" a tabela hash sem destruí-la completamente.
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
*---Função que preenche as informações do bairro--
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
