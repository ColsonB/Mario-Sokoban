#include <iostream>

void jouer(sf::Window* ecran)
{

	using namespace std;

	sf::Window *mario[4] = { NULL };
	sf::Window *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::Transformable position, positionJoueur;
	sf::Event event;
	sf::RenderWindow(marioActuel, NULL, ecran, &position);

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	sf::Texture mur;
	if (!mur.loadFromFile("src/img/mur.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}
	
	sf::Texture caisse;
	if (!caisse.loadFromFile("src/img/caisse.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture caisseOK;
	if (!caisseOK.loadFromFile("src/img/caisseOK.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture objectif;
	if (!objectif.loadFromFile("src/img/objectif.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture mario[BAS];
	if (!mario[BAS].loadFromFile("src/img/mario_bas.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture mario[GAUCHE];
	if (!mario[GAUCHE].loadFromFile("src/img/mario_gauche.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture mario[HAUT];
	if (!mario[HAUT].loadFromFile("src/img/mario_haut.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture mario[DROITE];
	if (!mario[DROITE].loadFromFile("src/img/mario_droite.jpg"))
	{
		cout << "La texture n'a pas chargée";
	}


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