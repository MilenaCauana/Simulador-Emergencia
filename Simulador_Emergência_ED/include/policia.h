#ifndef POLICIA_H_INCLUDED
#define POLICIA_H_INCLUDED

#include <stdbool.h>

//---------- DEFININDO ESTRUTURAS --------
typedef struct policia{

    //char nome[40]; Ainda não definimos se terá nome
    int id;
    int viaturas; //Total de viaturas na policia
    int viaturas_disp; //Quantidade de viaturas disponíveis no momento para atendimento
    bool disponivel; //Se não houver viatura disponível, então a policia X nao esta disponível
}Policia;

typedef struct policia_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Policia **itens;
}Policia_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Policia_Hash *cria_hash_policia(int tamanho);
void policia_libera_hash(Policia_Hash *ha);

int policia_insere_hash_sem_colisao(Policia_Hash *ha, Policia policia);

int policia_busca_hash_sem_colisao(Policia_Hash* ha, int id, Policia *policia);

void limpa_hash_policia(Policia_Hash *ha); //Retorna: void

Policia_Hash* preenche_policia();

#endif // POLICIA_H_INCLUDED
