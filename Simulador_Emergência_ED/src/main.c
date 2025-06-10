#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // For srand, time, and ctime/strftime
#include <windows.h> // For Sleep (on Windows), if needed
#include <locale.h>  // For setlocale

#include "../include/bairro.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"
#include "../include/ocorrencias.h" // Already includes morador.h
#include "../include/fila_de_ocorrencias.h"


int main() {
    // Configura o locale para exibir caracteres especiais (acentos, cedilhas)
    setlocale(LC_ALL, "");

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- SIMULACAO DE SISTEMA DE EMERGENCIA ---\n");

    // 1. Preencher as tabelas hash de bairros, polícia, bombeiro e hospitais
    printf("\nInicializando bases de dados...\n");
    Bairros_Hash *bairros = preenche_bairros();
    Policia_Hash *policias = preenche_policia();
    Bombeiro_Hash *bombeiros = preenche_bombeiro();
    Hospital_Hash *hospitais = preenche_hospital();

    if (!bairros || !policias || !bombeiros || !hospitais) {
        printf("Erro ao inicializar uma ou mais bases de dados. Encerrando.\n");
        return 1;
    }
    printf("Bases de dados inicializadas com sucesso!\n");

    //Exibir bairros carregados para verificação
    bairros_exibir(bairros);

    // 2. Criar a fila de ocorrências
    printf("\nCriando fila de ocorrencias...\n");
    Descritor *fila_ocorrencias = cria_fila();
    printf("Fila de ocorrencias criada!\n");

    // Lista para armazenar ocorrências atendidas para o relatório final
    RelatorioOcorrencia *relatorio_final = NULL;

    printf("\n--- INICIANDO SIMULACAO DE EMERGENCIAS ---\n");
    int ciclo = 1;
    while (ciclo <= 10) { // Simula 10 ciclos de tempo
        printf("\n========== CICLO DE TEMPO: %d ==========\n", ciclo);

        // 3. Gerar e enfileirar novas ocorrências aleatoriamente
        printf("\nGerando novas ocorrencias...\n");
        enfileirando(fila_ocorrencias, bairros);
        exibe_fila(fila_ocorrencias);

        // 4. Processar ocorrências na fila (despachar serviços)
        printf("\nProcessando ocorrencias na fila...\n");
        while (fila_ocorrencias->tamanho > 0) {
            Ocorrencia *ocorrencia_atual = remove_da_fila(fila_ocorrencias);
            if (ocorrencia_atual != NULL) {
                // Despacha os serviços para a ocorrência
                despacha_servicos(ocorrencia_atual, policias, bombeiros, hospitais);

                // Adiciona a ocorrência (com os tempos de registro e atendimento) ao relatório
                relatorio_final = adiciona_ao_relatorio(ocorrencia_atual, relatorio_final);

                // IMPORTANTE: Liberar a memória da ocorrência_atual e seu morador após adicionar ao relatório.
                // A copia da ocorrência é feita para o relatório, então o original pode ser liberado.
                if (ocorrencia_atual->morador) {
                    free(ocorrencia_atual->morador);
                }
                free(ocorrencia_atual);
            }
            // Pequena pausa para simular o tempo de processamento
            // sleep(gera_tempo()); // Descomente para ver a simulação mais lenta
        }
        printf("\nFila de ocorrencias esvaziada para este ciclo.\n");

        // Simular o retorno de algumas viaturas/ambulâncias ao final do ciclo
        // Em um sistema real, isso seria mais complexo e baseado em eventos.
        // Aqui, vamos apenas restaurar a disponibilidade de todas as unidades.
        printf("\nSimulando retorno de unidades...\n");
        for (int i = 0; i < policias->tamanho; i++) {
            if (policias->itens[i] != NULL) {
                policias->itens[i]->viaturas_disp = policias->itens[i]->viaturas; // Reinicia para full
                policias->itens[i]->disponivel = true;
            }
        }
        for (int i = 0; i < bombeiros->tamanho; i++) {
            if (bombeiros->itens[i] != NULL) {
                bombeiros->itens[i]->caminhoes_disp = bombeiros->itens[i]->caminhoes; // Reinicia para full
                bombeiros->itens[i]->disponivel = true;
            }
        }
        for (int i = 0; i < hospitais->tamanho; i++) {
            if (hospitais->itens[i] != NULL) {
                hospitais->itens[i]->ambulancias_disp = hospitais->itens[i]->ambulancias; // Reinicia para full
                hospitais->itens[i]->disponivel = true;
            }
        }
        printf("Unidades de servico restauradas para o proximo ciclo.\n");

        printf("\nSimulacao em pausa para o proximo ciclo...\n");
        sleep(2); // Pausa de 2 segundos entre ciclos
        ciclo++;
    }

    printf("\n--- SIMULACAO ENCERRADA ---\n");

    // 5. Imprimir o relatório final
    imprime_relatorio(relatorio_final);

    // 6. Liberar toda a memória alocada
    printf("\nLiberando memoria alocada...\n");
    free_fila(fila_ocorrencias); // Libera a fila (que deve estar vazia ao final)
    free_relatorio(relatorio_final); // Libera a lista do relatório
    bairro_libera_hash(bairros);
    policia_libera_hash(policias);
    bombeiro_libera_hash(bombeiros);
    hospital_libera_hash(hospitais);
    printf("Memoria liberada com sucesso!\n");

    return 0;
}
