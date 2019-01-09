/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Manipula_pontuacao.h"

int pontuacao = 50;
int vidas = 3;
int fim_de_jogo = 0;

int imprime_pontuacao(int movimentou)
{
    gotoxy(1,29);
    printf("Pontos: %2d", pontuacao);

    if(movimentou)
    {
        pontuacao--;
    }
    if(pontuacao==0)
    {
        decresce_vidas();
        pontuacao=50;
    }
    return 0;
}

int imprime_vidas()
{
    int i;

    gotoxy(15,29);

    printf("Vidas: ");

    textcolor(RED);
    for(i=0;i<vidas;i++)
    {
        printf("%c",3);
    }
    textcolor(WHITE);
    return 0;
}

int decresce_vidas()
{
    vidas--;

    if(!vidas)
    {
        sinaliza_fim_de_jogo(1);
        zera_jogo();
    }
    return 0;
}

int imprime_fim_de_jogo()
{

    gotoxy(19,10);
    printf("***************");
    gotoxy(19,11);
    printf("*             *");
    gotoxy(19,12);
    printf("*  GAME OVER  *");
    gotoxy(19,13);
    printf("*             *");
    gotoxy(19,14);
    printf("***************");
    char a = _getch();

    return 0;
}

int sinaliza_fim_de_jogo(int estado)
{
    fim_de_jogo = estado; //estado =1 fim de jogo e 0 caso contrário
    return 0;
}

int retorna_status_jogo()
{
    return fim_de_jogo;
}

int ganhou_jogo()
{
    int i;
    pontuacao+=50;

    //aumenta velocidade dos objetos para o proximo nivel
    aumenta_velocidade_objetos();

    return 0;
}

int zera_jogo()
{
    pontuacao=50;
    vidas=3;
    inicializa_objetos();
    return 0;
}

int seta_vidas_pontuacao(int _pontuacao,int _vidas)
{
    pontuacao=_pontuacao;
    vidas=_vidas;

    return 0;
}

int retorna_vidas_pontuacao(int *_pontuacao,int *_vidas)
{
    *_pontuacao = pontuacao;
    *_vidas = vidas;

    return 0;
}
