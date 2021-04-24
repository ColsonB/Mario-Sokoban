#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "jeu.h"

int main(int argc, char **argv)
{
	using namespace std;

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "Mario Sokoban");

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/caisse.jpg")) // permet de charger la texture
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture menu;
	if (!menu.loadFromFile("src/img/menu.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Sprite sprite;
	sprite.setTexture(menu);

	sprite.setPosition(sf::Vector2f(0.f, 0.f)); // modifie la position absolue

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{

		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.key.code == sf::Event::KeyPressed)
			{


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
				{
					//jouer(ecran);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
				{
					//editeur(ecran);
				}

			}
		
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();

		}
		
		window.clear(sf::Color::Black);

		window.draw(sprite); // on dessine le sprite

		window.display();
	}

		return 0;
}