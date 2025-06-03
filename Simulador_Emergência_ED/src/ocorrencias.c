#include <stdio.h>
#include <stdlib.h>
#include "../include/ocorrencias.h"
#include "../include/bairro.h"

#define NOME 40

typedef struct{

    int id;
    char nome[NOME];
    Bairros *reside;

}Morador;

typedef struct{

    int id;
    char tipo[NOME];
    int servico[3];
    Morador *vitima;

}Ocorrencia;

typedef enum tipo_de_ocorrencia{

    T_ASS = 0,
    ROUBO,
    FURTO,
    FOGO1,
    FOGO2,
    ACI_CAR,
    ACI_DOM1,
    ACI_DOM2,
    INFARTO,
    RESGATO

};

int gera_id_ocorrencia(){

    srand(time(NULL));
    return 1000 + (rand() % (10000 - 1000 + 1));

}

char* seleciona_tipo_ocorrencia(int num){

    char* texto = (char*) malloc(sizeof(NOME));

    if(texto == NULL){

        peintf("ERRO DE ALOCACAO DE MEMORIA!");
        return 0;

    }

    switch (num){

        case T_ASS:

            texto = "TENTATIVA DE ASSASSINATO!";

        break;
        case ROUBO:

            texto = "PESSOA FOI ASSALTADA!";

        break;
        case FURTO:

            texto = "PESSOA FOI FURTADA!";

        break;
        case FOGO1:

            texto = "CASA PEGANDO FOGO!";

        break;
        case FOGO2:

            texto = "ESTABELECIMENTO PEGANDO FOGO!";

        break;
        case ACI_CAR:

            texto = "ACIDENTE DE CARRO!";

        break;
        case ACI_DOM1:

            texto = "PESSOA CAIU DA ESCADA!";

        break;
        case ACI_DOM2:

            texto = "PESSOA CAIU E BATEU A CABECA";

        break;
        case INFARTO:

            texto = "PESSOA TEVE UM INFARTO";

        break;
        case RESGATO:

            texto = "Gato preso na arvore!";

        break;
        default:

            texto = "Gato preso na arvore!";

        break;

    }

    return texto;

}

int* indica_servico(int num){

    static int array[3];

        switch (num) {
        case T_ASS:
        case ROUBO:
        case FURTO:

            array[0] = 1; array[1] = 0; array[2] = 0;

            break;
        case FOGO1:
        case FOGO2:
        case RESGATO:

            array[0] = 0; array[1] = 1; array[2] = 0;

            break;
        case ACI_CAR:
        case ACI_DOM1:
        case ACI_DOM2:

            array[0] = 0; array[1] = 1; array[2] = 1;

            break;
        case INFARTO:

            array[0] = 0; array[1] = 0; array[2] = 1;

            break;
        default:

            array[0] = 0; array[1] = 1; array[2] = 0;

            break;
    }

    return array;

}

int gera_id_morador(){

    srand(time(NULL));
    return 100 + (rand() % (1000 - 100 + 1));

}

char* seleciona_nome_morador(int num){

    char* name = (char*) malloc(sizeof(NOME));

    if(name == NULL){

        printf("ERRO DE ALOCACAO DE MEMORIA!");
        return 0;

    }

    if(num <= 5){

        name = "João Silva Santos";

    }else if(num >= 6 && num <= 10){

        name = "Pedro Oliveira Costa";

    }else if(num >= 11 && num <= 15){

        name = "Lucas Pereira Almeida";

    }else if(num >= 16 && num <= 20){

        name = "Gabriel Souza Rodrigues";

    }else if(num >= 21 && num <= 25){

        name = "Rafael Fernandes Lima";

    }else if(num >= 26 && num <= 30){

        name = "Carlos Mendes Carvalho";

    }else if(num >= 31 && num <= 35){

        name = "Daniel Barbosa Martins";

    }else if(num >= 36 && num <= 40){

        name = "André Rocha Nunes";

    }else if(num >= 41 && num <= 45){

        name = "Marcelo Castro Ribeiro";

    }else if(num >= 46 && num <= 50){

        name = "Felipe Gomes Duarte";

    }else if(num >= 51 && num <= 55){

        name = "Maria Ferreira Alves";

    }else if(num >= 56 && num <= 60){

        name = "Ana Santos Monteiro";

    }else if(num >= 61 && num <= 65){

        name = "Sofia Lima Xavier";

    }else if(num >= 66 && num <= 70){

        name = "Laura Cunha Neves";

    }else if(num >= 71 && num <= 75){

        name = "Beatriz Cardoso Dias";

    }else if(num >= 76 && num <= 80){

        name = "Camila Teixeira Moreira";

    }else if(num >= 81 && num <= 85){

        name = "Juliana Andrade Pinto";

    }else if(num >= 86 && num <= 90){

        name = "Isabel Moraes Peixoto";

    }else if(num >= 91 && num <= 95){

        name = "Carolina Azevedo Guimarães";

    }else if(num >= 96 && num <= 100){

        name = "Amanda Correia Viana";

    }

    return name;

}

Morador* cria_morador(int region){

    Morador* residente = (Morador*) malloc(sizeof(Morador));
    if(residente == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }
    srand(time(NULL));
    residente->id = 100 + ((rand() % (1000 - 100 + 1)) * 10) + region;
    residente->nome[NOME] = seleciona_nome_morador(residente->id / 100);
    return residente;

}

Ocorrencia* cria_ocorrencia(){

    Ocorrencia* novo = (Ocorrencia*) malloc(sizeof(Ocorrencia));
    if(novo == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }

    srand(time(NULL));
    novo->id = 1000 + (rand() % (10000 - 1000 + 1));
    novo->tipo = seleciona_tipo_ocorrencia(novo->id / 1000);
    novo->servico[3] = indica_servico(novo->id / 1000);
    novo->vitima = cria_morador(novo->id % 10);
    return novo;

}
