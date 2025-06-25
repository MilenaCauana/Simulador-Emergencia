#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"
//#include "../include/arvore_binaria_busca.h"

#define MAX 40

//--- ºº ENUM PRIVADO ºº ---
typedef enum tipo_de_ocorrencia{
    T_ASS = 0,
    ROUBO,
    FURTO,
    FOGO_RESIDENCIA,
    FOGO_COMERCIAL,
    ACI_VEICULAR,
    ACI_DOM_LEVE,
    ACI_DOM_GRAVE,
    INFARTO,
    RESGATE_ANIMAL,
    VIOLENCIA_DOMESTICA,
    DESABAMENTO,
    PESSOA_DESAPARECIDA,
    MANIFESTACAO,
    ENVOLVIMENTO_ARMA,
    SUICIDIO,
    AFOGAMENTO,
    INUNDACAO,
    FALSA_ALARME, // Para casos de default ou erro
    NUM_TIPOS_OCORRENCIA
} tipo_de_ocorrencia;

//------ ºº FUNÇÕES ºº ------

/*
*---Função Geradora de IDs--
* Recebe: dois inteiros (num base para o ID e um ponteiro para a ocorrencia)
* Retorna: void
*
*/
int incr_ocor = 0; //incrementador em escopo global para o valor aumentar com a geração de ids

void gera_id_ocorrencia(Ocorrencia *ocorrencia){
     incr_ocor++;
     ocorrencia -> id = 2000 + incr_ocor;; // ID simples para facilitar chaveamento da ABB
}

/*
*---Função cria ocorrencia--
* Recebe: Ponteiro para o hash de bairros e para o hash de moradores
* Retorna: Ocorrencia criada
*
* - Nessa função, o tipo da ocorrência, sua prioridade e quais serviços serão necessarios já serão preenchidos
*
*/
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha, Morador_Hash *hash_morador){
    Ocorrencia* ocorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));

    if(ocorrencia == NULL){
        printf("ERRO AO ALOCAR MEMORIA PARA OCORRENCIA!");
        return NULL;
    }

    // Inicializa todos os serviços como false antes de definir
    ocorrencia->servico[0] = false; // Polícia
    ocorrencia->servico[1] = false; // Bombeiro
    ocorrencia->servico[2] = false; // Hospital

    // tempo_registro e tempo_atendimento serão preenchidos em main.c com base no ciclo
    ocorrencia->tempo_registro = 0;
    ocorrencia->tempo_atendimento = 0; // Inicialmente não atendida

    //Pegando um numero aleatório para selecionar o tipo da ocorrência
    int num = rand() % NUM_TIPOS_OCORRENCIA;

    switch (num){
        case T_ASS:
            strcpy(ocorrencia->tipo, "TENTATIVA DE HOMICIDIO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Polícia
            ocorrencia->servico[2] = true; // Hospital
            break;

        case ROUBO:
            strcpy(ocorrencia->tipo, "ROUBO EM ANDAMENTO!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[0] = true; // Polícia
            break;

        case FURTO:
            strcpy(ocorrencia->tipo, "FURTO REGISTRADO!");
            ocorrencia->prioridade = 2;
            ocorrencia->servico[0] = true; // Polícia
            break;

        case FOGO_RESIDENCIA:
            strcpy(ocorrencia->tipo, "INCENDIO EM RESIDENCIA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro
            ocorrencia->servico[2] = true; // Hospital (Pode haver vítimas)
            break;

        case FOGO_COMERCIAL:
            strcpy(ocorrencia->tipo, "INCENDIO EM ESTABELECIMENTO COMERCIAL!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro
            ocorrencia->servico[2] = true; // Hospital (Pode haver vítimas)
            ocorrencia->servico[0] = true; // Polícia (Controle de área/evacuação)
            break;

        case ACI_VEICULAR:
            strcpy(ocorrencia->tipo, "ACIDENTE DE VEICULO (POTENCIAL VITIMAS)!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[0] = true; // Polícia
            ocorrencia->servico[1] = true; // Bombeiro (Resgate)
            ocorrencia->servico[2] = true; // Hospital (Atendimento a feridos)
            break;

        case ACI_DOM_LEVE:
            strcpy(ocorrencia->tipo, "ACIDENTE DOMESTICO (LESAO LEVE)!");
            ocorrencia->prioridade = 2;
            ocorrencia->servico[2] = true; // Hospital
            break;

        case ACI_DOM_GRAVE:
            strcpy(ocorrencia->tipo, "ACIDENTE DOMESTICO (TRAUMA GRAVE)!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[2] = true; // Hospital
            ocorrencia->servico[1] = true; // Bombeiro (Se precisar de resgate)
            break;

        case INFARTO:
            strcpy(ocorrencia->tipo, "EMERGENCIA MEDICA: INFARTO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[2] = true; // Hospital
            break;

        case RESGATE_ANIMAL:
            strcpy(ocorrencia->tipo, "RESGATE DE ANIMAL EM SITUACAO DE RISCO!");
            ocorrencia->prioridade = 1;
            ocorrencia->servico[1] = true; // Bombeiro
            break;

        case VIOLENCIA_DOMESTICA:
            strcpy(ocorrencia->tipo, "VIOLENCIA DOMESTICA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Polícia
            ocorrencia->servico[2] = true; // Hospital (Pode haver feridos)
            break;

        case DESABAMENTO:
            strcpy(ocorrencia->tipo, "DESABAMENTO DE ESTRUTURA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Polícia (Isolamento)
            ocorrencia->servico[1] = true; // Bombeiro (Busca e Resgate)
            ocorrencia->servico[2] = true; // Hospital (Atendimento a feridos)
            break;

        case PESSOA_DESAPARECIDA:
            strcpy(ocorrencia->tipo, "PESSOA DESAPARECIDA!");
            ocorrencia->prioridade = 3;
            ocorrencia->servico[0] = true; // Polícia
            break;

        case MANIFESTACAO:
            strcpy(ocorrencia->tipo, "MANIFESTACAO/DISTURBIO EM VIA PUBLICA!");
            ocorrencia->prioridade = 3;
            ocorrencia->servico[0] = true; // Polícia (Controle)
            break;

        case ENVOLVIMENTO_ARMA:
            strcpy(ocorrencia->tipo, "ENVOLVIMENTO COM ARMA DE FOGO/BRANCA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Polícia (Altíssimo risco)
            ocorrencia->servico[2] = true; // Hospital (Pode haver feridos)
            break;

        case SUICIDIO:
            strcpy(ocorrencia->tipo, "TENTATIVA DE SUICIDIO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Polícia (Controle da situação)
            ocorrencia->servico[2] = true; // Hospital (Atendimento psiquiátrico/médico)
            break;

        case AFOGAMENTO:
            strcpy(ocorrencia->tipo, "OCORRENCIA DE AFOGAMENTO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro (Resgate aquático)
            ocorrencia->servico[2] = true; // Hospital (Atendimento médico)
            break;

        case INUNDACAO:
            strcpy(ocorrencia->tipo, "AREA DE INUNDACAO/ALAGAMENTO!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[1] = true; // Bombeiro (Resgate, avaliação de risco)
            ocorrencia->servico[0] = true; // Polícia (Isolamento da área)
            break;

        case FALSA_ALARME:
            strcpy(ocorrencia->tipo, "FALSO ALARME OU OCORRENCIA SEM GRAVIDADE!");
            ocorrencia->prioridade = 0;
            // Nenhum serviço acionado, ou apenas polícia para verificar
            break;

        default:
            strcpy(ocorrencia->tipo, "TIPO DE OCORRENCIA DESCONHECIDO!");
            ocorrencia->prioridade = 0; // Prioridade mínima ou para investigação
            ocorrencia -> servico[0] = true; // Polícia para verificar
            break;
        }

        gera_id_ocorrencia(ocorrencia);

        //Pegar um morador de forma aleatória
        ocorrencia -> morador = morador_aleatorio(hash_morador);

        //Agora, iremos adicionar um bairro aleatório para a ocorrência
        int id_bairro_aleatorio = 1000 + (1 + rand() % 9); // Gera IDs de bairro de 1001 a 1009
        ocorrencia -> bairro = bairro_busca_hash_sem_colisao(ha, id_bairro_aleatorio);

        if (ocorrencia -> bairro == NULL){
            printf("AVISO: Nao foi possivel atribuir um bairro a ocorrencia (ID %d). Isso pode indicar um erro no preenche_bairros ou ID invalido.\n", id_bairro_aleatorio);
        }

        //Colocando a ocorrencia no histórico de ocorrencias do morador
        if (ocorrencia -> morador != NULL) {
            if (ocorrencia -> morador -> num_ocorrencias < 50) {
                int indice = ocorrencia -> morador -> num_ocorrencias;

                // Aloca memória para a cópia da Ocorrencia para o histórico do morador
                Ocorrencia *copia_ocorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));
                if (copia_ocorrencia == NULL) {
                    printf("ERRO AO ALOCAR MEMORIA PARA COPIA DE OCORRENCIA NO MORADOR!\n");
                    // Se não conseguir alocar a cópia, ainda assim prossegue com a ocorrência original, mas sem registrar no morador.
                } else {
                    // Copia os dados da ocorrência para a nova memória alocada
                    memcpy(copia_ocorrencia, ocorrencia, sizeof(Ocorrencia));
                    // IMPORTANTE: O ponteiro 'bairro' dentro da cópia deve apontar para o mesmo bairro na hash principal,
                    // pois o bairro em si não é duplicado, apenas a estrutura da Ocorrencia.
                    // O mesmo vale para 'morador', a cópia deve apontar para o morador original.
                    copia_ocorrencia->bairro = ocorrencia->bairro;
                    copia_ocorrencia->morador = ocorrencia->morador; // A cópia aponta para o morador original

                    ocorrencia->morador->ocorrencias[indice] = copia_ocorrencia;
                    ocorrencia->morador->num_ocorrencias++;
                }

            } else {
                printf("AVISO: O morador %s atingiu o limite de ocorrencias (50). Nao foi possivel adicionar a ocorrencia ao historico.\n", ocorrencia -> morador -> nome);
            }
        } else {
            printf("ERRO: Nao foi possivel atribuir a ocorrencia a um morador valido. Ocorrencia criada sem morador associado.\n");
        }

        return ocorrencia;
}

/*
*---Função que exibe ocorrência específica--
* Recebe: Ponteiro para ocorrência específica
* Retorna: void
*
*/
void exibir_ocorrencia_especifica(Ocorrencia *ocorrencia){
    printf("\n...\n");
    if (ocorrencia == NULL) {
        printf("Erro: Ocorrencia nao existe.\n");
        return;
    }

    printf("ID: %d\n", ocorrencia -> id);
    printf("Tipo: %s\n", ocorrencia -> tipo);

    if (ocorrencia->bairro != NULL) {
        printf("Bairro: %s (ID: %d)\n", ocorrencia->bairro->nome, ocorrencia->bairro->id);
    } else {
        printf("Bairro: Nao Atribuido\n");
    }

    if (ocorrencia->morador != NULL) {
        printf("Morador: %s (CPF: %lld)\n", ocorrencia->morador->nome, ocorrencia->morador->cpf);
    } else {
        printf("Morador: Nao Atribuido\n");
    }


    printf("--- Servicos Necessitados ---\n");
        if (ocorrencia -> servico[0]){
            printf("- Policia\n");
        }

        if (ocorrencia -> servico[1]){
            printf("- Bombeiro\n");
        }

        if (ocorrencia -> servico[2]){
            printf("- Hospital\n");
        }

    printf("Prioridade: %d\n", ocorrencia -> prioridade);
    // Tempos em ciclos (que representam 10 minutos)
    printf("Tempo de Registro (ciclo): %lld (Hora Aprox.: %02lld:%02lld)\n",
           (long long)ocorrencia->tempo_registro,
           ((long long)ocorrencia->tempo_registro - 1) * 10 / 60,
           ((long long)ocorrencia->tempo_registro - 1) * 10 % 60);
    printf("Tempo de Atendimento (ciclo): %lld (Hora Aprox.: %02lld:%02lld)\n",
           (long long)ocorrencia->tempo_atendimento,
           ((long long)ocorrencia->tempo_atendimento - 1) * 10 / 60,
           ((long long)ocorrencia->tempo_atendimento - 1) * 10 % 60);
    printf("--------------------------\n");
}
