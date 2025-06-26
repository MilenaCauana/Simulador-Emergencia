#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../include/fila_de_ocorrencias.h"
#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"

//------ �� FUN��ES �� ------

/*
*---Fun��o de cria��o e inicializa��o da fila--
* Recebe: void
* Retorna: Um ponteiro para um descritor da fila
*
*/
Descritor* cria_fila(){
    Descritor *D = (Descritor*) malloc(sizeof(Descritor));
    confere_aloc(D);
    D->inicio = NULL;
    D->fim = NULL;
    D->tamanho = 0;
    return D;
}

/*
*---Fun��o para verificar aloca��o de mem�ria--
* Recebe: Um ponteiro gen�rico
* Retorna: void (encerra o programa se a aloca��o falhar)
*
*/
void confere_aloc(void *ptr){
    if (ptr == NULL){
        printf("ERRO DE ALOCACAO DE MEMORIA!\n");
        exit(1); // Encerra o programa
    }
}

/*
*---Fun��o para criar um novo n� da fila com uma ocorr�ncia--
* Recebe: Um ponteiro para a tabela hash de bairros e de moradores (para criar a ocorr�ncia)
* Retorna: Um ponteiro para o n� rec�m-criado
*
*/
No* cria_no(Bairros_Hash *ha, Morador_Hash *hash_morador){
    No* novo = (No*) malloc(sizeof(No));
    confere_aloc(novo);
    int x = 0;
    novo->ocorrencia = cria_ocorrencia(ha, hash_morador, x); // Cria a ocorr�ncia
    confere_aloc(novo->ocorrencia); // Confere se a ocorr�ncia foi criada
    novo->prox = NULL;
    return novo;
}

/*
*---Fun��o para adicionar uma ocorr�ncia na fila de prioridade--
* A inser��o mant�m a fila ordenada por prioridade (maior prioridade primeiro).
* Recebe: Um ponteiro para o n� a ser adicionado e um ponteiro para o descritor da fila
* Retorna: void
*
*/
void adiciona_na_fila_prioridade(No* novo, Descritor *D){
    if (D->inicio == NULL || novo->ocorrencia->prioridade > D->inicio->ocorrencia->prioridade) {
        // Se a fila estiver vazia ou o novo n� tiver maior prioridade que o primeiro
        novo->prox = D->inicio;
        D->inicio = novo;
    } else {
        No* atual = D->inicio;
        // Percorre a fila para encontrar a posi��o correta
        while (atual->prox != NULL && novo->ocorrencia->prioridade <= atual->prox->ocorrencia->prioridade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    // Se a fila estava vazia, o novo n� tamb�m � o fim
    if (D->fim == NULL) {
        D->fim = novo;
    } else if (novo->prox == NULL) { // Atualiza o fim se o novo n� foi adicionado ao final
        D->fim = novo;
    }
    D->tamanho++;
}

/*
*---Fun��o para remover uma ocorr�ncia do in�cio da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: Um ponteiro para a ocorr�ncia removida, ou NULL se a fila estiver vazia
*
*/
Ocorrencia* remove_da_fila(Descritor *D){
    if (D->inicio == NULL){
        return NULL; // Fila vazia
    }
    No* no_removido = D->inicio;
    Ocorrencia* ocorrencia_removida = no_removido->ocorrencia;
    D->inicio = D->inicio->prox;
    if (D->inicio == NULL){ // Se a fila ficou vazia
        D->fim = NULL;
    }
    free(no_removido); // Libera o n�, mas n�o a ocorr�ncia
    D->tamanho--;
    return ocorrencia_removida;
}

/*
*---Fun��o para exibir as informa��es de uma ocorr�ncia--
* (Esta fun��o agora chama exibir_ocorrencia_especifica de ocorrencias.c)
* Recebe: Um ponteiro para a ocorr�ncia
* Retorna: void
*
*/
void exibe_ocorrencia(Ocorrencia *ocorrencia){
    exibir_ocorrencia_especifica(ocorrencia);
}

/*
*---Fun��o para exibir todos os itens da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void exibe_fila(Descritor *D){
    if (D->inicio == NULL){
        printf("Fila de ocorrencias esta vazia.\n");
        return;
    }
    printf("\n--- Conteudo da Fila de Ocorrencias (Prioridade Decrescente) ---\n");
    No* atual = D->inicio;
    while (atual != NULL){
        printf("ID: %d | Tipo: %s | Prioridade: %d | Bairro: %s | Morador: %s\n",
               atual->ocorrencia->id,
               atual->ocorrencia->tipo,
               atual->ocorrencia->prioridade,
               (atual->ocorrencia->bairro != NULL) ? atual->ocorrencia->bairro->nome : "N/A",
               (atual->ocorrencia->morador != NULL) ? atual->ocorrencia->morador->nome : "N/A");
        atual = atual->prox;
    }
    printf("Tamanho da fila: %d\n", D->tamanho);
    printf("------------------------------------------------------------------\n");
}

/*
*---Fun��o para liberar a mem�ria da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void free_fila(Descritor* D){
    if (D == NULL) return;
    No *atual = D->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        // Nao libera atual->ocorrencia, pois ela e liberada em main.c
        // ou copiada para o relatorio/historico do morador.
        free(atual);
        atual = proximo;
    }
    free(D);
}

/*
*---Fun��o para gerar um tempo aleat�rio (simula��o de espera)--
* Recebe: void
* Retorna: inteiro (tempo em segundos)
*
*/
int gera_tempo(){
    return 1 + rand() % 5; // Tempo entre 1 e 5 segundos
}

/*
*---Fun��o para gerar uma quantidade aleat�ria de n�s (ocorr�ncias)--
* Recebe: void
* Retorna: inteiro (quantidade de ocorr�ncias)
*
*/
int gera_qtd_no(){
    return 1 + rand() % 3; // Gera entre 1 e 3 novas ocorr�ncias por ciclo
}

/*
*---Fun��o para simular o enfileiramento de ocorr�ncias--
* Recebe: Um ponteiro para o descritor da fila e a tabela hash de bairros e moradores
* Retorna: void
*
*/
void enfileirando(Descritor *D, Bairros_Hash *ha, Morador_Hash *hash_morador){
    int x = 0;
    for (int i = 0; i < x; i++){
        No* novo_no = cria_no(ha, hash_morador); // Passa hash_morador
        if (novo_no != NULL) {
             // O tempo de registro � o ciclo atual da simula��o (ser� definido em main.c)
             novo_no->ocorrencia->ciclo_registro = D->tamanho + 1; // Tempor�rio, ajustado em main.c
             adiciona_na_fila_prioridade(novo_no, D);
             printf("  - Ocorrencia ID %d (Prioridade %d) adicionada.\n", novo_no->ocorrencia->id, novo_no->ocorrencia->prioridade);
        }
    }
}

/*---Fun��o para liberar a pilha --
* Recebe: Um ponteiro para a ocorr�ncia atendida e o ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
void free_ocorrencia(Ocorrencia *ocorr) {
    if (ocorr == NULL) return;
    free(ocorr->tipo); // Assuming 'tipo' is dynamically allocated
    // Free other dynamically allocated members if any
    free(ocorr);
}

