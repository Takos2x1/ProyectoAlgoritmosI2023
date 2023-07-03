#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>

#include "fileCtrl.h"
#include "graphics.h"
#include "rlutil.h"
#include "commons.h"

enum DIR {UP,DOWN, LEFT, RIGHT};
enum STA {WIN, LOSE, NA};

int ppos[2]; // Posicion del Jugador


int move_menu(int cur, bool up)
{
	int resul;

	if (up)
		resul = max((cur - 1), 0);
	else
		resul = min((cur + 1), 2);

	return resul;
}

void skip_level(char (&map)[30][30], int n, int m, std::string data)
{
	char c;

	system("CLS");

	do
	{
		printf("\n\t\t\tSeguro que deseas saltar este nivel?\n\t\t\t(Y)Si (N)No\n");
		std::cin >> c;
		c = toupper(c);

	} while (!(c == 'Y' || c == 'N'));
	
	if (c == 'Y')
	{
		gen_map(n, m, data);
		read_data(map, data, ppos);
	}
}

bool retry_level(char map[30][30], std::string data, enum STA &res)
{
	char c;
	bool no = false;

	do
	{
		printf("\n\t\t\tReintentar?\n \t\t\t(Y)Si (N)No\n");
		std::cin >> c;
		c = toupper(c);

	} while (!(c == 'Y' || c == 'N'));

	if (c == 'Y')
	{
		read_data(map, data, ppos);
		res = NA;
	}
	else if (res == LOSE && c == 'N')
	{
		no = true;
	}		

	return no;
}

bool next_level(char(&map)[30][30], int n, int m, std::string data)
{
	bool resul = false;
	char c;

	do
	{
		printf("\n\t\t\tSigiente nivel?\n \t\t\t(Y)Si (N)No\n");
		std::cin >> c;
		c = toupper(c);

	} while (!(c == 'Y' || c == 'N'));

	if (c == 'Y')
	{
		gen_map(n, m, data);
		read_data(map, data, ppos);
	}
	else
	{
		resul = true;
	}

	return resul;
}

enum STA move_player(char (&map)[30][30], enum DIR dir, int ppos[2], int n, int m)
{
	int x, y, xd, yd;
	enum STA resul = NA;

	x = ppos[0]; y = ppos[1];
	xd = x; yd = y;

	switch (dir)
	{
		case LEFT:
			yd = max(y - 1, 0);
			break;
		case RIGHT:
			yd = min(y + 1, n);
			break;
		case UP:
			xd = max(x - 1, 0);
			break;
		case DOWN:
			xd = min(x + 1, m);
			break;
	}

	if (map[xd][yd] == '*')
	{
		map[x][y] = '*';
		map[xd][yd] = 'H';
		ppos[0] = xd; ppos[1] = yd;
	}
	else if (map[xd][yd] == 'T')
	{
		resul = WIN;
	}
	else if (map[xd][yd] == 'E', map[xd][yd] == 'D')
	{
		resul = LOSE;
	}

	return resul; 
	/*
		Retorna LOSE si el jugador se trata de de mover a un Destructor o una estrella.
		WIN si se mueve al lugar de la base destino.
		y NA si se pudo mover al siguiente espacio.
	*/
}

void game(int n, int m, std::string data) 
{
	TCHAR input = 2;
	enum STA res = NA;
	char map[30][30];
	bool end = false;

	play_intro(2);

	srand((unsigned)time(NULL));
	system("CLS");

	gen_map(n, m, data);
	read_data(map, data, ppos);
	draw_map(map, data, ppos);
	printf("Player Position: (%d, %d)", ppos[0], ppos[1]);

	do
	{

		input = rlutil::getkey();

		switch (input)
		{
			case 14: // UP
				res = move_player(map, UP, ppos, n, m);
				break;
			case 15: // DOWN
				res = move_player(map, DOWN, ppos, n, m);
				break;
			case 16: // LEFT
				res = move_player(map, LEFT, ppos, n, m);
				break;
			case 17: // RIGHT
				res = move_player(map, RIGHT, ppos, n, m);
				break;
			case 1: // ENTER (Saltar Nivel)
				skip_level(map, n, m, data);
				break;
			case 32: // SPACE (Reintentar)
				end = retry_level(map, data, res);
				break;
			case 0: // ESC
				end = true;
				break;
		}

		if (res == WIN)
		{
			draw("WIN.txt", 2);
			end = next_level(map, n,m, data);
		}
		else if (res == LOSE)
		{
			draw("LOSE.txt", 1);
			end = retry_level(map, data, res);
		}

		draw_map(map, data, ppos);
		printf("Player Position: (%d, %d)", ppos[0], ppos[1]);
		

	} while (res != LOSE && end != true);
}

void change_dif(int &n, int &m)
{
	int dif;

	do
	{
		system("CLS");
		printf("- ESCOJA SU DIFICULTAD -\n\n");
		printf("\t[1]Facil: Mapa 30x30\n");
		printf("\t[2]Medio: Mapa 15x15\n");
		printf("\t[3]Dificil: Mapa 8x8\n");

		std::cin >> dif;

		system("CLS");
		printf("%d no es un numero valido", dif);

	} while (dif <= 0 || dif > 3);

	switch (dif)
	{
		case 1:
			n = N_FACIL;
			m = M_FACIL;
			break;
		case 2:
			n = N_MED;
			m = M_MED;
			break;
		case 3:
			n = N_DIF;
			m = M_DIF;
			break;
	}
}

void main_menu()
{
	TCHAR input = 0;
	bool end = false;
	int sel = 0;
	int n = N_MED, m = M_MED;

	draw_menu(0, n);

	do
	{
		input = rlutil::getkey();

		switch (input)
		{
		case 14:// UP Arrow
			sel = move_menu(sel, true);
			break;
		case 15: // DOWN Arrow
			sel = move_menu(sel, false);
			break;
		case 0: /* ESC */
			end = true;
			break;
		case 1: /* ENTER */
			switch (sel)
			{
			case 0:
				game(n, m, "EST.DAT.txt");
				break;
			case 1:
				change_dif(n, m);
				break;
			case 2:
				end = true;
				break;
			}
			break;
		}

		draw_menu(sel, n);

	} while (end == false);
}