#pragma once
/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#define _WIN32_WINNT 0x0500
#include "Include_commons.h"
#include <windows.h>
#include "desenha_pixel.h"
#include "Manipula_menu.h"
#include "Manipula_colisoes.h"
//#include "Manipula_pontuacao.h"
//#include "Manipula_cenario.h"


#define TAM_CARRO 10
#define TAM_TARTARUGA 4

typedef struct TIPO_FASE
{
    char objeto;
    int tamanho;
    int espacamento;
    float velocidade;
    int temporizador;
    int linha_inicial;
    int coluna_inicial;
};

struct TIPO_FASE objetos[NUM_LINHAS];

/* Preenche o array de estruturas TIPO_FASE com os valores iniciais */
int inicializa_objetos();

/* Imprime os objetos na tela de acordo com os valores armazenados na estrutura
 TIPO_FASE */
int imprime_objetos();

/* Imprime o tronco na tela */
int imprime_objeto(struct TIPO_FASE objeto);

/* Atualiza velocidade e posicao do objeto em questao */
int atualiza_objeto(struct TIPO_FASE* objeto);

/* Imprime os caracteres do objeto passado como parametro */
int imprime_ASCII (struct TIPO_FASE objeto, int linha, int coluna);

/* Rotaciona as tartarugas para submergirem na agua */
int rotaciona_tartaruga (struct TIPO_FASE* tartaruga);

/*Aumenta a velocidade de todos os objetos para a passagem do proximo nivel*/
int aumenta_velocidade_objetos();




