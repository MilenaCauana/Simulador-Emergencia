#ifndef OCORRENCIA_H_INCLUDED
#define OCORRENCIA_H_INCLUDED

#include <stdbool.h>
#include <time.h> // Para time_t

// Forward declarations para Morador e Bairros para evitar dependência circular
typedef struct morador Morador;
typedef struct bairros_da_cidade Bairros;
typedef struct bairros_hash Bairros_Hash;
typedef struct morador_hash Morador_Hash;

#define MAX 40

//---------- DEFININDO ESTRUTURAS E TIPOS ENUMERADOS --------
typedef enum{
    PENDENTE,
    EM_ATENDIMENTO,
    FINALIZADA
} StatusOcorrencia;

typedef struct ocorrencia{
    int id;
    char tipo[MAX];
    Bairros *bairro; // Ponteiro para o bairro da ocorrência
    bool servico[3]; //INDICES: 0 -> Policia; 1 -> Bombeiro; 2 -> Hospital.
    Morador *morador; // Ponteiro para o morador envolvido na ocorrência
    int prioridade; //Será uma escala de 1 - 5, no qual 1 é o menos prioritário
    int qtd_ciclos_duracao; //Duração total do atendimento
    int ciclos_restantes;
    int ciclo_registro;
    int ciclo_finalizacao;
    int id_unidade_policia;
    int id_unidade_bombeiro;
    int id_unidade_hospital;
    StatusOcorrencia status;
}Ocorrencia;

//------ ºº FUNÇÕES ºº ------
Ocorrencia* cria_ocorrencia(Bairros_Hash* ha, Morador_Hash *hash_morador, int ciclo);

void exibir_ocorrencia_especifica(Ocorrencia *ocorrencia);

#endif // OCORRENCIA_H_INCLUDED
