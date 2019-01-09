/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/
#include "Manipula_cenario.h"
#define X 30
#define Y 27
int imprime_intro()
{
    textcolor(GREEN);
    int i;
    int cursorX = X/2-5;
    int cursorY = 3;
    //int cursorY = Y/2-4;

    for(i=0;i<50;i++)
        printf("%c",220);

    printf("\n");


    for(i=0; i<25; i++)
    {
        printf("%c                                                %c\n",219,219);
    }

    printf("%c",219);

    for(i=1;i<49;i++)
        printf("%c",220);

    printf("%c",219);


    gotoxy(5,cursorY++);
    printf("  __");
    gotoxy(5,cursorY++);
    printf(" / _|");
    gotoxy(5,cursorY++);
    printf("| |_ _ __ ___   __ _  __ _  ___ _ __ ");
    gotoxy(5,cursorY++);
    printf("|  _| '__/ _ \\ / _` |/ _` |/ _ \\ '__|");
    gotoxy(5,cursorY++);
    printf("| | | | | (_) | (_| | (_| |  __/ |");
    gotoxy(5,cursorY++);
    printf("|_| |_|  \\___/ \\__, |\\__, |\\___|_|");
    gotoxy(21,cursorY++);
    printf("__/ | __/ |");
    gotoxy(21,cursorY++);
    printf("___/ |___/ ");

    textbackground(BLACK);

    textcolor(GREEN);
    gotoxy(5,cursorY++);
    printf("     ___       ___");
    gotoxy(5,cursorY++);
    printf("    /   \\\\----/   \\");
    gotoxy(5,cursorY++);
    printf("   |-----|   |-----|");
    gotoxy(5,cursorY++);
    printf("   /\\\\_");
    textcolor(WHITE);
    printf("0");
    textcolor(GREEN);
    printf("_/    \\\\_");
    textcolor(WHITE);
    printf("0");
    textcolor(GREEN);
    printf("_/");
    gotoxy(5,cursorY++);
    printf(" -|       o  o     |-");
    gotoxy(5,cursorY++);
    printf("/  \\______________/  \\");
    gotoxy(5,cursorY++);
    printf("\\\\ \\ |   |    |   | / /");
    gotoxy(5,cursorY++);
    printf(" ww ooooo-----ooooo ww");

    cursorY++;
    textcolor(WHITE);
    gotoxy(cursorX+4,cursorY+=3);
    printf("PRESS ANY KEY TO CONTINUE");
    char a=_getch();
    return 0;


}
int print_background()
{
    /*gotoxy(y,x)*/
    clrscr();

    int i, j;
    gotoxy(1,1);
        printf("|------------------------------------------------|\n"); //50 caracteres

    for(i=0;i<2;i++){
        printf("|");
        textcolor(BLUE);
        printf("~~~~~~");
        for(j=0;j<3;j++){
            textcolor(WHITE);
            printf("|    |");
            textcolor(BLUE);
            printf("~~~~");
        }
        textcolor(WHITE);
        printf("|    |");
        textcolor(BLUE);
        printf("~~~~~~");
        textcolor(WHITE);
        printf("|\n");
    }
    for(i=0;i<10;i++){
        printf("|");
        textcolor(BLUE);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        textcolor(WHITE);
        printf("|\n");
    }
    textcolor(WHITE);
    for(i=0;i<14;i++){
        printf("|                                                |\n");
    }
        printf("|------------------------------------------------|\n");
    return 0;
}
