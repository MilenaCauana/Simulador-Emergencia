#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#include "../include/fila_de_ocorrencias.h"
#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"


int main() {
    // Configura o locale para exibir caracteres especiais (acentos, cedilhas)
    setlocale(LC_ALL, "");

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- SIMULACAO DE SISTEMA DE EMERGENCIA ---\n");

    // 1. Preencher as tabelas hash de bairros, morador, polícia, bombeiro, hospitais e moradores
    printf("\nInicializando bases de dados...\n");
    Bairros_Hash *bairros = preenche_bairros();
    Morador_Hash *moradores = preenche_morador();
    Policia_Hash *policias = preenche_policia();
    Bombeiro_Hash *bombeiros = preenche_bombeiro();
    Hospital_Hash *hospitais = preenche_hospital();

    if (!bairros || !moradores || !policias || !bombeiros || !hospitais) {
        printf("Erro ao inicializar uma ou mais bases de dados. Encerrando.\n");
        return 1;
    }
    printf("Bases de dados inicializadas com sucesso!\n");

    //Exibindo bairros e moradores para conferência
    bairros_exibir(bairros);
    morador_exibir(moradores);

    printf("\nCriando fila de ocorrencias...\n");
    Descritor *fila_ocorrencias = cria_fila();
    printf("Fila de ocorrencias criada!\n");

    // Pilha para armazenar ocorrências atendidas para o relatório final
    PilhaRelatorio *relatorio_final = cria_pilha_relatorio(); // Inicializa a pilha
    if (!relatorio_final) {
        printf("Erro ao criar a pilha de relatorio. Encerrando.\n");
        // Liberar o que já foi alocado antes de sair
        free_fila(fila_ocorrencias);
        bairro_libera_hash(bairros);
        policia_libera_hash(policias);
        bombeiro_libera_hash(bombeiros);
        hospital_libera_hash(hospitais);
        morador_libera_hash(moradores);
        return 1;
    }


    printf("\n--- INICIANDO SIMULACAO DE EMERGENCIAS (1 Dia = 144 ciclos de 10 min) ---\n");
    int ciclo = 1;
    int total_ciclos_dia = 144; // 24 horas * 60 minutos/hora / 10 minutos/ciclo = 144 ciclos

    while (ciclo <= total_ciclos_dia) { // Simula 144 ciclos de tempo (equivalente a 1 dia)
        printf("\n========== CICLO DE TEMPO: %d (Hora: %02d:%02d) ==========\n", ciclo, (ciclo - 1) * 10 / 60, (ciclo - 1) * 10 % 60);

        // 3. Gerar e enfileirar novas ocorrências aleatoriamente
        printf("Gerando %d novas ocorrencias...\n", gera_qtd_no()); // Chama gera_qtd_no para informar a quantidade
        // Passa o hash de moradores para cria_ocorrencia via enfileirando
        enfileirando(fila_ocorrencias, bairros, moradores);
        exibe_fila(fila_ocorrencias);

        // 4. Processar ocorrências na fila (despachar serviços)
        printf("\nProcessando ocorrencias na fila...\n");
        while (fila_ocorrencias->tamanho > 0) {
            Ocorrencia *ocorrencia_atual = remove_da_fila(fila_ocorrencias);
            if (ocorrencia_atual != NULL) {
                // Define o tempo de atendimento com base no ciclo atual
                ocorrencia_atual->tempo_atendimento = ciclo;

                // Despacha os serviços para a ocorrência
                despacha_servicos(ocorrencia_atual, policias, bombeiros, hospitais);

                // Adiciona a ocorrência (com os tempos de registro e atendimento) ao relatório
                // A função push_pilha_relatorio apenas empilha o ponteiro da ocorrência,
                // a ocorrência será liberada no final, após o relatório ser impresso,
                // ou se for movida para o histórico do morador.
                push_pilha_relatorio(relatorio_final, ocorrencia_atual);

                // IMPORTANTE: Não libera ocorrencia_atual aqui. Ela será liberada
                // por 'free_ocorrencia' quando for movida para o histórico do morador
                // ou quando o relatório final for liberado (se a ocorrência não tiver sido movida).
                // A lógica de liberação da ocorrência deve ser centralizada para evitar double free ou memory leak.
                // Considerando o seu `free_fila` e `free_pilha_relatorio` que não liberam a Ocorrencia*,
                // a liberação da Ocorrencia* em si deve ser feita na main.c, provavelmente
                // após processar o relatório ou o histórico do morador.
            }
        }
        printf("Fila de ocorrencias esvaziada para este ciclo.\n");

        // Unidades de serviço retornam (são redefinidas para o total disponível para este ciclo)
        printf("Restaurando a disponibilidade total das unidades para o proximo ciclo...\n");
        for (int i = 0; i < policias->tamanho; i++) {
            if (policias->itens[i] != NULL) {
                policias->itens[i]->viaturas_disp = policias->itens[i]->viaturas;
            }
        }
        for (int i = 0; i < bombeiros->tamanho; i++) {
            if (bombeiros->itens[i] != NULL) {
                bombeiros->itens[i]->caminhoes_disp = bombeiros->itens[i]->caminhoes;
            }
        }
        for (int i = 0; i < hospitais->tamanho; i++) {
            if (hospitais->itens[i] != NULL) {
                hospitais->itens[i]->ambulancias_disp = hospitais->itens[i]->ambulancias;
            }
        }
        printf("Disponibilidade das unidades restaurada.\n");

        ciclo++;
    }

    printf("\n--- SIMULACAO ENCERRADA ---\n");

    // -- MENU --
    int opcao;
    do {
        printf("\n--- MENU DE CONSULTA POS-SIMULACAO ---\n");
        printf("Escolha uma opcao:\n");
        printf("1. Visualizar Moradores\n");
        printf("2. Buscar morador por CPF\n");
        printf("3. Visualizar Bairros\n");
        printf("4. Buscar bairro por ID\n");
        printf("5. Relatório das Ocorrências Atendidas\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        long long int cpf;
        int id;
        Morador *morador_encontrado; // Variável para armazenar o morador encontrado
        Bairros *bairro_encontrado; // Variável para armazenar o bairro encontrado

        switch (opcao) {
            case 1:
                morador_exibir(moradores);
                break;
            case 2:
                printf("Digite o CPF do morador: ");
                scanf("%lld", &cpf);
                getchar(); // Limpar o buffer
                morador_encontrado = morador_busca_hash_sem_colisao(moradores, cpf);
                exibir_morador_especifico(morador_encontrado);
                break;
            case 3:
                bairros_exibir(bairros);
                break;
            case 4:
                printf("Digite o ID do bairro: ");
                scanf("%d", &id);
                getchar(); // Limpar o buffer
                bairro_encontrado = bairro_busca_hash_sem_colisao(bairros, id);
                exibir_bairro_especifico(bairro_encontrado);
                break;
            case 5:
                printf("\n--- RELATORIO FINAL DAS OCORRENCIAS ATENDIDAS ---\n");
                imprime_pilha_relatorio(relatorio_final);
                break;
            case 0:
                printf("Saindo do menu de consulta.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // 7. Liberar toda a memória alocada
    printf("\nLiberando memoria alocada...\n");
    free_fila(fila_ocorrencias); // Libera a fila (que deve estar vazia ao final)

    // Libera as ocorrências que estão na pilha do relatório, e depois a própria pilha.
    // Isso é crucial para evitar memory leaks das ocorrências.
    Ocorrencia *temp_ocorrencia;
    while ((temp_ocorrencia = pop_pilha_relatorio(relatorio_final)) != NULL) {
        free_ocorrencia(temp_ocorrencia); // Assuming you have a free_ocorrencia function in ocorrencias.c
    }
    free_pilha_relatorio(relatorio_final); // Libera a estrutura da pilha

    bairro_libera_hash(bairros);
    policia_libera_hash(policias);
    bombeiro_libera_hash(bombeiros);
    hospital_libera_hash(hospitais);
    morador_libera_hash(moradores); // Libera o hash de moradores e seus históricos de ocorrências

    printf("Memoria liberada com sucesso!\n");

    return 0;
}
