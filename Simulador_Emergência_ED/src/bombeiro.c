#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/bombeiro.h"
#include "../include/bairro.h"

//Definindo o tamanho da tabela hash
#define TAMANHO 7

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
* Recebe: um ponteiro para a tabela hash e o bombeiro que ser� inserido
* Retorna: inteiro booleano para definir se deu certo a inser��o
*
*/
int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro){
    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    int chave = bombeiro.id;
    int pos = bombeiro_chave_divisao(chave, ha -> tamanho);

    // Tentativa de tratamento de colis�o simples (linear probing)
    int inicio_pos = pos;
    while (ha->itens[pos] != NULL) {
        if (ha->itens[pos]->id == bombeiro.id) {
            return 0;
        }
        pos = (pos + 1) % ha->tamanho;
        if (pos == inicio_pos) {
            return 0;
        }
    }

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
* Recebe: um ponteiro para a tabela hash,  e o bombeiro que ser� buscado
* Retorna: inteiro booleano para definir se deu certo a busca, preenchendo o ponteiro 'bombeiro'
*
*/
int bombeiro_busca_hash_sem_colisao(Bombeiro_Hash* ha, int id, Bombeiro *bombeiro){
   if (ha == NULL){
    return 0;
   }

   int pos = bombeiro_chave_divisao(id, ha -> tamanho);
   int inicio_pos = pos;

   // L�gica de busca que reflete o linear probing da inser��o
   while (ha->itens[pos] != NULL) {
       if (ha->itens[pos]->id == id) {
           *bombeiro = *(ha -> itens[pos]); // Copia os dados encontrados
           return 1; // Encontrado
       }
       pos = (pos + 1) % ha->tamanho;
       if (pos == inicio_pos) { // Loop completo, n�o encontrado
           return 0;
       }
   }
   return 0;
}

/*
*---Fun��o que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
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
*---Fun��o que preenche as informa��es do bombeiro--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Bombeiro_Hash* preenche_bombeiro(){
    Bombeiro_Hash *ha = cria_hash_bombeiro(TAMANHO);
    if (ha == NULL) return NULL;

    // IDs de bombeiro mapeados para bairros:
    // Bombeiro 100193 -> Bairro 1001
    // Bombeiro 100293 -> Bairro 1002
    // ...
    // Bombeiro 100793 -> Bairro 1007

    Bombeiro bombeiro1;
    bombeiro1.id = 100193;
    bombeiro1.caminhoes = 2;
    bombeiro1.caminhoes_disp = 2;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro1);

    Bombeiro bombeiro2;
    bombeiro2.id = 100293;
    bombeiro2.caminhoes = 1;
    bombeiro2.caminhoes_disp = 1;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro2);

    Bombeiro bombeiro3;
    bombeiro3.id = 100393;
    bombeiro3.caminhoes = 3;
    bombeiro3.caminhoes_disp = 3;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro3);

    Bombeiro bombeiro4;
    bombeiro4.id = 100493;
    bombeiro4.caminhoes = 2;
    bombeiro4.caminhoes_disp = 2;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro4);

    Bombeiro bombeiro5;
    bombeiro5.id = 100593;
    bombeiro5.caminhoes = 2;
    bombeiro5.caminhoes_disp = 2;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro5);

    Bombeiro bombeiro6;
    bombeiro6.id = 100693;
    bombeiro6.caminhoes = 1;
    bombeiro6.caminhoes_disp = 1;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro6);

    Bombeiro bombeiro7;
    bombeiro7.id = 100793;
    bombeiro7.caminhoes = 2;
    bombeiro7.caminhoes_disp = 2;
    bombeiro_insere_hash_sem_colisao(ha, bombeiro7);

    return ha;
}

// Fun��o para tentar alocar um caminh�o para uma ocorr�ncia.
// Retorna o ID da delegacia se bem-sucedido, 0 caso contr�rio.
int despacha_bombeiro(Bombeiro_Hash *ha, int id_bombeiro_ocorrencia) {
    if (ha == NULL) return 0;

    // L�gica para mapear ID do bairro para ID da pol�cia (ex: 1001 -> 100190)
    int id_bombeiro_local = ((id_bombeiro_ocorrencia / 1000) * 10000) + (id_bombeiro_ocorrencia % 1000) * 10 + 90;

    // 1. Tenta encontrar a pol�cia do bairro da ocorr�ncia
    for (int i = 0; i < ha -> tamanho; i++) {
        if (ha -> itens[i] != NULL && ha -> itens[i]->id == id_bombeiro_local) {
            if (ha->itens[i]->caminhoes_disp > 0) {
                ha->itens[i]->caminhoes_disp--;
                return ha->itens[i]->id;
            }
            break; // Encontrou a delegacia local, mas n�o tem viatura, n�o adianta procurar mais por ela
        }
    }

    // 2. Se n�o conseguiu no bairro local, procura em qualquer outro bairro
    for (int i = 0; i < ha->tamanho; i++) {
        if (ha->itens[i] != NULL && ha->itens[i]->caminhoes_disp > 0) {
            ha->itens[i]->caminhoes_disp--;
            return ha->itens[i]->id; // Retorna o ID da unidade que atendeu
        }
    }

    return 0; // Nenhuma viatura dispon�vel em nenhum lugar
}

// Fun��o para liberar uma viatura, devolvendo-a para sua delegacia.
void liberar_bombeiro(Bombeiro_Hash *ha, int id_unidade_bombeiro) {
    if (ha == NULL || id_unidade_bombeiro == 0) return;

    for (int i = 0; i < ha->tamanho; i++) {
        if (ha->itens[i] != NULL && ha->itens[i]->id == id_unidade_bombeiro) {
            if (ha->itens[i]->caminhoes_disp < ha->itens[i]->caminhoes) {
                ha->itens[i]->caminhoes_disp++;
            }
            return;
        }
    }
}
