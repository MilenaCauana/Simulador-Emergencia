#ifndef FILA_DE_OCORRENCIAS_H_INCLUDED
#define FILA_DE_OCORRENCIAS_H_INCLUDED

typedef struct Bairros_da_cidade Bairro;

typedef struct pessoa Morador;

typedef struct emergencias Ocorrencia;

typedef struct no No;

typedef struct descritor_fila Descritor;

Descritor cria_fila();

void confere_aloc(No *novo);

void exibe_ocorrencia(No *novo);

No* cria_no(Descritor *D);

void adiciona_fim_fila(No* novo, Descritor *D);

void exibe_fila(No *ultimo, Descritor *D);

void free_fila(No* ultimo);

int gera_tempo();

int gera_qtd_no();

void enfileirando();

#endif // FILA_DE_OCORRENCIAS_H_INCLUDED
