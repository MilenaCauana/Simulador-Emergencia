#ifndef BAIRRO_H_INCLUDED
#define BAIRRO_H_INCLUDED

typedef struct Bairros_da_cidade Bairros;

typedef struct hash Hash;

void confere_alloc(Hash *item);

Hash* cria_hash_bairros(int tamanho);

int chave_divisao(int chave, int tamanho);

int sondagem_linear(int pos, int i, int tamanho);

int insere_hash_ender_aberto(Hash* ha, Bairros bairro);

int busca_hash_ender_aberto(Hash* ha, int mat, Bairros* bairro);

void preenche_bairros();

#endif // BAIRRO_H_INCLUDED
