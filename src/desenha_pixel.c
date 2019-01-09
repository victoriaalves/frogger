#include "desenha_pixel.h"

int ja_carregou=0;
FILE *f;
HWND myconsole;
HDC mydc;
int rgb_sapo[3][330];

int desenha_sapo(int coluna_inicial, int linha_inicial)
{

    int r,g,b;
    int i,j;
    if(!ja_carregou) //abre o arquivo para carregamento dos pixels apenas uma vez
    {
        ja_carregou=1;
        f = fopen("rgb_sapo.txt", "r");
        //Get a console handle
        myconsole = GetConsoleWindow();
        //Get a handle to device context
        mydc = GetDC(myconsole);

        for(i=0;i<330;i++)//carrega valores do txt para um array
        {
            fscanf(f,"%d %d %d",&r,&g,&b);
            rgb_sapo[0][i]=b;
            rgb_sapo[1][i]=g;
            rgb_sapo[2][i]=r;
        }

        fclose(f);
    }

    int pixel=0;
    for(j=linha_inicial*11;j<linha_inicial*11+22;j++) //row
        for(i=coluna_inicial*7+15;i<coluna_inicial*7+30;i++) //col
        {
            //fscanf(f,"%d %d %d",&r,&g,&b);

            COLORREF COLOR= RGB(rgb_sapo[0][pixel],rgb_sapo[1][pixel],rgb_sapo[2][pixel]);
            if(r+g+b!=0)
                SetPixel(mydc,i,j,COLOR);
            pixel++;

        }

    //ReleaseDC(myconsole, mydc);


    return 0;
}
