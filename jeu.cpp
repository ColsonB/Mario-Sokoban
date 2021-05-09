#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"


void jouer(sf::RenderWindow* window)
{

	using namespace std;

	sf::Sprite* mario[4] = { NULL }; // 4 surfaces pour 4 directions de Mario
	sf::Sprite mur, caisse, caisseOk, objectif, marioActuel;
	sf::Sprite* allAsset[6] = {&mur, &caisse, &caisseOk, &objectif, &marioActuel};
	sf::Vector2i Position, PositionJoueur;
	sf::Event event;

	sf::RenderWindow(marioActuel, window, &Position);

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (décors, personnage...)
	sf::Texture texturemur;
	if (!texturemur.loadFromFile("src/img/mur.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}
	sf::Texture texturecaisse;
	if (!texturecaisse.loadFromFile("src/img/caisse.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}
	sf::Texture texturecaisseOK;
	if (!texturecaisseOK.loadFromFile("src/img/caisseOK.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture textureobjectif;
	if (!textureobjectif.loadFromFile("src/img/objectif.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texturemario[BAS];
	if (!texturemario[BAS].loadFromFile("src/img/mario_bas.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texturemario[GAUCHE];
	if (!texturemario[GAUCHE].loadFromFile("src/img/mario_gauche.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texturemario[HAUT];
	if (!texturemario[HAUT].loadFromFile("src/img/mario_haut.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texturemario[DROITE];
	if (!texturemario[DROITE].loadFromFile("src/img/mario_droite.jpg"));
	{
		cout << "La texture n'a pas chargée";
	}



	// Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
	}

	// Recherche de la Position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == MARIO) // Si Mario se trouve à cette Position
			{
				PositionJoueur.x = i;
				PositionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	sf::Event::KeyPressed* (100, 100); // Activation de la répétition des touches

	sf::Event event;

	while (window->pollEvent(event))
	{

		if (event.key.code == sf::Event::KeyPressed)
		{

			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window->close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					marioActuel = mario[HAUT];
					deplacerJoueur(carte, &PositionJoueur, HAUT);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					marioActuel = mario[BAS];
					deplacerJoueur(carte, &PositionJoueur, BAS);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					marioActuel = mario[DROITE];
					deplacerJoueur(carte, &PositionJoueur, DROITE);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					marioActuel = mario[GAUCHE];
					deplacerJoueur(carte, &PositionJoueur, GAUCHE);
				}

			}
		}

		// Effacement de l'écran
		window->clear(sf::Color::Black);

		// Placement des objets à l'écran
		objectifsRestants = 0;
		
		sf::FloatRect Position;
		for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
			for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) 
				Position.top = colonne * TAILLE_BLOC;
				Position.left = ligne * TAILLE_BLOC;
				Position.width = TAILLE_BLOC;
				Position.height = TAILLE_BLOC;
				sf::Sprite* asset = allAsset[carte[ligne][colonne]];
				asset->setPosition(Position.left, Position.top);
				window->draw(*asset);
			}
		}

		// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
		if (!objectifsRestants)
			continuer = 0;

		// On place le joueur à la bonne Position
		Position.x = PositionJoueur.x * TAILLE_BLOC;
		Position.y = PositionJoueur.y * TAILLE_BLOC;
		sf::RenderWindow(marioActuel, window, &Position);
	}

	void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction)
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
	}