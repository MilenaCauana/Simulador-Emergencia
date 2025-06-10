// fila_de_ocorrencia.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // For srand and time, and gmtime/localtime/strftime
#include <string.h> // For strftime

#include "../include/fila_de_ocorrencias.h"
#include "../include/ocorrencias.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"
#include "../include/bairro.h" // Necessário para cria_ocorrencia

//------ ºº FUNÇÕES DA FILA ºº ------

/*
*---Função de criação e inicialização da fila--
* Recebe: void
* Retorna: Um descritor da fila inicializado
*
*/
Descritor* cria_fila() {
    Descritor *D = (Descritor*) malloc(sizeof(Descritor));
    if (D == NULL) {
        printf("ERRO AO ALOCAR MEMORIA PARA O DESCRITOR DA FILA!\n");
        exit(EXIT_FAILURE);
    }
    D->inicio = NULL;
    D->fim = NULL;
    D->tamanho = 0;
    return D;
}

/*
*---Função para verificar alocação de memória--
* Recebe: Um ponteiro genérico
* Retorna: void (encerra o programa se a alocação falhar)
*
*/
void confere_aloc(void *ptr) {
    if (ptr == NULL) {
        printf("ERRO AO ALOCAR MEMORIA!\n");
        exit(EXIT_FAILURE);
    }
}

/*
*---Função para criar um novo nó da fila com uma ocorrência--
* Recebe: Um ponteiro para a tabela hash de bairros (para criar a ocorrência)
* Retorna: Um ponteiro para o nó recém-criado
*
*/
No* cria_no(Bairros_Hash *ha) {
    No *novo = (No*) malloc(sizeof(No));
    confere_aloc(novo);
    novo->ocorrencia = cria_ocorrencia(ha); // Cria a ocorrência dentro do nó
    novo->prox = NULL;
    return novo;
}

/*
*---Função para adicionar uma ocorrência na fila de prioridade--
* A inserção mantém a fila ordenada por prioridade (maior prioridade primeiro).
* Recebe: Um ponteiro para o nó a ser adicionado e um ponteiro para o descritor da fila
* Retorna: void
*
*/
void adiciona_na_fila_prioridade(No* novo, Descritor *D) {
    if (D->inicio == NULL || novo->ocorrencia->prioridade > D->inicio->ocorrencia->prioridade) {
        // Insere no início se a fila estiver vazia ou a nova ocorrência tiver maior prioridade
        novo->prox = D->inicio;
        D->inicio = novo;
        if (D->fim == NULL) { // Se a fila estava vazia, o novo nó é também o fim
            D->fim = novo;
        }
    } else {
        // Procura a posição correta para inserção, mantendo a ordem de prioridade
        No *atual = D->inicio;
        while (atual->prox != NULL && novo->ocorrencia->prioridade <= atual->prox->ocorrencia->prioridade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
        if (novo->prox == NULL) { // Se inseriu no fim
            D->fim = novo;
        }
    }
    D->tamanho++;
    char buffer_registro[80];
    strftime(buffer_registro, 80, "%Y-%m-%d %H:%M:%S", localtime(&novo->ocorrencia->tempo_registro));
    printf("--> Ocorrencia '%s' (ID: %d, Prioridade: %d) registrada em %s e adicionada a fila.\n",
           novo->ocorrencia->tipo, novo->ocorrencia->id, novo->ocorrencia->prioridade, buffer_registro);
}


/*
*---Função para remover uma ocorrência do início da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: Um ponteiro para a ocorrência removida, ou NULL se a fila estiver vazia
*
*/
Ocorrencia* remove_da_fila(Descritor *D) {
    if (D->inicio == NULL) {
        return NULL; // Fila vazia
    }
    No *temp = D->inicio;
    Ocorrencia *ocorrencia_removida = temp->ocorrencia;
    D->inicio = D->inicio->prox;
    if (D->inicio == NULL) { // Se a fila ficou vazia
        D->fim = NULL;
    }
    free(temp);
    D->tamanho--;
    return ocorrencia_removida;
}

/*
*---Função para exibir as informações de uma ocorrência--
* Recebe: Um ponteiro para a ocorrência
* Retorna: void
*
*/
void exibe_ocorrencia(Ocorrencia *ocorrencia) {
    if (ocorrencia == NULL) {
        printf("Ocorrencia NULL.\n");
        return;
    }
    char buffer_registro[80];
    char buffer_atendimento[80];

    strftime(buffer_registro, 80, "%Y-%m-%d %H:%M:%S", localtime(&ocorrencia->tempo_registro));
    if (ocorrencia->tempo_atendimento > 0) {
        strftime(buffer_atendimento, 80, "%Y-%m-%d %H:%M:%S", localtime(&ocorrencia->tempo_atendimento));
    } else {
        strcpy(buffer_atendimento, "Nao atendida");
    }

    printf("\n------ Detalhes da Ocorrencia ------\n");
    printf("ID: %d\n", ocorrencia->id);
    printf("Tipo: %s\n", ocorrencia->tipo);
    printf("Prioridade: %d\n", ocorrencia->prioridade);
    printf("Registrada em: %s\n", buffer_registro);
    printf("Atendida em: %s\n", buffer_atendimento);
    if (ocorrencia->bairro) {
        printf("Bairro: %s (ID: %d)\n", ocorrencia->bairro->nome, ocorrencia->bairro->id);
    } else {
        printf("Bairro: N/A\n");
    }
    if (ocorrencia->morador) {
        printf("Morador: %s (CPF: %lld)\n", ocorrencia->morador->nome, ocorrencia->morador->cpf);
    } else {
        printf("Morador: N/A\n");
    }
    printf("Servicos Necessarios:\n");
    if (ocorrencia->servico[0]) printf("  - Policia\n");
    if (ocorrencia->servico[1]) printf("  - Bombeiro\n");
    if (ocorrencia->servico[2]) printf("  - Hospital\n");
    printf("------------------------------------\n");
}


/*
*---Função para exibir todos os itens da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void exibe_fila(Descritor *D) {
    if (D->inicio == NULL) {
        printf("A fila de ocorrencias esta vazia.\n");
        return;
    }
    printf("\n--- Conteudo da Fila de Ocorrencias (Prioridade: Maior primeiro) ---\n");
    No *atual = D->inicio;
    while (atual != NULL) {
        char buffer_registro[80];
        strftime(buffer_registro, 80, "%H:%M:%S", localtime(&atual->ocorrencia->tempo_registro));
        printf("ID: %d | Tipo: %s | Prioridade: %d | Bairro: %s | Registrada: %s\n",
               atual->ocorrencia->id,
               atual->ocorrencia->tipo,
               atual->ocorrencia->prioridade,
               atual->ocorrencia->bairro ? atual->ocorrencia->bairro->nome : "N/A",
               buffer_registro);
        atual = atual->prox;
    }
    printf("Tamanho da fila: %d\n", D->tamanho);
    printf("------------------------------------------------------------------\n");
}

/*
*---Função para liberar a memória da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void free_fila(Descritor* D) {
    if (D == NULL) return;
    No *atual = D->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        if (temp->ocorrencia) {
            if (temp->ocorrencia->morador) {
                 free(temp->ocorrencia->morador);
            }
            free(temp->ocorrencia);
        }
        free(temp);
    }
    free(D);
}

/*
*---Função para gerar um tempo aleatório (simulação de espera)--
* Recebe: void
* Retorna: inteiro (tempo em segundos)
*
*/
int gera_tempo() {
    return (rand() % 3) + 1; // Tempo entre 1 e 3 segundos
}

/*
*---Função para gerar uma quantidade aleatória de nós (ocorrências)--
* Recebe: void
* Retorna: inteiro (quantidade de ocorrências)
*
*/
int gera_qtd_no() {
    return (rand() % 3) + 1; // Gera entre 1 e 3 novas ocorrências
}

/*
*---Função para simular o enfileiramento de ocorrências--
* Recebe: Um ponteiro para o descritor da fila e a tabela hash de bairros
* Retorna: void
*
*/
void enfileirando(Descritor *D, Bairros_Hash *ha) {
    int num_novas_ocorrencias = gera_qtd_no();
    for (int i = 0; i < num_novas_ocorrencias; i++) {
        No *novo_no = cria_no(ha);
        adiciona_na_fila_prioridade(novo_no, D);
    }
    printf("\n%d novas ocorrencias foram adicionadas a fila.\n", num_novas_ocorrencias);
}

// Funções auxiliares para buscar e despachar unidades de serviço
// Adaptadas para a nova lógica de ID de bairro

/*
*---Função para buscar e despachar uma unidade de polícia--
* Recebe: A tabela hash da polícia, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_policia(Policia_Hash *policia_ha, int id_bairro_ocorrencia) {
    Policia *unidade_policia = NULL;
    int bairro_id_unidade;

    // 1. Tentar encontrar polícia no mesmo bairro da ocorrência
    for (int i = 0; i < policia_ha->tamanho; i++) {
        if (policia_ha->itens[i] != NULL) {
            bairro_id_unidade = policia_ha->itens[i]->id / 100; // Extrai os 4 primeiros dígitos
            if (bairro_id_unidade == id_bairro_ocorrencia &&
                policia_ha->itens[i]->disponivel && policia_ha->itens[i]->viaturas_disp > 0) {
                unidade_policia = policia_ha->itens[i];
                break;
            }
        }
    }

    // 2. Se não encontrou no mesmo bairro, procurar em qualquer outro bairro
    if (unidade_policia == NULL) {
        for (int i = 0; i < policia_ha->tamanho; i++) {
            if (policia_ha->itens[i] != NULL &&
                policia_ha->itens[i]->disponivel && policia_ha->itens[i]->viaturas_disp > 0) {
                unidade_policia = policia_ha->itens[i];
                break;
            }
        }
    }

    if (unidade_policia != NULL) {
        unidade_policia->viaturas_disp--;
        if (unidade_policia->viaturas_disp == 0) {
            unidade_policia->disponivel = false;
        }
        printf("--> Policia (ID: %d, Bairro: %d) despachada. Viaturas disponiveis restantes: %d.\n",
               unidade_policia->id, unidade_policia->id / 100, unidade_policia->viaturas_disp);
        return true;
    } else {
        printf("--> Nenhuma unidade de Policia disponivel para esta ocorrencia.\n");
        return false;
    }
}

/*
*---Função para buscar e despachar uma unidade de bombeiro--
* Recebe: A tabela hash do bombeiro, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_bombeiro(Bombeiro_Hash *bombeiro_ha, int id_bairro_ocorrencia) {
    Bombeiro *unidade_bombeiro = NULL;
    int bairro_id_unidade;

    // 1. Tentar encontrar bombeiro no mesmo bairro da ocorrência
    for (int i = 0; i < bombeiro_ha->tamanho; i++) {
        if (bombeiro_ha->itens[i] != NULL) {
            bairro_id_unidade = bombeiro_ha->itens[i]->id / 100; // Extrai os 4 primeiros dígitos
            if (bairro_id_unidade == id_bairro_ocorrencia &&
                bombeiro_ha->itens[i]->disponivel && bombeiro_ha->itens[i]->caminhoes_disp > 0) {
                unidade_bombeiro = bombeiro_ha->itens[i];
                break;
            }
        }
    }

    // 2. Se não encontrou no mesmo bairro, procurar em qualquer outro bairro
    if (unidade_bombeiro == NULL) {
        for (int i = 0; i < bombeiro_ha->tamanho; i++) {
            if (bombeiro_ha->itens[i] != NULL &&
                bombeiro_ha->itens[i]->disponivel && bombeiro_ha->itens[i]->caminhoes_disp > 0) {
                unidade_bombeiro = bombeiro_ha->itens[i];
                break;
            }
        }
    }

    if (unidade_bombeiro != NULL) {
        unidade_bombeiro->caminhoes_disp--;
        if (unidade_bombeiro->caminhoes_disp == 0) {
            unidade_bombeiro->disponivel = false;
        }
        printf("--> Bombeiro (ID: %d, Bairro: %d) despachado. Caminhoes disponiveis restantes: %d.\n",
               unidade_bombeiro->id, unidade_bombeiro->id / 100, unidade_bombeiro->caminhoes_disp);
        return true;
    } else {
        printf("--> Nenhuma unidade de Bombeiro disponivel para esta ocorrencia.\n");
        return false;
    }
}

/*
*---Função para buscar e despachar uma unidade de hospital--
* Recebe: A tabela hash do hospital, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_hospital(Hospital_Hash *hospital_ha, int id_bairro_ocorrencia) {
    Hospital *unidade_hospital = NULL;
    int bairro_id_unidade;

    // 1. Tentar encontrar hospital no mesmo bairro da ocorrência
    for (int i = 0; i < hospital_ha->tamanho; i++) {
        if (hospital_ha->itens[i] != NULL) {
            bairro_id_unidade = hospital_ha->itens[i]->id / 100; // Extrai os 4 primeiros dígitos
            if (bairro_id_unidade == id_bairro_ocorrencia &&
                hospital_ha->itens[i]->disponivel && hospital_ha->itens[i]->ambulancias_disp > 0) {
                unidade_hospital = hospital_ha->itens[i];
                break;
            }
        }
    }

    // 2. Se não encontrou no mesmo bairro, procurar em qualquer outro bairro
    if (unidade_hospital == NULL) {
        for (int i = 0; i < hospital_ha->tamanho; i++) {
            if (hospital_ha->itens[i] != NULL &&
                hospital_ha->itens[i]->disponivel && hospital_ha->itens[i]->ambulancias_disp > 0) {
                unidade_hospital = hospital_ha->itens[i];
                break;
            }
        }
    }

    if (unidade_hospital != NULL) {
        unidade_hospital->ambulancias_disp--;
        if (unidade_hospital->ambulancias_disp == 0) {
            unidade_hospital->disponivel = false;
        }
        printf("--> Hospital (ID: %d, Bairro: %d) despachado. Ambulancias disponiveis restantes: %d.\n",
               unidade_hospital->id, unidade_hospital->id / 100, unidade_hospital->ambulancias_disp);
        return true;
    } else {
        printf("--> Nenhuma unidade de Hospital disponivel para esta ocorrencia.\n");
        return false;
    }
}


/*
*---Função para simular o despacho de serviços--
* Recebe: A ocorrência a ser despachada e as tabelas hash das unidades de serviço
* Retorna: void
*
*/
void despacha_servicos(Ocorrencia *ocorrencia, Policia_Hash *policia_ha, Bombeiro_Hash *bombeiro_ha, Hospital_Hash *hospital_ha) {
    printf("\n------ DESPACHANDO SERVICOS PARA OCORRENCIA ID: %d (%s) ------\n", ocorrencia->id, ocorrencia->tipo);

    bool servico_despachado = false;
    int id_bairro_ocorrencia = ocorrencia->bairro ? ocorrencia->bairro->id : -1;

    // Polícia
    if (ocorrencia->servico[0]) {
        if (despacha_policia(policia_ha, id_bairro_ocorrencia)) {
            servico_despachado = true;
        }
    }

    // Bombeiro
    if (ocorrencia->servico[1]) {
        if (despacha_bombeiro(bombeiro_ha, id_bairro_ocorrencia)) {
            servico_despachado = true;
        }
    }

    // Hospital
    if (ocorrencia->servico[2]) {
        if (despacha_hospital(hospital_ha, id_bairro_ocorrencia)) {
            servico_despachado = true;
        }
    }

    if (servico_despachado) {
        ocorrencia->tempo_atendimento = time(NULL); // Marca o tempo de atendimento
        printf("Ocorrencia ID %d despachada com sucesso em %s.\n",
               ocorrencia->id, ctime(&ocorrencia->tempo_atendimento)); // ctime inclui nova linha
    } else {
        printf("Nenhum servico necessario ou disponivel para esta ocorrencia no momento.\n");
    }
    printf("------------------------------------------------------------------\n");
}

/*
*---Estrutura para armazenar ocorrências atendidas para o relatório--
*/
typedef struct relatorio_ocorrencia {
    Ocorrencia ocorrencia_copia; // Copia da ocorrencia para evitar ponteiros inválidos
    struct relatorio_ocorrencia *prox;
} RelatorioOcorrencia;

/*
*---Função para adicionar uma ocorrência atendida ao relatório--
* Recebe: Um ponteiro para a ocorrência atendida e o ponteiro para o início da lista de relatório
* Retorna: O novo início da lista (pode ser o mesmo ou o novo nó)
*
*/
RelatorioOcorrencia* adiciona_ao_relatorio(Ocorrencia *ocorr_atendida, RelatorioOcorrencia *lista_relatorio) {
    RelatorioOcorrencia *novo_relatorio = (RelatorioOcorrencia*) malloc(sizeof(RelatorioOcorrencia));
    confere_aloc(novo_relatorio);

    // Copia os dados da ocorrência (especialmente os campos de tempo)
    novo_relatorio->ocorrencia_copia = *ocorr_atendida;
    novo_relatorio->prox = lista_relatorio; // Adiciona no início para simplificar

    return novo_relatorio;
}

/*
*---Função para imprimir o relatório final da simulação--
* Recebe: O ponteiro para o início da lista de relatório
* Retorna: void
*
*/
void imprime_relatorio(RelatorioOcorrencia *lista_relatorio) {
    printf("\n\n=============== RELATORIO DA SIMULACAO ===============\n");
    if (lista_relatorio == NULL) {
        printf("Nenhuma ocorrencia foi atendida durante a simulacao.\n");
        return;
    }

    RelatorioOcorrencia *atual = lista_relatorio;
    char buffer_registro[80];
    char buffer_atendimento[80];
    double tempo_espera;

    while (atual != NULL) {
        strftime(buffer_registro, 80, "%Y-%m-%d %H:%M:%S", localtime(&atual->ocorrencia_copia.tempo_registro));
        if (atual->ocorrencia_copia.tempo_atendimento > 0) {
            strftime(buffer_atendimento, 80, "%Y-%m-%d %H:%M:%S", localtime(&atual->ocorrencia_copia.tempo_atendimento));
            tempo_espera = difftime(atual->ocorrencia_copia.tempo_atendimento, atual->ocorrencia_copia.tempo_registro);
        } else {
            strcpy(buffer_atendimento, "Nao atendida");
            tempo_espera = -1.0; // Indica que não foi atendida
        }

        printf("\n----------------------------------------------------\n");
        printf("ID da Ocorrencia: %d\n", atual->ocorrencia_copia.id);
        printf("Tipo: %s\n", atual->ocorrencia_copia.tipo);
        printf("Bairro: %s (ID: %d)\n", atual->ocorrencia_copia.bairro ? atual->ocorrencia_copia.bairro->nome : "N/A",
                                       atual->ocorrencia_copia.bairro ? atual->ocorrencia_copia.bairro->id : 0);
        printf("Registrada em: %s\n", buffer_registro);
        printf("Atendida em: %s\n", buffer_atendimento);
        if (tempo_espera >= 0) {
            printf("Tempo de espera (segundos): %.0f\n", tempo_espera);
        } else {
            printf("Tempo de espera: N/A (ocorrencia nao atendida)\n");
        }
        printf("----------------------------------------------------\n");

        atual = atual->prox;
    }
    printf("\n=============== FIM DO RELATORIO ===============\n");
}

/*
*---Função para liberar a memória alocada para o relatório--
* Recebe: O ponteiro para o início da lista de relatório
* Retorna: void
*
*/
void free_relatorio(RelatorioOcorrencia *lista_relatorio) {
    RelatorioOcorrencia *atual = lista_relatorio;
    while (atual != NULL) {
        RelatorioOcorrencia *temp = atual;
        atual = atual->prox;
        free(temp); // A ocorrencia_copia está dentro da struct, então não precisa de free separado
    }
}
