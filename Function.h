#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, XOA };
struct khung
{
	int **a;
	int m;
	int n;
	int flagDeleteKhung;
}; typedef struct khung KHUNG;
struct toaDo
{
	int x;
	int y;
}; typedef struct toaDo TOADO;
struct snake
{
	TOADO body[100];
	int nBody;
	TRANGTHAI tt;
}; typedef struct snake SNAKE;
struct fruit
{
	TOADO hq;
}; typedef struct fruit FRUIT;
struct score
{
	int s;
}; typedef struct score SCORE;
void resizeCMD(int, int);
void gotoxy(int, int);
void textColor(int);
void veHinh(int, int, int, int);

void creatKhung(KHUNG &);
void displayKhung(KHUNG);
void deleteKhung(KHUNG &);

void creatSnake(SNAKE &);
void displaySnake(SNAKE, KHUNG &);
void deleteSnake(SNAKE, KHUNG &);

void creatFruit(FRUIT &, KHUNG);
void displayFruit(FRUIT, KHUNG &);
void deleteFruit(FRUIT, KHUNG &);

void creatScore(SCORE &);
void displayScore(SCORE, KHUNG);

void dieuKhien(SNAKE &);
int xuLi(SNAKE &, FRUIT, KHUNG &, SCORE &);
int winLost(SNAKE &, KHUNG &);