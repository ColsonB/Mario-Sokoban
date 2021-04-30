#include <SFML/Graphics.hpp>
#include <iostream>

#include "constantes.h"
#include "jeu.h"

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Transformable* pos, int direction)
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