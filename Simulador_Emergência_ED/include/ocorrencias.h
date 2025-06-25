#ifndef OCORRENCIA_H_INCLUDED
#define OCORRENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // Para time_t

// Forward declarations para Morador e Bairros para evitar depend�ncia circular
typedef struct morador Morador;
typedef struct bairros_da_cidade Bairros;
typedef struct bairros_hash Bairros_Hash;
typedef struct morador_hash Morador_Hash;

#define MAX 40

//---------- DEFININDO ESTRUTURAS E TIPOS ENUMERADOS --------
typedef struct ocorrencia{
    int id;
    char tipo[MAX];
    Bairros *bairro; // Ponteiro para o bairro da ocorr�ncia
    bool servico[3]; //INDICES: 0 -> Policia; 1 -> Bombeiro; 2 -> Hospital.
    Morador *morador; // Ponteiro para o morador envolvido na ocorr�ncia
    int prioridade; //Ser� uma escala de 1 - 5, no qual 1 � o menos priorit�rio
    time_t tempo_registro; // Tempo em que a ocorr�ncia foi registrada (agora representa o ciclo)
    time_t tempo_atendimento; // Tempo em que a ocorr�ncia foi atendida/despachada (agora representa o ciclo)
}Ocorrencia;

//------ �� FUN��ES �� ------
void gera_id_ocorrencia(Ocorrencia *ocorrencia);
// Adicionado hash_morador para que a ocorrencia possa escolher um morador
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha, Morador_Hash *hash_morador);

// Corrigido prot�tipo para void
void exibir_ocorrencia_especifica(Ocorrencia *ocorrencia);

#endif // OCORRENCIA_H_INCLUDED
