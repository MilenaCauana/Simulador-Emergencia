// fila_de_ocorrencia.h
#ifndef FILA_DE_OCORRENCIAS_H_INCLUDED
#define FILA_DE_OCORRENCIAS_H_INCLUDED

#include <stdbool.h> // Para usar o tipo bool
#include "ocorrencias.h" // Inclui a defini��o de Ocorrencia
#include "policia.h"
#include "bombeiro.h"
#include "hospital.h"
#include "bairro.h"
#include "morador.h" // Inclui a defini��o de Morador_Hash
#include "../include/pilha1.h"

//---------- DEFININDO ESTRUTURAS --------

/*
*---Estrutura de um n� da fila--
* Cont�m um ponteiro para uma Ocorrencia e um ponteiro para o pr�ximo n�.
*
*/
typedef struct no {
    Ocorrencia *ocorrencia;
    struct no *prox;
}No;

/*
*---Estrutura do descritor da fila--
* Cont�m ponteiros para o in�cio e fim da fila, e o tamanho atual.
*
*/
typedef struct descritor_fila {
    No *inicio;
    No *fim;
    int tamanho;
}Descritor;

//------ �� PROT�TIPOS DAS FUN��ES �� ------

/*
*---Fun��o de cria��o e inicializa��o da fila--
* Recebe: void
* Retorna: Um ponteiro para um descritor da fila
*
*/
Descritor* cria_fila();

/*
*---Fun��o para verificar aloca��o de mem�ria--
* Recebe: Um ponteiro gen�rico
* Retorna: void (encerra o programa se a aloca��o falhar)
*
*/
void confere_aloc(void *ptr);

/*
*---Fun��o para criar um novo n� da fila com uma ocorr�ncia--
* Recebe: Um ponteiro para a tabela hash de bairros e de moradores (para criar a ocorr�ncia)
* Retorna: Um ponteiro para o n� rec�m-criado
*
*/
No* cria_no(Bairros_Hash *ha, Morador_Hash *hash_morador);

/*
*---Fun��o para adicionar uma ocorr�ncia na fila de prioridade--
* A inser��o mant�m a fila ordenada por prioridade (maior prioridade primeiro).
* Recebe: Um ponteiro para o n� a ser adicionado e um ponteiro para o descritor da fila
* Retorna: void
*
*/
void adiciona_na_fila_prioridade(No* novo, Descritor *D);

/*
*---Fun��o para remover uma ocorr�ncia do in�cio da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: Um ponteiro para a ocorr�ncia removida, ou NULL se a fila estiver vazia
*
*/
Ocorrencia* remove_da_fila(Descritor *D);

/*
*---Fun��o para exibir as informa��es de uma ocorr�ncia--
* (Esta fun��o agora chama exibir_ocorrencia_especifica de ocorrencias.c)
* Recebe: Um ponteiro para a ocorr�ncia
* Retorna: void
*
*/
void exibe_ocorrencia(Ocorrencia *ocorrencia);

/*
*---Fun��o para exibir todos os itens da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void exibe_fila(Descritor *D);

/*
*---Fun��o para liberar a mem�ria da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void free_fila(Descritor* D);

/*
*---Fun��o para gerar um tempo aleat�rio (simula��o de espera)--
* Recebe: void
* Retorna: inteiro (tempo em segundos)
*
*/
int gera_tempo();

/*
*---Fun��o para gerar uma quantidade aleat�ria de n�s (ocorr�ncias)--
* Recebe: void
* Retorna: inteiro (quantidade de ocorr�ncias)
*
*/
int gera_qtd_no();

/*
*---Fun��o para simular o enfileiramento de ocorr�ncias--
* Recebe: Um ponteiro para o descritor da fila, a tabela hash de bairros e de moradores
* Retorna: void
*
*/
void enfileirando(Descritor *D, Bairros_Hash *ha, Morador_Hash *hash_morador);

#endif // FILA_DE_OCORRENCIAS_H_INCLUDED
