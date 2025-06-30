#ifndef BOMBEIRO_H_INCLUDED
#define BOMBEIRO_H_INCLUDED

#include <stdbool.h> // Para usar bool

//---------- DEFININDO ESTRUTURAS --------
typedef struct bombeiro{
    //char nome[40]; Ainda não definimos se terá nome
    int id; // O ID pode ser relacionado ao bairro (e.g., ID Bairro + Sufixo)
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes disponíveis no momento para atendimento
    //bool disponivel; //Se não houver ambulancia disponível, então o bombeiro X nao esta disponível (controlado por caminhoes_disp)
}Bombeiro;

typedef struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
}Bombeiro_Hash;

//---Função privada de hashing para evitar repetição no .h ---
int bombeiro_chave_divisao(int chave, int tamanho);


//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Bombeiro_Hash *cria_hash_bombeiro(int tamanho);
void bombeiro_libera_hash(Bombeiro_Hash *ha);

int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro);

Bombeiro* bombeiro_busca_hash(Bombeiro_Hash* ha, int id);

void limpa_hash_bombeiro(Bombeiro_Hash *ha); //Retorna: void

Bombeiro_Hash* preenche_bombeiro();

int despacha_bombeiro(Bombeiro_Hash *ha, int id_bombeiro_ocorrencia);

void liberar_bombeiro(Bombeiro_Hash *ha, int id_unidade_bombeiro);

#endif // BOMBEIRO_H_INCLUDED
