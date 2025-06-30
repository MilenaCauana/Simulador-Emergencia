#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/ocorrencias.h"
#include "../include/fila_de_ocorrencias.h"
#include "../include/arvore_avl.h"

// =========================================================================
// IMPLEMENTA��O DAS FUN��ES DA �RVORE AVL

/*
    Fun��o que cria e inicializa uma nova �rvore AVL
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
    Fun��o que cria um novo n� da �rvore AVL.
    Ele n�o recebe apenas um valor inteiro, mas uma Ocorrencia para inicializar a fila.
    ocorrencia -> a primeira ocorr�ncia a ser inserida na fila deste n�.
    Retorna: o endere�o do n� AVL criado.
*/
NoAVL* novoNoAVL(Ocorrencia* ocorrencia){
    NoAVL* novo = malloc(sizeof(NoAVL));
    if(novo == NULL){
        printf("\nERRO AO ALOCAR MEMORIA PARA NO AVL!\n");
        return NULL;
    }

    novo->prioridade = ocorrencia->prioridade; // A chave do n� � a prioridade

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

    adiciona_na_fila_prioridade(novo_no_fila, novo->fila_ocorrencias); // Insere a primeira ocorr�ncia na fila

    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0; // Altura inicial de um n� folha
    return novo;
}


// ======== FUN��ES AUXILIARES ========
/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois n�s da �rvore
*/
int maior(int a, int b){
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Retorna a altura de um n� ou -1 caso ele seja null
int alturaDoNo(NoAVL* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

// Calcula e retorna o fator de balanceamento de um n�
int fatorDeBalanceamento(NoAVL* no){
    if(no){
        return alturaDoNo(no->esquerdo) - alturaDoNo(no->direito);
    }else{
        return 0;
    }
}


// --- FUN��ES DE ROTA��O ---

// fun��o para a rota��o � esquerda
NoAVL* rotacaoEsquerda(NoAVL* raiz){
    NoAVL* aux;
    NoAVL* filho;

    aux = raiz->direito;
    filho = aux->esquerdo;

    aux->esquerdo = raiz;
    raiz->direito = filho;

    // Atualiza as alturas
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    aux->altura = maior(alturaDoNo(aux->esquerdo), alturaDoNo(aux->direito)) + 1; // Altura do aux � baseada nos seus novos filhos

    return aux;
}

// fun��o para a rota��o � direita
NoAVL* rotacaoDireita(NoAVL* raiz){
    NoAVL* aux;
    NoAVL* filho;

    aux = raiz->esquerdo;
    filho = aux->direito;

    aux->direito = raiz;
    raiz->esquerdo = filho;

    // Atualiza as alturas
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
    aux->altura = maior(alturaDoNo(aux->esquerdo), alturaDoNo(aux->direito)) + 1; // Altura do aux � baseada nos seus novos filhos

    return aux;
}

// Fun��es de rota��o dupla
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
    Fun��o para realizar o balanceamento da �rvore ap�s uma inser��o ou remo��o
    Recebe o n� que est� desbalanceado e retorna a nova raiz ap�s o balanceamento
*/
NoAVL* balancear(NoAVL* raiz){
    int fb = fatorDeBalanceamento(raiz);

    // Rota��o � esquerda (RR)
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rota��o � direita (LL)
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rota��o dupla � direita (LR)
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rota��o dupla � esquerda (RL)
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}


// ===== INSER��O ====
/*
    Fun��o recursiva para inserir uma ocorr�ncia na AVL.
    raiz -> raiz do sub�rvore atual
    ocorrencia -> a ocorr�ncia a ser inserida
    Retorno: endere�o do novo n� ou nova raiz ap�s o balanceamento
*/
NoAVL* inserirAVL_Rec(NoAVL* raiz, Ocorrencia* ocorrencia){
    if(raiz == NULL){ // Se chegamos a um ponto de inser��o ou �rvore vazia
        // ### CORRE��O AQUI: novoNo() agora � novoNoAVL() ###
        return novoNoAVL(ocorrencia); // Cria um novo n� com a ocorr�ncia e sua prioridade
    }

    // Se a prioridade da ocorr�ncia for igual � prioridade do n� atual, insere na fila
    if(ocorrencia->prioridade == raiz->prioridade){
        // ### CORRE��O AQUI: insereFila() agora � adiciona_na_fila_prioridade() ###
        // Precisamos criar um No* tempor�rio para encapsular a Ocorrencia.
        No* novo_no_fila = (No*) malloc(sizeof(No));
        if (novo_no_fila == NULL) {
            printf("\nERRO AO ALOCAR NO PARA FILA INTERNA AO INSERIR NO AVL!\n");
            return raiz; // Retorna a raiz atual sem inserir a ocorr�ncia
        }
        novo_no_fila->ocorrencia = ocorrencia;
        novo_no_fila->prox = NULL;
        adiciona_na_fila_prioridade(novo_no_fila, raiz->fila_ocorrencias);
    } else if(ocorrencia->prioridade < raiz->prioridade){
        raiz->esquerdo = inserirAVL_Rec(raiz->esquerdo, ocorrencia);
    } else { // ocorrencia->prioridade > raiz->prioridade
        raiz->direito = inserirAVL_Rec(raiz->direito, ocorrencia);
    }

    // Recalcular a altura do n� atual
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verifica a necessidade de balancear a �rvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Fun��o p�blica para inserir uma ocorr�ncia na AVL.
    arvore -> ponteiro para a struct AVL
    ocorrencia -> a ocorr�ncia a ser inserida
*/
void inserirOcorrenciaAVL(AVL* arvore, Ocorrencia* ocorrencia){
    if(arvore == NULL || ocorrencia == NULL){
        printf("Erro: arvore ou ocorrencia nulos para insercao.\n");
        return;
    }
    // As prioridades s�o de 0 a 5. Se for fora desse range, pode ser um problema
    if (ocorrencia->prioridade < 0 || ocorrencia->prioridade > 5) {
        printf("Erro: Prioridade da ocorrencia fora do range valido (0-5).\n");
        return;
    }

    // A contagem do tamanho da �rvore deve ser apenas para o n�mero total de ocorr�ncias
    // e n�o o n�mero de n�s AVL. O incremento deve ser feito aqui, pois uma ocorr�ncia
    // sempre � inserida (ou em um n� novo, ou em uma fila existente).
    arvore->raiz = inserirAVL_Rec(arvore->raiz, ocorrencia);
    arvore->tamanho++; // Incrementa o contador total de ocorr�ncias
}


// === REMO��O ===
/*
    Fun��o auxiliar para encontrar o n� com a menor prioridade na sub�rvore direita
    (para ser o sucessor na remo��o de um n� com dois filhos).
*/
NoAVL* menorNo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual && atual->esquerdo != NULL)
        atual = atual->esquerdo;
    return atual;
}

/*
    Remove e retorna a ocorr�ncia de maior prioridade da AVL.
    Esta fun��o remove o primeiro elemento da fila do n� de maior prioridade.
    Se a fila ficar vazia, o n� AVL correspondente � removido da �rvore.
    Retorna a Ocorrencia removida, ou NULL se a �rvore estiver vazia.
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

    // Se a fila ficou vazia ap�s a remo��o, o n� AVL precisa ser removido
    if (noMaiorPrioridade->fila_ocorrencias->inicio == NULL) {
        printf("Fila vazia no no de prioridade %d. Removendo no AVL.\n", noMaiorPrioridade->prioridade);

        // ======================= A CORRE��O EST� AQUI =======================
        // A linha abaixo foi REMOVIDA. A fun��o removendo_no_AVL ser�
        // a respons�vel por liberar a fila do n� que ela est� destruindo.
        // free_fila(noMaiorPrioridade->fila_ocorrencias); // <<<<<<< REMOVA ESTA LINHA
        // ====================================================================

        arvore->raiz = removendo_no_AVL(arvore->raiz, noMaiorPrioridade->prioridade);
    }

    return ocorrenciaRemovida;
}


/*
    Remo��o de um n� na arvore (adaptada para a nova estrutura)
    chave -> a prioridade do n� AVL a ser removido (quando sua fila estiver vazia)
*/
NoAVL* removendo_no_AVL(NoAVL* raiz, int chave){ // 'chave' aqui � a prioridade do n� a ser removido
    if(raiz == NULL){
        return NULL;
    }else{
        if(raiz->prioridade == chave){ // Encontrou o n� com a prioridade a ser removida
            // Valida��o: A fila DEVE estar vazia para removermos o n� AVL
            // ### CORRE��O AQUI: filaVazia() verifica agora D->tamanho == 0 ou D->inicio == NULL ###
            if (raiz->fila_ocorrencias != NULL && raiz->fila_ocorrencias->inicio != NULL) {
                printf("Erro: Tentativa de remover no AVL com fila nao vazia (prioridade %d). Nao removido.\n", chave);
                return raiz; // Nao remove o n�
            }

            //remove n�s folhas (n�s sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL){
                // ### CORRE��O AQUI: liberaFila() agora � free_fila() ###
                free_fila(raiz->fila_ocorrencias); // Libera a fila antes de liberar o n�
                free(raiz);
                return NULL;
            }else{
                //  n�s que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    NoAVL *aux = menorNo(raiz->direito); // Encontra o sucessor

                    // Libera a fila ANTIGA do n� que estamos "substituindo"
                    free_fila(raiz->fila_ocorrencias);

                    // Copia os dados do sucessor para o n� atual
                    raiz->prioridade = aux->prioridade;
                    raiz->fila_ocorrencias = aux->fila_ocorrencias; // Transfere a fila

                    // ================== A CORRE��O EST� AQUI ==================
                    // Desanexa a fila do n� sucessor para que ela n�o seja liberada
                    // quando o n� 'aux' for removido na chamada recursiva.
                    // Isso evita o "double-free" ou "use-after-free".
                    aux->fila_ocorrencias = NULL;
                    // ==========================================================

                    // Agora, remove o n� sucessor (que agora n�o tem mais fila)
                    // da sub-�rvore direita.
                    raiz->direito = removendo_no_AVL(raiz->direito, aux->prioridade);

                    // O return raiz estava faltando no seu c�digo original neste bloco.
                    return raiz;
                }else{
                    //remover n�s que possuem apenas 1 filho
                    NoAVL* aux; // ### CORRE��O AQUI: Tipo de ponteiro para NoAVL* ###
                    if(raiz->esquerdo != NULL){
                        aux = raiz->esquerdo;
                    }else{
                        aux = raiz->direito;
                    }
                    // ### CORRE��O AQUI: liberaFila() agora � free_fila() ###
                    free_fila(raiz->fila_ocorrencias); // Libera a fila antes de liberar o n�
                    free(raiz);
                    return aux;
                }
            }
        }else{ // Continua a busca pelo n� a ser removido
            if(chave < raiz->prioridade){
                // ### CORRE��O AQUI: removendo_no() agora � removendo_no_AVL() ###
                raiz->esquerdo = removendo_no_AVL(raiz->esquerdo, chave);
            }else{ // chave > raiz->prioridade
                // ### CORRE��O AQUI: removendo_no() agora � removendo_no_AVL() ###
                raiz->direito = removendo_no_AVL(raiz->direito, chave);
            }
        }
    }

    // Ap�s a remo��o (ou se n�o removeu, mas recursivamente subiu), recalcula a altura e balanceia
    if (raiz != NULL) {
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
        raiz = balancear(raiz);
    }

    return raiz;
}

// === Imprimindo a �rvore ===
// Esta fun��o agora imprime a prioridade do n� e o tamanho da fila associada.
void imprimir(NoAVL* raiz, int nivel){
    int i;
    if (raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n"); // Nova linha para cada n�vel

        for(i = 0; i < nivel; i++){
            printf("\t");
        }
        // ### CORRE��O AQUI: Acessando o tamanho da fila corretamente ###
        printf("Prioridade %d (Ocorrencias: %d)", raiz->prioridade, (raiz->fila_ocorrencias != NULL ? raiz->fila_ocorrencias->tamanho : 0));
        imprimir(raiz->esquerdo, nivel + 1);
    }
}


// ==== BUSCA ====
/*
    Busca um n� na AVL pela prioridade.
    Retorna o ponteiro para o n� se encontrado, NULL caso contr�rio.
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
    // 1. Verifica se a �rvore � v�lida e n�o est� vazia.
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }

    // 2. Navega at� o n� mais � direita (que tem a maior prioridade).
    NoAVL* no_maior_prioridade = arvore->raiz;
    while (no_maior_prioridade->direito != NULL) {
        no_maior_prioridade = no_maior_prioridade->direito;
    }

    // 3. Verifica se a fila de ocorr�ncias daquele n� n�o est� vazia.
    if (no_maior_prioridade->fila_ocorrencias == NULL || no_maior_prioridade->fila_ocorrencias->inicio == NULL) {
        // Estado inconsistente, mas retornamos NULL por seguran�a.
        return NULL;
    }

    // 4. Retorna um ponteiro para a primeira ocorr�ncia na fila (a mais antiga daquela prioridade).
    return no_maior_prioridade->fila_ocorrencias->inicio->ocorrencia;
}

void liberarArvoreAVL_Rec(NoAVL* raiz) {
    if (raiz == NULL) {
        return;
    }

    // Libera recursivamente as sub-�rvores esquerda e direita
    liberarArvoreAVL_Rec(raiz->esquerdo);
    liberarArvoreAVL_Rec(raiz->direito);

    // Agora, libera a mem�ria do n� atual
    // 1. Libera a fila de ocorr�ncias (a estrutura da fila, n�o as ocorr�ncias)
    free_fila(raiz->fila_ocorrencias);

    // 2. Libera o n� da �rvore AVL
    free(raiz);
}

void destruirArvoreAVL(AVL* arvore) {
    if (arvore == NULL) {
        return;
    }

    // Chama a fun��o recursiva para liberar todos os n�s a partir da raiz
    liberarArvoreAVL_Rec(arvore->raiz);

    // Por fim, libera a pr�pria estrutura da �rvore
    free(arvore);
}
