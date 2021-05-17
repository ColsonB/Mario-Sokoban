#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"
#include "jeu.h"

using namespace std;
using namespace sf;

int jouer(sf::RenderWindow* window, int lvl) {

	sf::Sprite vide, mur, caisse, objectif, caisseOk, mario;
	sf::Sprite* allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };
	sf::Vector2i Position, PositionJoueur;

	int continuer = 1, objectifsRestants = NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR, direction = BAS, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement de la police d'écriture
	sf::Font font;
	font.loadFromFile("src/font/Ketchum.otf");

	// Chargement des textures des objets
	sf::Texture textureVide, textureMur, textureCaisse, textureCaisseOk, textureObjectif, textureMario[5];

	textureVide.loadFromFile("src/img/vide.png");
	vide.setTexture(textureVide);

	textureMur.loadFromFile("src/img/mur.png");
	mur.setTexture(textureMur);

	textureCaisse.loadFromFile("src/img/caisse.png");
	caisse.setTexture(textureCaisse);

	textureCaisseOk.loadFromFile("src/img/caisse_ok.png");
	caisseOk.setTexture(textureCaisseOk);

	textureObjectif.loadFromFile("src/img/objectif.png");
	objectif.setTexture(textureObjectif);

	textureMario[HAUT].loadFromFile("src/img/mario_haut.png");

	textureMario[BAS].loadFromFile("src/img/mario_bas.png");

	textureMario[GAUCHE].loadFromFile("src/img/mario_gauche.png");

	textureMario[DROITE].loadFromFile("src/img/mario_droite.png");

	// Chargement des musiques
	sf::SoundBuffer sonBufferVictoire;
	sf::Sound sonVictoire;

	sonBufferVictoire.loadFromFile("src/audio/victoire.ogg");
	sonVictoire.setBuffer(sonBufferVictoire);

	// Chargement du niveau
	chargerNiveau(carte, lvl);

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
					return -1;
				}

				if (event.key.code == sf::Keyboard::Backspace) {
					return jouer(window, lvl);
				}

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z) {
					deplacerJoueur(carte, &PositionJoueur, HAUT);
					direction = HAUT;
				}

				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					deplacerJoueur(carte, &PositionJoueur, BAS);
					direction = BAS;
				}

				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q) {
					deplacerJoueur(carte, &PositionJoueur, GAUCHE);
					direction = GAUCHE;
				}

				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
					deplacerJoueur(carte, &PositionJoueur, DROITE);
					direction = DROITE;
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
			
			// Affichage du numéro du niveau
			sf::Text niveau;
			niveau.setFont(font);
			niveau.setCharacterSize(36);
			niveau.setString("Niveau " + std::to_string(lvl));
			niveau.setPosition(
				(LARGEUR_FENETRE_JEU - niveau.getLocalBounds().width) / 2,
				(HAUTEUR_FENETRE_JEU + niveau.getLocalBounds().height)
			);
			window->draw(niveau);

			// Affichage du commande echap
			sf::Text echap1, echap2, echap3;
			echap1.setFont(font);
			echap2.setFont(font);
			echap3.setFont(font);
			echap1.setCharacterSize(18);
			echap2.setCharacterSize(18);
			echap3.setCharacterSize(18);
			echap1.setString("Cliquez sur");
			echap2.setString("echap pour");
			echap3.setString("quitter");
			echap1.setPosition(
				(LARGEUR_FENETRE - echap1.getLocalBounds().width),
				(echap1.getLocalBounds().height) * 1
			);
			echap2.setPosition(
				(LARGEUR_FENETRE - echap2.getLocalBounds().width),
				(echap2.getLocalBounds().height) * 2
			);
			echap3.setPosition(
				(LARGEUR_FENETRE - echap3.getLocalBounds().width),
				(echap3.getLocalBounds().height) * 3
			);
			window->draw(echap1);
			window->draw(echap2);
			window->draw(echap3);

			// S'il ne reste plus d'objectif on gagne la partie
			if (objectifsRestants == 0) {
				sf::Text victoire, enter;

				victoire.setFont(font);
				victoire.setCharacterSize(36);
				enter.setFont(font);
				enter.setCharacterSize(18);
				victoire.setString("Victoire");
				enter.setString("Cliquez sur le bouton entrer pour continuer");
				victoire.setPosition(
					(LARGEUR_FENETRE_JEU - victoire.getLocalBounds().width) / 2,
					(HAUTEUR_FENETRE_JEU - victoire.getLocalBounds().height) / 2
				);
				enter.setPosition(
					(LARGEUR_FENETRE_JEU - enter.getLocalBounds().width) / 2,
					((HAUTEUR_FENETRE_JEU - enter.getLocalBounds().height) / 2) + 40
				);

				sonVictoire.play();
				window->draw(victoire);
				window->draw(enter);

				if (event.key.code == sf::Keyboard::Enter) {
					sonVictoire.stop();
					if (lvl < 5) {
						lvl++;
						return jouer(window, lvl);
					} else {
						continuer = 0;
					}
				}
			} else {
				objectifsRestants = NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR;
				for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
					for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
						if (carte[i][j] != OBJECTIF) {
							objectifsRestants--;
						}
					}
				}
			}
			window->display();
		}
		window->clear(sf::Color::Black);
	}
	return 0;
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* PositionJoueur, int direction) {

	// Test des collisions dans la direction du haut
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
				carte[PositionJoueur->x][PositionJoueur->y - 1] = VIDE;
			}

			// Déplacement du joueur sur le haut
			if ((carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y - 2] == MUR ||
				carte[PositionJoueur->x][PositionJoueur->y - 2] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y - 2] == CAISSE_OK)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y--;
				carte[PositionJoueur->x][PositionJoueur->y + 1] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction du bas
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
				carte[PositionJoueur->x][PositionJoueur->y + 1] = VIDE;
			}

			// Déplacement du joueur sur le bas
			if ((carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y + 2] == MUR ||
				carte[PositionJoueur->x][PositionJoueur->y + 2] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y + 2] == CAISSE_OK)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y++;
				carte[PositionJoueur->x][PositionJoueur->y - 1] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction de la gauche
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
				carte[PositionJoueur->x - 1][PositionJoueur->y] = VIDE;

			}

			// Déplacement du joueur sur la gauche
			if ((carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x - 2][PositionJoueur->y] == MUR ||
				carte[PositionJoueur->x - 2][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x - 2][PositionJoueur->y] == CAISSE_OK)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x--;
				carte[PositionJoueur->x + 1][PositionJoueur->y] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction du droite
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
					carte[PositionJoueur->x + 1][PositionJoueur->y] = VIDE;
			}

			// Déplacement du joueur sur la droite
			if ((carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x + 2][PositionJoueur->y] == MUR ||
				carte[PositionJoueur->x + 2][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x + 2][PositionJoueur->y] == CAISSE_OK)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x++;
				carte[PositionJoueur->x - 1][PositionJoueur->y] = VIDE;
			}
		}
	}
}


void deplacerCaisse(int* premiereCase, int* secondeCase) {

	if (*premiereCase == CAISSE) {

		// Si la caisse va sur un objectif, la caisse devient une caisse_ok
		if (*secondeCase == OBJECTIF) {
			(*secondeCase) = CAISSE_OK;
		} else {
			(*secondeCase) = CAISSE;
		}

	}
}