#ifndef BAIRRO_H_INCLUDED
#define BAIRRO_H_INCLUDED

#define NOME 30

//---------- DEFININDO ESTRUTURAS --------
typedef struct bairros_da_cidade {
    char nome[NOME];
    int id;
} Bairros;

typedef struct bairros_hash{

    int qtd, tamanho;//qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Bairros **itens;

}Bairros_Hash;


//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Bairros_Hash *cria_hash_bairros(int tamanho);
void bairro_libera_hash(Bairros_Hash *ha);

int bairro_insere_hash_sem_colisao(Bairros_Hash *ha, Bairros bairro);

Bairros* bairro_busca_hash_sem_colisao(Bairros_Hash *ha, int id);

void bairros_exibir(Bairros_Hash *ha);

void exibir_bairro_especifico(Bairros *bairro);

void limpa_hash_bairros(Bairros_Hash *ha);

Bairros_Hash* preenche_bairros();

#endif // BAIRRO_H_INCLUDED
