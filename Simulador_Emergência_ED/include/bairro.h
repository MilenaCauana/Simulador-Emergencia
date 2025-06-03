#ifndef BAIRRO_H_INCLUDED
#define BAIRRO_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct Bairros_da_cidade Bairros;
typedef struct bairros_hash Bairros_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Bairros_Hash *cria_hash_bairros(int tamanho);
void bairro_libera_hash(Bairros_Hash *ha);

int bairro_insere_hash_sem_colisao(Bairros_Hash *ha, Bairros bairro);

int bairro_busca_hash_sem_colisao(Bairros_Hash *ha, int mat, Bairros* bairro);

//Bairros* rand_bairro(Bairros_Hash *ha, int num);

void limpa_hash_bairros(Bairros_Hash *ha);

Bairros_Hash* preenche_bairros();

#endif // BAIRRO_H_INCLUDED
