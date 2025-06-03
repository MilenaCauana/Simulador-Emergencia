#ifndef BOMBEIRO_H_INCLUDED
#define BOMBEIRO_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct bombeiro Bombeiro;
typedef struct bombeiro_hash Bombeiro_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Bombeiro_Hash *cria_hash_bombeiro(int tamanho);
void bombeiro_libera_hash(Bombeiro_Hash *ha);

int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro);

int bombeiro_busca_hash_sem_colisao(Bombeiro_Hash* ha, int id, Bombeiro *bombeiro);

void limpa_hash_bombeiro(Bombeiro_Hash *ha); //Retorna: void

Bombeiro_Hash* preenche_bombeiro();

#endif // BOMBEIRO_H_INCLUDED

