#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/morador.h"
#include "../include/bairro.h"
#include "../include/ocorrencias.h"


#define MAX 40
#define TAMANHO 23

//---FUNÇÕES PRIVADAS---

/*
*---Função de criação de primeira posição de acordo com o ID (chave)--
* Recebe: dois inteiros (chave -id- e o tamanho da tabela)
* Retorna: inteiro referente a posição
*
*/
int morador_chave_divisao(long long int cpf){
    return cpf % 100; // Ele pegará o cpf e retornará a posição na tabela hash em que esse cpf se encontra
}

//---FUNÇÕES PÚBLICAS---

/*
*---Função de criação da tabela--
* Recebe: um tamanho
* Retorna: Um ponteiro para a tabela
*
*/
Morador_Hash* cria_hash_morador(int tamanho){
    Morador_Hash* ha = (Morador_Hash*) malloc(sizeof(Morador_Hash));

    if(ha != NULL){
        ha -> tamanho = tamanho;
        ha -> itens = (Morador**) malloc(tamanho * sizeof(Morador*));

        if(ha -> itens == NULL){
            free(ha);
            return NULL;
        }

        ha -> qtd = 0;

        for(int i = 0; i < ha -> tamanho; i++){
            ha -> itens[i] = NULL;
        }
    }
    return ha;
}

/*
*---Função de liberação da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
*/
void morador_libera_hash(Morador_Hash *ha){
    if (ha != NULL){
        int i;
        for (i = 0; i < ha -> tamanho; i++){
            if (ha -> itens[i] != NULL){
                for (int j = 0; j < ha->itens[i]->num_ocorrencias; j++) {
                    if (ha->itens[i]->ocorrencias[j] != NULL) {
                        free(ha->itens[i]->ocorrencias[j]);
                    }
                }
                free (ha -> itens[i]);
            }
        }
        free(ha -> itens);
        free (ha);
    }
}

/*
*---Função de inserção da tabela--
* Recebe: um ponteiro para a tabela hash e a o morador que será inserido
* Retorna: inteiro booleano para definir se deu certo a inserção
*
*/
int morador_insere_hash_sem_colisao(Morador_Hash *ha, Morador morador){
    if(ha == NULL || ha -> qtd == ha -> tamanho){
        return 0;
    }

    long long int chave = morador.cpf; // CPF como chave
    int pos = morador_chave_divisao(chave);

    // Verifica se a posição já está ocupada (problema de colisão não tratada explicitamente)
    // Para os CPFs predefinidos, não haverá colisão com cpf % 100 na tabela de tamanho 23.
    if (ha->itens[pos] != NULL) {
        // Isso indica uma colisão para uma tabela "sem colisao", que sobrescreveria o item.
        // Com os dados de preenche_morador e TAMANHO 23, os CPFs gerarão posições únicas (01 a 20).
        printf("AVISO: Colisao detectada na insercao do morador %lld na posicao %d. Dados podem ser sobrescritos ou nao inseridos.\n", morador.cpf, pos);
        return 0; // Ou implementar tratamento de colisão aqui
    }


    Morador *novo;
    novo = (Morador *) malloc(sizeof(Morador));

    if (novo == NULL){
        return 0;
    }

    *novo = morador;
    ha -> itens[pos] = novo;
    ha -> qtd ++;

    return 1;
}

/*
*---Função de busca da tabela--
* Recebe: um ponteiro para a tabela hash,  e o morador que será buscada
* Retorna: = NULL se não der certo ou um ponteiro para o bairro
*
* Para receber o aluno, mandar como parâmetro um ponteiro do tipo bairro, o qual será atribuido as informações
*
*/
Morador* morador_busca_hash_sem_colisao(Morador_Hash* ha, long long int cpf){ // CPF como chave
   if (ha == NULL){
    return NULL;
   }

   int pos = morador_chave_divisao(cpf);

   if (ha -> itens[pos] == NULL){
    return NULL;
   }

   // Verifica se o CPF na posição encontrada realmente corresponde (evita falsos positivos em caso de hash fraco)
   if (ha->itens[pos]->cpf == cpf) {
        return ha -> itens[pos];
   }
   return NULL; // CPF não corresponde, mesmo que o hash colida (se a estratégia de colisão não for linear probing)
}

/*
*---Função que limpa a da tabela--
* Recebe: um ponteiro para a tabela hash
* Retorna: void
*
* "Esvaziar" a tabela hash sem destruí-la completamente.
*
*/
void limpa_hash_morador(Morador_Hash *ha){
    if(ha == NULL){
        return;
    }

    for(int i=0; i < ha->tamanho; i++){
        if(ha->itens[i] != NULL){
            // Libera as cópias das ocorrências antes de liberar o morador
            for (int j = 0; j < ha->itens[i]->num_ocorrencias; j++) {
                if (ha->itens[i]->ocorrencias[j] != NULL) {
                    free(ha->itens[i]->ocorrencias[j]);
                }
            }
            free(ha->itens[i]);
            ha->itens[i] = NULL;
        }
    }
    ha->qtd = 0;
}

/*
*---Função que preenche as informações dos moradores--
* Recebe:
* Retorna: Ponteiro para a tabela
*
*/
Morador_Hash* preenche_morador(){

    Morador_Hash *ha = cria_hash_morador(TAMANHO);
    if (ha == NULL) return NULL;


    //MORADOR 1:
    Morador morador1;
    strcpy(morador1.nome, "Joao Silva Santos");
    morador1.cpf = 78945612301LL;
    morador1.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador1.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador1);

    //MORADOR 2:
    Morador morador2;
    strcpy(morador2.nome, "Pedro Oliveira Costa");
    morador2.cpf = 12378945602LL;
    morador2.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador2.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador2);

    //MORADOR 3:
    Morador morador3;
    strcpy(morador3.nome, "Lucas Pereira Almeida");
    morador3.cpf = 45612378903LL;
    morador3.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador3.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador3);

    //MORADOR 4:
    Morador morador4;
    strcpy(morador4.nome, "Gabriel Souza Rodrigues");
    morador4.cpf = 98765432104LL;
    morador4.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador4.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador4);

    //MORADOR 5:
    Morador morador5;
    strcpy(morador5.nome, "Rafael Fernandes Lima");
    morador5.cpf = 32165498705LL;
    morador5.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador5.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador5);

    //MORADOR 6:
    Morador morador6;
    strcpy(morador6.nome, "Carlos Mendes Carvalho");
    morador6.cpf = 65498732106LL;
    morador6.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador6.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador6);

    //MORADOR 7:
    Morador morador7;
    strcpy(morador7.nome, "Daniel Barbosa Martins");
    morador7.cpf = 15935785207LL;
    morador7.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador7.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador7);

    //MORADOR 8:
    Morador morador8;
    strcpy(morador8.nome, "Andre Rocha Nunes");
    morador8.cpf = 75395125808LL;
    morador8.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador8.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador8);

    //MORADOR 9:
    Morador morador9;
    strcpy(morador9.nome, "Marcelo Castro Ribeiro");
    morador9.cpf = 24680135709LL;
    morador9.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador9.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador9);

    //MORADOR 10:
    Morador morador10;
    strcpy(morador10.nome, "Felipe Gomes Duarte");
    morador10.cpf = 13579246810LL;
    morador10.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador10.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador10);

    //MORADOR 11:
    Morador morador11;
    strcpy(morador11.nome, "Maria Ferreira Alves");
    morador11.cpf = 97531864211LL;
    morador11.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador11.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador11);

    //MORADOR 12:
    Morador morador12;
    strcpy(morador12.nome, "Ana Santos Monteiro");
    morador12.cpf = 86420975312LL;
    morador12.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador12.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador12);

    //MORADOR 13:
    Morador morador13;
    strcpy(morador13.nome, "Sofia Lima Xavier");
    morador13.cpf = 50286419713LL;
    morador13.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador13.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador13);

    //MORADOR 14:
    Morador morador14;
    strcpy(morador14.nome, "Laura Cunha Neves");
    morador14.cpf = 19375826414LL;
    morador14.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador14.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador14);

    //MORADOR 15:
    Morador morador15;
    strcpy(morador15.nome, "Beatriz Cardoso Dias");
    morador15.cpf = 71498253615LL;
    morador15.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador15.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador15);

    //MORADOR 16:
    Morador morador16;
    strcpy(morador16.nome, "Camila Teixeira Moreira");
    morador16.cpf = 25836914716LL;
    morador16.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador16.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador16);

    //MORADOR 17:
    Morador morador17;
    strcpy(morador17.nome, "Juliana Andrade Pinto");
    morador17.cpf = 36985214717LL;
    morador17.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador17.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador17);

    //MORADOR 18:
    Morador morador18;
    strcpy(morador18.nome, "Isabel Moraes Peixoto");
    morador18.cpf = 47125836918LL;
    morador18.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador18.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador18);

    //MORADOR 19:
    Morador morador19;
    strcpy(morador19.nome, "Carolina Azevedo Guimaraes");
    morador19.cpf = 58214736919LL;
    morador19.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador19.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador19);

    //MORADOR 20:
    Morador morador20;
    strcpy(morador20.nome, "Amanda Correia Viana");
    morador20.cpf = 69321478520LL;
    morador20.num_ocorrencias = 0;
    for (int i = 0; i < 50; i++){ morador20.ocorrencias[i] = NULL; }
    morador_insere_hash_sem_colisao(ha, morador20);

    return ha;
}

/* --- Função para pegar um morador aletório ---
* Recebe: ponteiro para a tabela hash de moradores
* Retorna: ponteiro para um morador aleatório
*
*/
Morador* morador_aleatorio(Morador_Hash *ha){
    if (ha == NULL || ha->qtd == 0) {
        return NULL;
    }
    int num_moradores_preenchidos = 20;
    int indice_aleatorio_do_cpf = (rand() % num_moradores_preenchidos) + 1; // De 1 a 20

    return ha->itens[indice_aleatorio_do_cpf];
}


/*---Função que exibe todos os moradores--
* Recebe: ponteiro para a tabela de moradores
* Retorna:
*
*/
void morador_exibir(Morador_Hash *ha){
    if (ha == NULL) {
        printf("Erro: Tabela hash de morador nao inicializada.\n");
        return;
    }

    for (int i = 0; i < ha -> tamanho; i++){
        if (ha -> itens[i] != NULL){
            printf("\n\n----------------\n\n");
            printf("Nome: %s\n", ha -> itens[i] -> nome);
            printf("CPF: %lld\n", ha -> itens[i] -> cpf);

            //Agora, iremos exibir as ocorrências, para isso, iremos percorrer o vetor de ocorrênicas
            if (ha -> itens[i] -> num_ocorrencias == 0){
                printf("Nao ha ocorrencias para esse morador.\n");
            } else {
                printf("Ocorrencias para este morador:\n");
                for (int j = 0; j < ha->itens[i]->num_ocorrencias; j++){
                    printf("Ocorrencia %d: ", j + 1);
                    exibir_ocorrencia_especifica(ha -> itens[i] -> ocorrencias[j]);
                }
            }
        }
    }
}

/*
*---Função que exibe morador específico--
* Recebe: Ponteiro para morador específico
* Retorna:
*
*/
void exibir_morador_especifico(Morador *morador){
    if (morador == NULL) {
        printf("Erro: Morador nao existe.\n");
        return;
    }

    printf("\n----------------\n");
    printf("Nome: %s\n", morador -> nome);
    printf("CPF: %lld\n", morador -> cpf);

    //Agora, iremos exibir as ocorrências, para isso, iremos percorrer o vetor de ocorrênicas
    if (morador -> num_ocorrencias == 0){
        printf("Nao ha ocorrencias para esse morador.\n");
    } else {
        printf("Ocorrencias para este morador:\n");
        printf("------------------");
        for (int j = 0; j < morador->num_ocorrencias; j++){
            printf("Ocorrencia %d: ", j + 1);
            exibir_ocorrencia_especifica(morador -> ocorrencias[j]);
        }
    }
}
