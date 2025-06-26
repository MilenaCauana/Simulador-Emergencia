#include "../include/lista.h"

// ========== FUNÇÕES LISTA LIGADA ===========
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

// Adiciona um elemento no início da lista (equivalente ao push da pilha)
void adiciona_inicio_lista_relatorio(ListaLigadaRelatorio *lista, Ocorrencia *ocorrencia) {
    if (lista == NULL) {
        printf("ERRO: Lista não inicializada.\n");
        return;
    }
    NoLista *novo_no = (NoLista*) malloc(sizeof(NoLista));
    if (novo_no == NULL) {
        printf("ERRO AO ALOCAR NOVO NÓ\n");
        return;
    }

    novo_no->ocorrencia = ocorrencia; // Armazena o ponteiro para a ocorrência
    novo_no->prox = lista->cabeca;
    lista->cabeca = novo_no;
    lista->tamanho++;
}

// Remove e retorna o elemento do início da lista (equivalente ao pop da pilha)
Ocorrencia* remove_inicio_lista_relatorio(ListaLigadaRelatorio *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        return NULL; // Lista vazia ou não inicializada
    }
    NoLista *no_removido = lista->cabeca;
    Ocorrencia *ocorrencia = no_removido->ocorrencia; // Pega o ponteiro da ocorrência
    lista->cabeca = no_removido->prox;
    free(no_removido); // Libera apenas o nó da lista
    lista->tamanho--;
    return ocorrencia; // Retorna o ponteiro da ocorrência
}

void imprime_lista_relatorio(ListaLigadaRelatorio *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        printf("Lista de ocorrencias do relatorio esta vazia.\n");
        return;
    }
    printf("\n---------- RELATORIO DE OCORRENCIAS ATENDIDAS (Lista Ligada - Ultima -> Primeira) ----------\n");
    NoLista *atual = lista->cabeca;
    // Para manter a ordem de exibição similar à pilha (último adicionado primeiro),
    // podemos iterar do início. Se a pilha imprimia do topo para a base (último adicionado primeiro),
    // a lista ligada com inserção no início faz o mesmo.
    int count = lista->tamanho;
    while (atual != NULL) {
        exibir_ocorrencia_especifica(atual -> ocorrencia);
        // Supondo que 'exibir_ocorrencia_especifica' esteja definida em outro lugar
        // e é capaz de exibir os detalhes de 'Ocorrencia'.
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
        free(atual->ocorrencia); // <<< LIBERA A OCORRENCIA ASSOCIADA AO NÓ
        free(atual);             // Libera o nó da lista
        atual = proximo;
    }
    free(lista); // Libera a estrutura descritora da lista
}
