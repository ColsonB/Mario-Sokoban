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
		cout << "L'image n'a pas chargée";
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{

		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		window.display();
	}

	return 0;
}