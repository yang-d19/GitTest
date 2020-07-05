#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include"2048.h"
#define RI printf("        ")
/*
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define LKBLUE 3
#define RED 4
#define 
*/
static int MoveToDirection(int Direction);
static int Merge(int Direction);
static int Update(void);
static _Bool IsFailed(void);

int DirectX[5] = { -1, 0, 1, 0 };
int DirectY[5] = { 0, 1, 0, - 1 };

int Score = 0;
int Best = 0;

static int ChessBoard[SIZE + 1][SIZE + 1];
static int MaxNumber = 2;

void PrintClr(int Num)
{
    int Value;
    switch (Num)
    {
        case 2: Value = 14; break; //light yellow
        case 4: Value = 9; break; //light blue
        case 8: Value = 13; break; //light purple
        case 16: Value = 3; break; //grey
        case 32: Value = 7; break; //white
        case 64: Value = 1; break; //blue
        case 128: Value = 5; break; //Purple
        case 256: Value = 2; break; //green
        case 512: Value = 4; break; //red
        case 1024: Value = 15; break; //high white
        default: Value = 7;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Value);
}

extern int MakeAMove(int Direction)
{
    _Bool IsChanged = 0;
    if (MoveToDirection(Direction) == 1)
    {
        IsChanged = 1;
    }

    int ExtraScore = Merge(Direction);
    Score += ExtraScore;
    Best = max(Best, Score);

    if (ExtraScore > 0)
    {
        IsChanged = 1;
    }

    MoveToDirection(Direction);

    if (IsChanged == 1)
    {
        Update();
    }

    if (MaxNumber == 2048)
    {
        return 1;    //用户胜局返回1
    }

    if (IsFailed() == 1)
    {
        return 2;    //用户败局返回2
    }

    return 0;        //无法判断返回0
}

extern void Print(void)
{
    
    SetPos(5, 0);
    RI;
    printf("Score: %d\tBest: %d\n", Score, Best);

    RI;
    printf(" ");
    for (int Col = 1; Col <= 19; Col++)
    {
        printf("_");
    }
    printf(" ");
    printf("\n");
    for (int Row = 0; Row < SIZE; Row++)
    {
        RI;
        printf("|");
        for (int Col = 0; Col < SIZE; Col++)
        {
            int Num = ChessBoard[Row][Col];
            if (Num == 0)
            {
                printf("    ");
            }
            else
            {
                PrintClr(Num);
                printf("%4d", Num);
                PrintClr(0);
            }

            printf("|");
        }
        printf("\n");
        RI;
        for (int Col = 0; Col < SIZE; Col++)
        {
            printf("|____");
        }
        printf("|");
        printf("\n");
        
    }

    printf("\n");
    SetPos(9, 36);  printf("按 W A S D 以滑动数字块");
    SetPos(11, 36);    printf("按 X 退出游戏");
    SetPos(13, 36);   printf("按 N 重新开始");

    SetPos(6, 36);
    printf("Powered By Yang Ding");
}

void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);    //获取控制台光标信息
    CursorInfo.bVisible = 0;                      //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);    //设置控制台光标状态
}

void SetPos(int y, int x)
{
    COORD point = { x, y };                           //光标要设置的位置x,y       
    HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄       
    SetConsoleCursorPosition(HOutput, point);         //设置光标位置}
}

static _Bool IsFailed(void)
{
    _Bool IsFull = 1;
    _Bool CanMerge = 0;

    for (int Row = 0; Row < SIZE; Row++)
    {
        for (int Col = 0; Col < SIZE; Col++)
        {
            if (ChessBoard[Row][Col] == 0)
            {
                return 0;
            }
        }
    }

    for (int Row = 0; Row < SIZE - 1; Row++)
    {
        for (int Col = 0; Col < SIZE; Col++)
        {
            if (ChessBoard[Row][Col] == ChessBoard[Row + 1][Col])
            {
                return 0;
            }
        }
    }

    for (int Col = 0; Col < SIZE - 1; Col++)
    {
        for (int Row = 0; Row < SIZE; Row++)
        {
            if (ChessBoard[Row][Col] == ChessBoard[Row][Col + 1])
            {
                return 0;
            }
        }
    }

    return 1;
}

extern void NewGame(void)
{
    Score = 0;
    MaxNumber = 2;
//    memset(ChessBoard, 0, SIZE * SIZE);  //初始化
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            ChessBoard[i][j] = 0;
        }
    }
    Update();
    Update();

}

static int Update()
{
    int SpacePosition[SIZE * SIZE];
    int SpaceCount = 0;
    int TmpPos = 0;
    int RandPos = 0;
    int PosX = 0;
    int PosY = 0;

    for (int Row = 0; Row < SIZE; Row++)
    {
        for (int Col = 0; Col < SIZE; Col++)
        {
            TmpPos = Row * SIZE + Col;
            if (ChessBoard[Row][Col] == 0)
            {
                SpaceCount++;
                SpacePosition[SpaceCount - 1] = TmpPos;
            }
        }
    }

    if (SpaceCount == 0)
    {
        return 0;
    }

    srand((unsigned)time(NULL));

    RandPos = SpacePosition[rand() % SpaceCount];

    ChessBoard[RandPos / SIZE][RandPos % SIZE] = 2;

    return 1;
}

static int MoveToDirection(int Direction)
{

    _Bool IsMoved = 0;
    if (Direction == UP)
    {
        for (int Row = 1; Row < SIZE; Row++)
        {
            for (int Col = 0; Col < SIZE; Col++)
            {
                if (ChessBoard[Row][Col] != 0)
                {
                    int RowMove = Row;
                    do
                    {
                        RowMove--;

                    } while (RowMove >= 0 && ChessBoard[RowMove][Col] == 0);

                    RowMove++;

                    if (RowMove != Row)
                    {
                        IsMoved = 1;
                        ChessBoard[RowMove][Col] = ChessBoard[Row][Col];
                        ChessBoard[Row][Col] = 0;
                    }
                }
            }
        }
        return IsMoved;
    }

    if (Direction == RIGHT)
    {
        for (int Col = SIZE - 2; Col >= 0; Col--)
        {
            for (int Row = 0; Row < SIZE; Row++)
            {
                if (ChessBoard[Row][Col] != 0)
                {
                    int ColMove = Col;
                    do
                    {
                        ColMove++;

                    } while (ColMove < SIZE && ChessBoard[Row][ColMove] == 0);

                    ColMove--;

                    if (ColMove != Col)
                    {
                        IsMoved = 1;
                        ChessBoard[Row][ColMove] = ChessBoard[Row][Col];
                        ChessBoard[Row][Col] = 0;
                    }
                }
            }
        }
        return IsMoved;
    }

    if (Direction == DOWN)
    {
        for (int Row = SIZE - 2; Row >= 0; Row--)
        {
            for (int Col = 0; Col < SIZE; Col++)
            {
                if (ChessBoard[Row][Col] != 0)
                {
                    int RowMove = Row;
                    do
                    {
                        RowMove++;

                    } while (RowMove <SIZE && ChessBoard[RowMove][Col] == 0);

                    RowMove--;

                    if (RowMove != Row)
                    {
                        IsMoved = 1;
                        ChessBoard[RowMove][Col] = ChessBoard[Row][Col];
                        ChessBoard[Row][Col] = 0;
                    }
                }
            }
        }
        return IsMoved;
    }

    if (Direction == LEFT)
    {
        for (int Col = 1; Col < SIZE; Col++)
        {
            for (int Row = 0; Row < SIZE; Row++)
            {
                if (ChessBoard[Row][Col] != 0)
                {
                    int ColMove = Col;
                    do
                    {
                        ColMove--;

                    } while (ColMove >= 0 && ChessBoard[Row][ColMove] == 0);

                    ColMove++;

                    if (ColMove != Col)
                    {
                        IsMoved = 1;
                        ChessBoard[Row][ColMove] = ChessBoard[Row][Col];
                        ChessBoard[Row][Col] = 0;
                    }
                }
            }
        }
        return IsMoved;
    }
    return -1;
}

static int Merge(int Direction)
{
    int iSumScore = 0;

    if (Direction == UP)
    {
        for (int Row = 1; Row < SIZE; Row++)
        {
            for (int Col = 0; Col < SIZE; Col++)
            {
                if (ChessBoard[Row][Col] != 0
                    && ChessBoard[Row][Col] == ChessBoard[Row - 1][Col])
                {
                    ChessBoard[Row - 1][Col] *= 2;
                    ChessBoard[Row][Col] = 0;

                    iSumScore += ChessBoard[Row - 1][Col];
                    MaxNumber = max(MaxNumber, ChessBoard[Row - 1][Col]);
                }
            }
        }
    }

    if (Direction == RIGHT)
    {
        for (int Col = SIZE - 2; Col >= 0; Col--)
        {
            for (int Row = 0; Row < SIZE; Row++)
            {
                if (ChessBoard[Row][Col] != 0
                    && ChessBoard[Row][Col] == ChessBoard[Row][Col + 1])
                {
                    ChessBoard[Row][Col + 1] *= 2;
                    ChessBoard[Row][Col] = 0;

                    iSumScore += ChessBoard[Row][Col + 1];
                    MaxNumber = max(MaxNumber, ChessBoard[Row][Col + 1]);
                 }
            }
        }
    }

    if (Direction == DOWN)
    {
        for (int Row = SIZE - 2; Row >= 0; Row--)
        {
            for (int Col = 0; Col < SIZE; Col++)
            {
                if (ChessBoard[Row][Col] != 0
                    && ChessBoard[Row][Col] == ChessBoard[Row + 1][Col])
                {
                    ChessBoard[Row + 1][Col] *= 2;
                    ChessBoard[Row][Col] = 0;

                    iSumScore += ChessBoard[Row + 1][Col];
                    MaxNumber = max(MaxNumber, ChessBoard[Row + 1][Col]);
                }
            }
        }
    }

    if (Direction == LEFT)
    {
        for (int Col = 1; Col < SIZE; Col++)
        {
            for (int Row = 0; Row < SIZE; Row++)
            {
                if (ChessBoard[Row][Col] != 0
                    && ChessBoard[Row][Col] == ChessBoard[Row][Col - 1])
                {
                    ChessBoard[Row][Col - 1] *= 2;
                    ChessBoard[Row][Col] = 0;

                    iSumScore += ChessBoard[Row][Col - 1];
                    MaxNumber = max(MaxNumber, ChessBoard[Row][Col - 1]);
                }
            }
        }
    }

    return iSumScore;
}

extern int GetOrder()
{
    char Ch = _getch();
    switch (Ch)
    {
        case 'w':
        case 'W': return UP;

        case 'd':
        case 'D': return RIGHT;

        case 's':
        case 'S': return DOWN;

        case 'a':
        case 'A': return LEFT;

        case 'x':
        case 'X': return EXIT;

        case 'n':
        case 'N': return NEW;

        default: return OTHER;
    }
}