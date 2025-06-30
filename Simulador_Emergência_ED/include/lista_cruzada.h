#ifndef LISTA_CRUZADA_H_INCLUDED
#define LISTA_CRUZADA_H_INCLUDED

#include "bairro.h"
#include "policia.h"
#include "bombeiro.h"
#include "hospital.h"

/*
*---Fun��o para exibir a lista cruzada de bairros e servi�os--
* Recebe: Ponteiros para as tabelas hash de bairros, pol�cia, bombeiro e hospital
* Retorna: void
*
*/
void exibir_lista_cruzada_bairros_servicos(Bairros_Hash *bairros, Policia_Hash *policias, Bombeiro_Hash *bombeiros, Hospital_Hash *hospitais);

#endif // LISTA_CRUZADA_H_INCLUDED
