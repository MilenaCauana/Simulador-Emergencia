#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"

#define MAX 40

//--> enum privado!
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
* Recebe: sem parâmetros
* Retorna: inteiro
*
*/
void gera_id_ocorrencia(int num, Ocorrencia *ocorrencia){

     int complemento = rand() % 1000; // Gera um ID único de 0 a 999

     ocorrencia -> id = (num * 1000) + complemento;

}

/*
*---Função cria ocorrencia--
* Recebe: nada
* Retorna: Ocorrencia criada
*
* - Nessa função, o tipo da ocorrência, sua prioridade e quais serviços serão necessarios já serão preenchidos
*
*/
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha){

     Ocorrencia* ocorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));

     if(ocorrencia == NULL){
        printf("ERRO AO ALOCAR MEMORIA!");
        return NULL;
    }

    // Inicializa todos os serviços como false antes de definir
    ocorrencia->servico[0] = false; // Polícia
    ocorrencia->servico[1] = false; // Bombeiro
    ocorrencia->servico[2] = false; // Hospital

    //pegando o tempo de registro
    ocorrencia->tempo_registro = time(NULL);
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
            strcpy(ocorrencia->tipo, "OCORRRECIA DE AFOGAMENTO!");
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

        gera_id_ocorrencia(num, ocorrencia);

        //Pegar um morador de forma aleatória
        ocorrencia -> morador = cria_morador(ha);

        //Agora, iremos adicionar um bairro aleatório para a ocorrência
        int id_bairro = 1000 + (1 + rand() % 9);
        ocorrencia -> bairro = bairro_busca_hash_sem_colisao(ha, id_bairro);

        if (ocorrencia -> bairro == NULL){
            printf("AVISO: Não foi possível atribuir um bairro à ocorrência");
        }

        //Colocando a ocorrencia no histórico de ocorrencias do morador
        if (ocorrencia -> morador != NULL) {

            if (ocorrencia -> morador -> num_ocorrencias < 50) {
                int indice = ocorrencia -> morador -> num_ocorrencias;

                ocorrencia -> morador-> ocorrencias[indice] = ocorrencia;
                ocorrencia -> morador -> num_ocorrencias++;

            } else {
                printf("AVISO: O morador %s atingiu o limite de ocorrencias (50).\n", ocorrencia -> morador -> nome);
            }

        } else {
            printf("ERRO: Nao foi possivel atribuir a ocorrencia a um morador valido.\n");
        }

        return ocorrencia;
}
