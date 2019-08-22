#include"Function.h"

int main()
{
	int second = 40;
	resizeCMD(1200, 600);
	system("cls");
	gotoxy(1, 1);
	KHUNG khung;
	creatKhung(khung);
	displayKhung(khung);
	SNAKE snake;
	creatSnake(snake);
	displaySnake(snake, khung);
	FRUIT f;
	creatFruit(f, khung);
	displayFruit(f, khung);
	SCORE score;
	creatScore(score);
	displayScore(score, khung);
	int key;
	while (1)
	{
		deleteSnake(snake, khung);
		if (_kbhit())
		{
			key = _getch();
			if (key == 'A' || key == 'a') snake.tt = LEFT;
			else if (key == 'D' || key == 'd') snake.tt = RIGHT;
			else if (key == 'W' || key == 'w') snake.tt = UP;
			else if (key == 'S' || key == 's') snake.tt = DOWN;
			else if (key == '0') khung.flagDeleteKhung = 1; // xoa khung thanh cong
			else if (key == '1') khung.flagDeleteKhung = -1; // dong lai khung
		}
		if (winLost(snake, khung) == 0)
		{
			gotoxy(khung.n / 2 - 16, khung.m / 2);
			textColor(240);
			printf("=============YOU LOST=============");
			break;
		}
		else;
		dieuKhien(snake);
		if (xuLi(snake, f, khung, score) == 1)
		{
			deleteFruit(f, khung);
			srand(time(0));
			f.hq.x = 1 + rand() % (khung.n - 2);
			f.hq.y = 1 + rand() % (khung.m - 2);
			displayFruit(f, khung);
			displayScore(score, khung);
		}
		else;
		displaySnake(snake, khung);
		Sleep(second);
	}
	for (int i = 0; i < khung.m; i++)
		delete[] khung.a[i];
	delete[] khung.a;
	/*for (int i = 0; i < 256; i++)
	{
	textColor(i);
	printf("%c - %d\n\n", i, i);
	}*/
	_getch();
	return 0;
}