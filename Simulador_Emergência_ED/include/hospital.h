#ifndef HOSPITAL_H_INCLUDED
#define HOSPITAL_H_INCLUDED

//---------- DEFININDO ESTRUTURAS --------
typedef struct hospital Hospital;
typedef struct hospital_hash Hospital_Hash;

//------ ºº FUNÇÕES DE IMPLEMENTAÇÂO DO HASHING ºº ------

//---FUNÇÕES PÚBLICAS---
Hospital_Hash *cria_hash_hospital(int tamanho);
void hospital_libera_hash(Hospital_Hash *ha);

int hospital_insere_hash_sem_colisao(Hospital_Hash *ha, Hospital hospital);

int hospital_busca_hash_sem_colisao(Hospital_Hash* ha, int id, Hospital *hospital);

void limpa_hash_hospital(Hospital_Hash *ha); //Retorna: void

Hospital_Hash* preenche_hospital();

#endif // HOSPITAL_H_INCLUDED
