#ifndef POLICIA_H_INCLUDED
#define POLICIA_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct policia Policia;
typedef struct policia_hash Policia_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Policia_Hash *cria_hash_polica(int tamanho);
void policia_libera_hash(Policia_Hash *ha);

int policia_insere_hash_sem_colisao(Policia_Hash *ha, Policia policia);

int policia_busca_hash_sem_colisao(Policia_Hash* ha, int id, Policia *policia);

void limpa_hash_policia(Policia_Hash *ha); //Retorna: void

Policia_Hash* preenche_policia();

#endif // POLICIA_H_INCLUDED
