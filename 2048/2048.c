#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include"2048.h"
#define R SetPos(3, 5)
int main(void)
{
    HideCursor();
    int Direction;

    while (1)
    {
        NewGame();
        Print();

        while (1)
        {
            HideCursor();
            Direction = GetOrder();
            if (Direction == OTHER)
            {
                continue;
            }
            if (Direction == EXIT)
            {
                system("cls");
                R;
                printf("GAME OVER\n");
                Sleep(3000);
                system("cls");
                return 0;
            }
            if (Direction == NEW)
            {
                system("cls");
                R;
                printf("NEW GAME\n");
                Sleep(3000);
                system("cls");
                break;
            }

            int OutCome = MakeAMove(Direction);
            Print();

            if (OutCome == 1)
            {
                Sleep(1000);
                system("cls");
                R;
                printf("YOU WIN\n");
                Sleep(3000);
                system("cls");
                break;
            }
            if (OutCome == 2)
            {
                Sleep(1000);
                system("cls");
                
                R;
                printf("YOU FAILED\n");
                Sleep(3000);
                system("cls");
                break;
            }

        }
    }
   
    return 0;
}