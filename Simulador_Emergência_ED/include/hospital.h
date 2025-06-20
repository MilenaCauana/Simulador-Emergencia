#ifndef HOSPITAL_H_INCLUDED
#define HOSPITAL_H_INCLUDED

#include <stdbool.h> // Para usar bool

//---------- DEFININDO ESTRUTURAS --------
typedef struct hospital{
    //char nome[40]; Ainda n�o definimos se ter� nome
    int id; // O ID pode ser relacionado ao bairro (e.g., ID Bairro + Sufixo)
    int ambulancias; //Total de ambulancias no hospital
    int ambulancias_disp; //Quantidade de ambulancias dispon�veis no momento para atendimento
    //bool disponivel; //Se n�o houver ambulancia dispon�vel, ent�o o hospital X nao esta dispon�vel (controlado por ambulancias_disp)
}Hospital;

typedef struct hospital_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Hospital **itens;
}Hospital_Hash;

//---Fun��o privada de hashing para evitar repeti��o no .h ---
int hospital_chave_divisao(int chave, int tamanho);


//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Hospital_Hash *cria_hash_hospital(int tamanho);
void hospital_libera_hash(Hospital_Hash *ha);

int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital);

int hospital_busca_hash_sem_colisao(Hospital_Hash* ha, int id, Hospital *hospital);

void limpa_hash_hospital(Hospital_Hash *ha); //Retorna: void

Hospital_Hash* preenche_hospital();

#endif // HOSPITAL_H_INCLUDED
