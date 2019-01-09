/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Manipula_arquivos.h"

int carrega_arquivo_binario ()
{
    int i;
    int pontuacao,vidas;

    FILE *ptr_myfile;

    ptr_myfile=fopen("fase.bin","rb");

    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        return 1;
    }

    for ( i=0; i <= 10; i++)
    {
        fseek(ptr_myfile,sizeof(struct TIPO_FASE)*i,SEEK_SET);

        fread(&objetos[i], sizeof(struct TIPO_FASE), 1, ptr_myfile);

    }

    fread(&pontuacao, sizeof(int), 1, ptr_myfile);
    fread(&vidas, sizeof(int), 1, ptr_myfile);

    seta_vidas_pontuacao(pontuacao,vidas);

    fclose(ptr_myfile);
    return 0;
}

int salva_arquivo_binario ()
{
    int i;
    int pontuacao,vidas;

    FILE *ptr_myfile;

    ptr_myfile=fopen("fase.bin","wb");

    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        return 1;
    }

    for ( i=0; i <= 10; i++)
    {
        fwrite(&objetos[i], sizeof(struct TIPO_FASE), 1, ptr_myfile);
    }

    retorna_vidas_pontuacao(&pontuacao,&vidas);

    fwrite(&pontuacao, sizeof(int), 1, ptr_myfile);
    fwrite(&vidas, sizeof(int), 1, ptr_myfile);

    fclose(ptr_myfile);
    return 0;
}

int salva_captura_de_tela()
{
    int i, j;
    int col_cursor;

    FILE *ptr_myfile;

    ptr_myfile=fopen("tela_salva.txt","w");

    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        return 1;
    }

        fprintf(ptr_myfile, "|------------------------------------------------|\n"); //50 caracteres

    for(i=0;i<2;i++){
        fprintf(ptr_myfile, "|");
        fprintf(ptr_myfile, "~~~~~~");
        for(j=0;j<3;j++){
            fprintf(ptr_myfile, "|    |");
            fprintf(ptr_myfile, "~~~~");
        }
        fprintf(ptr_myfile, "|    |");
        fprintf(ptr_myfile, "~~~~~~");
        fprintf(ptr_myfile, "|\n");
    }
    for(i=0;i<10;i++){
        fprintf(ptr_myfile, "|");
        fprintf(ptr_myfile, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        fprintf(ptr_myfile, "|\n");
    }
    for(i=0;i<14;i++){
        fprintf(ptr_myfile, "|                                                |\n");
    }
        fprintf(ptr_myfile, "|------------------------------------------------|\n");

    /* Imprimindo objetos */
    int k;
    //int imprimiu_sapo = 0;
    for(k=1;k<11;k++)
    {
//        if(k==10&&!imprimiu_sapo) //imprime o sapo por ultimo para ficar sobre tartarugas e troncos
//        {
//            k=0;
//            imprimiu_sapo=1;
//        }

        int deu_a_volta = 0;
        int col_cursor = objetos[k].coluna_inicial;
        int old_col_cursor;

        while(!deu_a_volta)
        {
            //imprime a primeira linha do objeto
            old_col_cursor = col_cursor;
            for(i = 0; i < objetos[k].tamanho; i++)
            {
                /* Se o objeto bateu na parede da direita */
                if(col_cursor >= 49)
                {
                    col_cursor = 1; /* Comeca a imprimir o objeto novamente na esquerda */
                }
                imprime_ASCII_arquivo(ptr_myfile,objetos[k], 0, i,col_cursor);
                col_cursor++;
            }

            /* Atualiza col_cursor com seu valor na iteracao anterior para que se
            iguale a posicao dada pela funcao gotoxy */
            col_cursor = old_col_cursor;

            //imprime a segunda linha do objeto
            for(i = 0; i < objetos[k].tamanho; i++)
            {
                /* Se o objeto bateu na parede da direita */
                if(col_cursor >= 49)
                {
                    col_cursor = 1; /* Comeca a imprimir o objeto novamente na esquerda */
                }
                imprime_ASCII_arquivo(ptr_myfile,objetos[k], 1, i,col_cursor);
                col_cursor++;

            }
            col_cursor += objetos[k].espacamento;
            if(col_cursor >= 50)
            {
                col_cursor -= 48;
            }
            //terminou de imprimir aquela linha do objeto
            if(col_cursor == objetos[k].coluna_inicial)
            {
                deu_a_volta = 1;
            }
            /* Evita que o sapo seja impresso indefinidamente */
            if(objetos[k].espacamento == 0)
            {
                deu_a_volta = 1;
            }
        }
    }

    for(i = 0; i < objetos[0].tamanho; i++)
    {
        imprime_ASCII_arquivo(ptr_myfile,objetos[0], 0, i,objetos[0].coluna_inicial+i-1);
        imprime_ASCII_arquivo(ptr_myfile,objetos[0], 1, i,objetos[0].coluna_inicial+i-1);
    }

    fclose(ptr_myfile);
    return 0;
}

int imprime_ASCII_arquivo (FILE *ptr_myfile, struct TIPO_FASE objeto, int linha, int coluna,int coluna_geral)
{

    int posicao_arquivo = ((objeto.linha_inicial-1)*52+coluna_geral-52*linha);

    fseek(ptr_myfile,sizeof(char)*posicao_arquivo,SEEK_SET);

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
        if(linha == 1)
        {
            //printf("imprimindo %cna posicao %d\n",array_ASCII_sapo_1[coluna],posicao_arquivo);
            fprintf(ptr_myfile, "%c", array_ASCII_sapo_1[coluna]);
        }
        else
        {
            //printf("imprimindo %c na posicao %d\n",array_ASCII_sapo_2[coluna],posicao_arquivo);
            fprintf(ptr_myfile, "%c", array_ASCII_sapo_2[coluna]);
        }
        break;

    case 'T': //Tronco
        fprintf(ptr_myfile, "%c", array_ASCII_tronco[0]);
        break;

    case 'R': //Tartaruga
        if(linha == 1)
        {
            fprintf(ptr_myfile, "%c", array_ASCII_tartaruga_1[(coluna%objeto.tamanho)%4]);
        }
        else
        {
            fprintf(ptr_myfile, "%c", array_ASCII_tartaruga_2[(coluna%objeto.tamanho)%4]);
        }
        break;

    case 'r': //Tartaruga virada
        if(linha == 1)
        {
            fprintf(ptr_myfile, "%c", array_ASCII_tartaruga_2[(coluna%objeto.tamanho)%4]);
        }
        else
        {
            fprintf(ptr_myfile, "%c", array_ASCII_tartaruga_1[(coluna%objeto.tamanho)%4]);
        }
        break;

    case 'C': //Carro
    if(objeto.velocidade > 0) //indo para a direita
    {
        if(linha == 1)
        {
            fprintf(ptr_myfile, "%c", array_ASCII_carro_1[coluna]);
        }
        else
        {
            fprintf(ptr_myfile, "%c", array_ASCII_carro_2[coluna]);
        }
    }
    else //carro indo para a esquerda
    {
        if(linha == 1)
        {
            fprintf(ptr_myfile, "%c", array_ASCII_carro_3[coluna]);
        }
        else
        {
            fprintf(ptr_myfile, "%c", array_ASCII_carro_4[coluna]);
        }
    }
        break;
    }

    return 0;
}

