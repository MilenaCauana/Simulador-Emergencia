#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/policia.h"
#include "../include/bombeiro.h"
#include "../include/hospital.h"
#include "../include/arvore_avl.h"
#include "../include/lista.h"
#include "../include/arvore_binaria_busca.h"
#include "../include/lista_cruzada.h"

#define DIA 5

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    printf("--- SIMULACAO DE SISTEMA DE EMERGENCIA ---\n");

    //Preenchendo as tabelas hash de bairros, morador, polícia, bombeiro, hospitais e moradores
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

    // ---- Estruturas de dados ----

    // Fila para armazenar ocorrências atendidas para o relatório final
    ListaLigadaRelatorio *relatorio_final = cria_lista_relatorio(); // Inicializa a pilha
    if (relatorio_final == NULL) {
        printf("Erro ao criar a pilha de relatorio. Encerrando.\n");
        // Liberar o que já foi alocado antes de sair
        bairro_libera_hash(bairros);
        policia_libera_hash(policias);
        bombeiro_libera_hash(bombeiros);
        hospital_libera_hash(hospitais);
        morador_libera_hash(moradores);
        return 1;
    }

    //Fila para armazenar as ocorrências que estão sendo atendidas
    ListaLigadaRelatorio *em_atendimento = cria_lista_relatorio(); // Inicializa a pilha
    if (em_atendimento == NULL) {
        printf("Erro ao criar a fila de relatorio. Encerrando.\n");
        // Liberar o que já foi alocado antes de sair
        bairro_libera_hash(bairros);
        policia_libera_hash(policias);
        bombeiro_libera_hash(bombeiros);
        hospital_libera_hash(hospitais);
        morador_libera_hash(moradores);
        return 1;
    }

    //Criando Árvore AVL para prioridade
    AVL *arvoreAVL = criarArvoreAVL();

    printf("\n--- INICIANDO SIMULACAO DE EMERGENCIAS (1 Dia = 144 ciclos de 10 min) ---\n");
    int ciclo = 0;
    Ocorrencia *ocorrencia1, *ocorrencia2;

    while (ciclo <= DIA) {
        int hora = (ciclo * 10) /60;
        int min = (ciclo * 10) %60;

        printf("\n========== CICLO DE TEMPO: %d (Hora: %02d:%02d) ==========\n", ciclo, hora, min);

        //Gerar e enfileirar novas ocorrências
        int qtd_ocorr_ciclo = rand() % 3;

        while(qtd_ocorr_ciclo > 0){
            printf("Gerando nova ocorrencia...\n");
            Ocorrencia *ocorrencia = cria_ocorrencia(bairros, moradores, ciclo);


            printf(" \nOCORRÊNCIA CRIADA: \n");
            exibir_ocorrencia_especifica(ocorrencia);

            //Agora, adicionaremos na Árvore AVL de prioridade
            inserirOcorrenciaAVL(arvoreAVL, ocorrencia);

            qtd_ocorr_ciclo--;
        }


        printf("Ocorrência na lista árvore AVL.\n ");

         //Tentar despachar a ocorrência de maior prioridade ---
        if (arvoreAVL -> raiz != NULL) {

            //Conferimos a ocorrência mais urgente sem removê-la.
            Ocorrencia* ocorr_para_atender = obter_ocorrencia_maior_prioridade(arvoreAVL);

            printf("Tentando despachar Ocorrencia ID %d (Prioridade %d)...\n", ocorr_para_atender->id, ocorr_para_atender->prioridade);

            bool recursos_alocados = true;
            int id_pol = 0, id_bom = 0, id_hos = 0;

            // Verificamos se temos os recursos necessários para atende-la.
            if (ocorr_para_atender->servico[0]) {
                id_pol = despacha_policia(policias, ocorr_para_atender->bairro->id);
                if (id_pol == 0) recursos_alocados = false;
            }
            if (recursos_alocados && ocorr_para_atender->servico[1]) {
                id_bom = despacha_bombeiro(bombeiros, ocorr_para_atender->bairro->id);
                if (id_bom == 0) recursos_alocados = false;
            }
            if (recursos_alocados && ocorr_para_atender->servico[2]) {
                id_hos = despacha_hospital(hospitais, ocorr_para_atender->bairro->id);
                if (id_hos == 0) recursos_alocados = false;
            }

            //Se todos os recursos foram alocados com sucesso...
            if (recursos_alocados) {
                printf("=> SUCESSO! Recursos alocados para Ocorrencia ID %d.\n", ocorr_para_atender->id);

                //Removemos a ocorrência da árvore de pendentes.
                Ocorrencia* ocorr_atendida = removerOcorrenciaMaiorPrioridade(arvoreAVL);

                // E a movemos para a lista de "Em Atendimento".
                ocorr_atendida->status = EM_ATENDIMENTO;
                ocorr_atendida->id_unidade_policia = id_pol;
                ocorr_atendida->id_unidade_bombeiro = id_bom;
                ocorr_atendida->id_unidade_hospital = id_hos;
                adiciona_inicio_lista_relatorio(em_atendimento, ocorr_atendida);

            } else {
                printf("=> FALHA! Recursos indisponiveis. Ocorrencia ID %d permanece pendente.\n", ocorr_para_atender->id);

                //Se a alocação falhou no meio do caminho (ex: alocou polícia mas não bombeiro),
                //temos que devolver os recursos que foram temporariamente pegos.
                if (id_pol != 0) liberar_policia(policias, id_pol);
                if (id_bom != 0) liberar_bombeiro(bombeiros, id_bom);
                if (id_hos != 0) liberar_hospital(hospitais, id_hos);
            }
        }

        printf("\n\n=========== ATUALIZAÇÃO DE OCORRÊNCIAS EM ANDAMENTO ============\n\n");
        // --- Atualizando ocorrências em atendimento ---
        NoLista **pp_atual = &(em_atendimento -> cabeca);
        while (*pp_atual != NULL) {

            Ocorrencia *ocorr_atual = (*pp_atual) -> ocorrencia;
            exibir_ocorrencia_especifica(ocorr_atual);
            ocorr_atual -> ciclos_restantes--;
            printf("----: Nova quantidade de ciclos restantes: %d\n", ocorr_atual -> ciclos_restantes);

            if (ocorr_atual->ciclos_restantes <= 0) {
                printf("Ocorrencia ID %d FINALIZADA no ciclo %d.\n", ocorr_atual->id, ciclo);
                ocorr_atual -> status = FINALIZADA;
                ocorr_atual -> ciclo_finalizacao = ciclo;

                // Liberar recursos
                liberar_policia(policias, ocorr_atual->id_unidade_policia);
                liberar_bombeiro(bombeiros, ocorr_atual->id_unidade_bombeiro);
                liberar_hospital(hospitais, ocorr_atual->id_unidade_hospital);

                // Mover para a lista do relatório final
                NoLista *no_a_remover = *pp_atual;
                *pp_atual = no_a_remover->prox;
                em_atendimento->tamanho--;

                no_a_remover->prox = NULL;
                adiciona_inicio_lista_relatorio(relatorio_final, ocorr_atual);
                free(no_a_remover);

            } else {
                pp_atual = &((*pp_atual)->prox);
            }
        }

        ciclo ++;
    }

    printf("\n--- SIMULACAO ENCERRADA ---\n");

    // Montando o relatório final completo
    printf("Montando relatorio final...\n");
    // Mover ocorrências que ainda estavam "Em Atendimento" para o relatório
    while(em_atendimento -> cabeca != NULL) {
        Ocorrencia* ocorr = remove_inicio_lista_relatorio(em_atendimento);
        adiciona_inicio_lista_relatorio(relatorio_final, ocorr);
    }
    // Mover ocorrências que ficaram "Pendentes" para o relatório
    while(arvoreAVL -> raiz != NULL) {
        Ocorrencia* ocorr = removerOcorrenciaMaiorPrioridade(arvoreAVL);
        adiciona_inicio_lista_relatorio(relatorio_final, ocorr);
    }

    morador_atribui_relatorio_final(moradores, relatorio_final);

    ArvB ABB;
    ABB.raiz = cria_arvore_binaria(relatorio_final);
    preenche_arvore_binaria(ABB.raiz, relatorio_final);
    printf("\n--- SIMULACAO ENCERRADA ---\n");

    // -- MENU --
    int opcao;
    int id_escolha;
    do {
        printf("\n--- MENU DE CONSULTA POS-SIMULACAO ---\n");
        printf("Escolha uma opcao:\n");
        printf("1. Visualizar Moradores\n");
        printf("2. Buscar morador por CPF\n");
        printf("3. Visualizar Bairros\n");
        printf("4. Buscar bairro por ID\n");
        printf("5. Relatório das Ocorrências Atendidas\n");
        printf("6. Procura Ocorrência por ID na ABB\n");
        printf("7. Exibir Lista Cruzada de Bairros e Serviços\n");
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
                getchar();

                morador_encontrado = morador_busca_hash_encadeamento(moradores, cpf);

                if (morador_encontrado != NULL) {
                    exibir_morador_especifico(morador_encontrado);
                } else {
                    printf("Morador com CPF %lld nao encontrado na base de dados.\n", cpf);
                }
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
                imprime_lista_relatorio(relatorio_final);
                break;

            case 6:
                printf("\nDigite ID de uma ocorrencia:");
                scanf("%d", &id);
                no_abb* procurado = buscaBinaria(ABB.raiz, id);
                if(procurado == NULL){
                    printf("\nID inválido!");
                }else{
                    exibir_ocorrencia_especifica(procurado -> problema);
                }
                break;

            case 7:
                exibir_lista_cruzada_bairros_servicos(bairros, policias, bombeiros, hospitais);
                break;

            case 0:
                printf("Saindo do menu de consulta.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    printf("\nLiberando memoria alocada...\n");
    free_lista_relatorio(relatorio_final); // Esta função já deve liberar as ocorrências
    free_lista_relatorio(em_atendimento); // Deveria estar vazia, mas por segurança
    destruirArvoreAVL(arvoreAVL); // Libera a árvore e nós restantes
    liberarArvore(ABB.raiz);
    bairro_libera_hash(bairros);
    policia_libera_hash(policias);
    bombeiro_libera_hash(bombeiros);
    hospital_libera_hash(hospitais);
    morador_libera_hash(moradores);

    printf("Memoria liberada com sucesso!\n");
    return 0;
}
