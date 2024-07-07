#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define ANCHO 20

void limpiarPantalla()
{
    system("cls");
}

void dibujarNave(int posicion, char simbolo)
{
    for (int i = 0; i < ANCHO; i++)
    {
        if (i == posicion)
        {
            printf("%c", simbolo);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main()
{
    int posicion = ANCHO / 2;
    char simbolo = '@';
    char tecla;

    while (1)
    {
        limpiarPantalla();
        dibujarNave(posicion, simbolo);

        if (_kbhit())
        {
            tecla = _getch();
            switch (tecla)
            {
            case 'a':
                if (posicion > 0)
                    posicion--;
                break;
            case 'd':
                if (posicion < ANCHO - 1)
                    posicion++;
                break;
            case 'c':
                if (simbolo == '@')
                    simbolo = '%';
                else if (simbolo == '%')
                    simbolo = '&';
                else
                    simbolo = '@';
                break;
            case 'q':
                return 0;
            }
        }
        Sleep(50);
    }

    return 0;
}