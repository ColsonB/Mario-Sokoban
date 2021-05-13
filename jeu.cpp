#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"
#include "jeu.h"


void jouer(sf::RenderWindow* window) {

	using namespace std;

	sf::Sprite vide, mur, caisse, objectif, caisseOk, mario;
	sf::Sprite* allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };
	sf::Vector2i Position, PositionJoueur;

	int continuer = 1, objectifsRestants = 1, direction = BAS, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des textures des objets
	sf::Texture textureVide;
	textureVide.loadFromFile("src/img/vide.png");
	vide.setTexture(textureVide);

	sf::Texture textureMur;
	textureMur.loadFromFile("src/img/mur.png");
	mur.setTexture(textureMur);

	sf::Texture textureCaisse;
	textureCaisse.loadFromFile("src/img/caisse.png");
	caisse.setTexture(textureCaisse);

	sf::Texture textureCaisseOk;
	textureCaisseOk.loadFromFile("src/img/caisse_ok.png");
	caisseOk.setTexture(textureCaisseOk);

	sf::Texture textureObjectif;
	textureObjectif.loadFromFile("src/img/objectif.png");
	objectif.setTexture(textureObjectif);

	sf::Texture textureMario[5];
	textureMario[HAUT].loadFromFile("src/img/mario_haut.png");
	textureMario[BAS].loadFromFile("src/img/mario_bas.png");
	textureMario[GAUCHE].loadFromFile("src/img/mario_gauche.png");
	textureMario[DROITE].loadFromFile("src/img/mario_droite.png");

	// Chargement du niveau
	chargerNiveau(carte);

	// Recherche de la Position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++){
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++){
			if (carte[i][j] == MARIO){ // Si Mario se trouve à cette Position
				PositionJoueur.x = i;
				PositionJoueur.y = j;
			}
		}
	}


	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer == 1) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					continuer = 0;
				}

				if (event.key.code == sf::Keyboard::Up) {
					deplacerJoueur(carte, &PositionJoueur, HAUT);
					direction = HAUT;
					carte[PositionJoueur.x][PositionJoueur.y + 1] = VIDE;
				}

				if (event.key.code == sf::Keyboard::Down) {
					deplacerJoueur(carte, &PositionJoueur, BAS);
					direction = BAS;
					carte[PositionJoueur.x][PositionJoueur.y - 1] = VIDE;
				}

				if (event.key.code == sf::Keyboard::Left) {
					deplacerJoueur(carte, &PositionJoueur, GAUCHE);
					direction = GAUCHE;
					carte[PositionJoueur.x + 1][PositionJoueur.y] = VIDE;
				}

				if (event.key.code == sf::Keyboard::Right) {
					deplacerJoueur(carte, &PositionJoueur, DROITE);
					direction = DROITE;
					carte[PositionJoueur.x - 1][PositionJoueur.y] = VIDE;
				}
				carte[PositionJoueur.x][PositionJoueur.y] = MARIO;
			}

			/* Affichage du niveau */
			sf::FloatRect Position;
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ligne * TAILLE_BLOC;
					sf::Sprite* asset = allAsset[carte[ligne][colonne]];
					asset->setPosition(Position.left, Position.top);
					window->draw(*asset);
				}
			}
			mario.setTexture(textureMario[direction]);
			
			// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
			if (objectifsRestants == 0) {
				sf::Font font;
				font.loadFromFile("src/font/Ketchum.otf");
				sf::Text text;
				text.setFont(font);
				text.setString("Victoire");
				window->draw(text);
			}
			window->display();
		}
		window->clear(sf::Color::Black);
	}
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* PositionJoueur, int direction) {
	if (direction == HAUT) {
		if (carte[PositionJoueur->x][PositionJoueur->y - 1] != MUR &&
			carte[PositionJoueur->x][PositionJoueur->y - 1] != OBJECTIF &&
			carte[PositionJoueur->x][PositionJoueur->y - 1] != CAISSE_OK &&
			PositionJoueur->x - 1 > 0) {

			if ((carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y - 2] != MUR &&
				carte[PositionJoueur->x][PositionJoueur->y - 2] != CAISSE &&
				carte[PositionJoueur->x][PositionJoueur->y - 2] != CAISSE_OK &&
				PositionJoueur->x - 2 > 0)) {

				deplacerCaisse(&carte[PositionJoueur->x][PositionJoueur->y - 1], &carte[PositionJoueur->x][PositionJoueur->y - 2]);
			}

			if ((carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE_OK) &&
				(carte[PositionJoueur->x][PositionJoueur->y - 2] == MUR)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y--;
			}
		}
	}
	if (direction == BAS) {
		if (carte[PositionJoueur->x][PositionJoueur->y + 1] != MUR &&
			carte[PositionJoueur->x][PositionJoueur->y + 1] != OBJECTIF &&
			carte[PositionJoueur->x][PositionJoueur->y + 1] != CAISSE_OK &&
			PositionJoueur->y + 1 < NB_BLOCS_HAUTEUR) {

			if ((carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y + 2] != MUR &&
				carte[PositionJoueur->x][PositionJoueur->y + 2] != CAISSE &&
				carte[PositionJoueur->x][PositionJoueur->y + 2] != CAISSE_OK &&
				PositionJoueur->y + 2 < NB_BLOCS_HAUTEUR)) {

				deplacerCaisse(&carte[PositionJoueur->x][PositionJoueur->y + 1], &carte[PositionJoueur->x][PositionJoueur->y + 2]);
			}

			if ((carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE_OK) &&
				(carte[PositionJoueur->x][PositionJoueur->y + 2] == MUR)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y++;
			}
		}
	}
	if (direction == GAUCHE) {
		if (carte[PositionJoueur->x - 1][PositionJoueur->y] != MUR &&
			carte[PositionJoueur->x - 1][PositionJoueur->y] != OBJECTIF &&
			carte[PositionJoueur->x - 1][PositionJoueur->y] != CAISSE_OK &&
			PositionJoueur->x - 1 > 0) {

			if ((carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x - 2][PositionJoueur->y] != MUR &&
				carte[PositionJoueur->x - 2][PositionJoueur->y] != CAISSE &&
				carte[PositionJoueur->x - 2][PositionJoueur->y] != CAISSE_OK &&
				PositionJoueur->x - 2 > 0)) {

				deplacerCaisse(&carte[PositionJoueur->x - 1][PositionJoueur->y], &carte[PositionJoueur->x - 2][PositionJoueur->y]);
			}

			if ((carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE_OK) &&
				(carte[PositionJoueur->x - 2][PositionJoueur->y] == MUR)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x--;
			}
		}
	}
	if (direction == DROITE) {
		if (carte[PositionJoueur->x + 1][PositionJoueur->y] != MUR && 
			carte[PositionJoueur->x + 1][PositionJoueur->y] != OBJECTIF && 
			carte[PositionJoueur->x + 1][PositionJoueur->y] != CAISSE_OK &&
			PositionJoueur->x + 1 < NB_BLOCS_LARGEUR) {

			if ((carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x + 2][PositionJoueur->y] != MUR &&
				carte[PositionJoueur->x + 2][PositionJoueur->y] != CAISSE &&
				carte[PositionJoueur->x + 2][PositionJoueur->y] != CAISSE_OK &&
				PositionJoueur->x + 2 < NB_BLOCS_LARGEUR)) {

					deplacerCaisse(&carte[PositionJoueur->x + 1][PositionJoueur->y], &carte[PositionJoueur->x + 2][PositionJoueur->y]);
			}

			if ((carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE_OK) &&
				(carte[PositionJoueur->x + 2][PositionJoueur->y] == MUR)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x++;
			}
		}
	}
}


void deplacerCaisse(int* premiereCase, int* secondeCase) {
	if (*premiereCase == CAISSE) {

		if (*secondeCase == OBJECTIF) {
			(*secondeCase) = CAISSE_OK;
		} else {
			(*secondeCase) = CAISSE;
		}

		if (*premiereCase == CAISSE_OK) {
			(*premiereCase) = OBJECTIF;
		} else {
			(*premiereCase) = VIDE;
		}
	}
}