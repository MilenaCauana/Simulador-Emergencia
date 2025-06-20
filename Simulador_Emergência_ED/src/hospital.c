#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/hospital.h"
#include "../include/bairro.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

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
* Recebe: um ponteiro para a tabela hash e o hospital que será inserido
* Retorna: inteiro booleano para definir se deu certo a inserção
*
*/
int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital){
    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = hospital.id;
    int pos = hospital_chave_divisao(chave, ha -> tamanho);

    // Tentativa de tratamento de colisão simples (linear probing)
    int inicio_pos = pos;
    while (ha->itens[pos] != NULL) {
        if (ha->itens[pos]->id == hospital.id) {
            return 0;
        }
        pos = (pos + 1) % ha->tamanho; // Próxima posição
        if (pos == inicio_pos) {
            return 0;
        }
    }

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
* Recebe: um ponteiro para a tabela hash,  e o hospital que será buscado
* Retorna: inteiro booleano para definir se deu certo a busca, preenchendo o ponteiro 'hospital'
*
*/
int hospital_busca_hash_sem_colisao(Hospital_Hash* ha, int id, Hospital *hospital){
   if (ha == NULL){
    return 0;
   }

   int pos = hospital_chave_divisao(id, ha -> tamanho);
   int inicio_pos = pos;

   // Lógica de busca que reflete o linear probing da inserção
   while (ha->itens[pos] != NULL) {
       if (ha->itens[pos]->id == id) {
           *hospital = *(ha -> itens[pos]);
           return 1;
       }
       pos = (pos + 1) % ha->tamanho;
       if (pos == inicio_pos) {
           return 0;
       }
   }
   return 0;
}

/*
*---Função que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
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
*---Função que preenche as informações do hospital--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Hospital_Hash* preenche_hospital(){
    Hospital_Hash *ha = cria_hash_hospital(TAMANHO);
    if (ha == NULL) return NULL;

    // IDs de hospital mapeados para bairros:
    // Hospital 100195 -> Bairro 1001
    // Hospital 100295 -> Bairro 1002
    // ...
    // Hospital 100795 -> Bairro 1007

    Hospital hospital1;
    hospital1.id = 100195;
    hospital1.ambulancias = 2;
    hospital1.ambulancias_disp = 2;
    hospital_insere_hash_sem_colisao(ha, hospital1);

    Hospital hospital2;
    hospital2.id = 100295;
    hospital2.ambulancias = 1;
    hospital2.ambulancias_disp = 1;
    hospital_insere_hash_sem_colisao(ha, hospital2);

    Hospital hospital3;
    hospital3.id = 100395;
    hospital3.ambulancias = 3;
    hospital3.ambulancias_disp = 3;
    hospital_insere_hash_sem_colisao(ha, hospital3);

    Hospital hospital4;
    hospital4.id = 100495;
    hospital4.ambulancias = 2;
    hospital4.ambulancias_disp = 2;
    hospital_insere_hash_sem_colisao(ha, hospital4);

    Hospital hospital5;
    hospital5.id = 100595;
    hospital5.ambulancias = 2;
    hospital5.ambulancias_disp = 2;
    hospital_insere_hash_sem_colisao(ha, hospital5);

    Hospital hospital6;
    hospital6.id = 100695;
    hospital6.ambulancias = 1;
    hospital6.ambulancias_disp = 1;
    hospital_insere_hash_sem_colisao(ha, hospital6);

    Hospital hospital7;
    hospital7.id = 100795;
    hospital7.ambulancias = 2;
    hospital7.ambulancias_disp = 2;
    hospital_insere_hash_sem_colisao(ha, hospital7);

    return ha;
}
