#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//#include "constantes.h"
//#include "jeu.h"

int main(int argc, char **argv)
{
	using namespace std;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Sokoban");

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/caisse.jpg"))
	{
		cout << "L'image n'a pas charg�e";
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{

		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		window.display();
	}

	return 0;
}