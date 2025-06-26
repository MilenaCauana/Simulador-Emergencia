#ifndef POLICIA_H_INCLUDED
#define POLICIA_H_INCLUDED

#include <stdbool.h>

//---------- DEFININDO ESTRUTURAS --------
typedef struct policia{
    //char nome[40]; Ainda n�o definimos se ter� nome
    int id; // ID �nico da unidade policial, pode ser relacionado ao ID do bairro
    int viaturas; //Total de viaturas na policia
    int viaturas_disp; //Quantidade de viaturas dispon�veis no momento para atendimento
    //bool disponivel; //Se n�o houver viatura dispon�vel, ent�o a policia X nao esta dispon�vel (controlado por viaturas_disp)
}Policia;

typedef struct policia_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Policia **itens;
}Policia_Hash;

//---Fun��o privada de hashing para evitar repeti��o no .h ---
int policia_chave_divisao(int chave, int tamanho);


//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Policia_Hash *cria_hash_policia(int tamanho);
void policia_libera_hash(Policia_Hash *ha);

int policia_insere_hash_sem_colisao(Policia_Hash *ha, Policia policia);

int policia_busca_hash_sem_colisao(Policia_Hash* ha, int id, Policia *policia);

void limpa_hash_policia(Policia_Hash *ha); //Retorna: void

Policia_Hash* preenche_policia();

int despacha_policia(Policia_Hash *ha, int id_bairro_ocorrencia);

void liberar_policia(Policia_Hash *ha, int id_unidade_policial);

#endif // POLICIA_H_INCLUDED
