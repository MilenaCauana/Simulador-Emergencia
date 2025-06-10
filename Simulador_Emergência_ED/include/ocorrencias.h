#ifndef OCORRENCIA_H_INCLUDED
#define OCORRENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/ocorrencias.h"
#include "../include/morador.h"
#include "../include/bairro.h"

// Forward declaration para Morador, pois Ocorrencia tem um Morador*
typedef struct morador Morador;

#define MAX 40

//---------- DEFININDO ESTRUTURAS E TIPOS ENUMERADOS --------
typedef struct ocorrencia{
    int id;
    char tipo[MAX];
    Bairros *bairro;
    bool servico[3]; //INDICES: 0 -> Policia; 1 -> Bombeiro; 2 -> Hospital.
    Morador *morador;
    int prioridade; //Será uma escala de 1 - 5, no qual 1 é o menos prioritário
    time_t tempo_registro; // Tempo em que a ocorrência foi registrada
    time_t tempo_atendimento; // Tempo em que a ocorrência foi atendida/despachada
}Ocorrencia;

//------ ºº FUNÇÕES ºº ------
void gera_id_ocorrencia(int num, Ocorrencia *ocorrencia);
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha);

#endif // OCORRENCIA_H_INCLUDED
