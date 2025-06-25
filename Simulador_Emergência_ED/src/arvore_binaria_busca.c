#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/ocorrencias.h"
#include "../include/arvore_binaria_busca.h"
#include "../include/pilha1.h"

no_abb* cria_arvore_binaria(Pilha* pilha){
    if(pilha == NULL || pilha->tamanho == 0){
        printf("\nNão foi possível criar a árvore!(pilha vazia)\n");
        return NULL;
    }

    int chave = (pilha->tamanho / 2) + 2000;
    NoPilha* aux = pilha->topo;

    // Procura pela ocorrência com o ID calculado
    while(aux != NULL){
        if(aux->ocorrencia != NULL && aux->ocorrencia->id == chave){
            break;
        }
        aux = aux->prox;
    }

    // Se não encontrou a chave específica, pega a primeira ocorrência válida
    if(aux == NULL || aux->ocorrencia == NULL){
        aux = pilha->topo;
        while(aux != NULL && aux->ocorrencia == NULL){
            aux = aux->prox;
        }
    }

    if(aux == NULL || aux->ocorrencia == NULL){
        printf("\nNão foi possível criar a árvore!(nenhuma ocorrência válida)\n");
        return NULL;
    }

    no_abb* novo = (no_abb*)malloc(sizeof(no_abb));
    if(novo == NULL){
        printf("\nERRO AO ALOCAR MEMORIA PARA RAIZ!\n");
        return NULL;
    }

    novo->problema = aux->ocorrencia;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

void preenche_arvore_binaria(no_abb* raiz, Pilha* pilha){
    if(raiz == NULL || pilha == NULL){
        return;
    }

    NoPilha* aux = pilha->topo;
    while(aux != NULL){
        if(aux->ocorrencia != NULL && aux->ocorrencia->id != raiz->problema->id){
            inserirABB(raiz, aux->ocorrencia);
        }
        aux = aux->prox;
    }
}

void inserirEsquerda(no_abb *No, Ocorrencia* ocorr){
    if(No->esquerdo == NULL){
        no_abb* novo = (no_abb*)malloc(sizeof(no_abb));
        if(novo == NULL){
            printf("\nERRO AO ALOCAR MEMORIA!\n");
            return;
        }
        novo->problema = ocorr;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        No->esquerdo = novo;
    }else{
        if(ocorr->id < No->esquerdo->problema->id){
            inserirEsquerda(No->esquerdo, ocorr);
        }
        else if(ocorr->id > No->esquerdo->problema->id){
            inserirDireita(No->esquerdo, ocorr);
        }
        // Se forem iguais, não insere (evita duplicatas)
    }
}

void inserirDireita(no_abb *No, Ocorrencia* ocorr){
    if(No->direito == NULL){
        no_abb* novo = (no_abb*)malloc(sizeof(no_abb));
        if(novo == NULL){
            printf("\nERRO AO ALOCAR MEMORIA!\n");
            return;
        }
        novo->problema = ocorr;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        No->direito = novo;
    }else{
        if(ocorr->id < No->direito->problema->id){
            inserirEsquerda(No->direito, ocorr);
        }
        else if(ocorr->id > No->direito->problema->id){
            inserirDireita(No->direito, ocorr);
        }
        // Se forem iguais, não insere (evita duplicatas)
    }
}

void inserirABB(no_abb* raiz, Ocorrencia* ocorr){
    if(raiz == NULL || ocorr == NULL){
        return;
    }

    if(ocorr->id < raiz->problema->id){
        inserirEsquerda(raiz, ocorr);
    }
    else if(ocorr->id > raiz->problema->id){
        inserirDireita(raiz, ocorr);
    }
    // Se forem iguais, não insere (evita duplicatas)
}

no_abb* buscaBinaria(no_abb* raiz, int procurado){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->problema->id == procurado){
        return raiz;
    }
    if(procurado < raiz->problema->id){
        return buscaBinaria(raiz->esquerdo, procurado);
    }
    else{
        return buscaBinaria(raiz->direito, procurado);
    }
}

void liberarArvore(no_abb* raiz){
    if(raiz == NULL){
        return;
    }
    liberarArvore(raiz->esquerdo);
    liberarArvore(raiz->direito);
    free(raiz);
}
