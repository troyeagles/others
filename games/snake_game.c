//motivated by google snake game
//with visual studio 2019
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include <conio.h>
#include<fcntl.h>
#include<io.h>
#include<winuser.h>


#define SNAKE L"\u2B1B "
#define BLOCK L"\u2B1C "
#define APPLE L"\u2206 "
#define EMPTY L"\u2B1C "
//0: x 1~: snake 2000: block 3000: apple

#define SIZE 16
#define INTERVAL 300

int length = 3;
int map[SIZE][SIZE] = { { 0, }, };
unsigned int apple_x;
unsigned int apple_y;
int direction=3;
int finish = 0;
char key;
int xPos = 0;
int yPos = 0;
int _in;
int score = 0;
int front_x;
int front_y;
int front__x;
int front__y;
int dir[90000];
int num=1;
int nsx, nsy;
unsigned long count = 0;

void make_map();
void edge_map(int a);
void control_snake();
void move_snake(int stop);
void find_in_map(int a);
void apple_move();
void add_snake();

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	map[6 - 1][8 - 1] = 3;
	map[7 - 1][8 - 1] = 2;
	map[8 - 1][8 - 1] = 1;

	wprintf(L"Get apple.");
	Sleep(1000);
	system("cls");

	srand(time(NULL));
	apple_move();
	make_map();

	while (finish==0)
	{
		if (GetAsyncKeyState(0x41) == 1)
		{
			if (num <= 1) direction = 4;
			else
			{
				if (dir[num - 2]!=2)
					direction = 4;
			}
		}
		else if (GetAsyncKeyState(0x44) == 1)
		{
			if (num <= 1) direction = 2;
			else
			{
				if (dir[num - 2] != 4)
					direction = 2;
			}
		}
		else if (GetAsyncKeyState(0x53) == 1)
		{
			if (num <= 1) direction = 3;
			else
			{
				if (dir[num - 2] != 1)
					direction = 3;
			}
		}
		else if (GetAsyncKeyState(0x57) == 1)
		{
			if (num <= 1) direction = 1;
			
			else
			{
				if (dir[num - 2] != 3)
					direction = 1;
			}
		}
		
		move_snake(0);
		Sleep(INTERVAL);
		count++;
	}

	system("cls");
	wprintf(L"Finished\nYour score is %d", score);
	Sleep(1000);
	
	return 0;
}


void make_map()
{
	system("cls");
	wprintf(L" score: %d\n\n", score);
	edge_map(1);
	for (int y = 1; y <= SIZE; y++)
	{
		edge_map(2);
		for (int x = 1; x <= SIZE; x++)
		{
			if (map[y - 1][x - 1] == 2000) wprintf(BLOCK);
			else if (map[y - 1][x - 1] == 3000)
			{
				//wprintf(L" ");
				wprintf(APPLE);
				wprintf(L" ");
			}
			else if (map[y - 1][x - 1] == 0) wprintf(EMPTY);
			else wprintf(SNAKE);
		}

		edge_map(3);
		wprintf(L"\n");
	}

	edge_map(4);
}

void edge_map(int a)
{
	if (a == 1 || a == 4)
	{
		for (int i = 2; i <= SIZE + 2; i++) wprintf(L"---");
		
		wprintf(L"\n");
	}
	else if (a == 2) wprintf(L"| ");
	else wprintf(L"|");
}

void control_snake()
{
	int in;

	in = _getch();
	key = (char)in;

	if (in == (int)'w')
	{
		if (_in != 3 && _in !=1)
		{
			direction = 1;
			_in = 1;
		}
	}
	else if (in == (int)'d')
	{
		if (_in != 4 && _in != 2)
		{
			direction = 2;
			_in = 2;
		}
	}
	else if (in == (int)'s')
	{
		if (_in != 1 && _in != 3)
		{
			direction = 3;
			_in = 3;
		}
	}
		else if (in == (int)'a')
	{
		if (_in != 2 && _in != 4)
		{
			direction = 4;
			_in = 4;
		}
	}
}

void move_snake(int stop)
{
	
	int last_dir = direction;
	int a_x=0, a_y=0;
	
	//while (stop == 0 && finish == 0 && last_dir==direction)
	//{
		for (int i = 1; i <= 250; i++)
		{
			xPos = 0;
			yPos = 0;
			find_in_map(i);

			
			front__x = xPos;
			front__y = yPos;
			
			if(xPos != -1 || yPos != -1)
			{
				map[yPos][xPos] = 0;
				if (i == 1)
				{
					if (direction == 1)
					{
						if (yPos - 1 >= 0)
						{
							map[yPos - 1][xPos] = i;
							a_x = front__x;
							a_y = front__y - 1;
						}
						else
						{
							finish = 1;
							break;
						}
					}
					else if (direction == 2)
					{
						if (xPos + 1 < SIZE)
						{
							map[yPos][xPos + 1] = i;
							a_x = front__x + 1;
							a_y = front__y;
						}
						else
						{
							finish = 1;
							break;
						}
					}
					else if (direction == 3)
					{
						if (yPos + 1 < SIZE)
						{
							map[yPos + 1][xPos] = i;
							a_x = front__x;
							a_y = front__y + 1;
						}
						else
						{
							finish = 1;
							break;
						}
					}
					else if (direction == 4)
					{
						if (xPos - 1 >= 0)
						{
							map[yPos][xPos - 1] = i;
							a_x = front__x - 1;
							a_y = front__y;
						}
						else
						{
							finish = 1;
							break;
						}
					}
					if ((a_x +1) == apple_x && (a_y + 1) == apple_y)
					{
						score ++;
						length ++;
						apple_move();
						//add_snake(); 미완
					}

				}
				else map[front_y][front_x] = i;

				front_x = xPos;
				front_y = yPos;
			}
		}
	//}

		dir[num] = direction;
		num++;

		make_map();
		wprintf(L"dir:%d, %d, %d, %d, %d", direction, xPos, yPos, apple_x, apple_y);
}

void find_in_map(int a)
{
	int found=0;
	int i_, j_;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (map[i][j] == a)
			{
				found = 1;
				i_ = i;
				j_ = j;
				break;
			}
		}
	}


	if (found == 1)
	{
		xPos = j_;
		yPos = i_;
		nsx = j_;
		nsy = i_;
	}
	else
	{
		xPos = -1;
		yPos = -1;
	}
}

void apple_move()
{
	apple_x = rand() % 16 + 1;
	apple_y = rand() % 16 + 1;
	map[apple_y - 1][apple_x - 1] = 3000;
}

void add_snake()
{
	int last_dir;

	if (num <= 3)
		last_dir=3;
	else
		last_dir=dir[num-1-length];

	find_in_map(length);

	if(last_dir==1)
	map[nsy - 1][nsx] = length + 1;
	else if (last_dir == 2) map[nsy][nsx - 1] = length + 1;
	else if (last_dir == 3) map[nsy + 1][nsx] = length + 1;
	else if (last_dir == 4) map[nsy][nsx + 1] = length + 1;
}//미완
