#include "../include/ocorrencias.h"

// ========= ESTRUTURA LISTA LIGADA =========
typedef struct NoLista {
    Ocorrencia *ocorrencia; // ponteiro para a ocorrência
    struct NoLista *prox;
} NoLista;

typedef struct ListaLigada {
    NoLista *cabeca; // O equivalente ao 'topo' da pilha
    int tamanho;
} ListaLigadaRelatorio;

// ======== FUNÇÕES ========
ListaLigadaRelatorio* cria_lista_relatorio();

void adiciona_inicio_lista_relatorio(ListaLigadaRelatorio *lista, Ocorrencia *ocorrencia);

Ocorrencia* remove_inicio_lista_relatorio(ListaLigadaRelatorio *lista);

void imprime_lista_relatorio(ListaLigadaRelatorio *lista);

void free_lista_relatorio(ListaLigadaRelatorio *lista);
