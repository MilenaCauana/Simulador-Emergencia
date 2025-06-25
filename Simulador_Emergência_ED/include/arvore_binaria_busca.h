#ifndef ARVORE_BINARIA_BUSCA_H_INCLUDED
#define ARVORE_BINARIA_BUSCA_H_INCLUDED

#include "ocorrencias.h"
#include "pilha1.h"

typedef struct modulo_abb{
    Ocorrencia* problema;
    struct modulo_abb* esquerdo;
    struct modulo_abb* direito;
}no_abb;

typedef struct arvore{
    no_abb* raiz;
}ArvB;

no_abb* cria_arvore_binaria(Pilha* pilha);

void preenche_arvore_binaria(no_abb* raiz, Pilha* pilha);

void inserirEsquerda(no_abb *No, Ocorrencia* ocorr);

void inserirDireita(no_abb *No, Ocorrencia* ocorr);

void inserirABB(no_abb* raiz, Ocorrencia* ocorr);

no_abb* buscaBinaria(no_abb* raiz, int procurado);

void liberarArvore(no_abb* raiz);

#endif // ARVORE_BINARIA_BUSCA_H_INCLUDED
