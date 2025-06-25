#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "ocorrencias.h"

//---------- DEFININDO ESTRUTURAS --------

/*
*---Estrutura de um n� da pilha para o relat�rio--
* Cont�m um ponteiro para uma Ocorrencia e um ponteiro para o pr�ximo n�.
*
*/
typedef struct NoDaPilha{
    Ocorrencia *ocorrencia; // ponteiro para a ocorr�ncia
    struct NoDaPilha *prox;
} NoPilha;

/*
*---Estrutura do descritor da pilha de relat�rio--
* Cont�m ponteiros para o topo da pilha e o tamanho atual.
*
*/
typedef struct Pilha {
    NoPilha *topo;
    int tamanho;
} Pilha;

// ------- FUN��ES --------

/*
*---Fun��o para inicializar a pilha de ocorr�ncias --
* Recebe: void
* Retorna: Um ponteiro para o descritor da pilha de relat�rio
*
*/
Pilha* cria_pilha();

/*
*---Fun��o para adicionar uma ocorr�ncia atendida ao relat�rio (pilha)--
* Recebe: Um ponteiro para o descritor da pilha de relat�rio e um ponteiro para a ocorr�ncia atendida
* Retorna: void
*
*/
void push_pilha(Pilha *pilha, Ocorrencia *ocorrencia);

/*
*---Fun��o para remover uma ocorr�ncia do topo da pilha de relat�rio--
* Recebe: Um ponteiro para o descritor da pilha de relat�rio
* Retorna: Um ponteiro para a ocorr�ncia removida, ou NULL se a pilha estiver vazia
*
*/
Ocorrencia* pop_pilha(Pilha *pilha);

/*
*---Fun��o para imprimir o relat�rio final da simula��o (pilha)--
* Recebe: O ponteiro para o descritor da pilha de relat�rio
* Retorna: void
*
*/
void imprime_pilha(Pilha *pilha);

/*
*---Fun��o para liberar a mem�ria alocada para o relat�rio (pilha)--
* Recebe: O ponteiro para o descritor da pilha de relat�rio
* Retorna: void
*
*/
void free_pilha(Pilha *pilha);


#endif // PILHA_H_INCLUDED
