#ifndef MORADOR_H_INCLUDED
#define MORADOR_H_INCLUDED

#include "bairro.h"

// Forward declaration para Ocorrencia, pois Morador tem um array de Ocorrencia*
typedef struct ocorrencia Ocorrencia;

#define MAX 40

// ---------- DEFININDO ESTRUTURAS --------
typedef struct morador {
    long long int cpf;
    char nome[MAX];
    Bairros *bairro;
    Ocorrencia *ocorrencias[50];
    int num_ocorrencias;
} Morador;

// ------ ºº PROTÓTIPOS DAS FUNÇÕES ºº ------
Morador* cria_morador(Bairros_Hash *ha);

#endif // MORADOR_H_INCLUDED
