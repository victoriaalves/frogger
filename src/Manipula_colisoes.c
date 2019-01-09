/*
FROGGER 2015
Integrantes:
Guilherme Cattani de Castro
Victória Elizabetha Alves
*/

#include "Manipula_colisoes.h"

int trata_colisao_sapo ()
{
    int linha_sapo = objetos[0].linha_inicial;
    int coluna_sapo = objetos[0].coluna_inicial;
    /*Dada a posição no sapo na tela, retorna a respectiva posição do
    respectivo carro no array de objetos*/
    int posicao_carro_array = ((linha_sapo-11) / 2)+3;
    int coluna_objeto = objetos[posicao_carro_array].coluna_inicial;
    int coluna_outro_carro = coluna_objeto;

    /*detecta colisões com as paredes*/
    if(coluna_sapo<3||coluna_sapo>47||linha_sapo<3||linha_sapo>27)
    {
        objetos[0].coluna_inicial=COLUNA_INICIO_SAPO;
        objetos[0].linha_inicial =LINHA_INICIO_SAPO;
        decresce_vidas();
    }


    /* Se sapo esta' entre os carros */
    if (linha_sapo > 15 && linha_sapo <= 25 )
    {
        do
        {
            int linha_objeto  = objetos[posicao_carro_array].linha_inicial;
            int espacamento   = objetos[posicao_carro_array].espacamento;
            coluna_outro_carro+=TAM_CARRO+espacamento;

            //gotoxy(1,30);

            /*Evita com que a posição dos carros da linha onde o sapo se encontra
            ultrapassem o tamanho da tela*/
            if(coluna_outro_carro>1+TAM_TELA)
                coluna_outro_carro-=TAM_TELA;

            //printf("coluna proximo corrigida: %d \n",coluna_outro_carro);

            if(coluna_sapo>=coluna_outro_carro && coluna_sapo<=coluna_outro_carro+TAM_CARRO)
            {
                //printf("matou sapo\n");
                objetos[0].coluna_inicial=COLUNA_INICIO_SAPO;
                objetos[0].linha_inicial=LINHA_INICIO_SAPO;
                decresce_vidas();
            }
            else
                printf("                  ");

        }
        while(coluna_outro_carro!=coluna_objeto);
        //printf("testou todos\n");
    }

    /*se sapo esta na agua*/
    int andando_sobre_objeto = 0;
    //printf("coluna_sapo %d",coluna_sapo);
    if (linha_sapo < 14)
    {
        if(linha_sapo<5)
        {
           if(  coluna_sapo==9
              ||coluna_sapo==10
              ||coluna_sapo==11
              ||coluna_sapo==19
              ||coluna_sapo==20
              ||coluna_sapo==21
              ||coluna_sapo==29
              ||coluna_sapo==30
              ||coluna_sapo==31
              ||coluna_sapo==39
              ||coluna_sapo==40
              ||coluna_sapo==41)
            {
                ganhou_jogo();
            }
            else //sapo se afogou nas águas do rio turvo
            {
                objetos[0].coluna_inicial=COLUNA_INICIO_SAPO;
                objetos[0].linha_inicial=LINHA_INICIO_SAPO;
                decresce_vidas();
                return 0;
            }
        }
        else if(linha_sapo!=11&&linha_sapo!=7)/*sao os troncos*/
        {
            int posicao_tronco_array;
            switch(linha_sapo)
            {
                case 13: posicao_tronco_array=3; break;
                case  9: posicao_tronco_array=2; break;
                case  5: posicao_tronco_array=1; break;
            }
            int coluna_objeto = objetos[posicao_tronco_array].coluna_inicial;
            int coluna_outro_tronco= coluna_objeto;
            do
            {
                int linha_objeto  = objetos[posicao_tronco_array].linha_inicial;
                int espacamento   = objetos[posicao_tronco_array].espacamento;
                coluna_outro_tronco+=objetos[posicao_tronco_array].tamanho+espacamento;

                /*Evita com que a posição dos carros da linha onde o sapo se encontra
                ultrapassem o tamanho da tela*/
                if(coluna_outro_tronco>1+TAM_TELA)
                    coluna_outro_tronco-=TAM_TELA;

                //sapo vai navegar no tronco
                if(coluna_sapo-1>=coluna_outro_tronco && coluna_sapo<=coluna_outro_tronco+objetos[posicao_tronco_array].tamanho-2)
                {
                    objetos[0].coluna_inicial+=2*objetos[posicao_tronco_array].velocidade;
                    andando_sobre_objeto = 1;
                }
            }
            while(coluna_outro_tronco!=coluna_objeto);


        }
        else /*sao tartarugas*/
        {
            int posicao_tartaruga_array;
            switch(linha_sapo)
            {
                case 11: posicao_tartaruga_array=5; break;
                case  7: posicao_tartaruga_array=4; break;
            }
            int coluna_objeto = objetos[posicao_tartaruga_array].coluna_inicial;
            int coluna_outra_tartaruga= coluna_objeto;
            do
            {
                int linha_objeto  = objetos[posicao_tartaruga_array].linha_inicial;
                int espacamento   = objetos[posicao_tartaruga_array].espacamento;
                coluna_outra_tartaruga+=objetos[posicao_tartaruga_array].tamanho+espacamento;

                /*Evita com que a posição dos carros da linha onde o sapo se encontra
                ultrapassem o tamanho da tela*/
                if(coluna_outra_tartaruga>1+TAM_TELA)
                    coluna_outra_tartaruga-=TAM_TELA;

                //sapo vai navegar na tartaruga
                if(coluna_sapo-1>=coluna_outra_tartaruga && coluna_sapo<=coluna_outra_tartaruga+objetos[posicao_tartaruga_array].tamanho-2)
                {
                    // Se a tartaruga esta virada para cima, o sapo anda sobre ela
                    if(objetos[posicao_tartaruga_array].objeto == 'R')
                    {
                        objetos[0].coluna_inicial+=2*objetos[posicao_tartaruga_array].velocidade;
                        andando_sobre_objeto = 1;
                    }
                }
            }
            while(coluna_outra_tartaruga!=coluna_objeto);
        }
        // Sapo se afogou
        if (andando_sobre_objeto == 0)
        {
            objetos[0].coluna_inicial=COLUNA_INICIO_SAPO;
            objetos[0].linha_inicial=LINHA_INICIO_SAPO;
            decresce_vidas();
        }
    }
    return 0;
}


