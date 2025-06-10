#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/ocorrencias.h"


#define MAX 40

//------ ºº FUNÇÕES ºº ------
Morador* cria_morador(Bairros_Hash *ha){

    Morador* morador = (Morador*) malloc(sizeof(Morador));

    if(morador == NULL){
        printf("ERRO AO ALOCAR MEMÓRIA!");
        return NULL;
    }


    int num = (rand() % 20) + 1;

    switch (num){

        case 1:
            strcpy(morador -> nome, "Joao Silva Santos");
            morador -> cpf = 78945612301;
            break;

        case 2:
            strcpy(morador -> nome, "Pedro Oliveira Costa");
            morador -> cpf = 12378945602;
            break;

        case 3:
            strcpy(morador -> nome, "Lucas Pereira Almeida");
            morador -> cpf = 45612378903;
            break;

        case 4:
            strcpy(morador -> nome, "Gabriel Souza Rodrigues");
            morador -> cpf = 98765432104;
            break;

        case 5:
            strcpy(morador -> nome, "Rafael Fernandes Lima");
            morador -> cpf = 32165498705;
            break;

        case 6:
            strcpy(morador -> nome, "Carlos Mendes Carvalho");
            morador -> cpf = 65498732106;
            break;

        case 7:
            strcpy(morador -> nome, "Daniel Barbosa Martins");
            morador -> cpf = 15935785207;
            break;

        case 8:
            strcpy(morador -> nome, "Andre Rocha Nunes");
            morador -> cpf = 75395125808;
            break;

        case 9:
            strcpy(morador -> nome, "Marcelo Castro Ribeiro");
            morador -> cpf = 24680135709;
            break;

        case 10:
            strcpy(morador -> nome, "Felipe Gomes Duarte");
            morador -> cpf = 13579246810;
            break;

        case 11:
            strcpy(morador -> nome, "Maria Ferreira Alves");
            morador -> cpf = 97531864211;
            break;

        case 12:
            strcpy(morador -> nome, "Ana Santos Monteiro");
            morador -> cpf = 86420975312;
            break;

        case 13:
            strcpy(morador -> nome, "Sofia Lima Xavier");
            morador -> cpf = 50286419713;
            break;

        case 14:
            strcpy(morador -> nome, "Laura Cunha Neves");
            morador -> cpf = 19375826414;
            break;

        case 15:
            strcpy(morador -> nome, "Beatriz Cardoso Dias");
            morador -> cpf = 71498253615;
            break;

        case 16:
            strcpy(morador -> nome, "Camila Teixeira Moreira");
            morador -> cpf = 25836914716;
            break;

        case 17:
            strcpy(morador -> nome, "Juliana Andrade Pinto");
            morador -> cpf = 36985214717;
            break;

        case 18:
            strcpy(morador -> nome, "Isabel Moraes Peixoto");
            morador -> cpf = 47125836918;
            break;

        case 19:
            strcpy(morador -> nome, "Carolina Azevedo Guimarães");
            morador -> cpf = 58214736919;
            break;

        case 20:
            strcpy(morador -> nome, "Amanda Correia Viana");
            morador -> cpf = 69321478520;
            break;

        default: // Opcional, para valores de 'num' fora do esperado
            strcpy(morador -> nome, "Nome Desconhecido");
            morador -> cpf = 0;
            break;
}

    //Agora, iremos adicionar um bairro aleatório para o morador
    int id_bairro = 1000 + (1 + rand() % 9);
    morador -> bairro = bairro_busca_hash_sem_colisao(ha, id_bairro);

    if (morador -> bairro == NULL){
        printf("AVISO: Nao foi possível atribuir um bairro ao morador");
    }

    //Agora, irei inicilializar o vetor de ocorrencias
    morador -> num_ocorrencias = 0;

    for (int i = 0; i < 50; i++){
        morador -> ocorrencias[i] = NULL;
    }


    return morador;
}
