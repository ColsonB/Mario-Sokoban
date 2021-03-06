#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "fichier.h"
#include "jeu.h"
#include "editeur.h"

void selectionJeu(sf::RenderWindow* window) {

    int continuer = 1;

    // Chargement des textures du menu de selection de niveau
    sf::Texture textureSeclectionLvl;
    sf::Sprite selectionLvl;

    textureSeclectionLvl.loadFromFile("src/img/selectionlvljeu.png");
    selectionLvl.setTexture(textureSeclectionLvl);

    // On fait tourner le programme jusqu'? ce que la fen?tre soit ferm?e
    while (continuer == 1) {
        // On inspecte tous les ?v?nements de la fen?tre qui ont ?t? ?mis depuis la pr?c?dente it?ration
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
                // Selection du niveau
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    jouer(window, 1);
                }
                if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    jouer(window, 2);
                }
                if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    jouer(window, 3);
                }
                if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                    jouer(window, 4);
                }
                if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    jouer(window, 5);
                } 
            }
            window->draw(selectionLvl);
            window->display();
        }
        window->clear(sf::Color::Black);
    }
}

void selectionEdition(sf::RenderWindow* window) {

    int continuer = 1;

    // Chargement des textures du menu de selection de niveau
    sf::Texture textureSeclectionLvl;
    sf::Sprite selectionLvl;

    textureSeclectionLvl.loadFromFile("src/img/selectionlvledition.png");
    selectionLvl.setTexture(textureSeclectionLvl);

    // On fait tourner le programme jusqu'? ce que la fen?tre soit ferm?e
    while (continuer == 1) {
        // On inspecte tous les ?v?nements de la fen?tre qui ont ?t? ?mis depuis la pr?c?dente it?ration
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
                // Selection du niveau
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    editeur(window, 1);
                }
                if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    editeur(window, 2);
                }
                if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    editeur(window, 3);
                }
                if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                    editeur(window, 4);
                }
                if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    editeur(window, 5);
                }
            }
            window->draw(selectionLvl);
            window->display();
        }
        window->clear(sf::Color::Black);
    }
}

void regle(sf::RenderWindow* window) {

    int continuer = 1;

    // Chargement des textures du menu de selection de niveau
    sf::Texture textureRegle;
    sf::Sprite regle;

    textureRegle.loadFromFile("src/img/regle.png");
    regle.setTexture(textureRegle);

    // On fait tourner le programme jusqu'? ce que la fen?tre soit ferm?e
    while (continuer == 1) {
        // On inspecte tous les ?v?nements de la fen?tre qui ont ?t? ?mis depuis la pr?c?dente it?ration
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
            }
            window->draw(regle);
            window->display();
        }
        window->clear(sf::Color::Black);
    }
}