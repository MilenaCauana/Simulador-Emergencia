// lista_cruzada.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_cruzada.h"

/*
*---Função para exibir a lista cruzada de bairros e serviços--
* Recebe: Ponteiros para as tabelas hash de bairros, polícia, bombeiro e hospital
* Retorna: void
*
*/
void exibir_lista_cruzada_bairros_servicos(Bairros_Hash *bairros, Policia_Hash *policias, Bombeiro_Hash *bombeiros, Hospital_Hash *hospitais) {
    if (bairros == NULL || bairros->qtd == 0) {
        printf("Nenhum bairro cadastrado para exibir a lista cruzada.\n");
        return;
    }

    printf("\n--- LISTA CRUZADA: BAIRROS E SERVICOS RESPONSAVEIS ---\n");

    for (int i = 0; i < bairros->tamanho; i++) {
        if (bairros->itens[i] != NULL) {
            Bairros *b = bairros->itens[i];
            printf("\nBairro: %s (ID: %d)\n", b ->nome, b->id);
            printf("  Serviços Responsáveis:\n");

            // Busca e exibe detalhes da Unidade de Policia
            Policia *policia_unit = policia_busca_hash(policias, b->id_policia_responsavel);
            if (policia_unit != NULL) {
                printf("    - Polícia: ID %d (Viaturas Totais: %d, Disponíveis: %d)\n",
                       policia_unit->id, policia_unit->viaturas, policia_unit->viaturas_disp);
            } else {
                printf("    - Polícia: Unidade ID %d Nao Encontrada\n", b->id_policia_responsavel);
            }

            // Busca e exibe detalhes da Unidade de Bombeiro
            Bombeiro *bombeiro_unit = bombeiro_busca_hash(bombeiros, b->id_bombeiro_responsavel);
            if (bombeiro_unit != NULL) {
                printf("    - Bombeiro: ID %d (Caminhoes Totais: %d, Disponíveis: %d)\n",
                       bombeiro_unit->id, bombeiro_unit->caminhoes, bombeiro_unit->caminhoes_disp);
            } else {
                printf("    - Bombeiro: Unidade ID %d Nao Encontrada\n", b->id_bombeiro_responsavel);
            }

            // Busca e exibe detalhes da Unidade de Hospital
            Hospital *hospital_unit = hospital_busca_hash(hospitais, b->id_hospital_responsavel);
            if (hospital_unit != NULL) {
                printf("    - Hospital: ID %d (Ambulancias Totais: %d, Disponíveis: %d)\n",
                       hospital_unit->id, hospital_unit->ambulancias, hospital_unit->ambulancias_disp);
            } else {
                printf("    - Hospital: Unidade ID %d Nao Encontrada\n", b->id_hospital_responsavel);
            }
        }
    }
    printf("\n------------------------------------------------\n");
}
