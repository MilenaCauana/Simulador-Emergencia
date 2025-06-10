#ifndef HOSPITAL_H_INCLUDED
#define HOSPITAL_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct hospital{

    //char nome[40]; Ainda não definimos se terá nome
    int id;
    int ambulancias; //Total de ambulancias no hospital
    int ambulancias_disp; //Quantidade de ambulancias disponíveis no momento para atendimento
    bool disponivel; //Se não houver ambulancia disponível, então o hospital X nao esta disponível
}Hospital;

typedef struct hospital_hash{
    int qtd, tamanho; //qtd -> diz respeito à quantidade de elementos já armazenados, e tamanho ao tamanho da tabela hash
    Hospital **itens;
}Hospital_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Hospital_Hash *cria_hash_hospital(int tamanho);
void hospital_libera_hash(Hospital_Hash *ha);

int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital);

int hospital_busca_hash_sem_colisao(Hospital_Hash* ha, int id, Hospital *hospital);

void limpa_hash_hospital(Hospital_Hash *ha); //Retorna: void

Hospital_Hash* preenche_hospital();

#endif // HOSPITAL_H_INCLUDED
