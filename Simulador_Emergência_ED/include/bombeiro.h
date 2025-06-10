#ifndef BOMBEIRO_H_INCLUDED
#define BOMBEIRO_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct bombeiro{

    //char nome[40]; Ainda não definimos se terá nome
    int id;
    int caminhoes; //Total de caminhoes no bombeiro
    int caminhoes_disp; //Quantidade de caminhoes disponíveis no momento para atendimento
    bool disponivel; //Se não houver ambulancia disponível, então o bombeiro X nao esta disponível
}Bombeiro;

typedef struct bombeiro_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Bombeiro **itens;
}Bombeiro_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Bombeiro_Hash *cria_hash_bombeiro(int tamanho);
void bombeiro_libera_hash(Bombeiro_Hash *ha);

int bombeiro_insere_hash_sem_colisao(Bombeiro_Hash *ha, Bombeiro bombeiro);

int bombeiro_busca_hash_sem_colisao(Bombeiro_Hash* ha, int id, Bombeiro *bombeiro);

void limpa_hash_bombeiro(Bombeiro_Hash *ha); //Retorna: void

Bombeiro_Hash* preenche_bombeiro();

#endif // BOMBEIRO_H_INCLUDED

