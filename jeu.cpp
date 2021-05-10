#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"


void jouer(sf::RenderWindow* window) {

	using namespace std;

	sf::Sprite vide, mur, caisse, caisseOk, objectif, marioHaut, marioBas, marioGauche, marioDroite;
	sf::Sprite* allAsset[6] = { &vide, &mur, &caisse, &caisseOk, &objectif };
	sf::Vector2i Position, PositionJoueur;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
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

	sf::Texture textureMarioHaut;
	textureMarioHaut.loadFromFile("src/img/mario_haut.png");
	marioHaut.setTexture(textureMarioHaut);

	sf::Texture textureMarioBas;
	textureMarioBas.loadFromFile("src/img/mario_bas.png");
	marioBas.setTexture(textureMarioBas);

	sf::Texture textureMarioGauche;
	textureMarioGauche.loadFromFile("src/img/mario_gauche.png");
	marioGauche.setTexture(textureMarioGauche);

	sf::Texture textureMarioDroite;
	textureMarioDroite.loadFromFile("src/img/mario_droite.png");
	marioDroite.setTexture(textureMarioDroite);

	// Chargement du niveau
	chargerNiveau(carte);

	// Recherche de la Position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++){
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++){
			if (carte[i][j] == MARIO){ // Si Mario se trouve à cette Position
				PositionJoueur.x = i;
				PositionJoueur.y = j;
				//carte[i][j] = VIDE;
			}
		}
	}

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window->isOpen()) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window->close();
				}

				if (event.key.code == sf::Keyboard::Up) {
					textureMarioHaut;
					//deplacerJoueur(carte, &PositionJoueur, HAUT);
				}

				if (event.key.code == sf::Keyboard::Down) {
					textureMarioBas;
					//deplacerJoueur(carte, &PositionJoueur, BAS);
				}

				if (event.key.code == sf::Keyboard::Right) {
					textureMarioDroite;
					//deplacerJoueur(carte, &PositionJoueur, DROITE);
				}

				if (event.key.code == sf::Keyboard::Left) {
					textureMarioGauche;
					//deplacerJoueur(carte, &PositionJoueur, GAUCHE);
				}
			}

			/* Affichage du niveau */
			sf::FloatRect Position;
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ligne * TAILLE_BLOC;
					Position.width = TAILLE_BLOC;
					Position.height = TAILLE_BLOC;
					sf::Sprite* asset = allAsset[carte[ligne][colonne]];
					asset->setPosition(Position.left, Position.top);
					window->draw(*asset);
				}
			}			
			window->display();
		}
		window->clear(sf::Color::Black);
		/* Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
		if (objectifsRestants == 0) {
			sf::Text text;
			text.setString("Victoire");
			window->draw(text);
			window->display();
		}*/
	}
}

	/*void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction)
	{
		switch (direction)
		{
			if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
				break;

			if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
				break;

			// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
			if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
				(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
					carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
				break;
		}

		// Si on arrive là, c'est qu'on peut déplacer le joueur !
		// On vérifie d'abord s'il y a une caisse à déplacer
		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--;

	}

	void deplacerCaisse(int* premiereCase, int* secondeCase)
	{
		if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
		{
			if (*secondeCase == OBJECTIF)
			{
				*secondeCase == CAISSE_OK;
			}

			else
			{
				*secondeCase = CAISSE;
			}

			if (*premiereCase == CAISSE_OK)
			{
				*premiereCase = OBJECTIF;
			}

			else
			{
				*premiereCase = VIDE;
			}
		}
	}*/