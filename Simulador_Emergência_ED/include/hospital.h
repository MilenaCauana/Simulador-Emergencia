#ifndef HOSPITAL_H_INCLUDED
#define HOSPITAL_H_INCLUDED

#include <stdbool.h> // Para usar bool

//---------- DEFININDO ESTRUTURAS --------
typedef struct hospital{
    //char nome[40]; Ainda não definimos se terá nome
    int id; // O ID pode ser relacionado ao bairro (e.g., ID Bairro + Sufixo)
    int ambulancias; //Total de ambulancias no hospital
    int ambulancias_disp; //Quantidade de ambulancias disponíveis no momento para atendimento
    //bool disponivel; //Se não houver ambulancia disponível, então o hospital X nao esta disponível (controlado por ambulancias_disp)
}Hospital;

typedef struct hospital_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Hospital **itens;
}Hospital_Hash;

//---Função privada de hashing para evitar repetição no .h ---
int hospital_chave_divisao(int chave, int tamanho);


//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Hospital_Hash *cria_hash_hospital(int tamanho);
void hospital_libera_hash(Hospital_Hash *ha);

int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital);

Hospital* hospital_busca_hash(Hospital_Hash* ha, int id);

void limpa_hash_hospital(Hospital_Hash *ha); //Retorna: void

Hospital_Hash* preenche_hospital();

int despacha_hospital(Hospital_Hash *ha, int id_hospital_ocorrencia);

void liberar_hospital(Hospital_Hash *ha, int id_unidade_hospi);

#endif // HOSPITAL_H_INCLUDED
