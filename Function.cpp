#include"Function.h"
#define than 232
#define dau 79
const int doc = 186, ngang = 205, cach = 32, gocTTren = 201, gocPTren = 187, gocTDuoi = 200, gocPDuoi = 188;
// dat lai kich thuoc khung
void resizeCMD(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT bien;
	GetWindowRect(console, &bien);
	MoveWindow(console, bien.left, bien.top, width, height, TRUE);
}
// To mau 
void textColor(int x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
// Ham dich chuyen con tro den toa do x y
void gotoxy(int x, int y)
{
	HANDLE toaDoDen;
	COORD toaDoHienTai = { x, y };
	toaDoDen = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(toaDoDen, toaDoHienTai);
}
// ve hinh
void veHinh(int x, int y, int c, int color)
{
	gotoxy(x, y);
	textColor(color);
	printf("%c", c);
	textColor(7);
}
// tao khung
void creatKhung(KHUNG &khung)
{
	khung.m = 30, khung.n = 120, khung.flagDeleteKhung = 0;
	khung.a = new int*[khung.m];
	for (int i = 0; i < khung.m; i++)
		khung.a[i] = new int[khung.n];
	for (int i = 0; i < khung.m; i++)
	{
		for (int j = 0; j < khung.n; j++)
		{
			if (i == 0 && j == 0) khung.a[i][j] = gocTTren;
			else if (i == 0 && j == khung.n - 1)  khung.a[i][j] = gocPTren;
			else if (i == khung.m - 1 && j == 0)  khung.a[i][j] = gocTDuoi;
			else if (i == khung.m - 1 && j == khung.n - 1)  khung.a[i][j] = gocPDuoi;
			else if (i == 0 || i == khung.m - 1) khung.a[i][j] = ngang;
			else if (j == 0 || j == khung.n - 1) khung.a[i][j] = doc;
			else khung.a[i][j] = cach;
		}
	}
}
// xuat khung
void displayKhung(KHUNG khung)
{
	for (int i = 0; i < khung.m; i++)
	{
		for (int j = 0; j < khung.n; j++)
		if (j == 0 || i == 0 || j == khung.n - 1 || i == khung.m - 1)
			veHinh(j, i, khung.a[i][j], 233);
		printf("\n");
	}
}
// xoa khung
void deleteKhung(KHUNG &khung)
{
	for (int i = 0; i < khung.m; i++)
	{
		for (int j = 0; j < khung.n; j++)
		{
			if (i == 0 || j == 0 || i == khung.m - 1 || j == khung.n - 1)
			{
				khung.a[i][j] = ' ';
				veHinh(j, i, ' ', 7);
			}
		}
	}
}
// tao snake
void creatSnake(SNAKE &snake)
{
	snake.body[0].x = 1;
	snake.body[0].y = 1;
	snake.nBody = 1;
}
// hien thi snake
void displaySnake(SNAKE snake, KHUNG &khung)
{
	for (int i = 0; i < snake.nBody; i++)
	{
		if (i == 0)
		{
			khung.a[snake.body[i].y][snake.body[i].x] = dau;
			veHinh(snake.body[i].x, snake.body[i].y, khung.a[snake.body[i].y][snake.body[i].x], 12);
		}
		else
		{
			khung.a[snake.body[i].y][snake.body[i].x] = than;
			veHinh(snake.body[i].x, snake.body[i].y, khung.a[snake.body[i].y][snake.body[i].x], 10);
		}
	}
}
// xoa snake
void deleteSnake(SNAKE snake, KHUNG &khung)
{
	for (int i = 0; i < snake.nBody; i++)
	{
		khung.a[snake.body[i].y][snake.body[i].x] = ' ';
		veHinh(snake.body[i].x, snake.body[i].y, khung.a[snake.body[i].y][snake.body[i].x], 12);
	}
}
// tao fruit
void creatFruit(FRUIT &f, KHUNG khung)
{
	f.hq.x = khung.n / 2;
	f.hq.y = khung.m / 2;
}
// hien thi fruit
void displayFruit(FRUIT f, KHUNG &khung)
{
	khung.a[f.hq.y][f.hq.x] = '$';
	veHinh(f.hq.x, f.hq.y, '$', 159);
}
// xoa fruit
void deleteFruit(FRUIT f, KHUNG &khung)
{
	khung.a[f.hq.y][f.hq.x] = ' ';
	veHinh(f.hq.x, f.hq.y, ' ', 8);
}
// tao score
void creatScore(SCORE &score)
{
	score.s = 0;
}
// hien thi score
void displayScore(SCORE score, KHUNG khung)
{
	gotoxy(khung.n + 3, 0);
	textColor(15);
	printf("SCORE = %d", score.s);
}
// dieu khien
void dieuKhien(SNAKE &snake)
{
	for (int i = snake.nBody - 1; i > 0; i--)
	{
		snake.body[i].x = snake.body[i - 1].x;  // cai than di theo sau cai dau
		snake.body[i].y = snake.body[i - 1].y;
	}
	if (snake.tt == LEFT)
		snake.body[0].x--;
	else if (snake.tt == RIGHT)
		snake.body[0].x++;
	else if (snake.tt == UP)
		snake.body[0].y--;
	else if (snake.tt == DOWN)
		snake.body[0].y++;
}
// xu ly
int xuLi(SNAKE &snake, FRUIT f, KHUNG &khung, SCORE &score)
{
	if (snake.body[0].x == f.hq.x && snake.body[0].y == f.hq.y)
	{
		for (int i = snake.nBody; i > 0; i--)
		{
			snake.body[i].x = snake.body[i - 1].x;  // cai than di theo sau cai dau
			snake.body[i].y = snake.body[i - 1].y;
		}
		if (snake.tt == LEFT)
			snake.body[0].x--;
		else if (snake.tt == RIGHT)
			snake.body[0].x++;
		else if (snake.tt == UP)
			snake.body[0].y--;
		else if (snake.tt == DOWN)
			snake.body[0].y++;
		snake.nBody++;
		score.s++;
		return 1;
	}
	return 0;
}
// win lost
int winLost(SNAKE &snake, KHUNG &khung)
{
	switch (khung.flagDeleteKhung)
	{
	case -1: // dong khung lai
		creatKhung(khung);
		displayKhung(khung);
		khung.flagDeleteKhung = 0; // cap nhat lai trang thai
		break;
	case 0:
		if (snake.body[0].x == 0 || snake.body[0].x == khung.n - 1 || snake.body[0].y == 0 || snake.body[0].y == khung.m - 1)
			return 0;
		break;
	case 1: // xoa khung thanh cong
		deleteKhung(khung);
		khung.flagDeleteKhung = 2; // cap nhat lai co hieu de tiep tuc kiem tra ma khong can xoa lai khung
		break;
	case 2:
		if (snake.tt == LEFT && snake.body[0].x == 0)
			snake.body[0].x = khung.n - 1;
		if (snake.tt == RIGHT && snake.body[0].x == khung.n - 1)
			snake.body[0].x = 0;
		if (snake.tt == UP && snake.body[0].y == 0)
			snake.body[0].y = khung.m - 1;
		if (snake.tt == DOWN && snake.body[0].y == khung.m - 1)
			snake.body[0].y = 0;
		break;
	}
	for (int i = 1; i < snake.nBody; i++)
	if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		return 0;
	return 1;
}