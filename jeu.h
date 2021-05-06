#include <SFML/Graphics.hpp>
#include <iostream>

#include "constantes.h"

void jouer(sf::RenderWindow* ecran)
{

	using namespace std;

	sf::Texture *mario[4] = { NULL }; // 4 surfaces pour 4 directions de Mario
	sf::Texture *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::Transformable position, positionJoueur;
	sf::Event event;

	sf::RenderTexture(marioActuel, NULL, ecran, &position);

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (d�cors, personnage...)
	sf::Texture texture_mur;
	if (!texture_mur.loadFromFile("src/img/mur.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texture_caisse;
	if (!texture_caisse.loadFromFile("src/img/caisse.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texture_caisseOK;
	if (!texture_caisseOK.loadFromFile("src/img/caisseOK.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}
	
	sf::Texture texture_objectif;
	if (!texture_objectif.loadFromFile("src/img/objectif.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texture_mario[BAS];
	if (!texture_mario[BAS].loadFromFile("src/img/mario_bas.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texture_mario[GAUCHE];
	if (!texture_mario[GAUCHE].loadFromFile("src/img/mario_gauche.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture texture_mario[HAUT];
	if (!texture_mario[HAUT].loadFromFile("src/img/mario_haut.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture mario[DROITE];
	if (!texture_mario[DROITE].loadFromFile("src/img/mario_droite.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	// Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE); // On arr�te le jeu si on n'a pas pu charger le niveau
	}

	// Recherche de la position de Mario au d�part
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j]) == MARIO) // Si Mario se trouve � cette position
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	sf::Event::KeyPressed(100, 100); // Activation de la r�p�tition des touches

	sf::Event event;

	while (window.pollEvent(event))
	{

		if (event.key.code == sf::Event::KeyPressed)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				marioActuel = mario[HAUT];
				deplacerJoueur(carte, &positionJoueur, HAUT);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				marioActuel = mario[BAS];
				deplacerJoueur(carte, &positionJoueur, BAS);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				marioActuel = mario[DROITE];
				deplacerJoueur(carte, &positionJoueur, DROITE);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				marioActuel = mario[GAUCHE];
				deplacerJoueur(carte, &positionJoueur, GAUCHE);
			}

		}
	}

	// Effacement de l'�cran
	window.clear(ecran, NULL);

	// Placement des objets � l'�cran
	objectifsRestants = 0;

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			position.x = i * TAILLE_BLOC;
			position.y = j * TAILLE_BLOC;

			switch(carte[i][j])
			{
			case MUR:
				sf::RenderTexture(mur, NULL, ecran, &position);
				break;
			case CAISSE:
				sf::RenderTexture(caisse, NULL, ecran, &position);
				break;
			case CAISSE_OK:
				sf::RenderTexture(caisseOK, NULL, ecran, &position);
				break;
			case OBJECTIF:
				sf::RenderTexture(objectif, NULL, ecran, &position);
				objectifsRestants = 1;
				break;
			}
		}
	}

	// Si on n'a trouv� aucun objectif sur la carte, c'est qu'on a gagn�
	if (!objectifsRestants)
		continuer = 0;

	// On place le joueur � la bonne position
	position.x = positionJoueur.x * TAILLE_BLOC;
	position.y = positionJoueur.y * TAILLE_BLOC;
	sf::RenderTexture(marioActuel, NULL, ecran, &position);
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Transformable* pos, int direction)
{
	switch (direction)
	{
		if (pos->y - 1 < 0) // Si le joueur d�passe l'�cran, on arr�te
			break;

		if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arr�te
			break;

		// Si on veut pousser une caisse, il faut v�rifier qu'il n'y a pas de mur derri�re (ou une autre caisse, ou la limite du monde)
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;
	}

	// Si on arrive l�, c'est qu'on peut d�placer le joueur !
	// On v�rifie d'abord s'il y a une caisse � d�placer
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
