/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Include_commons.h"
#include "Manipula_objetos.h"
#include "Manipula_cenario.h"
#include <time.h>
#include<stdio.h>
#include<windows.h>
#include<process.h>

int main(void)
{
    HANDLE handle = (HANDLE)_spawnl( P_NOWAIT, "beep.exe",
    "Frogger.exe", "Using spawnl", "Arg1", "Arg2", NULL );

    imprime_intro();

    srand(time(NULL));

    print_background();

    inicializa_objetos();

    TerminateProcess(handle, 1);

    return 0;
}
