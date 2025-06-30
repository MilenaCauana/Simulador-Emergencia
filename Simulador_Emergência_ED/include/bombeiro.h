#ifndef BOMBEIRO_H_INCLUDED
#define BOMBEIRO_H_INCLUDED

#include <stdbool.h> // Para usar bool

//---------- DEFININDO ESTRUTURAS --------
typedef struct bombeiro{
    //char nome[40]; Ainda n�o definimos se ter� nome
    int id; // O ID pode ser relacionado ao bairro (e.g., ID Bairro + Sufixo)
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes dispon�veis no momento para atendimento
    //bool disponivel; //Se n�o houver ambulancia dispon�vel, ent�o o bombeiro X nao esta dispon�vel (controlado por caminhoes_disp)
}Bombeiro;

typedef struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
}Bombeiro_Hash;

//---Fun��o privada de hashing para evitar repeti��o no .h ---
int bombeiro_chave_divisao(int chave, int tamanho);


//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Bombeiro_Hash *cria_hash_bombeiro(int tamanho);
void bombeiro_libera_hash(Bombeiro_Hash *ha);

int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro);

Bombeiro* bombeiro_busca_hash(Bombeiro_Hash* ha, int id);

void limpa_hash_bombeiro(Bombeiro_Hash *ha); //Retorna: void

Bombeiro_Hash* preenche_bombeiro();

int despacha_bombeiro(Bombeiro_Hash *ha, int id_bombeiro_ocorrencia);

void liberar_bombeiro(Bombeiro_Hash *ha, int id_unidade_bombeiro);

#endif // BOMBEIRO_H_INCLUDED
