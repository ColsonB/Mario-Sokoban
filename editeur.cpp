#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"

void editeur(sf::RenderWindow* window){
    sf::Sprite* mur = NULL, * caisse = NULL, * objectif = NULL, * mario = NULL;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    sf::Sprite* objetActuel = NULL;
    int objetSelect = VIDE;
    int i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

    // Chargement des textures des objets
    sf::Texture textureMur;
    textureMur.loadFromFile("src/img/mur.jpg");
    mur = new sf::Sprite(textureMur);
    sf::Texture textureCaisse;
    textureCaisse.loadFromFile("src/img/caisse.jpg");
    caisse = new sf::Sprite(textureCaisse);
    sf::Texture textureObjectif;
    textureObjectif.loadFromFile("src/img/objectif.png");
    objectif = new sf::Sprite(textureObjectif);
    sf::Texture textureMario;
    textureMario.loadFromFile("src/img/mario_bas.gif");
    mario = new sf::Sprite(textureMario);

    //Changement objet
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        objetSelect = MUR;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        objetSelect = CAISSE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        objetSelect = OBJECTIF;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        objetSelect = MARIO;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        objetSelect = VIDE;
    }

    //Placement objet
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    int x = mousePosition.x / TAILLE_BLOC;
    int y = mousePosition.y / TAILLE_BLOC;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        carte[x][y] = objetSelect;
    }

    //Sauvegarde et chargement du niveau
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        continuer = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sauvegarderNiveau(carte);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        chargerNiveau(carte);
    }
}