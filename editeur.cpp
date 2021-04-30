#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "constantes.h"

void editeur(sf::RenderWindow* window){
    sf::Sprite* mur = NULL, * caisse = NULL, * objectif = NULL, * mario = NULL;
    //sf:: position;
    sf::Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

    // Chargement des objets et du niveau
    sf::Texture texture;
    texture.loadFromFile("mur.jpg");
    texture.loadFromFile("caisse.jpg");
    texture.loadFromFile("objectif.png");
    texture.loadFromFile("mario_bas.gif");

    //A changer maintenant
    if (!chargerNiveau(carte)) {
        exit(EXIT_FAILURE);
    }

    switch(){
        case SDL_QUIT:
            continuer = 0;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
            }else if (event.button.button == SDL_BUTTON_RIGHT) // Clic droit pour effacer
                carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
                clicDroitEnCours = 1;
            }
            break;

        case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
            if (event.button.button == SDL_BUTTON_LEFT)
                clicGaucheEnCours = 0;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                clicDroitEnCours = 0;
            break;

        case SDL_MOUSEMOTION:
            if (clicGaucheEnCours){ // Si on déplace la souris et que le bouton gauche de la souris est enfoncé{
                carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
            }
            else if (clicDroitEnCours){ // Pareil pour le bouton droit de la souris
                carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_s:
                sauvegarderNiveau(carte);
                break;
            case SDLK_c:
                chargerNiveau(carte);
                break;
            case SDLK_KP1:
                objetActuel = MUR;
                break;
            case SDLK_KP2:
                objetActuel = CAISSE;
                break;
            case SDLK_KP3:
                objetActuel = OBJECTIF;
                break;
            case SDLK_KP4:
                objetActuel = MARIO;
                break;
            }
            break;
    }
}