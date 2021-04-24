void jouer(sf::Window* ecran)
{
	sf::Window *mario[4] = { NULL };
	sf::Window *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *MarioActuel = NULL;
	sf::Transformable position, positionJoueur;
	sf::Event event;
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