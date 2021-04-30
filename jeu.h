#include <SFML/Graphics.hpp>
#include <iostream>

void jouer(sf::RenderWindow* ecran)
{

	using namespace std;

	sf::Sprite* mario[4] = { NULL }; // 4 surfaces pour 4 directions de Mario
	sf::Sprite* mur = NULL, * caisse = NULL, * caisseOK = NULL, * objectif = NULL, * marioActuel = NULL;
	sf::Transformable position, positionJoueur;
	sf::Event event;

	sf::RenderWindow(marioActuel, NULL, ecran, &position);

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (d�cors, personnage...)
	sf::Texture mur;
	if (!texture.loadFromFile("src/img/mur.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture caisse;
	if (!texture.loadFromFile("src/img/caisse.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture caisseOK;
	if (!texture.loadFromFile("src/img/caisseOK.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}
	
	sf::Texture objectif;
	if (texture.loadFromFile("src/img/objectif.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture mario[BAS];
	if (!texture.loadFromFile("src/img/mario_bas.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture mario[GAUCHE];
	if (!texture.loadFromFile("src/img/mario_gauche.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture mario[HAUT];
	if (!texture.loadFromFile("src/img/mario_haut.jpg"))
	{
		cout << "La texture n'a pas charg�e";
	}

	sf::Texture mario[DROITE];
	if (!texture.loadFromFile("src/img/mario_droite.jpg"))
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
	window.clear(ecran, NULL, /*SDL_MapRGB(ecran->format, 255, 255, 255)*/);

}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Transformable *pos, int direction)
{




}

void deplacerCaisse(int *premiereCase, int *secondeCase)
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