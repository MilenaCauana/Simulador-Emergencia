// fila_de_ocorrencia.h
#ifndef FILA_DE_OCORRENCIAS_H_INCLUDED
#define FILA_DE_OCORRENCIAS_H_INCLUDED

#include <stdbool.h> // Para usar o tipo bool
#include "ocorrencias.h" // Inclui a definição de Ocorrencia
#include "policia.h"
#include "bombeiro.h"
#include "hospital.h"
#include "bairro.h"
#include "morador.h" // Inclui a definição de Morador_Hash
#include "../include/pilha1.h"

//---------- DEFININDO ESTRUTURAS --------

/*
*---Estrutura de um nó da fila--
* Contém um ponteiro para uma Ocorrencia e um ponteiro para o próximo nó.
*
*/
typedef struct no {
    Ocorrencia *ocorrencia;
    struct no *prox;
}No;

/*
*---Estrutura do descritor da fila--
* Contém ponteiros para o início e fim da fila, e o tamanho atual.
*
*/
typedef struct descritor_fila {
    No *inicio;
    No *fim;
    int tamanho;
}Descritor;

//------ ºº PROTÓTIPOS DAS FUNÇÕES ºº ------

/*
*---Função de criação e inicialização da fila--
* Recebe: void
* Retorna: Um ponteiro para um descritor da fila
*
*/
Descritor* cria_fila();

/*
*---Função para verificar alocação de memória--
* Recebe: Um ponteiro genérico
* Retorna: void (encerra o programa se a alocação falhar)
*
*/
void confere_aloc(void *ptr);

/*
*---Função para criar um novo nó da fila com uma ocorrência--
* Recebe: Um ponteiro para a tabela hash de bairros e de moradores (para criar a ocorrência)
* Retorna: Um ponteiro para o nó recém-criado
*
*/
No* cria_no(Bairros_Hash *ha, Morador_Hash *hash_morador);

/*
*---Função para adicionar uma ocorrência na fila de prioridade--
* A inserção mantém a fila ordenada por prioridade (maior prioridade primeiro).
* Recebe: Um ponteiro para o nó a ser adicionado e um ponteiro para o descritor da fila
* Retorna: void
*
*/
void adiciona_na_fila_prioridade(No* novo, Descritor *D);

/*
*---Função para remover uma ocorrência do início da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: Um ponteiro para a ocorrência removida, ou NULL se a fila estiver vazia
*
*/
Ocorrencia* remove_da_fila(Descritor *D);

/*
*---Função para exibir as informações de uma ocorrência--
* (Esta função agora chama exibir_ocorrencia_especifica de ocorrencias.c)
* Recebe: Um ponteiro para a ocorrência
* Retorna: void
*
*/
void exibe_ocorrencia(Ocorrencia *ocorrencia);

/*
*---Função para exibir todos os itens da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void exibe_fila(Descritor *D);

/*
*---Função para liberar a memória da fila--
* Recebe: Um ponteiro para o descritor da fila
* Retorna: void
*
*/
void free_fila(Descritor* D);

/*
*---Função para gerar um tempo aleatório (simulação de espera)--
* Recebe: void
* Retorna: inteiro (tempo em segundos)
*
*/
int gera_tempo();

/*
*---Função para gerar uma quantidade aleatória de nós (ocorrências)--
* Recebe: void
* Retorna: inteiro (quantidade de ocorrências)
*
*/
int gera_qtd_no();

/*
*---Função para simular o enfileiramento de ocorrências--
* Recebe: Um ponteiro para o descritor da fila, a tabela hash de bairros e de moradores
* Retorna: void
*
*/
void enfileirando(Descritor *D, Bairros_Hash *ha, Morador_Hash *hash_morador);

/*
*---Função para buscar e despachar uma unidade de polícia--
* Recebe: A tabela hash da polícia, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_policia(Policia_Hash *policia_ha, int id_bairro_ocorrencia);

/*
*---Função para buscar e despachar uma unidade de bombeiro--
* Recebe: A tabela hash do bombeiro, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_bombeiro(Bombeiro_Hash *bombeiro_ha, int id_bairro_ocorrencia);

/*
*---Função para buscar e despachar uma unidade de hospital--
* Recebe: A tabela hash do hospital, o ID do bairro da ocorrência
* Retorna: true se uma unidade foi despachada, false caso contrário
*
*/
bool despacha_hospital(Hospital_Hash *hospital_ha, int id_bairro_ocorrencia);

/*
*---Função para simular o despacho de serviços--
* Recebe: A ocorrência a ser despachada e as tabelas hash das unidades de serviço
* Retorna: void
*
*/
void despacha_servicos(Ocorrencia *ocorrencia, Policia_Hash *policia_ha, Bombeiro_Hash *bombeiro_ha, Hospital_Hash *hospital_ha);

void free_ocorrencia(Ocorrencia *ocorr);

#endif // FILA_DE_OCORRENCIAS_H_INCLUDED
