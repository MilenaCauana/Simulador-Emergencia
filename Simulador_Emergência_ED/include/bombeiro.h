#ifndef BOMBEIRO_H_INCLUDED
#define BOMBEIRO_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct bombeiro{

    //char nome[40]; Ainda n�o definimos se ter� nome
    int id;
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes dispon�veis no momento para atendimento
    bool disponivel; //Se n�o houver ambulancia dispon�vel, ent�o o bombeiro X nao esta dispon�vel
}Bombeiro;

typedef struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito � quantidade de elementos j� armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
}Bombeiro_Hash;

//------ �� FUN��ES DE IMPLEMENTA��O DO HASHING �� ------

//---FUN��ES P�BLICAS---
Bombeiro_Hash *cria_hash_bombeiro(int tamanho);
void bombeiro_libera_hash(Bombeiro_Hash *ha);

int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro);

int bombeiro_busca_hash_sem_colisao(Bombeiro_Hash* ha, int id, Bombeiro *bombeiro);

void limpa_hash_bombeiro(Bombeiro_Hash *ha); //Retorna: void

Bombeiro_Hash* preenche_bombeiro();

#endif // BOMBEIRO_H_INCLUDED

