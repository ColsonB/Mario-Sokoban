#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichier.h"

int main(int argc, char **argv) {
	using namespace std;

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "Mario Sokoban");

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/caisse.jpg")) // permet de charger la texture
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texturemenu;
	if (!texturemenu.loadFromFile("src/img/menu.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Sprite sprite;
	sprite.setTexture(texturemenu);

	sprite.setPosition(sf::Vector2f(0.f, 0.f)); // modifie la position absolue

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen()) {

		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Num1) {
					//jouer(&window);
				}
				if (event.key.code == sf::Keyboard::Num2) {
					editeur(&window);
				}
			}
		}
		window.clear(sf::Color::Black);

		window.draw(sprite); // on dessine le sprite

		window.display();
	}
		return 0;
}