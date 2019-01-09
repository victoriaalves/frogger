/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Include_commons.h"
#include "Manipula_objetos.h"

int carrega_arquivo_binario ();

int salva_arquivo_binario ();

int salva_captura_de_tela ();

int imprime_ASCII_arquivo (FILE *ptr_myfile, struct TIPO_FASE objeto, int linha, int coluna, int col_cursor);
