/**Structs do trabalho**/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//Bairros
typedef struct Bairros_da_cidade{

    char nome[40];
    int id;

}Bairros;

//Serviços

//Polícia
typedef struct Delegacia{

    //char nome[40];
    int id;
    int viaturas;
    int viaturas_disp;
    bool disponivel;


}Policia;

//Hospital
typedef struct Hospitais{

    //char nome[40];
    int id;
    int ambulancias;
    int ambulancias_disp;
    bool disponivel;

}Hospital;

//Bombeiros
typedef struct Corpo_de_Bombeiros{

    //char nome[40];
    int id;
    int caminhoes;
    int caminhoes_disp;
    bool disponivel;

}Bombeiros;

typedef struct pessoa{

    int id;
    char nome[40];
    Bairros *reside;

}Morador;

//Ocorrencias
typedef struct emergencias{

    int id;
    char tipo[40];
    int servico[3];
    Morador *vitima;

}Ocorrencia;

