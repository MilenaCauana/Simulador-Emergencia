#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../include/fila_de_ocorrencias.h"
#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"

//------ �� FUN��ES �� ------

/*
*---Fun��o de cria��o e inicializa��o da fila--
* Recebe: void
* Retorna: Um ponteiro para um descritor da fila
*
*/
Descritor* cria_fila(){
    Descritor *D = (Descritor*) malloc(sizeof(Descritor));
    confere_aloc(D);
    D->inicio = NULL;
    D->fim = NULL;
    D->tamanho = 0;
    return D;
}

/*
*---Fun��o para verificar aloca��o de mem�ria--
* Recebe: Um ponteiro gen�rico
* Retorna: void (encerra o programa se a aloca��o falhar)
*
*/
void confere_aloc(void *ptr){
    if (ptr == NULL){
        printf("ERRO DE ALOCACAO DE MEMORIA!\n");
        exit(1); // Encerra o programa
    }
}

/*
*---Fun��o para criar um novo n� da fila com uma ocorr�ncia--
* Recebe: Um ponteiro para a tabela hash de bairros e de moradores (para criar a ocorr�ncia)
* Retorna: Um ponteiro para o n� rec�m-criado
*
*/
No* cria_no(Bairros_Hash *ha, Morador_Hash *hash_morador){
    No* novo = (No*) malloc(sizeof(No));
    confere_aloc(novo);
    novo->ocorrencia = cria_ocorrencia(ha, hash_morador); // Cria a ocorr�ncia
    confere_aloc(novo->ocorrencia); // Confere se a ocorr�ncia foi criada
    novo->prox = NULL;
    return novo;
}

/*
*---Fun��o para adicionar uma ocorr�ncia na fila de prioridade--
* A inser��o mant�m a fila ordenada por prioridade (maior prioridade primeiro).
* Recebe: Um ponteiro para o n� a ser adicionado e um ponteiro para o descritor da fila
* Retorna: void
*
*/
void adiciona_na_fila_prioridade(No* novo, Descritor *D){
    if (D->inicio == NULL || novo->ocorrencia->prioridade > D->inicio->ocorrencia->prioridade) {
        // Se a fila estiver vazia ou o novo n� tiver maior prioridade que o primeiro
        novo->prox = D->inicio;
        D->inicio = novo;
    } else {
        No* atual = D->inicio;
        // Percorre a fila para encontrar a posi��o correta
        while (atual->prox != NULL && novo->ocorrencia->prioridade <= atual->prox->ocorrencia->prioridade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    // Se a fila estava vazia, o novo n� tamb�m � o fim
    if (D->fim == NULL) {
        D->fim = novo;
    } else if (novo->prox == NULL) { // Atualiza o fim se o novo n� foi adicionado ao final
        D->fim = novo;
    }
    D->tamanho++;
}

/*
*---Fun��o para remover uma ocorr�ncia do in�cio da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: Um ponteiro para a ocorr�ncia removida, ou NULL se a fila estiver vazia
*
*/
Ocorrencia* remove_da_fila(Descritor *D){
    if (D->inicio == NULL){
        return NULL; // Fila vazia
    }
    No* no_removido = D->inicio;
    Ocorrencia* ocorrencia_removida = no_removido->ocorrencia;
    D->inicio = D->inicio->prox;
    if (D->inicio == NULL){ // Se a fila ficou vazia
        D->fim = NULL;
    }
    free(no_removido); // Libera o n�, mas n�o a ocorr�ncia
    D->tamanho--;
    return ocorrencia_removida;
}

/*
*---Fun��o para exibir as informa��es de uma ocorr�ncia--
* (Esta fun��o agora chama exibir_ocorrencia_especifica de ocorrencias.c)
* Recebe: Um ponteiro para a ocorr�ncia
* Retorna: void
*
*/
void exibe_ocorrencia(Ocorrencia *ocorrencia){
    exibir_ocorrencia_especifica(ocorrencia);
}

/*
*---Fun��o para exibir todos os itens da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void exibe_fila(Descritor *D){
    if (D->inicio == NULL){
        printf("Fila de ocorrencias esta vazia.\n");
        return;
    }
    printf("\n--- Conteudo da Fila de Ocorrencias (Prioridade Decrescente) ---\n");
    No* atual = D->inicio;
    while (atual != NULL){
        printf("ID: %d | Tipo: %s | Prioridade: %d | Bairro: %s | Morador: %s\n",
               atual->ocorrencia->id,
               atual->ocorrencia->tipo,
               atual->ocorrencia->prioridade,
               (atual->ocorrencia->bairro != NULL) ? atual->ocorrencia->bairro->nome : "N/A",
               (atual->ocorrencia->morador != NULL) ? atual->ocorrencia->morador->nome : "N/A");
        atual = atual->prox;
    }
    printf("Tamanho da fila: %d\n", D->tamanho);
    printf("------------------------------------------------------------------\n");
}

/*
*---Fun��o para liberar a mem�ria da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void free_fila(Descritor* D){
    if (D == NULL) return;
    No *atual = D->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        // Nao libera atual->ocorrencia, pois ela e liberada em main.c
        // ou copiada para o relatorio/historico do morador.
        free(atual);
        atual = proximo;
    }
    free(D);
}

/*
*---Fun��o para gerar um tempo aleat�rio (simula��o de espera)--
* Recebe: void
* Retorna: inteiro (tempo em segundos)
*
*/
int gera_tempo(){
    return 1 + rand() % 5; // Tempo entre 1 e 5 segundos
}

/*
*---Fun��o para gerar uma quantidade aleat�ria de n�s (ocorr�ncias)--
* Recebe: void
* Retorna: inteiro (quantidade de ocorr�ncias)
*
*/
int gera_qtd_no(){
    return 1 + rand() % 3; // Gera entre 1 e 3 novas ocorr�ncias por ciclo
}

/*
*---Fun��o para simular o enfileiramento de ocorr�ncias--
* Recebe: Um ponteiro para o descritor da fila e a tabela hash de bairros e moradores
* Retorna: void
*
*/
void enfileirando(Descritor *D, Bairros_Hash *ha, Morador_Hash *hash_morador){
    int qtd_a_gerar = gera_qtd_no();
    printf("Gerando %d novas ocorrencias...\n", qtd_a_gerar);
    for (int i = 0; i < qtd_a_gerar; i++){
        No* novo_no = cria_no(ha, hash_morador); // Passa hash_morador
        if (novo_no != NULL) {
             // O tempo de registro � o ciclo atual da simula��o (ser� definido em main.c)
             novo_no->ocorrencia->tempo_registro = D->tamanho + 1; // Tempor�rio, ajustado em main.c
             adiciona_na_fila_prioridade(novo_no, D);
             printf("  - Ocorrencia ID %d (Prioridade %d) adicionada.\n", novo_no->ocorrencia->id, novo_no->ocorrencia->prioridade);
        }
    }
}

/*
*---Fun��o para buscar e despachar uma unidade de pol�cia--
* Recebe: A tabela hash da pol�cia, o ID do bairro da ocorr�ncia
* Retorna: true se uma unidade foi despachada, false caso contr�rio
*
*/
bool despacha_policia(Policia_Hash *policia_ha, int id_bairro_ocorrencia){
    if (policia_ha == NULL) return false;

    // Tenta encontrar a pol�cia do bairro da ocorr�ncia primeiro
    int id_policia_bairro = (id_bairro_ocorrencia / 1000) * 1000 + (id_bairro_ocorrencia % 1000) * 10 + 90;
    // Ex: Bairro 1001 -> id_policia 100190
    // O ID da pol�cia � uma combina��o do ID do bairro (1001, 1002...) + 90
    // id_policia_bairro = id_bairro_ocorrencia * 100 + 90; // Ex: 1001 * 100 + 90 = 100190 -> ISSO NAO EH CERTO.
    // O ID da policia eh id_bairro + 90. Se id_bairro = 1001, id_policia = 100190.
    // Precisa de uma funcao que pegue o id do bairro e retorne o id da policia.
    // No preenche_policia() os IDs sao 100190, 100290, etc.

    Policia policia_local;
    int pos_local = policia_chave_divisao(id_policia_bairro, policia_ha->tamanho);
    int inicio_pos_local = pos_local;
    bool found_local_unit = false;

    // Busca linear probing para a unidade local
    while (policia_ha->itens[pos_local] != NULL) {
        if (policia_ha->itens[pos_local]->id == id_policia_bairro) {
            policia_local = *(policia_ha->itens[pos_local]);
            found_local_unit = true;
            break;
        }
        pos_local = (pos_local + 1) % policia_ha->tamanho;
        if (pos_local == inicio_pos_local) {
            break; // Loop completo
        }
    }

    if (found_local_unit && policia_ha->itens[pos_local]->viaturas_disp > 0) {
        policia_ha->itens[pos_local]->viaturas_disp--;
        //printf("  - Policia ID %d (Bairro %d) despachada. Viaturas disponiveis: %d\n",
        //       policia_ha->itens[pos_local]->id, id_bairro_ocorrencia, policia_ha->itens[pos_local]->viaturas_disp);
        return true;
    }

    // Se n�o encontrou ou n�o tem viaturas no bairro, busca em qualquer outra pol�cia
    for (int i = 0; i < policia_ha->tamanho; i++) {
        if (policia_ha->itens[i] != NULL && policia_ha->itens[i]->viaturas_disp > 0) {
             // Verifica se n�o � a pr�pria unidade que j� foi tentada e falhou
             // e se realmente � uma unidade diferente para evitar loop ou dupla checagem.
             if (policia_ha->itens[i]->id != id_policia_bairro || !found_local_unit) {
                policia_ha->itens[i]->viaturas_disp--;
                printf("  - Policia ID %d (de outro bairro) despachada. Viaturas disponiveis: %d\n",
                       policia_ha->itens[i]->id, policia_ha->itens[i]->viaturas_disp);
                return true;
             }
        }
    }
    printf("  - Nenhuma viatura da policia disponivel.\n");
    return false;
}

/*
*---Fun��o para buscar e despachar uma unidade de bombeiro--
* Recebe: A tabela hash do bombeiro, o ID do bairro da ocorr�ncia
* Retorna: true se uma unidade foi despachada, false caso contr�rio
*
*/
bool despacha_bombeiro(Bombeiro_Hash *bombeiro_ha, int id_bairro_ocorrencia){
    if (bombeiro_ha == NULL) return false;

    // Tenta encontrar o bombeiro do bairro da ocorr�ncia primeiro
    int id_bombeiro_bairro = (id_bairro_ocorrencia / 1000) * 1000 + (id_bairro_ocorrencia % 1000) * 10 + 93;
    // id_bombeiro_bairro = id_bairro_ocorrencia * 100 + 93; -> ISSO NAO EH CERTO.

    Bombeiro bombeiro_local;
    int pos_local = bombeiro_chave_divisao(id_bombeiro_bairro, bombeiro_ha->tamanho);
    int inicio_pos_local = pos_local;
    bool found_local_unit = false;

    while (bombeiro_ha->itens[pos_local] != NULL) {
        if (bombeiro_ha->itens[pos_local]->id == id_bombeiro_bairro) {
            bombeiro_local = *(bombeiro_ha->itens[pos_local]);
            found_local_unit = true;
            break;
        }
        pos_local = (pos_local + 1) % bombeiro_ha->tamanho;
        if (pos_local == inicio_pos_local) {
            break;
        }
    }

    if (found_local_unit && bombeiro_ha->itens[pos_local]->caminhoes_disp > 0) {
        bombeiro_ha->itens[pos_local]->caminhoes_disp--;
        //printf("  - Bombeiro ID %d (Bairro %d) despachado. Caminhoes disponiveis: %d\n",
        //       bombeiro_ha->itens[pos_local]->id, id_bairro_ocorrencia, bombeiro_ha->itens[pos_local]->caminhoes_disp);
        return true;
    }

    // Se n�o encontrou ou n�o tem caminh�es no bairro, busca em qualquer outro bombeiro
    for (int i = 0; i < bombeiro_ha->tamanho; i++) {
        if (bombeiro_ha->itens[i] != NULL && bombeiro_ha->itens[i]->caminhoes_disp > 0) {
            if (bombeiro_ha->itens[i]->id != id_bombeiro_bairro || !found_local_unit) {
                bombeiro_ha->itens[i]->caminhoes_disp--;
                printf("  - Bombeiro ID %d (de outro bairro) despachado. Caminhoes disponiveis: %d\n",
                       bombeiro_ha->itens[i]->id, bombeiro_ha->itens[i]->caminhoes_disp);
                return true;
            }
        }
    }
    printf("  - Nenhum caminhao do bombeiro disponivel.\n");
    return false;
}

/*
*---Fun��o para buscar e despachar uma unidade de hospital--
* Recebe: A tabela hash do hospital, o ID do bairro da ocorr�ncia
* Retorna: true se uma unidade foi despachada, false caso contr�rio
*
*/
bool despacha_hospital(Hospital_Hash *hospital_ha, int id_bairro_ocorrencia){
    if (hospital_ha == NULL) return false;

    // Tenta encontrar o hospital do bairro da ocorr�ncia primeiro
    int id_hospital_bairro = (id_bairro_ocorrencia / 1000) * 1000 + (id_bairro_ocorrencia % 1000) * 10 + 95;
    // id_hospital_bairro = id_bairro_ocorrencia * 100 + 95; -> ISSO NAO EH CERTO.

    Hospital hospital_local;
    int pos_local = hospital_chave_divisao(id_hospital_bairro, hospital_ha->tamanho);
    int inicio_pos_local = pos_local;
    bool found_local_unit = false;

    while (hospital_ha->itens[pos_local] != NULL) {
        if (hospital_ha->itens[pos_local]->id == id_hospital_bairro) {
            hospital_local = *(hospital_ha->itens[pos_local]);
            found_local_unit = true;
            break;
        }
        pos_local = (pos_local + 1) % hospital_ha->tamanho;
        if (pos_local == inicio_pos_local) {
            break;
        }
    }

    if (found_local_unit && hospital_ha->itens[pos_local]->ambulancias_disp > 0) {
        hospital_ha->itens[pos_local]->ambulancias_disp--;
        //printf("  - Hospital ID %d (Bairro %d) despachado. Ambulancias disponiveis: %d\n",
        //       hospital_ha->itens[pos_local]->id, id_bairro_ocorrencia, hospital_ha->itens[pos_local]->ambulancias_disp);
        return true;
    }

    // Se n�o encontrou ou n�o tem ambul�ncias no bairro, busca em qualquer outro hospital
    for (int i = 0; i < hospital_ha->tamanho; i++) {
        if (hospital_ha->itens[i] != NULL && hospital_ha->itens[i]->ambulancias_disp > 0) {
            if (hospital_ha->itens[i]->id != id_hospital_bairro || !found_local_unit) {
                hospital_ha->itens[i]->ambulancias_disp--;
                printf("  - Hospital ID %d (de outro bairro) despachado. Ambulancias disponiveis: %d\n",
                       hospital_ha->itens[i]->id, hospital_ha->itens[i]->ambulancias_disp);
                return true;
            }
        }
    }
    printf("  - Nenhuma ambulancia do hospital disponivel.\n");
    return false;
}


/*
*---Fun��o para simular o despacho de servi�os--
* Recebe: A ocorr�ncia a ser despachada e as tabelas hash das unidades de servi�o
* Retorna: void
*
*/
void despacha_servicos(Ocorrencia *ocorrencia, Policia_Hash *policia_ha, Bombeiro_Hash *bombeiro_ha, Hospital_Hash *hospital_ha){
    printf("Despachando servicos para ocorrencia ID %d (Tipo: %s, Prioridade: %d, Bairro: %s):\n",
           ocorrencia->id, ocorrencia->tipo, ocorrencia->prioridade,
           (ocorrencia->bairro != NULL) ? ocorrencia->bairro->nome : "N/A");

    bool policia_despachada = false;
    bool bombeiro_despachado = false;
    bool hospital_despachado = false;

    if (ocorrencia->servico[0]){
        policia_despachada = despacha_policia(policia_ha, ocorrencia->bairro->id);
    }
    if (ocorrencia->servico[1]){
        bombeiro_despachado = despacha_bombeiro(bombeiro_ha, ocorrencia->bairro->id);
    }
    if (ocorrencia->servico[2]){
        hospital_despachado = despacha_hospital(hospital_ha, ocorrencia->bairro->id);
    }

    if (!policia_despachada && ocorrencia->servico[0]) {
        printf("    -> Nenhum servico de Policia foi despachado para esta ocorrencia.\n");
    }
    if (!bombeiro_despachado && ocorrencia->servico[1]) {
        printf("    -> Nenhum servico de Bombeiro foi despachado para esta ocorrencia.\n");
    }
    if (!hospital_despachado && ocorrencia->servico[2]) {
        printf("    -> Nenhum servico de Hospital foi despachado para esta ocorrencia.\n");
    }
}

/*
*---Fun��o para liberar a pilha --
* Recebe: Um ponteiro para a ocorr�ncia atendida e o ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
void free_ocorrencia(Ocorrencia *ocorr) {
    if (ocorr == NULL) return;
    free(ocorr->tipo); // Assuming 'tipo' is dynamically allocated
    // Free other dynamically allocated members if any
    free(ocorr);
}

/*
*---Fun��o para inicializar a pilha de ocorr�ncias --
* Recebe: Um ponteiro para a ocorr�ncia atendida e o ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
PilhaRelatorio* cria_pilha_relatorio() {
    PilhaRelatorio *pilha = (PilhaRelatorio*) malloc(sizeof(PilhaRelatorio));
    confere_aloc(pilha);
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

/*
*---Fun��o para adicionar uma ocorr�ncia atendida ao relat�rio--
* Recebe: Um ponteiro para a ocorr�ncia atendida e o ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
void push_pilha_relatorio(PilhaRelatorio *pilha, Ocorrencia *ocorrencia) {
    if (pilha == NULL) {
        printf("ERRO: Pilha n�o inicializada.\n");
        return;
    }
    NoPilha *novo_no = (NoPilha*) malloc(sizeof(NoPilha));
    confere_aloc(novo_no);

    novo_no->ocorrencia = ocorrencia; // Armazena o ponteiro para a ocorr�ncia
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho++;
}

/*
*---Fun��o para adicionar uma ocorr�ncia atendida ao relat�rio--
* Recebe: Um ponteiro para a ocorr�ncia atendida e o ponteiro para o in�cio da lista de relat�rio
* Retorna: O novo in�cio da lista (pode ser o mesmo ou o novo n�)
*
*/
Ocorrencia* pop_pilha_relatorio(PilhaRelatorio *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL; // Pilha vazia ou n�o inicializada
    }
    NoPilha *no_removido = pilha->topo;
    Ocorrencia *ocorrencia = no_removido->ocorrencia; // Pega o ponteiro da ocorr�ncia
    pilha->topo = no_removido->prox;
    free(no_removido); // Libera apenas o n� da pilha
    pilha->tamanho--;
    return ocorrencia; // Retorna o ponteiro da ocorr�ncia
}

/*
*---Fun��o para imprimir o relat�rio final da simula��o--
* Recebe: O ponteiro para o in�cio da lista de relat�rio
* Retorna: void
*
*/
void imprime_pilha_relatorio(PilhaRelatorio *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Pilha de ocorrencias do relatorio esta vazia.\n");
        return;
    }
    printf("\n---------- RELATORIO DE OCORRENCIAS ATENDIDAS (Pilha - Ultima -> Primeira) ----------\n");
    NoPilha *atual = pilha->topo;
    int count = pilha->tamanho; // Come�a a contagem do topo para baixo
    while (atual != NULL) {
        printf("\nOcorrencia #%d (ID: %d):\n", count--, atual->ocorrencia->id);
        exibir_ocorrencia_especifica(atual->ocorrencia); // Exibe a ocorr�ncia apontada
        atual = atual->prox;
    }
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Total de ocorrencias atendidas: %d\n", pilha->tamanho);
}

/*
*---Fun��o para liberar a mem�ria alocada para o relat�rio--
* Recebe: O ponteiro para o in�cio da lista de relat�rio
* Retorna: void
*
*/
void free_pilha_relatorio(PilhaRelatorio *pilha) {
    if (pilha == NULL) return;
    NoPilha *atual = pilha->topo;
    NoPilha *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        // IMPORTANTE: N�o libera atual->ocorrencia, pois o programa principal ser� respons�vel por isso
        free(atual); // Libera apenas o n� da pilha
        atual = proximo;
    }
    free(pilha); // Libera a estrutura descritora da pilha
}
