/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Manipula_objetos.h"
#include <windows.h>
#include <stdlib.h>
//#include "desenha_pixel.hpp"

int tempo_tartaruga_virada=0;

int inicializa_objetos()
{
    char array_objeto[NUM_LINHAS]        = { 'S', 'T', 'T', 'T', 'R', 'r', 'C', 'C', 'C', 'C', 'C'};
    int array_tamanho[NUM_LINHAS]        = {   2,   8,   6,   3,   8,   4,  10,  10,  10,  10,  10};
    int array_espacamento[NUM_LINHAS]    = {   0,   8,  18,  21,   8,   4,  38,  14,  14,  14,  38};
    float array_velocidade[NUM_LINHAS]   = {   0, 0.5,   1, 0.5,-0.3,-0.3, 1.5,-0.4, 0.5,-0.3, 0.5};
    int array_linha_inicial[NUM_LINHAS]  = {  27,   5,   9,  13,   7,  11,  17,  19,  21,  23,  25};
    int array_coluna_inicial[NUM_LINHAS] = {  25,   3,  23,   3,  12,  10,   2,  22,  19,  13,   3};
    int array_temporizador[NUM_LINHAS]   = {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

    int i;

    /* Passar os valores dos vetores declarados acima para as estruturas dos objetos */
    for (i = 0; i < NUM_LINHAS; i++)
    {
        objetos[i].objeto = array_objeto[i];
        objetos[i].tamanho = array_tamanho[i];
        objetos[i].espacamento = array_espacamento[i];
        objetos[i].velocidade = array_velocidade[i];
        objetos[i].temporizador = array_temporizador[i];
        objetos[i].linha_inicial = array_linha_inicial[i];
        objetos[i].coluna_inicial = array_coluna_inicial[i];
    }

    imprime_objetos();
    return 0;
}

int imprime_objetos()
{
    int deu_a_volta = 0;
    int coluna;
    int j,i;
    float velocidade = 10;

    while(1)
    {
        LockWindowUpdate(GetConsoleWindow());
        print_background();

        /*para cada objeto MENOS o sapo (deve ser impresso por ultimo para se
        sobrepor aos troncos e tartarugas*/
        for(i=1;i<11;i++)
        {
            imprime_objeto(objetos[i]);
        }

        /*agora imprime sapo*/
        imprime_objeto(objetos[0]);

        //Sleep(100);

        char a=' ';

        if (_kbhit() != 0)
        {
            a =_getch();

            switch (a)
            {
            case 'w': //UP
                objetos[0].linha_inicial-=2;
                imprime_pontuacao(1);
                break;
            case 's': //DOWN
                objetos[0].linha_inicial+=2;
                imprime_pontuacao(1);
                break;
            case 'a': //LEFT
                objetos[0].coluna_inicial-=2;
                imprime_pontuacao(1);
                break;
            case 'd': //RIGHT
                objetos[0].coluna_inicial+=2;
                imprime_pontuacao(1);
                break;
            }
        }

        imprime_pontuacao(0);
        imprime_vidas();

        LockWindowUpdate(NULL);
        Sleep(100);

        if(a=='p') //PAUSE
        {
            int terminou = menu();
            gotoxy(1,27);
            if(terminou)
                return 0;
        }

        if(retorna_status_jogo()||a=='q')
        {
            imprime_fim_de_jogo();
            sinaliza_fim_de_jogo(0);

        }

        //desenha_sapo(objetos[0].coluna_inicial, objetos[0].linha_inicial);

        atualiza_objeto(&objetos[0]);
        for(i=1;i<11;i++)
        {
            atualiza_objeto(&objetos[i]);
            if(objetos[i].objeto == 'R' || objetos[i].objeto == 'r')
            {
                rotaciona_tartaruga (&objetos[i]);
            }
        }

    }
    return  0;
}

int atualiza_objeto (struct TIPO_FASE* objeto)
{
    objeto->coluna_inicial+=2*objeto->velocidade;

    if(objeto->coluna_inicial>=50)
    {
        objeto->coluna_inicial=2;
    }

    if(objeto->coluna_inicial<2)
    {
        objeto->coluna_inicial=49;
    }
    return 0;
}

int imprime_objeto(struct TIPO_FASE objeto)
{
    int i;
    int deu_a_volta = 0;
    int col_cursor = objeto.coluna_inicial;
    int old_col_cursor;

    if (objeto.objeto == 'S')
    {
        trata_colisao_sapo();
    }

    while(!deu_a_volta)
    {
        //imprime a primeira linha do objeto
        gotoxy(col_cursor, objeto.linha_inicial);
        old_col_cursor = col_cursor;
        for(i = 0; i < objeto.tamanho; i++)
        {
            /* Se o objeto bateu na parede da direita */
            if(col_cursor >= 50)
            {
                col_cursor = 2; /* Comeca a imprimir o objeto novamente na esquerda */
                gotoxy(col_cursor, objeto.linha_inicial);
            }
            imprime_ASCII(objeto, 0, i);
            col_cursor++;
        }

        /* Atualiza col_cursor com seu valor na iteracao anterior para que se
        iguale a posicao dada pela funcao gotoxy */
        col_cursor = old_col_cursor;

        //imprime a segunda linha do objeto
        gotoxy(col_cursor, objeto.linha_inicial-1);
        for(i = 0; i < objeto.tamanho; i++)
        {
            /* Se o objeto bateu na parede da direita */
            if(col_cursor >= 50)
            {
                col_cursor = 2; /* Comeca a imprimir o objeto novamente na esquerda */
                gotoxy(col_cursor, objeto.linha_inicial-1);
            }
            imprime_ASCII(objeto, 1, i);
            col_cursor++;

        }
        col_cursor += objeto.espacamento;
        if(col_cursor >= 50)
        {
            col_cursor -= 48;
        }
        //terminou de imprimir aquela linha do objeto
        if(col_cursor == objeto.coluna_inicial)
        {
            deu_a_volta = 1;
        }
        /* Evita que o sapo seja impresso indefinidamente */
        if(objeto.espacamento == 0)
        {
            deu_a_volta = 1;
        }
    }
    return 0;
}

int imprime_ASCII (struct TIPO_FASE objeto, int linha, int coluna)
{
    char array_ASCII_carro_1[TAM_CARRO]          = {' ', '_', '|',  '=', '\\', '_',  '_', '_', ' ', ' '};
    char array_ASCII_carro_2[TAM_CARRO]          = {'/', 'o', '_', '_',  '_', '_',  'o', '_', '\\', ' '};
    char array_ASCII_carro_3[TAM_CARRO]          = {' ', ' ', '_', '_',  '_', '/',  '=', '|',  '_', ' '};
    char array_ASCII_carro_4[TAM_CARRO]          = {' ', '/', '_', 'o',  '_', '_',  '_', '_',  'o', '\\'};
    char array_ASCII_tronco[1]                   = {'#'};
    char array_ASCII_tartaruga_1[TAM_TARTARUGA]  = {'/', '\\', '/', '\\'};
    char array_ASCII_tartaruga_2[TAM_TARTARUGA]  = {'\\', '/', '\\', '/'};
    char array_ASCII_sapo_1[2]                   = {'@', '@'};
    char array_ASCII_sapo_2[2]                   = {'0', '0'};

    switch(objeto.objeto)
    {
    case 'S':
        desenha_sapo(objetos[0].coluna_inicial, objetos[0].linha_inicial);
        textcolor(LIGHTGREEN);
        if(linha == 1)
        {
            printf("%c", array_ASCII_sapo_1[coluna]);
        }
        else
        {
            printf("%c", array_ASCII_sapo_2[coluna]);
        }
        textcolor(WHITE);
        break;

    case 'T': //Tronco
        textcolor(30);
        printf("%c", array_ASCII_tronco[0]);
        textcolor(WHITE);
        break;

    case 'R': //Tartaruga
        textcolor(GREEN);
        if(linha == 1)
        {
            printf("%c", array_ASCII_tartaruga_1[(coluna%objeto.tamanho)%4]);
        }
        else
        {
            printf("%c", array_ASCII_tartaruga_2[(coluna%objeto.tamanho)%4]);
        }
        textcolor(WHITE);
        break;

    case 'r': //Tartaruga virada
        textcolor(GREEN);
        if(linha == 1)
        {
            printf("%c", array_ASCII_tartaruga_2[(coluna%objeto.tamanho)%4]);
        }
        else
        {
            printf("%c", array_ASCII_tartaruga_1[(coluna%objeto.tamanho)%4]);
        }
        textcolor(WHITE);
        break;

    case 'C': //Carro
    if(objeto.velocidade > 0) //indo para a direita
    {
        textcolor(LIGHTGRAY);
        if(linha == 1)
        {
            printf("%c", array_ASCII_carro_1[coluna]);
        }
        else
        {
            printf("%c", array_ASCII_carro_2[coluna]);
        }
        textcolor(WHITE);
    }
    else //carro indo para a esquerda
    {
        textcolor(DARKGRAY);
        if(linha == 1)
        {
            printf("%c", array_ASCII_carro_3[coluna]);
        }
        else
        {
            printf("%c", array_ASCII_carro_4[coluna]);
        }
        textcolor(WHITE);
    }
        break;
    }
    return 0;
}

int rotaciona_tartaruga (struct TIPO_FASE* tartaruga)
{
    /* Se a tartaruga esta emergida */
    if(tartaruga->objeto == 'R')
    {
        if(rand()%50 == 0)
        {
            tartaruga->objeto = 'r';
        }
    }
    else
    {
        if(rand()%35 == 0||tempo_tartaruga_virada>20)
        {
            tempo_tartaruga_virada=0;
            tartaruga->objeto = 'R';
        }
        if(tempo_tartaruga_virada>20)
            tempo_tartaruga_virada=0;
    }

    tempo_tartaruga_virada++;

    return 0;
}

int aumenta_velocidade_objetos()
{
    int i;

    objetos[0].coluna_inicial=COLUNA_INICIO_SAPO;
    objetos[0].linha_inicial=LINHA_INICIO_SAPO;

    for(i=1;i<10;i++)
    {
        objetos[i].velocidade*=1.5;
    }
    return 0;
}
