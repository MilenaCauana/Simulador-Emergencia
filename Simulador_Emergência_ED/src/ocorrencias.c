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

//------ �� FUN��ES �� ------

/*
*---Fun��o Geradora de IDs--
* Recebe: sem par�metros
* Retorna: inteiro
*
*/
void gera_id_ocorrencia(int num, Ocorrencia *ocorrencia){

     int complemento = rand() % 1000; // Gera um ID �nico de 0 a 999

     ocorrencia -> id = (num * 1000) + complemento;

}

/*
*---Fun��o cria ocorrencia--
* Recebe: nada
* Retorna: Ocorrencia criada
*
* - Nessa fun��o, o tipo da ocorr�ncia, sua prioridade e quais servi�os ser�o necessarios j� ser�o preenchidos
*
*/
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha){

     Ocorrencia* ocorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));

     if(ocorrencia == NULL){
        printf("ERRO AO ALOCAR MEMORIA!");
        return NULL;
    }

    // Inicializa todos os servi�os como false antes de definir
    ocorrencia->servico[0] = false; // Pol�cia
    ocorrencia->servico[1] = false; // Bombeiro
    ocorrencia->servico[2] = false; // Hospital

    //pegando o tempo de registro
    ocorrencia->tempo_registro = time(NULL);
    ocorrencia->tempo_atendimento = 0; // Inicialmente n�o atendida

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
            strcpy(ocorrencia->tipo, "OCORRRECIA DE AFOGAMENTO!");
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

        gera_id_ocorrencia(num, ocorrencia);

        //Pegar um morador de forma aleat�ria
        ocorrencia -> morador = cria_morador(ha);

        //Agora, iremos adicionar um bairro aleat�rio para a ocorr�ncia
        int id_bairro = 1000 + (1 + rand() % 9);
        ocorrencia -> bairro = bairro_busca_hash_sem_colisao(ha, id_bairro);

        if (ocorrencia -> bairro == NULL){
            printf("AVISO: N�o foi poss�vel atribuir um bairro � ocorr�ncia");
        }

        //Colocando a ocorrencia no hist�rico de ocorrencias do morador
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
