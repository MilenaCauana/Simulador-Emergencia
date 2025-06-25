#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha1.h"

/*
*---Fun��o para inicializar a pilha de ocorr�ncias --
* Recebe:
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
Pilha* cria_pilha() {
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    confere_aloc(pilha);
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

/*
*---Fun��o para adicionar uma ocorr�ncia ---
* Recebe: Um ponteiro para a ocorr�ncia e o ponteiro para o in�cio da pilha
* Retorna: O novo in�cio da pilha
*
*/
void push_pilha (Pilha *pilha, Ocorrencia *ocorrencia) {
    if (pilha == NULL) {
        printf("ERRO: Pilha n�o inicializada.\n");
        return;
    }
    NoPilha *novo_no = (NoPilha*) malloc(sizeof(NoPilha));
    confere_aloc(novo_no);

    novo_no->ocorrencia = ocorrencia; // Armazena o ponteiro para a ocorr�ncia
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho++;
}

/*
*---Fun��o para desempilhar uma ocorr�ncia --
* Recebe: Um ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da pilha
*
*/
Ocorrencia* pop_pilha_relatorio(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL; // Pilha vazia ou n�o inicializada
    }
    NoPilha *no_removido = pilha->topo;
    Ocorrencia *ocorrencia = no_removido->ocorrencia; // Pega o ponteiro da ocorr�ncia
    pilha->topo = no_removido->prox;
    free(no_removido); // Libera apenas o n� da pilha
    pilha->tamanho--;
    return ocorrencia; // Retorna o ponteiro da ocorr�ncia
}

/*
*---Fun��o para imprimir o relat�rio final da simula��o--
* Recebe: O ponteiro para o in�cio da lista de relat�rio
* Retorna: void
*
*/
void imprime_pilha(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Pilha de ocorrencias esta vazia.\n");
        return;
    }
    printf("\n---------- RELATORIO DE OCORRENCIAS ATENDIDAS (Pilha - Ultima -> Primeira) ----------\n");
    NoPilha *atual = pilha->topo;
    int count = pilha->tamanho; // Come�a a contagem do topo para baixo
    while (atual != NULL) {
        printf("\nOcorrencia #%d (ID: %d):\n", count--, atual->ocorrencia->id);
        exibir_ocorrencia_especifica(atual->ocorrencia); // Exibe a ocorr�ncia apontada
        atual = atual->prox;
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Total de ocorrencias atendidas: %d\n", pilha->tamanho);
}

/*
*---Fun��o para liberar a mem�ria alocada--
* Recebe: O ponteiro para o in�cio da lista de relat�rio
* Retorna: void
*
*/
void free_pilha_relatorio(Pilha
                           *pilha) {
    if (pilha == NULL) return;
    NoPilha *atual = pilha->topo;
    NoPilha *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        // IMPORTANTE: N�o libera atual->ocorrencia, pois o programa principal ser� respons�vel por isso
        free(atual); // Libera apenas o n� da pilha
        atual = proximo;
    }
    free(pilha); // Libera a estrutura descritora da pilha
}
