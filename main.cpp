#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include<windows.h>
#include<string>
using namespace std;

const int Y = 25;//max map Y size
const int X = 80;//max map X size
const int INVENTORY_SIZE = 18;//inventory size
int y_size = Y;//real map y size
int x_size = X;//real map x size
int y = 5;//player y place
int x = 5;//player x place
int hp = 100;
char map[Y][X];
string inventory[INVENTORY_SIZE];
int real_map_num = 1;
char way[256] = "map1.txt";

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_EXIT 27
#define KEY_Y 121
#define KEY_N 110

void clear_txt()
{
	setlocale(0, "russian");
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 21;
	SetConsoleCursorPosition(hConsole, position);
	char  clear_txt[3][79];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 79; j++)
		{
			clear_txt[i][j] = ' ';
		}
	}
	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < 79; j++)
		{
			cout << clear_txt[i][j];
		}
	}
}
void walk(int& x, int& y, int x_go, int y_go, char wall)
{
	setlocale(0, "russian");
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if ((x + x_go < X - 1) && (y + y_go < Y) && (x + x_go >= 0) && (y + y_go >= 0) && (map[y + y_go][x + x_go] != wall) && (map[y + y_go][x + x_go] != '_') && (map[y + y_go][x + x_go] != '|'))
	{
		char b[2] = { map[y][x] };
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(hConsole, position);
		cout << b;
		x = x + x_go;
		y = y + y_go;
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(hConsole, position);
		cout << "@";
	}
}
void draw_all(int x, int y)
{
	setlocale(0, "russian");
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
	for (int i = 0; i < y_size; i++)
	{
		for (int j = 0; j < x_size; j++)
		{
			cout << map[i][j];
		}
	}

	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
	cout << "@";
}
void map_create(char& wall, int change, int& x, int& y)
{
	setlocale(0, "russian");
	if (change == 1) {
		way[3]++;
	}
	else if (change == 0) {
		way[3]--;
	}
	else if (change == 2)
	{
		way[3] = '1';
	}
	ifstream fin(way);
	fin >> x_size >> y_size >> wall;
	fin.getline(map[0], x_size);
	for (int i = 0; i<y_size; i++)
	{
		fin.getline(map[i], x_size);
	}
	fin.close();
	for (int i = 0; i < y_size; i++)
	{
		for (int j = 0; j < x_size; j++)
		{
			if (map[i][j] == '@')
			{
				map[i][j] = ' ';
				x = j;
				y = i;
			}
		}
	}
}
void battle(char creature)
{
	setlocale(0, "russian");
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char way_c[256] = "warI.txt";
	if (creature == 'I')
	{
		way_c[3] = 'I';
	}
	if (creature == 'M')
	{
		way_c[3] = 'M';
	}
	ifstream battle_screen(way_c);
	int creature_hp = 0;
	battle_screen >> x_size >> y_size >> creature_hp;
	char bmp[Y][X];

	battle_screen.getline(bmp[0], x_size);
	for (int i = 0; i<y_size; i++)
	{
		battle_screen.getline(bmp[i], x_size);
	}
	battle_screen.close();
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
	for (int i = 0; i < y_size; i++)
	{
		for (int j = 0; j < x_size; j++)
		{
			cout << bmp[i][j];
		}
	}

	int j = 53;
	int k = 2;
	position.X = j;
	position.Y = k;
	SetConsoleCursorPosition(hConsole, position);
	for (int i = 0; i < 5; i++)
	{
		k++;
		position.X = j;
		position.Y = k;
		SetConsoleCursorPosition(hConsole, position);
		cout << (i+1) << '.' << inventory[i];
		if (inventory[i + 1] == "")
		{
			break;
		}
	}
	int answer = 0;

	while ((creature_hp>0) && (hp>0))
	{
		position.X = 13;
		position.Y = 15;
		SetConsoleCursorPosition(hConsole, position);
		cout << creature_hp;

		hp = hp - 4;
		position.X = 31;
		position.Y = 15;
		SetConsoleCursorPosition(hConsole, position);
		cout << hp;

		position.X = 1;
		position.Y = 17;
		SetConsoleCursorPosition(hConsole, position);
		cout << "Choose thing:";
		cin >> answer;

		if (inventory[answer-1] == "pistol")
		{
			creature_hp = creature_hp - 10;
		}
		if (inventory[answer-1] == "first aid")
		{
			if ((hp + 50)>100)
			{
				hp = 100;
			}
			else
			{
				hp = hp + 50;
			}
		}
		if (inventory[answer-1] == "super shotgun")
		{
			creature_hp = creature_hp - 20;
		}
		if (creature_hp <= 0)
		{
			map[y][x] = ' ';
			draw_all(x, y);
			clear_txt();
		}

	}
}

/*/объекты и структуры
struct point_of_go
{
	int x_place;
	int y_place;
	int next_map_x;
	int next_map_y;
	char way_to_go[255];
};*/


int main()
{
start:
	setlocale(0, "russian");
	hp = 100;
	int free_space = 0;
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = "";
	}

	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char wall = '#';
	int y_go = 0;
	int x_go = 0;
	int c = 0;
	map_create(wall, 2, x, y);

	clear_txt();

	draw_all(x, y);

	while (1)
	{
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(hConsole, position);
		cout << "@";

		y_go = 0;
		x_go = 0;

		c = 0;
		switch (c = _getch()) {
		case KEY_UP:
			y_go = -1;
			walk(x, y, x_go, y_go, wall);
			c = 0;
			break;
		case KEY_DOWN:
			y_go = 1;
			walk(x, y, x_go, y_go, wall);
			c = 0;
			break;
		case KEY_LEFT:
			x_go = -1;
			walk(x, y, x_go, y_go, wall);
			c = 0;
			break;
		case KEY_RIGHT:
			x_go = 1;
			walk(x, y, x_go, y_go, wall);
			c = 0;
			break;
		case KEY_SPACE:
			if (map[y + 1][x] == '_')
			{
				map[y + 1][x] = ' ';
				position.X = x;
				position.Y = y + 1;
				SetConsoleCursorPosition(hConsole, position);
				cout << map[y + 1][x];
			}
			else if (map[y - 1][x] == '_')
			{
				map[y - 1][x] = ' ';
				position.X = x;
				position.Y = y - 1;
				SetConsoleCursorPosition(hConsole, position);
				cout << map[y - 1][x];
			}
			else if (map[y][x + 1] == '|')
			{
				map[y][x + 1] = ' ';
				position.X = x + 1;
				position.Y = y;
				SetConsoleCursorPosition(hConsole, position);
				cout << map[y][x + 1];
			}
			else if (map[y][x - 1] == '|')
			{
				map[y][x - 1] = ' ';
				position.X = x - 1;
				position.Y = y;
				SetConsoleCursorPosition(hConsole, position);
				cout << map[y][x - 1];
			}
			else
			{
				position.X = 0;
				position.Y = 21;
				SetConsoleCursorPosition(hConsole, position);
				clear_txt();
				position.X = 0;
				position.Y = 21;
				SetConsoleCursorPosition(hConsole, position);
				cout << "it will do nothing";
			}
			c = 0;
			break;
		case KEY_EXIT:
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			cout << "Are you sure you want to exit?(Y/N)"<<endl<<"(this is pre alfa all your gameplay will not save)";
			int k = _getch();
			if (k == 121)
			{
				return 0;
			}
			clear_txt();
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			c = 0;
			break;
		}
		if (map[y][x] == '~') {
			hp = hp - 1;
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			clear_txt();
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			cout << "this water is radioactive(you have" << hp << "out of 100 hp";
		}
		if (map[y][x] == '\'') {
			hp = hp - 1;
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			clear_txt();
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);
			cout << "Your Geiger counter crackles like crazy it's time to cut(you have" << hp << "out of 100 hp";
		}
		if (map[y][x] == '<')
		{
			map_create(wall, 0, x, y);
			system("cls");
			draw_all(x, y);
			real_map_num--;
		}
		if (map[y][x] == '>')
		{
			map_create(wall, 1, x, y);
			system("cls");
			draw_all(x, y);
			real_map_num++;
		}
		if (map[y][x] == '1')
		{
			inventory[free_space] = { "pistol" };
			free_space++;
			map[y][x] = ' ';
		}
		if (map[y][x] == '2')
		{
			inventory[free_space] = { "super shotgun" };
			free_space++;
			map[y][x] = ' ';
		}
		if (map[y][x] == '+')
		{
			inventory[free_space] = { "first aid" };
			free_space++;
			map[y][x] = ' ';
		}
		if (map[y][x] == 'I')
		{
			battle('I');
		}

		/*if ((x == 45) && (y == 17))
		{
		if (real_map_num == 2)
		{
		clear_txt();
		position.X = 0;
		position.Y = 21;
		SetConsoleCursorPosition(hConsole, position);
		cout << "You see a glowing portal, and hear the whisper of a heap of different voices";
		}
		}*/

		if (hp <= 0)
		{
			clear_txt();

			if (map[y][x] == '~')
			{
				position.X = 0;
				position.Y = 21;
				SetConsoleCursorPosition(hConsole, position);
				cout << "You died, your body lying in a radioactive swamp so no one found";
			}
			else
			{
				position.X = 0;
				position.Y = 21;
				SetConsoleCursorPosition(hConsole, position);
				cout << "You died, again. Probably regret that not make it easier";
			}

			position.X = 0;
			position.Y = 22;
			SetConsoleCursorPosition(hConsole, position);
			cout << "Want to start over?(Y/N)";
			Sleep(1000);
			int k = _getch();
			while (1) {
				k = 0;
				switch (k = _getch()) {
				case KEY_Y:
					goto start;
					break;
				case KEY_N:
					return 0;
					break;
				}
			}
			position.X = 0;
			position.Y = 21;
			SetConsoleCursorPosition(hConsole, position);

		}
	}

	return 0;
}
