/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Manipula_menu.h"

int menu()
{
    gotoxy(20,10);
    printf("***************");
    gotoxy(20,11);
    printf("*             *");
    gotoxy(20,12);
    printf("* (N)ovo Jogo *");
    gotoxy(20,13);
    printf("* (D)espausar *");
    gotoxy(20,14);
    printf("* (P)rint tela*");
    gotoxy(20,15);
    printf("* (S)alvar    *");
    gotoxy(20,16);
    printf("* (C)arregar  *");
    gotoxy(20,17);
    printf("* (T)erminar  *");
    gotoxy(20,18);
    printf("*             *");
    gotoxy(20,19);
    printf("***************");
    char a = _getch();

    switch(a)
    {
        case 'n':
            zera_jogo();
            break;
        case 'd':
            break;
        case 'p':
            salva_captura_de_tela();
            break;
        case 's':
            salva_arquivo_binario();
            break;
        case 't':
            return 1;
            break;
        case 'c':
            carrega_arquivo_binario();
            break;
    }
    return 0;
}

