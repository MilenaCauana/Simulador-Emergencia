#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "ocorrencias.h"

//---------- DEFININDO ESTRUTURAS --------

/*
*---Estrutura de um nó da pilha para o relatório--
* Contém um ponteiro para uma Ocorrencia e um ponteiro para o próximo nó.
*
*/
typedef struct NoDaPilha{
    Ocorrencia *ocorrencia; // ponteiro para a ocorrência
    struct NoDaPilha *prox;
} NoPilha;

/*
*---Estrutura do descritor da pilha de relatório--
* Contém ponteiros para o topo da pilha e o tamanho atual.
*
*/
typedef struct Pilha {
    NoPilha *topo;
    int tamanho;
} Pilha;

// ------- FUNÇÕES --------

/*
*---Função para inicializar a pilha de ocorrências --
* Recebe: void
* Retorna: Um ponteiro para o descritor da pilha de relatório
*
*/
Pilha* cria_pilha();

/*
*---Função para adicionar uma ocorrência atendida ao relatório (pilha)--
* Recebe: Um ponteiro para o descritor da pilha de relatório e um ponteiro para a ocorrência atendida
* Retorna: void
*
*/
void push_pilha(Pilha *pilha, Ocorrencia *ocorrencia);

/*
*---Função para remover uma ocorrência do topo da pilha de relatório--
* Recebe: Um ponteiro para o descritor da pilha de relatório
* Retorna: Um ponteiro para a ocorrência removida, ou NULL se a pilha estiver vazia
*
*/
Ocorrencia* pop_pilha(Pilha *pilha);

/*
*---Função para imprimir o relatório final da simulação (pilha)--
* Recebe: O ponteiro para o descritor da pilha de relatório
* Retorna: void
*
*/
void imprime_pilha(Pilha *pilha);

/*
*---Função para liberar a memória alocada para o relatório (pilha)--
* Recebe: O ponteiro para o descritor da pilha de relatório
* Retorna: void
*
*/
void free_pilha(Pilha *pilha);


#endif // PILHA_H_INCLUDED
