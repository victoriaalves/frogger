/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Include_commons.h"
#include "Manipula_objetos.h"

#define COLUNA_INICIO_SAPO 25
#define LINHA_INICIO_SAPO 27

int imprime_pontuacao(int movimentou);

int imprime_vidas();

int decresce_vidas();

int sinaliza_fim_de_jogo();

int sinaliza_fim_de_jogo(int estado);

int seta_vidas_pontuacao(int _pontuacao,int _vidas);

int retorna_vidas_pontuacao(int *_pontuacao,int *_vidas);

int ganhou_jogo();

int zera_jogo();

int retorna_status_jogo();

int imprime_fim_de_jogo();

