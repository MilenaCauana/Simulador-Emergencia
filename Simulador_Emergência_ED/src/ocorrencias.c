#include <stdio.h>
#include <stdlib.h>
#include "../include/ocorrencia.h"
#include "../include/bairro.h"

#define NOME 40

typedef struct pessoa{

    int id;
    char nome[NOME];
    Bairros *reside;

}Morador;

typedef struct emergencias{

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

char seleciona_tipo_ocorrencia(int num){

    char texto[NOME];

    switch (num){

        case T_ASS:

            return "TENTATIVA DE ASSASSINATO!";

        break;
        case ROUBO:

            return "PESSOA FOI ASSALTADA!";

        break;
        case FURTO:

            return "PESSOA FOI FURTADA!";

        break;
        case FOGO1:

            return "CASA PEGANDO FOGO!";

        break;
        case FOGO2:

            return "ESTABELECIMENTO PEGANDO FOGO!";

        break;
        case ACI_CAR:

            return "ACIDENTE DE CARRO!";

        break;
        case ACI_DOM1:

            return "PESSOA CAIU DA ESCADA!";

        break;
        case ACI_DOM2:

            return "PESSOA CAIU E BATEU A CABEÇA";

        break;
        case INFARTO:

            return "PESSOA TEVE UM INFARTO";

        break;
        case RESGATO:

            return "Gato preso na árvore!";

        break;
        default:

            return "Gato preso na árvore!";

        break;

    }

}

int indica_servico(int num, int array[]){

    char texto[NOME];

    switch (num){

        case T_ASS:

            array[0] = 1;
            array[1] = 0;
            array[2] = 0;
            return array;

        break;
        case ROUBO:

            array[0] = 1;
            array[1] = 0;
            array[2] = 0;
            return array;

        break;
        case FURTO:

            array[0] = 1;
            array[1] = 0;
            array[2] = 0;
            return array;

        break;
        case FOGO1:

            array[0] = 0;
            array[1] = 1;
            array[2] = 0;
            return array;

        break;
        case FOGO2:

            array[0] = 0;
            array[1] = 1;
            array[2] = 0;
            return array;

        break;
        case ACI_CAR:

            array[0] = 0;
            array[1] = 1;
            array[2] = 1;
            return array;

        break;
        case ACI_DOM1:

            array[0] = 0;
            array[1] = 1;
            array[2] = 1;
            return array;

        break;
        case ACI_DOM2:

            array[0] = 0;
            array[1] = 1;
            array[2] = 1;
            return array;

        break;
        case INFARTO:

            array[0] = 0;
            array[1] = 0;
            array[2] = 1;
            return array;

        break;
        case RESGATO:

            array[0] = 0;
            array[1] = 1;
            array[2] = 0;
            return array;

        break;
        default:

            array[0] = 0;
            array[1] = 1;
            array[2] = 0;
            return array;

        break;

    }

}

int gera_id_morador(){

    srand(time(NULL));
    return 100 + (rand() % (1000 - 100 + 1));

}

char seleciona_nome_morador(int num){

    if(num <= 5){

        return "João Silva Santos";

    }else if(num >= 6 && num <= 10){

        return "Pedro Oliveira Costa";

    }else if(num >= 11 && num <= 15){

        return "Lucas Pereira Almeida";

    }else if(num >= 16 && num <= 20){

        return "Gabriel Souza Rodrigues";

    }else if(num >= 21 && num <= 25){

        return "Rafael Fernandes Lima";

    }else if(num >= 26 && num <= 30){

        return "Carlos Mendes Carvalho";

    }else if(num >= 31 && num <= 35){

        return "Daniel Barbosa Martins";

    }else if(num >= 36 && num <= 40){

        return "André Rocha Nunes";

    }else if(num >= 41 && num <= 45){

        return "Marcelo Castro Ribeiro";

    }else if(num >= 46 && num <= 50){

        return "Felipe Gomes Duarte";

    }else if(num >= 51 && num <= 55){

        return "Maria Ferreira Alves";

    }else if(num >= 56 && num <= 60){

        return "Ana Santos Monteiro";

    }else if(num >= 61 && num <= 65){

        return "Sofia Lima Xavier";

    }else if(num >= 66 && num <= 70){

        return "Laura Cunha Neves";

    }else if(num >= 71 && num <= 75){

        return "Beatriz Cardoso Dias";

    }else if(num >= 76 && num <= 80){

        return "Camila Teixeira Moreira";

    }else if(num >= 81 && num <= 85){

        return "Juliana Andrade Pinto";

    }else if(num >= 86 && num <= 90){

        return "Isabel Moraes Peixoto";

    }else if(num >= 91 && num <= 95){

        return "Carolina Azevedo Guimarães";

    }else if(num >= 96 && num <= 100){

        return "Amanda Correia Viana";

    }

}

Morador* cria_morador(int region){

    Morador* residente;
    residente->id = (gera_id_morador() * 10) + region;
    residente->nome[NOME] = seleciona_nome_morador(residente->id / 100);
    residente->reside = rand_bairro();

}

Ocorrencia* cria_ocorrencia(){

    Ocorrencia* novo = malloc(sizeof(Ocorrencia));
    if(novo == NULL){

        printf("ERRO AO ALOCAR MEMÓRIA!");

        return 0;

    }

    novo->id = gera_id_ocorrencia();
    novo->tipo[NOME] = seleciona_tipo_ocorrencia(novo->id / 1000);
    novo->servico[3] = indica_servico(novo->id / 1000, novo->servico);
    novo->vitima = cria_morador(novo->id % 10);
    return novo;

}
