#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED

#include "../include/ocorrencias.h"
#include "../include/fila_de_ocorrencias.h"

// --- Implementando estruturas ---

typedef struct noAVL{
    int prioridade;
    Descritor *fila_ocorrencias;
    struct noAVL *esquerdo;
    struct  noAVL *direito;
    int altura;
}NoAVL;

typedef struct arvore_AVL{
    NoAVL *raiz;
    int tamanho;
}AVL;

// ----- Funções -----
AVL* criarArvoreAVL();

NoAVL* novoNoAVL(Ocorrencia* ocorrencia);

int maior(int a, int b);

int alturaDoNo(NoAVL* no);

void inserirOcorrenciaAVL(AVL* arvore, Ocorrencia* ocorrencia);

Ocorrencia* removerOcorrenciaMaiorPrioridade(AVL* arvore);

NoAVL* removendo_no_AVL(NoAVL* raiz, int chave);

void imprimir(NoAVL* raiz, int nivel);

NoAVL* buscarNoPrioridade(NoAVL* raiz, int procurado);

void liberarArvoreAVL(NoAVL* raiz);

void destruirArvoreAVL(AVL* arvore);

Ocorrencia* obter_ocorrencia_maior_prioridade(AVL* arvore);

#endif // ARVORE_AVL_H_INCLUDED
