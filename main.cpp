#include <iostream>
using namespace std;

struct Point
{
	int x;
	int y;
};

#include <vector>
#include <windows.h>
#include <random>
#include <time.h>
#include <cstring>
#include <conio.h>


#define WIDTH 40
#define HEIGHT 20
#define BODYSNAKE '*'
#define APPLE '$'

enum class Direction
{
	up,
	right,
	down,
	left
};

vector<Point> snake = {
	Point{ WIDTH / 2 + 2, HEIGHT / 2 },
	Point{ WIDTH / 2 + 1, HEIGHT / 2 },
	Point{ WIDTH / 2, HEIGHT / 2 },
	Point{ WIDTH / 2 - 1, HEIGHT / 2 },
	Point{ WIDTH / 2 - 2, HEIGHT / 2 }
};
Direction direction = Direction::right;

void drawFence();
void drawSnake();
void drawSnakePoint();
void move();
void gotoxy(int x, int y);
void displayScore();
void startGame();
void startMenu();
void endMenu();
void growingSnake();
void resetSnake();
void drawApple();
bool hitWall();
bool biteYourself();
bool ateApple();
void ShowConsoleCursor(bool);
void drawHeadTail();

Point apple;
Point prevTail;
int score =0;
int speed =400;

int main()
{
    startMenu();
    return 0;
}

// vẽ hàng rào
void drawFence()
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	gotoxy(0, HEIGHT);
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(WIDTH, i);
		cout << '|';
	}
}

// random ra apple
void drawApple()
{
	srand(time(0));
	int x = rand() % (WIDTH - 2) + 2;
	int y = rand() % (HEIGHT - 2) + 2;
	apple = {
		x,
		y,
	};

	gotoxy(x, y);
	cout << APPLE;
	;
}

// đâm vào tường
bool hitWall()
{
     return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}


// tự cắn mình
bool biteYourself()
{
    Point head = snake[0];
	for (int i = 1; i < snake.size(); i++)
		if (head.x == snake[i].x && head.y == snake[i].y)
            return true;
    return false;
}

// ăn táo
bool ateApple()
{
       return  snake[0].x == apple.x && snake[0].y == apple.y;
}

// vị trí score
void displayScore()
{
    gotoxy(0, HEIGHT + 5);
	cout << "Your score: " << score;
}
void startMenu()
{
	cout << "         SNAKE GAME!!!        " << endl;
	cout << "       Welcom to my maze             "<< endl;
	cout << "You Choose:" << endl;
	cout << "Start = 1" << endl;
	cout << "Quit = 2" << endl;
	int option;
	cin >> option;
	if (option == 1)
	{
		system("cls");
		cout << "Choose your: "<< endl;
		cout << "1.Easy" << endl;
		cout << "2.Normal" << endl;
		cout << "3.Hard" << endl;
		int t;
		cin >> t;

		speed = 400 - t * 100;
		system("cls");
		cout << "Loading..." << endl;
		gotoxy(0, 3);
		cout << "Ready!";
		Sleep(1000);
		for (size_t i = 3; i > 0; i--)
		{
			gotoxy(0, 3);
			cout << i << "         ";
			Sleep(1000);
		}
		gotoxy(0, 3);
		cout << "Let's go!";
		Sleep(1000);
		startGame();
	}
	else if (option == 2)
		exit(1);
}

void endMenu()
{

	system("cls");
	gotoxy(0, 0);
	cout << "End game!" << endl;
	cout << "Your score: " << score << endl;
	cout << "Do you want to play again (y/n): ";
	char option;
	cin >> option;
	option = tolower(option);
	if (option == 'y')
	{
		resetSnake();
		startGame();
	}
	else if (option == 'n')
		exit(1);

}
void startGame()
{
    system("cls");
	ShowConsoleCursor(false);

	drawFence();
	drawSnake();
	drawApple();
	displayScore();

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			ch = tolower(ch);
			if (ch == 'a' && direction != Direction::right)
				direction = Direction::left;
			else if (ch == 'w' && direction != Direction::down)
				direction = Direction::up;
			else if (ch == 's' && direction != Direction::up)
				direction = Direction::down;
			else if (ch == 'd' && direction != Direction::left)
				direction = Direction::right;
			else if (ch == 'q')
			{
				endMenu();
				break;
			}
		}
		move();
		drawHeadTail();
		if (ateApple())
		{
			score++;
			displayScore();
			growingSnake();
			drawApple();
		}
		if (biteYourself())
		{
			ShowConsoleCursor(true);
			endMenu();
			break;
		}
		if (hitWall())
		{
			ShowConsoleCursor(true);
			endMenu();
			break;
		}
		Sleep(speed);
	}

}
void drawSnakePoint(Point p)
{
    gotoxy(p.x, p.y);
	cout << BODYSNAKE;
}

void drawSnake()
{
    for (int i = 0; i < snake.size(); i++)
		drawSnakePoint(snake[i]);
}

void resetSnake()
{
	score = 0;
	direction = Direction::right;
	snake = {
		Point{ WIDTH / 2 + 2, HEIGHT / 2 },
		Point{ WIDTH / 2 + 1, HEIGHT / 2 },
		Point{ WIDTH / 2,     HEIGHT / 2 },
		Point{ WIDTH / 2 - 1, HEIGHT / 2 },
		Point{ WIDTH / 2 - 2, HEIGHT / 2 }
	};
}

// Đi  tới toa độ  x,y
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void move()
{
	prevTail = snake.back();
	for (int i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	if (direction == Direction::up)
		snake[0].y -= 1;
	else if (direction == Direction::down)
		snake[0].y += 1;
	else if (direction == Direction::left)
		snake[0].x -= 1;
	else if (direction == Direction::right)
		snake[0].x += 1;
}

void  growingSnake()
{
    snake.push_back(prevTail);
}

void drawHeadTail()
{
	gotoxy(snake[0].x, snake[0].y);
	cout << BODYSNAKE;
	gotoxy(prevTail.x, prevTail.y);
	cout << ' ';
}


