#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/policia.h"
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

    // Tentativa de tratamento de colis�o simples (linear probing)
    // Isso � uma altera��o importante para garantir que a inser��o funcione mesmo com colis�es
    // A busca tamb�m precisar� refletir essa l�gica
    int inicio_pos = pos;
    while (ha->itens[pos] != NULL) {
        if (ha->itens[pos]->id == policia.id) {
            return 0;
        }
        pos = (pos + 1) % ha->tamanho;
        if (pos == inicio_pos) {
            return 0;
        }
    }

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
* Retorna: inteiro booleano para definir se deu certo a busca, preenchendo o ponteiro 'policia'
*
* Para receber a policia, mandar como par�metro um ponteiro do tipo policia, o qual ser� atribuido as informa��es
*
*/
Policia* policia_busca_hash(Policia_Hash* ha, int id){
    if (ha == NULL){
       return NULL;
   }

   int pos = policia_chave_divisao(id, ha -> tamanho);
   int inicio_pos = pos;

   // L�gica de busca que reflete o linear probing da inser��o
   while (ha->itens[pos] != NULL) {
       if (ha->itens[pos]->id == id) {
           return ha->itens[pos]; // Retorna o ponteiro para a Policia encontrada na hash
       }
       pos = (pos + 1) % ha->tamanho;
       if (pos == inicio_pos) {
           return NULL; // Percorreu a tabela sem encontrar
       }
   }
   return NULL; // N�o encontrado
}

/*
*---Fun��o que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
* "Esvaziar" a tabela hash sem destru�-la completamente.
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
*---Fun��o que preenche as informa��es da pol�cia--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Policia_Hash* preenche_policia(){
    Policia_Hash *ha = cria_hash_policia(TAMANHO);
    if (ha == NULL) return NULL;

    // IDs de pol�cia mapeados para bairros:
    // Policia 100190 -> Bairro 1001
    // Policia 100290 -> Bairro 1002
    // ...
    // Policia 100790 -> Bairro 1007

    Policia policia1;
    policia1.id = 100190;
    policia1.viaturas = 3;
    policia1.viaturas_disp = 3;
    policia_insere_hash_sem_colisao(ha, policia1);

    Policia policia2;
    policia2.id = 100290;
    policia2.viaturas = 2;
    policia2.viaturas_disp = 2;
    policia_insere_hash_sem_colisao(ha, policia2);

    Policia policia3;
    policia3.id = 100390;
    policia3.viaturas = 4;
    policia3.viaturas_disp = 4;
    policia_insere_hash_sem_colisao(ha, policia3);

    Policia policia4;
    policia4.id = 100490;
    policia4.viaturas = 2;
    policia4.viaturas_disp = 2;
    policia_insere_hash_sem_colisao(ha, policia4);

    Policia policia5;
    policia5.id = 100590;
    policia5.viaturas = 3;
    policia5.viaturas_disp = 3;
    policia_insere_hash_sem_colisao(ha, policia5);

    Policia policia6;
    policia6.id = 100690;
    policia6.viaturas = 2;
    policia6.viaturas_disp = 2;
    policia_insere_hash_sem_colisao(ha, policia6);

    Policia policia7;
    policia7.id = 100790;
    policia7.viaturas = 3;
    policia7.viaturas_disp = 3;
    policia_insere_hash_sem_colisao(ha, policia7);

    return ha;
}

// Fun��o para tentar alocar uma viatura para uma ocorr�ncia.
// Retorna o ID da delegacia se bem-sucedido, 0 caso contr�rio.
int despacha_policia(Policia_Hash *ha, int id_bairro_ocorrencia) {
    if (ha == NULL) return 0;

    // L�gica para mapear ID do bairro para ID da pol�cia (ex: 1001 -> 100190)
    int id_policia_local = ((id_bairro_ocorrencia / 1000) * 10000) + (id_bairro_ocorrencia % 1000) * 10 + 90;

    // 1. Tenta encontrar a pol�cia do bairro da ocorr�ncia
    for (int i = 0; i < ha->tamanho; i++) {
        if (ha->itens[i] != NULL && ha->itens[i]->id == id_policia_local) {
            if (ha->itens[i]->viaturas_disp > 0) {
                ha->itens[i]->viaturas_disp--;
                return ha->itens[i]->id;
            }
            break; // Encontrou a delegacia local, mas n�o tem viatura, n�o adianta procurar mais por ela
        }
    }

    // 2. Se n�o conseguiu no bairro local, procura em qualquer outro bairro
    for (int i = 0; i < ha->tamanho; i++) {
        if (ha->itens[i] != NULL && ha->itens[i]->viaturas_disp > 0) {
            ha->itens[i]->viaturas_disp--;
            return ha->itens[i]->id; // Retorna o ID da unidade que atendeu
        }
    }

    return 0; // Nenhuma viatura dispon�vel em nenhum lugar
}

// Fun��o para liberar uma viatura, devolvendo-a para sua delegacia.
void liberar_policia(Policia_Hash *ha, int id_unidade_policial) {
    if (ha == NULL || id_unidade_policial == 0) return;

    for (int i = 0; i < ha->tamanho; i++) {
        if (ha->itens[i] != NULL && ha->itens[i]->id == id_unidade_policial) {
            if (ha->itens[i]->viaturas_disp < ha->itens[i]->viaturas) {
                ha->itens[i]->viaturas_disp++;
            }
            return;
        }
    }
}
