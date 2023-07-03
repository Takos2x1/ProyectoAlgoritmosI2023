#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

// Constantes
const int mxob = 12; // Numero maximo de Destructores o estrellas en el mapa
const int mnob = 5; // Numero minimo de Destructores o estrellas en el mapa

std::fstream DATA;
std::fstream RES;

std::string fcoord(int x, int y); // Format Coords
std::string ran_coord(int n, int m);

std::string fcoord(int x,int y)
{
	char str[255];
	sprintf_s(str, "%d %d\n", x, y);

	return str;
}

std::string ran_coord(int n, int m)
{

	int x = (rand() % n), y = (rand() % m);

	std::string resul;
	resul = fcoord(x, y);
	//sprintf_s(resul, "%d %d\n", x, y);

	return resul;
}

void gen_map(int n, int m, std::string dir)
{
	int i, j, s;
	std::ofstream DATA (dir);



	if (DATA.is_open())
	{
		// Tamano en filas y columnas del mapa, si no cumple con 1<x<30 se asigna 15x15
		if (n > 1 && n <= 30 && m > 1 && m <= 30)
		{
			DATA << fcoord(n, m);
		}
		else
		{
			DATA << "15 15\n";
		}

		// Posicion incial de la Nave y pocision de la estrella destino
		for (i = 1; i < 3; i++)
		{
			DATA << ran_coord(n, m);
		}

		// Determina el numero de estrellas/destructotrs en el mapa y luego genera sus pocisiones
		for (i = 1; i < 3; i++)
		{
			s = (mnob + rand() % mxob);
			DATA << s << "\n";
			for (j = 1; j <= s; j++)
			{
				DATA << ran_coord(n, m);
			}
		}

		DATA.close();
	}
}

int getint(std::string str, bool sec = false)
{
	int i, f;
	std::string s;
	int num = 0;

	std::stringstream ss;
	ss << str;

	i = 1;
	while (!ss.eof())
	{
		ss >> s;

		if (std::stringstream(s) >> f)
		{
			num = f;
			if(!sec)
				break;
		}
		i++;
	}

	return num;
}

void read_data(char map[30][30], std::string dir, int (&ppos)[2])
{
	int prio[4];
	int fil, col, i, j, x, y, n;
	char ch = ' ';
	std::string line;
	std::ifstream DATA(dir);

	if (DATA.is_open())
	{
		getline(DATA, line);
		fil = getint(line);
		col = getint(line, true);

		for (i = 0; i <= fil; i++)
		{
			for (j = 0; j <= col; j++)
			{
				map[i][j] = '*';
			}
		}
		
		// Posicion Jugador
		getline(DATA, line);
		x = getint(line);
		y = getint(line, true);
		prio[0] = x; prio[1] = y;
		ppos[0] = x; ppos[1] = y;

		// Posicion Planeta
		getline(DATA, line);
		x = getint(line);
		y = getint(line, true);
		prio[2] = x; prio[3] = y;

		while (getline(DATA, line))
		{
			// Estrellas y Destructores
			for (i = 0; i < 2; i++)
			{
				switch (i)
				{
				case 0:
					ch = 'E';
					break;
				case 1:
					ch = 'D';
					break;
				}

				n = getint(line);
				for (j = 1; j <= n; j++)
				{
					getline(DATA, line);
					x = getint(line);
					y = getint(line, true);

					map[x][y] = ch;
				}
			}
		}

		x = prio[0]; y = prio[1];
		map[x][y] = 'H';

		x = prio[2]; y = prio[3];
		map[x][y] = 'T';
	}

	DATA.close();
}