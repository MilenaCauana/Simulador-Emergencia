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

//--- �� ENUM PRIVADO �� ---
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

//------ �� FUN��ES �� ------

/*
*---Fun��o Geradora de IDs (privada) --
* Recebe: dois inteiros (num base para o ID e um ponteiro para a ocorrencia)
* Retorna: void
*
*/
void gera_id_ocorrencia(Ocorrencia *ocorrencia){
    static incr_ocor = 0; //incrementador para o valor aumentar com a gera��o de ids

     incr_ocor++;
     ocorrencia -> id = 2000 + incr_ocor;; // ID simples para facilitar chaveamento da ABB
}

/*
*---Fun��o cria ocorrencia--
* Recebe: Ponteiro para o hash de bairros e para o hash de moradores
* Retorna: Ocorrencia criada
*
* - Nessa fun��o, o tipo da ocorr�ncia, sua prioridade e quais servi�os ser�o necessarios j� ser�o preenchidos
*
*/
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha, Morador_Hash *hash_morador, int ciclo_atual){
    Ocorrencia* ocorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));

    if(ocorrencia == NULL){
        printf("ERRO AO ALOCAR MEMORIA PARA OCORRENCIA!");
        return NULL;
    }

    // Inicializa todos os servi�os como false antes de definir
    ocorrencia->servico[0] = false; // Pol�cia
    ocorrencia->servico[1] = false; // Bombeiro
    ocorrencia->servico[2] = false; // Hospital

    //Deixando a ocorr�ncia pendente
    ocorrencia -> status = PENDENTE;

    //Tempo
    ocorrencia -> ciclo_registro = ciclo_atual;

    //Pegando um numero aleat�rio para selecionar o tipo da ocorr�ncia
    int num = rand() % NUM_TIPOS_OCORRENCIA;
    switch (num){
        case T_ASS:
            strcpy(ocorrencia->tipo, "TENTATIVA DE HOMICIDIO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Pol�cia
            ocorrencia->servico[2] = true; // Hospital
            break;

        case ROUBO:
            strcpy(ocorrencia->tipo, "ROUBO EM ANDAMENTO!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[0] = true; // Pol�cia
            break;

        case FURTO:
            strcpy(ocorrencia->tipo, "FURTO REGISTRADO!");
            ocorrencia->prioridade = 2;
            ocorrencia->servico[0] = true; // Pol�cia
            break;

        case FOGO_RESIDENCIA:
            strcpy(ocorrencia->tipo, "INCENDIO EM RESIDENCIA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro
            ocorrencia->servico[2] = true; // Hospital (Pode haver v�timas)
            break;

        case FOGO_COMERCIAL:
            strcpy(ocorrencia->tipo, "INCENDIO EM ESTABELECIMENTO COMERCIAL!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro
            ocorrencia->servico[2] = true; // Hospital (Pode haver v�timas)
            ocorrencia->servico[0] = true; // Pol�cia (Controle de �rea/evacua��o)
            break;

        case ACI_VEICULAR:
            strcpy(ocorrencia->tipo, "ACIDENTE DE VEICULO (POTENCIAL VITIMAS)!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[0] = true; // Pol�cia
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
            ocorrencia->servico[0] = true; // Pol�cia
            ocorrencia->servico[2] = true; // Hospital (Pode haver feridos)
            break;

        case DESABAMENTO:
            strcpy(ocorrencia->tipo, "DESABAMENTO DE ESTRUTURA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Pol�cia (Isolamento)
            ocorrencia->servico[1] = true; // Bombeiro (Busca e Resgate)
            ocorrencia->servico[2] = true; // Hospital (Atendimento a feridos)
            break;

        case PESSOA_DESAPARECIDA:
            strcpy(ocorrencia->tipo, "PESSOA DESAPARECIDA!");
            ocorrencia->prioridade = 3;
            ocorrencia->servico[0] = true; // Pol�cia
            break;

        case MANIFESTACAO:
            strcpy(ocorrencia->tipo, "MANIFESTACAO/DISTURBIO EM VIA PUBLICA!");
            ocorrencia->prioridade = 3;
            ocorrencia->servico[0] = true; // Pol�cia (Controle)
            break;

        case ENVOLVIMENTO_ARMA:
            strcpy(ocorrencia->tipo, "ENVOLVIMENTO COM ARMA DE FOGO/BRANCA!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Pol�cia (Alt�ssimo risco)
            ocorrencia->servico[2] = true; // Hospital (Pode haver feridos)
            break;

        case SUICIDIO:
            strcpy(ocorrencia->tipo, "TENTATIVA DE SUICIDIO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[0] = true; // Pol�cia (Controle da situa��o)
            ocorrencia->servico[2] = true; // Hospital (Atendimento psiqui�trico/m�dico)
            break;

        case AFOGAMENTO:
            strcpy(ocorrencia->tipo, "OCORRENCIA DE AFOGAMENTO!");
            ocorrencia->prioridade = 5;
            ocorrencia->servico[1] = true; // Bombeiro (Resgate aqu�tico)
            ocorrencia->servico[2] = true; // Hospital (Atendimento m�dico)
            break;

        case INUNDACAO:
            strcpy(ocorrencia->tipo, "AREA DE INUNDACAO/ALAGAMENTO!");
            ocorrencia->prioridade = 4;
            ocorrencia->servico[1] = true; // Bombeiro (Resgate, avalia��o de risco)
            ocorrencia->servico[0] = true; // Pol�cia (Isolamento da �rea)
            break;

        case FALSA_ALARME:
            strcpy(ocorrencia->tipo, "FALSO ALARME OU OCORRENCIA SEM GRAVIDADE!");
            ocorrencia->prioridade = 0;
            // Nenhum servi�o acionado, ou apenas pol�cia para verificar
            break;

        default:
            strcpy(ocorrencia->tipo, "TIPO DE OCORRENCIA DESCONHECIDO!");
            ocorrencia->prioridade = 0; // Prioridade m�nima ou para investiga��o
            ocorrencia -> servico[0] = true; // Pol�cia para verificar
            break;
        }

        //Quantidade de ciclos, ou seja, minutos que demorar� para a ocorr�ncia ser finalizada
        if (ocorrencia->prioridade == 0)
        {
            ocorrencia -> qtd_ciclos_duracao = 0;
        }else{
            ocorrencia -> qtd_ciclos_duracao = (rand() % 6) + 3; //De 30 a 80 minutos
            ocorrencia ->ciclos_restantes = ocorrencia -> qtd_ciclos_duracao;
        }

        gera_id_ocorrencia(ocorrencia);

        //Pegar um morador de forma aleat�ria
        ocorrencia -> morador = morador_aleatorio(hash_morador);

        //Agora, iremos adicionar um bairro aleat�rio para a ocorr�ncia
        int id_bairro_aleatorio = 1000 + (1 + rand() % 9); // Gera IDs de bairro de 1001 a 1009
        ocorrencia -> bairro = bairro_busca_hash_sem_colisao(ha, id_bairro_aleatorio);

        if (ocorrencia -> bairro == NULL){
            printf("AVISO: Nao foi possivel atribuir um bairro a ocorrencia (ID %d). Isso pode indicar um erro no preenche_bairros ou ID invalido.\n", id_bairro_aleatorio);
        }

        return ocorrencia;
}

/*
*---Fun��o que exibe ocorr�ncia espec�fica--
* Recebe: Ponteiro para ocorr�ncia espec�fica
* Retorna: void
*
*/
void exibir_ocorrencia_especifica(Ocorrencia *ocorrencia){

    if (ocorrencia == NULL) {
        printf("Erro: Ocorrencia nao existe.\n");
        return;
    }

    //Vendo se ela est� pendente ou n�o
    char status_str[20];
    switch(ocorrencia -> status){
        case PENDENTE: strcpy(status_str, "Pendente"); break;
        case EM_ATENDIMENTO: strcpy(status_str, "Em Atendimento"); break;
        case FINALIZADA: strcpy(status_str, "Finalizada"); break;
    }

    printf("------------------------\n");
    printf("ID: %d\nStatus: %s\n", ocorrencia -> id, status_str);
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

    int h_reg = (ocorrencia -> ciclo_registro * 10) / 60;
    int m_reg = (ocorrencia -> ciclo_registro * 10) % 60;

     printf("Horario Solicitacao: %02d:%02d (Ciclo: %d)\n", h_reg, m_reg, ocorrencia->ciclo_registro);

    if (ocorrencia->status == FINALIZADA) {
        int h_fin = (ocorrencia->ciclo_finalizacao * 10) / 60;
        int m_fin = (ocorrencia->ciclo_finalizacao * 10) % 60;
        printf("Horario Finalizacao: %02d:%02d (Ciclo: %d)\n", h_fin, m_fin, ocorrencia->ciclo_finalizacao);
    } else if (ocorrencia->status == EM_ATENDIMENTO) {
        printf("Horario Finalizacao: Em andamento (Ciclos restantes: %d)\n", ocorrencia->ciclos_restantes);
    } else {
        printf("Horario Finalizacao: Nao atendida\n");
    }

    printf("Quantidade de ciclos: %d\n", ocorrencia -> qtd_ciclos_duracao);
    printf("Quantidade de ciclos restantes: %d\n", ocorrencia -> ciclos_restantes);
}


