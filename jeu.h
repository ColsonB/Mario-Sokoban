#include <SFML/Graphics.hpp>
#include <iostream>

#include "constantes.h"

void jouer(sf::RenderWindow* ecran)
{

	using namespace std;

	sf::Sprite* mario[4] = { NULL }; // 4 surfaces pour 4 directions de Mario
	sf::Sprite* mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::Transformable position, positionJoueur;
	sf::Event event;

	sf::RenderWindow* (marioActuel, NULL, ecran, &position);

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (décors, personnage...)
	sf::Texture texture_mur;
	if (!texture_mur.loadFromFile("src/img/mur.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texture_caisse;
	if (!texture_caisse.loadFromFile("src/img/caisse.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texture_caisseOK;
	if (!texture_caisseOK.loadFromFile("src/img/caisseOK.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}
	
	sf::Texture texture_objectif;
	if (!texture_objectif.loadFromFile("src/img/objectif.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texture_mario[BAS];
	if (!texture_mario[BAS].loadFromFile("src/img/mario_bas.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texture_mario[GAUCHE];
	if (!texture_mario[GAUCHE].loadFromFile("src/img/mario_gauche.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texture_mario[HAUT];
	if (!texture_mario[HAUT].loadFromFile("src/img/mario_haut.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture mario[DROITE];
	if (!texture_mario[DROITE].loadFromFile("src/img/mario_droite.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	// Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
	}

	// Recherche de la position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j]) == MARIO) // Si Mario se trouve à cette position
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	sf::Event::KeyPressed(100, 100); // Activation de la répétition des touches

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

	// Effacement de l'écran
	window.clear(ecran, NULL, /*SDL_MapRGB(ecran->format, 255, 255, 255)*/);

	// Placement des objets à l'écran
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
				sf::RenderWindow*(mur, NULL, ecran, &position);
				break;
			case CAISSE:
				sf::RenderWindow*(caisse, NULL, ecran, &position);
				break;
			case CAISSE_OK:
				sf::RenderWindow*(caisseOK, NULL, ecran, &position);
				break;
			case OBJECTIF:
				sf::RenderWindow*(objectif, NULL, ecran, &position);
				objectifsRestants = 1;
				break;
			}
		}
	}

	// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
	if (!objectifsRestants)
		continuer = 0;

	// On place le joueur à la bonne position
	position.x = positionJoueur.x * TAILLE_BLOC;
	position.y = positionJoueur.y * TAILLE_BLOC;
	sf::RenderWindow*(marioActuel, NULL, ecran, &position);
}
