#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "fileCtrl.h"
#include "rlutil.h"
#include "commons.h"

void draw(std::string img_dir, int color = 0)
{
	std::ifstream img(img_dir);
	std::string line;

	if (color > 15 || color < 0)
		color = 7;

	system("CLS");
	rlutil::setColor(color);
	if (img.is_open())
	{
		while (getline(img, line))
		{
			std::cout << line << "\n";
		}
	}

	rlutil::setColor(7);
	img.close();
}

void draw_map(char map[30][30], std::string dir, int ppos[2])
{
	int i, j, fil = 15, col = 15, color;
	int x = ppos[0], y = ppos[1];
	std::string line;
	
	std::ifstream DATA(dir);

	if (DATA.is_open())
	{
		getline(DATA, line);
		fil = getint(line);
		col = getint(line, true);

		DATA.close();
	}

	system("CLS");
	rlutil::setColor(7); printf("# OBJETIVO: navega tu");
	rlutil::setColor(10); printf(" Nave ");
	rlutil::setColor(7); printf("hasta el ");
	rlutil::setColor(3); printf("Planeta de Destino");
	rlutil::setColor(7); printf(" #\n");
	rlutil::setColor(7); printf("\t# Evita chocar con los ");
	rlutil::setColor(12); printf("Destructores");
	rlutil::setColor(7); printf(" #\n");

	std::cout << std::endl;
	for (i = 0; i <= fil; i++)
	{
		std::cout << "\t";
		for (j = 0; j <= col; j++)
		{
			switch (map[i][j])
			{
				case 'H':
					color = 10;
					break;
				case 'T':
					color = 3;
					break;
				case 'E':
					color = 14;
					break;
				default:
					color = 7;
					break;
			}
			
			rlutil::setColor(color);

			if (map[i][j] != 'D')
			{
				std::cout << " " << map[i][j];
			}
			else if (map[i][j] == 'D')
			{
				if ((i > x - 2 && i < x + 2) && (j > y - 2 && j < y + 2))
				{
					rlutil::setColor(12);
					std::cout << " " << map[i][j];

				}
				else
				{
					rlutil::setColor(7);
					std::cout << " " << "*";
				}
			}
			
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
	printf("\t\t## Controles ##\n");
	printf("\t   Movimiento:\tFLECHAS\n");
	printf("\t   Saltar Nivel:\tENTER\n");
	printf("\t   Reintentar:\tESPACIO\n");
	printf("\t   Salir:\tESC\n");
}

void display_dif(int n)
{
	printf("\n## Difficultad Actual: ");

	if (n == N_FACIL)
	{
		rlutil::setColor(10);
		printf("Facil\n");
	}
	if (n == N_MED)
	{
		rlutil::setColor(14);
		printf("Media\n");
	}
	if (n == N_DIF)
	{
		rlutil::setColor(12);
		printf("Dificil\n");
	}
}

void draw_menu(int sel, int n)
{
	std::string img;
	int color = 11;

	switch (sel)
	{
		case 0:
			img = "menuPLAY.txt";
			break;
		case 1:
			img = "menuDIF.txt";
			break;
		case 2:
			img = "menuQUIT.txt";
			break;
	}

	rlutil::setColor(7);
	printf("\t\tDesarrollado por Juan Andres Perez Marquez");
	draw(img, color);
	rlutil::setColor(color);
	display_dif(n);
	rlutil::setColor(color);
	printf("\n## Controles ##\n");
	printf("   Navegacion:\tARRIBA Y ABAJO\n");
	printf("   Seleccionar:\tENTER\n");
	printf("   Salir:\tESC\n");
	//printf("%d\n", sel);
}

void play_intro(int n)
{
	std::string int1 ="Intro1.txt", int2 = "Intro2.txt";
	int i, color;
	int t = 500;

	if (n == 1)
	{
		for (i = 0; i < 5; i++)
		{
			switch (i)
			{
			case 0:
				color = i;
				break;
			case 1:
				color = 8;
				break;
			case 2:
				color = 7;
				break;
			case 3:
				color = 11;
				break;
			case 4:
				color = 13;
				break;
			}

			draw(int1, color);
			Sleep(t);
		}

		draw(int1, 5);
		Sleep(t+200);
	}
	else if (n == 2)
	{
		for (i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				color = i;
				break;
			case 1:
				color = 8;
				break;
			case 2:
				color = 7;
				break;
			}

			draw(int2, color);
			Sleep(t);
		}

		rlutil::getkey();
	}
	
}