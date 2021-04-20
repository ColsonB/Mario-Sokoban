#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//#include "constantes.h"
//#include "jeu.h"

int main(int argc, char **argv)
{
	using namespace std;

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/caisse.jpg"))
	{
	
	} 

	sf::Window window(sf::VideoMode(800, 600), "Mario Sokoban");

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
	}

	return 0;
}