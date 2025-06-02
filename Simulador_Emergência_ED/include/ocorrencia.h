#ifndef OCORRENCIA_H_INCLUDED
#define OCORRENCIA_H_INCLUDED

typedef struct pessoa Morador;

typedef struct emergencias Ocorrencia;

int gera_id_ocorrencia();

char seleciona_tipo_ocorrencia(int num);

int indica_servico(int num, int array[]);

int gera_id_morador();

char seleciona_nome_morador(int num);

Morador* cria_morador(int region);

Ocorrencia* cria_ocorrencia();

#endif // OCORRENCIA_H_INCLUDED
