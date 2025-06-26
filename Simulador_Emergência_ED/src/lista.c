#include "../include/lista.h"

// ========== FUN��ES LISTA LIGADA ===========
ListaLigadaRelatorio* cria_lista_relatorio() {
    ListaLigadaRelatorio *lista = (ListaLigadaRelatorio*) malloc(sizeof(ListaLigadaRelatorio));
    if (lista == NULL) {
        printf("ERRO AO ALOCAR LISTA\n");
        return NULL;
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

// Adiciona um elemento no in�cio da lista (equivalente ao push da pilha)
void adiciona_inicio_lista_relatorio(ListaLigadaRelatorio *lista, Ocorrencia *ocorrencia) {
    if (lista == NULL) {
        printf("ERRO: Lista n�o inicializada.\n");
        return;
    }
    NoLista *novo_no = (NoLista*) malloc(sizeof(NoLista));
    if (novo_no == NULL) {
        printf("ERRO AO ALOCAR NOVO N�\n");
        return;
    }

    novo_no->ocorrencia = ocorrencia; // Armazena o ponteiro para a ocorr�ncia
    novo_no->prox = lista->cabeca;
    lista->cabeca = novo_no;
    lista->tamanho++;
}

// Remove e retorna o elemento do in�cio da lista (equivalente ao pop da pilha)
Ocorrencia* remove_inicio_lista_relatorio(ListaLigadaRelatorio *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        return NULL; // Lista vazia ou n�o inicializada
    }
    NoLista *no_removido = lista->cabeca;
    Ocorrencia *ocorrencia = no_removido->ocorrencia; // Pega o ponteiro da ocorr�ncia
    lista->cabeca = no_removido->prox;
    free(no_removido); // Libera apenas o n� da lista
    lista->tamanho--;
    return ocorrencia; // Retorna o ponteiro da ocorr�ncia
}

void imprime_lista_relatorio(ListaLigadaRelatorio *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        printf("Lista de ocorrencias do relatorio esta vazia.\n");
        return;
    }
    printf("\n---------- RELATORIO DE OCORRENCIAS ATENDIDAS (Lista Ligada - Ultima -> Primeira) ----------\n");
    NoLista *atual = lista->cabeca;
    // Para manter a ordem de exibi��o similar � pilha (�ltimo adicionado primeiro),
    // podemos iterar do in�cio. Se a pilha imprimia do topo para a base (�ltimo adicionado primeiro),
    // a lista ligada com inser��o no in�cio faz o mesmo.
    int count = lista->tamanho;
    while (atual != NULL) {
        exibir_ocorrencia_especifica(atual -> ocorrencia);
        // Supondo que 'exibir_ocorrencia_especifica' esteja definida em outro lugar
        // e � capaz de exibir os detalhes de 'Ocorrencia'.
        // exibir_ocorrencia_especifica(atual->ocorrencia);
        atual = atual->prox;
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Total de ocorrencias atendidas: %d\n", lista->tamanho);
}

void free_lista_relatorio(ListaLigadaRelatorio *lista) {
    if (lista == NULL) return;
    NoLista *atual = lista->cabeca;
    NoLista *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual->ocorrencia); // <<< LIBERA A OCORRENCIA ASSOCIADA AO N�
        free(atual);             // Libera o n� da lista
        atual = proximo;
    }
    free(lista); // Libera a estrutura descritora da lista
}
