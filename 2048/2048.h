#ifndef _2019011382_07_03_2048_H_
#define _2019011382_07_03_2048_H_

#define SIZE 4
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define EXIT -1
#define NEW -2
#define OTHER -3

extern int Score;
extern int Best;
extern void NewGame(void);
extern int MakeAMove(int Direction);
extern void Print(void);
extern void HideCursor();
extern void SetPos(int x, int y);
extern int GetOrder();

/*
static int MoveToDirection(int Direction);
static int Merge(int Direction);
static int Update(void);
*/

#endif