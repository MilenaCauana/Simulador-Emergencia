#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/ocorrencias.h"
#include "../include/fila_de_ocorrencias.h"
#include "../include/arvore_avl.h"

// =========================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES DA ÁRVORE AVL

/*
    Função que cria e inicializa uma nova Árvore AVL
*/
AVL* criarArvoreAVL(){
    AVL* novaArvore = malloc(sizeof(AVL));
    if(novaArvore == NULL){
        printf("\nERRO AO ALOCAR MEMORIA PARA AVL!\n");
        return NULL;
    }
    novaArvore->raiz = NULL;
    novaArvore->tamanho = 0;
    return novaArvore;
}

/*
    Função que cria um novo nó da Árvore AVL.
    Ele não recebe apenas um valor inteiro, mas uma Ocorrencia para inicializar a fila.
    ocorrencia -> a primeira ocorrência a ser inserida na fila deste nó.
    Retorna: o endereço do nó AVL criado.
*/
NoAVL* novoNoAVL(Ocorrencia* ocorrencia){
    NoAVL* novo = malloc(sizeof(NoAVL));
    if(novo == NULL){
        printf("\nERRO AO ALOCAR MEMORIA PARA NO AVL!\n");
        return NULL;
    }

    novo->prioridade = ocorrencia->prioridade; // A chave do nó é a prioridade

    novo->fila_ocorrencias = cria_fila();
    if (novo->fila_ocorrencias == NULL) {
        printf("\nERRO AO INICIALIZAR FILA NO NO AVL!\n");
        free(novo);
        return NULL;
    }

    No* novo_no_fila = (No*) malloc(sizeof(No));
    if (novo_no_fila == NULL) {
        printf("\nERRO AO ALOCAR NO PARA FILA INTERNA!\n");
        free_fila(novo->fila_ocorrencias);
        free(novo);
        return NULL;
    }
    novo_no_fila->ocorrencia = ocorrencia;
    novo_no_fila->prox = NULL; // Importante para o primeiro elemento da fila

    adiciona_na_fila_prioridade(novo_no_fila, novo->fila_ocorrencias); // Insere a primeira ocorrência na fila

    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0; // Altura inicial de um nó folha
    return novo;
}


// ======== FUNÇÕES AUXILIARES ========
/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
int maior(int a, int b){
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Retorna a altura de um nó ou -1 caso ele seja null
int alturaDoNo(NoAVL* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

// Calcula e retorna o fator de balanceamento de um nó
int fatorDeBalanceamento(NoAVL* no){
    if(no){
        return alturaDoNo(no->esquerdo) - alturaDoNo(no->direito);
    }else{
        return 0;
    }
}


// --- FUNÇÕES DE ROTAÇÃO ---

// função para a rotação à esquerda
NoAVL* rotacaoEsquerda(NoAVL* raiz){
    NoAVL* aux;
    NoAVL* filho;

    aux = raiz->direito;
    filho = aux->esquerdo;

    aux->esquerdo = raiz;
    raiz->direito = filho;

    // Atualiza as alturas
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    aux->altura = maior(alturaDoNo(aux->esquerdo), alturaDoNo(aux->direito)) + 1; // Altura do aux é baseada nos seus novos filhos

    return aux;
}

// função para a rotação à direita
NoAVL* rotacaoDireita(NoAVL* raiz){
    NoAVL* aux;
    NoAVL* filho;

    aux = raiz->esquerdo;
    filho = aux->direito;

    aux->direito = raiz;
    raiz->esquerdo = filho;

    // Atualiza as alturas
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    aux->altura = maior(alturaDoNo(aux->esquerdo), alturaDoNo(aux->direito)) + 1; // Altura do aux é baseada nos seus novos filhos

    return aux;
}

// Funções de rotação dupla
NoAVL* rotacaoDireitaEsquerda(NoAVL* raiz){
    raiz->direito = rotacaoDireita(raiz->direito);
    return rotacaoEsquerda(raiz);
}

NoAVL* rotacaoEsquerdaDireita(NoAVL* raiz){
    raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo);
    return rotacaoDireita(raiz);
}


// --- CONFERINDO BALANCEAMENTO ---

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
NoAVL* balancear(NoAVL* raiz){
    int fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda (RR)
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita (LL)
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à direita (LR)
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à esquerda (RL)
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}


// ===== INSERÇÃO ====
/*
    Função recursiva para inserir uma ocorrência na AVL.
    raiz -> raiz do subárvore atual
    ocorrencia -> a ocorrência a ser inserida
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
NoAVL* inserirAVL_Rec(NoAVL* raiz, Ocorrencia* ocorrencia){
    if(raiz == NULL){ // Se chegamos a um ponto de inserção ou árvore vazia
        // ### CORREÇÃO AQUI: novoNo() agora é novoNoAVL() ###
        return novoNoAVL(ocorrencia); // Cria um novo nó com a ocorrência e sua prioridade
    }

    // Se a prioridade da ocorrência for igual à prioridade do nó atual, insere na fila
    if(ocorrencia->prioridade == raiz->prioridade){
        // ### CORREÇÃO AQUI: insereFila() agora é adiciona_na_fila_prioridade() ###
        // Precisamos criar um No* temporário para encapsular a Ocorrencia.
        No* novo_no_fila = (No*) malloc(sizeof(No));
        if (novo_no_fila == NULL) {
            printf("\nERRO AO ALOCAR NO PARA FILA INTERNA AO INSERIR NO AVL!\n");
            return raiz; // Retorna a raiz atual sem inserir a ocorrência
        }
        novo_no_fila->ocorrencia = ocorrencia;
        novo_no_fila->prox = NULL;
        adiciona_na_fila_prioridade(novo_no_fila, raiz->fila_ocorrencias);
    } else if(ocorrencia->prioridade < raiz->prioridade){
        raiz->esquerdo = inserirAVL_Rec(raiz->esquerdo, ocorrencia);
    } else { // ocorrencia->prioridade > raiz->prioridade
        raiz->direito = inserirAVL_Rec(raiz->direito, ocorrencia);
    }

    // Recalcular a altura do nó atual
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verifica a necessidade de balancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função pública para inserir uma ocorrência na AVL.
    arvore -> ponteiro para a struct AVL
    ocorrencia -> a ocorrência a ser inserida
*/
void inserirOcorrenciaAVL(AVL* arvore, Ocorrencia* ocorrencia){
    if(arvore == NULL || ocorrencia == NULL){
        printf("Erro: arvore ou ocorrencia nulos para insercao.\n");
        return;
    }
    // As prioridades são de 0 a 5. Se for fora desse range, pode ser um problema
    if (ocorrencia->prioridade < 0 || ocorrencia->prioridade > 5) {
        printf("Erro: Prioridade da ocorrencia fora do range valido (0-5).\n");
        return;
    }

    // A contagem do tamanho da árvore deve ser apenas para o número total de ocorrências
    // e não o número de nós AVL. O incremento deve ser feito aqui, pois uma ocorrência
    // sempre é inserida (ou em um nó novo, ou em uma fila existente).
    arvore->raiz = inserirAVL_Rec(arvore->raiz, ocorrencia);
    arvore->tamanho++; // Incrementa o contador total de ocorrências
}


// === REMOÇÃO ===
/*
    Função auxiliar para encontrar o nó com a menor prioridade na subárvore direita
    (para ser o sucessor na remoção de um nó com dois filhos).
*/
NoAVL* menorNo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual && atual->esquerdo != NULL)
        atual = atual->esquerdo;
    return atual;
}

/*
    Remove e retorna a ocorrência de maior prioridade da AVL.
    Esta função remove o primeiro elemento da fila do nó de maior prioridade.
    Se a fila ficar vazia, o nó AVL correspondente é removido da árvore.
    Retorna a Ocorrencia removida, ou NULL se a árvore estiver vazia.
*/
Ocorrencia* removerOcorrenciaMaiorPrioridade(AVL* arvore){
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }

    NoAVL* noMaiorPrioridade = arvore->raiz;
    while (noMaiorPrioridade->direito != NULL) {
        noMaiorPrioridade = noMaiorPrioridade->direito;
    }

    if (noMaiorPrioridade->fila_ocorrencias == NULL || noMaiorPrioridade->fila_ocorrencias->inicio == NULL) {
        return NULL;
    }

    Ocorrencia* ocorrenciaRemovida = remove_da_fila(noMaiorPrioridade->fila_ocorrencias);
    arvore->tamanho--;

    // Se a fila ficou vazia após a remoção, o nó AVL precisa ser removido
    if (noMaiorPrioridade->fila_ocorrencias->inicio == NULL) {
        printf("Fila vazia no no de prioridade %d. Removendo no AVL.\n", noMaiorPrioridade->prioridade);

        // ======================= A CORREÇÃO ESTÁ AQUI =======================
        // A linha abaixo foi REMOVIDA. A função removendo_no_AVL será
        // a responsável por liberar a fila do nó que ela está destruindo.
        // free_fila(noMaiorPrioridade->fila_ocorrencias); // <<<<<<< REMOVA ESTA LINHA
        // ====================================================================

        arvore->raiz = removendo_no_AVL(arvore->raiz, noMaiorPrioridade->prioridade);
    }

    return ocorrenciaRemovida;
}


/*
    Remoção de um nó na arvore (adaptada para a nova estrutura)
    chave -> a prioridade do nó AVL a ser removido (quando sua fila estiver vazia)
*/
NoAVL* removendo_no_AVL(NoAVL* raiz, int chave){ // 'chave' aqui é a prioridade do nó a ser removido
    if(raiz == NULL){
        return NULL;
    }else{
        if(raiz->prioridade == chave){ // Encontrou o nó com a prioridade a ser removida
            // Validação: A fila DEVE estar vazia para removermos o nó AVL
            // ### CORREÇÃO AQUI: filaVazia() verifica agora D->tamanho == 0 ou D->inicio == NULL ###
            if (raiz->fila_ocorrencias != NULL && raiz->fila_ocorrencias->inicio != NULL) {
                printf("Erro: Tentativa de remover no AVL com fila nao vazia (prioridade %d). Nao removido.\n", chave);
                return raiz; // Nao remove o nó
            }

            //remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL){
                // ### CORREÇÃO AQUI: liberaFila() agora é free_fila() ###
                free_fila(raiz->fila_ocorrencias); // Libera a fila antes de liberar o nó
                free(raiz);
                return NULL;
            }else{
                //  nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    NoAVL *aux = menorNo(raiz->direito); // Encontra o sucessor

                    // Libera a fila ANTIGA do nó que estamos "substituindo"
                    free_fila(raiz->fila_ocorrencias);

                    // Copia os dados do sucessor para o nó atual
                    raiz->prioridade = aux->prioridade;
                    raiz->fila_ocorrencias = aux->fila_ocorrencias; // Transfere a fila

                    // ================== A CORREÇÃO ESTÁ AQUI ==================
                    // Desanexa a fila do nó sucessor para que ela não seja liberada
                    // quando o nó 'aux' for removido na chamada recursiva.
                    // Isso evita o "double-free" ou "use-after-free".
                    aux->fila_ocorrencias = NULL;
                    // ==========================================================

                    // Agora, remove o nó sucessor (que agora não tem mais fila)
                    // da sub-árvore direita.
                    raiz->direito = removendo_no_AVL(raiz->direito, aux->prioridade);

                    // O return raiz estava faltando no seu código original neste bloco.
                    return raiz;
                }else{
                    //remover nós que possuem apenas 1 filho
                    NoAVL* aux; // ### CORREÇÃO AQUI: Tipo de ponteiro para NoAVL* ###
                    if(raiz->esquerdo != NULL){
                        aux = raiz->esquerdo;
                    }else{
                        aux = raiz->direito;
                    }
                    // ### CORREÇÃO AQUI: liberaFila() agora é free_fila() ###
                    free_fila(raiz->fila_ocorrencias); // Libera a fila antes de liberar o nó
                    free(raiz);
                    return aux;
                }
            }
        }else{ // Continua a busca pelo nó a ser removido
            if(chave < raiz->prioridade){
                // ### CORREÇÃO AQUI: removendo_no() agora é removendo_no_AVL() ###
                raiz->esquerdo = removendo_no_AVL(raiz->esquerdo, chave);
            }else{ // chave > raiz->prioridade
                // ### CORREÇÃO AQUI: removendo_no() agora é removendo_no_AVL() ###
                raiz->direito = removendo_no_AVL(raiz->direito, chave);
            }
        }
    }

    // Após a remoção (ou se não removeu, mas recursivamente subiu), recalcula a altura e balanceia
    if (raiz != NULL) {
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
        raiz = balancear(raiz);
    }

    return raiz;
}

// === Imprimindo a Árvore ===
// Esta função agora imprime a prioridade do nó e o tamanho da fila associada.
void imprimir(NoAVL* raiz, int nivel){
    int i;
    if (raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n"); // Nova linha para cada nível

        for(i = 0; i < nivel; i++){
            printf("\t");
        }
        // ### CORREÇÃO AQUI: Acessando o tamanho da fila corretamente ###
        printf("Prioridade %d (Ocorrencias: %d)", raiz->prioridade, (raiz->fila_ocorrencias != NULL ? raiz->fila_ocorrencias->tamanho : 0));
        imprimir(raiz->esquerdo, nivel + 1);
    }
}


// ==== BUSCA ====
/*
    Busca um nó na AVL pela prioridade.
    Retorna o ponteiro para o nó se encontrado, NULL caso contrário.
*/
NoAVL* buscarNoPrioridade(NoAVL* raiz, int procurado){
    if(raiz == NULL){
        return NULL;
    }
    if(procurado == raiz->prioridade){
        return raiz;
    }
    if(procurado < raiz->prioridade){
        return buscarNoPrioridade(raiz->esquerdo, procurado);
    } else { // procurado > raiz->prioridade
        return buscarNoPrioridade(raiz->direito, procurado);
    }
}


Ocorrencia* obter_ocorrencia_maior_prioridade(AVL* arvore) {
    // 1. Verifica se a árvore é válida e não está vazia.
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }

    // 2. Navega até o nó mais à direita (que tem a maior prioridade).
    NoAVL* no_maior_prioridade = arvore->raiz;
    while (no_maior_prioridade->direito != NULL) {
        no_maior_prioridade = no_maior_prioridade->direito;
    }

    // 3. Verifica se a fila de ocorrências daquele nó não está vazia.
    if (no_maior_prioridade->fila_ocorrencias == NULL || no_maior_prioridade->fila_ocorrencias->inicio == NULL) {
        // Estado inconsistente, mas retornamos NULL por segurança.
        return NULL;
    }

    // 4. Retorna um ponteiro para a primeira ocorrência na fila (a mais antiga daquela prioridade).
    return no_maior_prioridade->fila_ocorrencias->inicio->ocorrencia;
}

void liberarArvoreAVL_Rec(NoAVL* raiz) {
    if (raiz == NULL) {
        return;
    }

    // Libera recursivamente as sub-árvores esquerda e direita
    liberarArvoreAVL_Rec(raiz->esquerdo);
    liberarArvoreAVL_Rec(raiz->direito);

    // Agora, libera a memória do nó atual
    // 1. Libera a fila de ocorrências (a estrutura da fila, não as ocorrências)
    free_fila(raiz->fila_ocorrencias);

    // 2. Libera o nó da árvore AVL
    free(raiz);
}

void destruirArvoreAVL(AVL* arvore) {
    if (arvore == NULL) {
        return;
    }

    // Chama a função recursiva para liberar todos os nós a partir da raiz
    liberarArvoreAVL_Rec(arvore->raiz);

    // Por fim, libera a própria estrutura da árvore
    free(arvore);
}
