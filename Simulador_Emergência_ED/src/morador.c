#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/ocorrencias.h"
#include "../include/lista.h"

#define TAMANHO_TABELA 701 // Um número primo ideal para ~520 itens

// --- FUNÇÕES PRIVADAS ---

int morador_chave_divisao(long long int cpf) {
    return cpf % TAMANHO_TABELA;
}

// --- FUNÇÕES PÚBLICAS ---

Morador_Hash* cria_hash_morador(int tamanho) {
    Morador_Hash* ha = (Morador_Hash*) malloc(sizeof(Morador_Hash));
    if (ha != NULL) {
        ha->tamanho = tamanho;
        ha->itens = (Morador**) malloc(tamanho * sizeof(Morador*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (int i = 0; i < ha->tamanho; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

void morador_libera_hash(Morador_Hash *ha) {
    if (ha != NULL) {
        for (int i = 0; i < ha->tamanho; i++) {
            Morador *atual = ha->itens[i];
            while (atual != NULL) {
                Morador *temp = atual;
                atual = atual->proximo;
                for (int j = 0; j < temp->num_ocorrencias; j++) {
                    if (temp->ocorrencias[j] != NULL) free(temp->ocorrencias[j]);
                }
                free(temp);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

int morador_insere_hash_encadeamento(Morador_Hash *ha, Morador morador) {
    if (ha == NULL) return 0;

    Morador *novo = (Morador*) malloc(sizeof(Morador));
    if (novo == NULL) return 0;

    *novo = morador;
    novo->proximo = NULL;

    int pos = morador_chave_divisao(morador.cpf);

    novo->proximo = ha->itens[pos];
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

Morador* morador_busca_hash_encadeamento(Morador_Hash* ha, long long int cpf) {
    if (ha == NULL) return NULL;

    int pos = morador_chave_divisao(cpf);
    Morador *atual = ha->itens[pos];
    while (atual != NULL) {
        if (atual->cpf == cpf) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/*
*---Função que preenche as informações dos moradores a partir de um arquivo .txt--
*
*   Lê o arquivo "moradores.txt" que deve estar no formato: CPF,Nome
*
*   Retorna: Ponteiro para a tabela preenchida ou NULL em caso de erro.
*/
Morador_Hash* preenche_morador() {
    // 1. Cria a estrutura da tabela hash
    Morador_Hash *ha = cria_hash_morador(TAMANHO_TABELA);
    if (ha == NULL) {
        perror("Erro ao criar a tabela hash");
        return NULL;
    }

    // 2. Abre o arquivo de dados
    FILE *arquivo = fopen("moradores.txt", "r");
    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo 'moradores.txt'. Verifique se ele existe no diretorio do executavel.");
        free(ha); // Libera a hash criada se o arquivo não puder ser aberto
        return NULL;
    }

    char linha[256]; // Buffer para ler cada linha do arquivo
    int linha_num = 0;

    // 3. Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha_num++;
        Morador morador_temp;

        // Separa a linha em CPF e Nome usando a vírgula como delimitador
        char *token_cpf = strtok(linha, ",");
        char *token_nome = strtok(NULL, "\n"); // Pega o resto até a quebra de linha

        if (token_cpf && token_nome) {
            // Inicializa o morador com os dados do arquivo
            morador_temp.cpf = atoll(token_cpf); // atoll converte string para long long
            strcpy(morador_temp.nome, token_nome);

            // Inicializa os outros campos
            morador_temp.num_ocorrencias = 0;
            for (int i = 0; i < 50; i++) {
                morador_temp.ocorrencias[i] = NULL;
            }
            morador_temp.proximo = NULL;

            // Insere o morador na tabela hash
            morador_insere_hash_encadeamento(ha, morador_temp);

        } else {
            fprintf(stderr, "Aviso: Linha %d do arquivo 'moradores.txt' esta mal formatada e foi ignorada.\n", linha_num);
        }
    }

    // 4. Fecha o arquivo e retorna a tabela preenchida
    fclose(arquivo);
    printf("Carga de dados finalizada. Total de %d moradores carregados do arquivo.\n", ha->qtd);
    return ha;
}

/*
* As funções abaixo permanecem como na versão anterior, pois sua lógica não depende
* de como os dados foram carregados, apenas da estrutura da tabela.
*/

Morador* morador_aleatorio(Morador_Hash *ha) {
    if (ha == NULL || ha->qtd == 0) return NULL;
    int pos_aleatoria;
    do {
        pos_aleatoria = rand() % ha->tamanho;
    } while (ha->itens[pos_aleatoria] == NULL);
    return ha->itens[pos_aleatoria];
}

void morador_atribui_relatorio_final(Morador_Hash *ha, ListaLigadaRelatorio *relatorio) {
    if (ha == NULL || relatorio == NULL || relatorio->cabeca == NULL) {
        return; // Nada a fazer
    }

    printf("\nAtribuindo historico de ocorrencias aos moradores...\n");

    NoLista *no_atual = relatorio->cabeca;
    while (no_atual != NULL) {
        Ocorrencia *ocorrencia_original = no_atual->ocorrencia;

        // Verifica se a ocorrência tem um morador associado
        if (ocorrencia_original->morador != NULL) {
            // 1. Pega o CPF do morador da ocorrência original.
            long long int cpf_alvo = ocorrencia_original -> morador -> cpf;

            // 2. USA A FUNÇÃO DE BUSCA para encontrar o ponteiro para o morador
            //    original e definitivo que está na tabela hash.
            Morador *morador_na_hash = morador_busca_hash_encadeamento(ha, cpf_alvo);

            // 3. Garante que o morador foi encontrado na tabela.
            if (morador_na_hash != NULL) {
                // Verifica se há espaço no histórico do morador.
                if (morador_na_hash->num_ocorrencias < 50) {
                    // Aloca memória para a CÓPIA DEFINITIVA da ocorrência.
                    Ocorrencia *copia_para_historico = (Ocorrencia*) malloc(sizeof(Ocorrencia));
                    if (copia_para_historico != NULL) {
                        // Copia os dados finais da ocorrência.
                        *copia_para_historico = *ocorrencia_original;

                        // Adiciona a cópia ao histórico do morador encontrado na hash.
                        int indice = morador_na_hash->num_ocorrencias;
                        morador_na_hash->ocorrencias[indice] = copia_para_historico;
                        morador_na_hash->num_ocorrencias++;
                    }
                }
            }
        }
        no_atual = no_atual->prox;
    }
    printf("Historico de ocorrencias atribuido com sucesso.\n");
}

void exibir_morador_especifico(Morador *morador) {
    if (morador == NULL) {
        printf("Erro: Morador nao existe ou ponteiro nulo.\n");
        return;
    }
    printf("\nNome: %s\n", morador->nome);
    printf("CPF: %lld\n", morador->cpf);
    if (morador -> num_ocorrencias == 0) {
        printf("Nao ha ocorrencias para este morador.\n");
    } else {
        printf("Ocorrencias (%d):\n", morador->num_ocorrencias);
        for (int j = 0; j < morador->num_ocorrencias; j++) {
            printf("\n--- Ocorrencia %d ---\n", j + 1);
            exibir_ocorrencia_especifica(morador->ocorrencias[j]);
        }
    }
}

void morador_exibir(Morador_Hash *ha) {
    if (ha == NULL) {
        printf("Erro: Tabela hash de morador nao inicializada.\n");
        return;
    }
    printf("\nExibindo todos os %d moradores cadastrados...\n", ha->qtd);
    for (int i = 0; i < ha->tamanho; i++) {
        Morador *atual = ha->itens[i];
        while (atual != NULL) {
            printf("\n==============================================================\n");
            exibir_morador_especifico(atual);
            atual = atual->proximo;
        }
    }
}
