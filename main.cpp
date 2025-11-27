#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#ifndef _DEBUG
#include <Windows.h>
#endif

// colori
#define COLORE_GRIGLIA		sf::Color(128, 128, 128)
#define COLORE_CROCE		sf::Color(170, 255, 0)
#define COLORE_BACKGROUND	sf::Color(64, 64, 64)
#define CIANO				sf::Color::Cyan
#define ROSSO				sf::Color::Red
#define TRASPARENTE			sf::Color::Transparent


std::tuple<bool, char, std::string> CheckWin(char matrix[3][3])
{
	bool isWin		= false;
	char giocatore	= ' ';
	std::string coordinata;

	// Righe
	if (matrix[0][0] == matrix[0][1] && matrix[0][1] == matrix[0][2] && matrix[0][0] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][0];
		coordinata = "H0";
	}

	else if (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2] && matrix[1][0] != ' ')
	{
		isWin = true;
		giocatore = matrix[1][0];
		coordinata = "H1";
	}

	else if (matrix[2][0] == matrix[2][1] && matrix[2][1] == matrix[2][2] && matrix[2][0] != ' ')
	{
		isWin = true;
		giocatore = matrix[2][0];
		coordinata = "H2";
	}

	// Colonne
	else if (matrix[0][0] == matrix[1][0] && matrix[1][0] == matrix[2][0] && matrix[0][0] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][0];
		coordinata = "V0";
	}

	else if (matrix[0][1] == matrix[1][1] && matrix[1][1] == matrix[2][1] && matrix[0][1] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][1];
		coordinata = "V1";
	}

	else if (matrix[0][2] == matrix[1][2] && matrix[1][2] == matrix[2][2] && matrix[0][2] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][2];
		coordinata = "V2";
	}

	// Diagonali
	else if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][0];
		coordinata = "D0";
	}

	else if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2] != ' ')
	{
		isWin = true;
		giocatore = matrix[0][2];
		coordinata = "D1";
	}

	return std::make_tuple(isWin, giocatore, coordinata);
}


#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
) // DEBUG
#endif
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 4;

	// parametri geometrici
	float spessore	= 5.0f;
	float width		= 600.0f;
	float height	= 600.0f;
	float scale		= 0.8f;

	bool IsTurnoGiocatore = true;

	sf::RenderWindow window(sf::VideoMode({ (unsigned int)width,  (unsigned int)height }), 
		"Tris", sf::State::Windowed, settings);


	float window_center_x = width / 2;
	float window_center_y = height / 2;

	float x_position = window_center_x;
	float y_position = window_center_y;

	char matrix[3][3] =
	{
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	/*----------------------------TESTA-------------------------------------*/

	sf::CircleShape circle((width / 6) - spessore / 2, 60);
	circle.setOrigin({ (width / 6) - spessore / 2, (width / 6) - spessore / 2 });
	circle.setFillColor(TRASPARENTE);
	circle.setOutlineThickness(-spessore);
	circle.setOutlineColor(TRASPARENTE);

	auto drawCircle = [&](int i, int j, sf::Color color)
	{
		circle.setOutlineColor(color);
		x_position = ((width / 3) * j) + width / 6;
		y_position = ((width / 3) * i) + width / 6;
		circle.setPosition({ x_position , y_position });
		window.draw(circle);
	};

	/*----------------------------CROCE-------------------------------------*/

	sf::RectangleShape cross;
	cross.setSize({ (float)((width / 3) * sqrt(2) * scale), spessore });
	cross.setOrigin(cross.getGeometricCenter());
	cross.setFillColor(TRASPARENTE);

	auto drawCross = [&](int i, int j)
	{
		x_position = ((width / 3) * j) + width / 6;
		y_position = ((width / 3) * i) + width / 6;
		cross.setPosition({ x_position , y_position });
		cross.setFillColor(COLORE_CROCE);
		cross.setRotation(sf::degrees(45));
		window.draw(cross);
		cross.setRotation(sf::degrees(-45));
		window.draw(cross);
	};

	/*----------------------------LINEA VINCITA-------------------------------------*/
	sf::RectangleShape WinLine;

	auto drawWinLine = [&](std::string combinazione)
	{
		WinLine.setFillColor(ROSSO);
		float offset_diagonale = 0.5 * ((width * sqrt(2)) - (width * sqrt(2) * scale));
		offset_diagonale		*= (float)std::cos(45.0f * 3.1416 / 180.0f);

		if (combinazione == "H0")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			auto a = WinLine.getGeometricCenter();
			std::cout << a.x << "; " << a.y << std::endl;
			WinLine.setPosition({ width / 2, width / 6 });
		}
		else if (combinazione == "H1")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			WinLine.setPosition({ width / 2, width / 3 });
		}
		else if (combinazione == "H2")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			WinLine.setPosition({ width / 2, width - (width / 6) });
		}
		else if (combinazione == "V0")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			WinLine.setPosition({ width / 6, width / 2 });
			WinLine.setRotation(sf::degrees(90));
		}
		else if (combinazione == "V1")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			WinLine.setPosition({ width / 2, width / 2 });
			WinLine.setRotation(sf::degrees(90));
		}
		else if (combinazione == "V2")
		{
			WinLine.setSize({ width * scale , spessore });
			WinLine.setOrigin(WinLine.getGeometricCenter());
			WinLine.setPosition({ width - (width / 6), width / 2 });
			WinLine.setRotation(sf::degrees(90));
		}
		else if (combinazione == "D0")
		{
			WinLine.setSize({ (float)sqrt(2) * width * scale , spessore });
			WinLine.setOrigin({ spessore / 2, spessore / 2 });
			WinLine.setPosition({ offset_diagonale, offset_diagonale });
			WinLine.setRotation(sf::degrees(45));
		}

		else // combinazione == "D1"
		{
			WinLine.setSize({ (float)sqrt(2) * width * scale , spessore });
			WinLine.setPosition({ width - offset_diagonale + spessore / 2, spessore / 2 + offset_diagonale });
			WinLine.setRotation(sf::degrees(135));
		}

		window.draw(WinLine);
	};

	/*----------------------------GRIGLIA-------------------------------------*/
	sf::RectangleShape HorizonalLine1;
	HorizonalLine1.setSize({ width, spessore });
	HorizonalLine1.setPosition({ 0, (width / 3) - spessore / 2 });
	HorizonalLine1.setFillColor(COLORE_GRIGLIA);

	sf::RectangleShape HorizonalLine2;
	HorizonalLine2.setSize({ width, spessore });
	HorizonalLine2.setPosition({ 0, (width * 0.666f) - spessore / 2 });
	HorizonalLine2.setFillColor(COLORE_GRIGLIA);

	sf::RectangleShape VerticalLine1;
	VerticalLine1.setSize({ width, spessore });
	VerticalLine1.setPosition({ (width / 3) + spessore / 2, 0 });
	VerticalLine1.setFillColor(COLORE_GRIGLIA);
	VerticalLine1.setRotation(sf::degrees(90));

	sf::RectangleShape VerticalLine2;
	VerticalLine2.setSize({ width, spessore });
	VerticalLine2.setPosition({ (width * 0.666f) + spessore / 2, 0 });
	VerticalLine2.setFillColor(COLORE_GRIGLIA);
	VerticalLine2.setRotation(sf::degrees(90));

	/*----------------------------CURSORE-------------------------------------*/
	sf::RectangleShape cursore;
	float  posizione_cursore_x = window_center_x;
	float posizione_cursore_y = window_center_y;

	cursore.setSize({ width / 3, width / 3 });
	cursore.setOrigin({ width / 6, width / 6 });
	cursore.setPosition({ window_center_x, window_center_y });
	cursore.setFillColor(TRASPARENTE);
	cursore.setOutlineThickness(-spessore);
	cursore.setOutlineColor(ROSSO);


	auto MuoviCursore = [&](float x, float y)
	{
		posizione_cursore_x += x;
		posizione_cursore_y += y;
		cursore.setPosition({ posizione_cursore_x , posizione_cursore_y });
	};

	auto SpegniCursore = [&]()
	{
		cursore.setOutlineColor(TRASPARENTE);
	};

	unsigned int count = 0;

	while (window.isOpen())
	{

		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			else if (event->is<sf::Event::Resized>())
			{
				sf::View view(sf::FloatRect({ 0.0f, 0.0f }, sf::Vector2f(window.getSize())));
				window.setView(view);
			}

			else if (auto* key = event->getIf<sf::Event::KeyPressed>())
			{
				if ((key->scancode == sf::Keyboard::Scancode::Up))
				{
					if (posizione_cursore_y == (width / 6))
						MuoviCursore(0, width / 3);
					else
						MuoviCursore(0, -(width / 3));
				}
				else if ((key->scancode == sf::Keyboard::Scancode::Down))
				{
					if (posizione_cursore_y == (width - (width / 6)))
						MuoviCursore(0, -(width / 3));
					else
						MuoviCursore(0, (width / 3));
				}
				else if ((key->scancode == sf::Keyboard::Scancode::Left))
				{
					if (posizione_cursore_x == (width / 6))
						MuoviCursore(width / 3, 0);
					else
						MuoviCursore(-(width / 3), 0);
				}
				else if ((key->scancode == sf::Keyboard::Scancode::Right))
				{
					if (posizione_cursore_x == (width - (width / 6)))
						MuoviCursore(-(width / 3), 0);
					else
						MuoviCursore((width / 3), 0);
				}
				else if ((key->scancode == sf::Keyboard::Scancode::Enter))
				{
					unsigned int colonna = ((posizione_cursore_x + width / 6) / (width / 3)) - 1;
					unsigned int riga = ((posizione_cursore_y + width / 6) / (width / 3)) - 1;

					#ifdef _DEBUG
					std::cout << "coordinate inviate: " << riga << "; " << colonna << std::endl;
					#endif // DEBUG


					// mossa già selezionata
					if (matrix[riga][colonna] != ' ')
					{
						continue;
					}

					else if (IsTurnoGiocatore)
					{
						matrix[riga][colonna] = 'O';
						IsTurnoGiocatore = false;
						count++;
					}
					else
					{
						matrix[riga][colonna] = 'X';
						IsTurnoGiocatore = true;
						count++;
					}
				}

			}
		}

		// cancello tutto ciò che c'era prima nella finestra
		window.clear(COLORE_BACKGROUND);


		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (matrix[i][j] == 'O')
				{
					drawCircle(i, j, CIANO);
				}
				else if (matrix[i][j] == 'X')
				{
					drawCross(i, j);
				}
			}
		}

		auto result = CheckWin(matrix);

		if (std::get<0>(result))
		{
			drawWinLine(std::get<2>(result));
			SpegniCursore();
		}

		window.draw(HorizonalLine1);
		window.draw(HorizonalLine2);
		window.draw(VerticalLine1);
		window.draw(VerticalLine2);
		window.draw(cursore);

		window.display();

		// pareggio
		if (count > 8)
		{
			SpegniCursore();
		}
	}

	return 0;
}