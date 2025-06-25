#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha1.h"

/*
*---Função para inicializar a pilha de ocorrências --
* Recebe:
* Retorna: O novo início da lista (pode ser o mesmo ou o novo nó)
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
*---Função para adicionar uma ocorrência ---
* Recebe: Um ponteiro para a ocorrência e o ponteiro para o início da pilha
* Retorna: O novo início da pilha
*
*/
void push_pilha (Pilha *pilha, Ocorrencia *ocorrencia) {
    if (pilha == NULL) {
        printf("ERRO: Pilha não inicializada.\n");
        return;
    }
    NoPilha *novo_no = (NoPilha*) malloc(sizeof(NoPilha));
    confere_aloc(novo_no);

    novo_no->ocorrencia = ocorrencia; // Armazena o ponteiro para a ocorrência
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho++;
}

/*
*---Função para desempilhar uma ocorrência --
* Recebe: Um ponteiro para o início da lista de relatório
* Retorna: O novo início da pilha
*
*/
Ocorrencia* pop_pilha_relatorio(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL; // Pilha vazia ou não inicializada
    }
    NoPilha *no_removido = pilha->topo;
    Ocorrencia *ocorrencia = no_removido->ocorrencia; // Pega o ponteiro da ocorrência
    pilha->topo = no_removido->prox;
    free(no_removido); // Libera apenas o nó da pilha
    pilha->tamanho--;
    return ocorrencia; // Retorna o ponteiro da ocorrência
}

/*
*---Função para imprimir o relatório final da simulação--
* Recebe: O ponteiro para o início da lista de relatório
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
    int count = pilha->tamanho; // Começa a contagem do topo para baixo
    while (atual != NULL) {
        printf("\nOcorrencia #%d (ID: %d):\n", count--, atual->ocorrencia->id);
        exibir_ocorrencia_especifica(atual->ocorrencia); // Exibe a ocorrência apontada
        atual = atual->prox;
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Total de ocorrencias atendidas: %d\n", pilha->tamanho);
}

/*
*---Função para liberar a memória alocada--
* Recebe: O ponteiro para o início da lista de relatório
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
        // IMPORTANTE: Não libera atual->ocorrencia, pois o programa principal será responsável por isso
        free(atual); // Libera apenas o nó da pilha
        atual = proximo;
    }
    free(pilha); // Libera a estrutura descritora da pilha
}
