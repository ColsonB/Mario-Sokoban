#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"

void editeur(sf::RenderWindow* window) {

    sf::Sprite vide, mur, caisse, caisseOk, objectif, mario;
    sf::Sprite *allAsset[6] = { &vide, &mur, &caisse, &caisseOk, &objectif, &mario };

    int objetSelect = VIDE;
    int i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

    // Chargement des textures des objets
    sf::Texture textureVide;
    textureVide.loadFromFile("src/img/vide.jpg");
    vide.setTexture(textureVide);

    sf::Texture textureMur;
    textureMur.loadFromFile("src/img/mur.jpg");
    mur.setTexture(textureMur);

    sf::Texture textureCaisse;
    textureCaisse.loadFromFile("src/img/caisse.jpg");
    caisse.setTexture(textureCaisse);

    sf::Texture textureCaisseOk;
    textureCaisseOk.loadFromFile("src/img/caisse_ok.jpg");
    caisseOk.setTexture(textureCaisseOk);

    sf::Texture textureObjectif;
    textureObjectif.loadFromFile("src/img/objectif.png");
    objectif.setTexture(textureObjectif);

    sf::Texture textureMario;
    textureMario.loadFromFile("src/img/mario_bas.gif");
    mario.setTexture(textureMario);

    sf::Event event;
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }
                //Changement objet
                if (event.key.code == sf::Keyboard::Num1) {
                    objetSelect = MUR;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    objetSelect = CAISSE;
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    objetSelect = CAISSE_OK;
                }
                if (event.key.code == sf::Keyboard::Num4) {
                    objetSelect = OBJECTIF;
                }
                if (event.key.code == sf::Keyboard::Num5) {
                    objetSelect = MARIO;
                }
                if (event.key.code == sf::Keyboard::Num0) {
                    objetSelect = VIDE;
                }
                //Sauvegarde et chargement du niveau
                if (event.key.code == sf::Keyboard::S) {
                    sauvegarderNiveau(carte);
                }
                if (event.key.code == sf::Keyboard::C) {
                    chargerNiveau(carte);
                }
            }
            //Placement objet
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            int x = mousePosition.x / TAILLE_BLOC;
            int y = mousePosition.y / TAILLE_BLOC;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                carte[x][y] = objetSelect;
                sauvegarderNiveau(carte);
            }
        }
        window->clear(sf::Color::Black);
        window->draw(*allAsset[objetSelect]);
        window->display();
        chargerNiveau(carte);
    }
}