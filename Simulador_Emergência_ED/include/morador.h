#ifndef MORADOR_H_INCLUDED
#define MORADOR_H_INCLUDED

// Forward declaration para Bairros e Ocorrencia para evitar depend�ncia circular
typedef struct bairros_da_cidade Bairros;
typedef struct ocorrencia Ocorrencia;

#define MAX 40
#define TAMANHO 23 // Tamanho da hash para moradores, ajustado para os CPFs gerados

// ---------- DEFININDO ESTRUTURAS --------
typedef struct morador {
    long long int cpf; // Alterado para long long int para o CPF
    char nome[MAX];
    Ocorrencia *ocorrencias[50]; // Um array de ponteiros para as ocorr�ncias
    int num_ocorrencias;
} Morador;

typedef struct morador_hash{
    int qtd, tamanho;//qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Morador **itens;
}Morador_Hash;

//---Fun��o privada de hashing para evitar repeti��o no .h ---
int morador_chave_divisao(long long int cpf);


//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Morador_Hash *cria_hash_morador(int tamanho);
void morador_libera_hash(Morador_Hash *ha);

int morador_insere_hash_sem_colisao(Morador_Hash *ha, Morador morador);

Morador* morador_busca_hash_sem_colisao(Morador_Hash *ha, long long int cpf); // Alterado para long long int

void limpa_hash_morador(Morador_Hash *ha);

Morador_Hash* preenche_morador();

Morador* morador_aleatorio(Morador_Hash *ha); // Adicionado ponto e virgula

// ------ �� PROT�TIPOS DAS FUN��ES DE EXIBI��O �� ------
void morador_exibir(Morador_Hash *ha);
void exibir_morador_especifico(Morador *morador);

#endif // MORADOR_H_INCLUDED
