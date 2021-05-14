#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"

void editeur(sf::RenderWindow* window, int lvl) {

    sf::Sprite vide, mur, caisse, objectif, caisseOk, mario;
    sf::Sprite choixVide, choixMur, choixCaisse, choixObjectif, choixCaisseOk, choixMario;
    sf::Sprite *allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };

    int objetSelect = VIDE;
    int continuer = 1, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

    // Chargement de la police d'�criture
    sf::Font font;
    font.loadFromFile("src/font/Ketchum.otf");

    // Chargement des sprites
    sf::Texture textureVide;
    textureVide.loadFromFile("src/img/vide.png");
    vide.setTexture(textureVide);

    sf::Texture textureChoixVide;
    textureChoixVide.loadFromFile("src/img/choix_vide.png");
    choixVide.setTexture(textureChoixVide);

    sf::Texture textureMur;
    textureMur.loadFromFile("src/img/mur.png");
    mur.setTexture(textureMur);

    sf::Texture textureChoixMur;
    textureChoixMur.loadFromFile("src/img/choix_mur.png");
    choixMur.setTexture(textureChoixMur);

    sf::Texture textureCaisse;
    textureCaisse.loadFromFile("src/img/caisse.png");
    caisse.setTexture(textureCaisse);

    sf::Texture textureChoixCaisse;
    textureChoixCaisse.loadFromFile("src/img/choix_caisse.png");
    choixCaisse.setTexture(textureChoixCaisse);

    sf::Texture textureObjectif;
    textureObjectif.loadFromFile("src/img/objectif.png");
    objectif.setTexture(textureObjectif);

    sf::Texture textureChoixObjectif;
    textureChoixObjectif.loadFromFile("src/img/choix_objectif.png");
    choixObjectif.setTexture(textureChoixObjectif);

    sf::Texture textureCaisseOk;
    textureCaisseOk.loadFromFile("src/img/caisse_ok.png");
    caisseOk.setTexture(textureCaisseOk);

    sf::Texture textureChoixCaisseOK;
    textureChoixCaisseOK.loadFromFile("src/img/choix_caisse_ok.png");
    choixCaisseOk.setTexture(textureChoixCaisseOK);

    sf::Texture textureMario;
    textureMario.loadFromFile("src/img/mario_bas.png");
    mario.setTexture(textureMario);

    sf::Texture textureChoixMario;
    textureChoixMario.loadFromFile("src/img/mario.png");
    choixMario.setTexture(textureChoixMario);

    chargerNiveau(carte, lvl);

    // On fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
    while (continuer == 1) {
        // On inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
                //Changement objet
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    objetSelect = MUR;
                }
                if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    objetSelect = CAISSE;
                }
                if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    objetSelect = OBJECTIF;
                }
                if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                    objetSelect = CAISSE_OK;
                }
                if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    objetSelect = MARIO;
                }
                if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
                    objetSelect = VIDE;
                }
                //Sauvegarde et chargement du niveau
                if (event.key.code == sf::Keyboard::Enter) {
                    sauvegarderNiveau(carte, lvl);
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    chargerNiveau(carte, lvl);
                }
            }

            //Placement objet
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::FloatRect Position;
            for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
                for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) { 
                    int x = mousePosition.x / TAILLE_BLOC;
                    int y = mousePosition.y / TAILLE_BLOC;
                    Position.top = colonne * TAILLE_BLOC;
                    Position.left = ligne * TAILLE_BLOC;
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        carte[x][y] = objetSelect;
                    }
                    sf::Sprite* asset = allAsset [carte[ligne][colonne]] ;
                    asset->setPosition(Position.left, Position.top);
                    window->draw(*asset);
                }
            }

            // Affichage du num�ro du niveau
            sf::Text niveau;
            niveau.setFont(font);
            niveau.setString("Edition Niveau " + std::to_string(lvl));
            niveau.setPosition(
                (LARGEUR_FENETRE_JEU - niveau.getLocalBounds().width) / 2,
                (HAUTEUR_FENETRE_JEU + niveau.getLocalBounds().height)
            );
            window->draw(niveau);

            // Affichage choix des sprites
            sf::RectangleShape select(sf::Vector2f(68.f, 68.f));

            float largeur = LARGEUR_FENETRE - choixVide.getLocalBounds().width * 1.3;
            float hauteur = (TAILLE_BLOC / 2) + (choixVide.getLocalBounds().height);

            select.setFillColor(sf::Color(255, 255, 255, 80));
            choixVide.setPosition(largeur, hauteur * VIDE);
            choixMur.setPosition(largeur, hauteur * MUR);
            choixCaisse.setPosition(largeur, hauteur * CAISSE);
            choixObjectif.setPosition(largeur, hauteur * OBJECTIF);
            choixCaisseOk.setPosition(largeur, hauteur * CAISSE_OK);
            choixMario.setPosition(largeur, hauteur * MARIO);
            if (objetSelect == VIDE) {
                select.setPosition(largeur, hauteur * VIDE);
            }
            if (objetSelect == MUR) {
                select.setPosition(largeur, hauteur * MUR);
            }
            if (objetSelect == CAISSE) {
                select.setPosition(largeur, hauteur * CAISSE);
            }
            if (objetSelect == OBJECTIF) {
                select.setPosition(largeur, hauteur * OBJECTIF);
            }
            if (objetSelect == CAISSE_OK) {
                select.setPosition(largeur, hauteur * CAISSE_OK);
            }
            if (objetSelect == MARIO) {
                select.setPosition(largeur, hauteur * MARIO);
            }
            window->draw(choixMur);
            window->draw(choixCaisse);
            window->draw(choixObjectif);
            window->draw(choixCaisseOk);
            window->draw(choixMario);
            window->draw(select);

            window->display();
            
        }
        window->clear(sf::Color::Black);
        
    }
}