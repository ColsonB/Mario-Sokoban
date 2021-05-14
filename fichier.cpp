#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "constantes.h"

using namespace std;

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl){
	FILE* fichier = NULL;
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = { 0 };
	int i = 0, j = 0;
    std::string path = "src/stage/niveau";
    path += std::to_string(lvl);
    path += ".lvl";

    fichier = fopen(path.c_str(), "r");
	if (fichier == NULL) {
		return 0;
	}else{
		fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
        for (i = 0; i < NB_BLOCS_LARGEUR; i++){
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++){
                switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j]){
                    case '0':
                        niveau[j][i] = 0;
                        break;
                    case '1':
                        niveau[j][i] = 1;
                        break;
                    case '2':
                        niveau[j][i] = 2;
                        break;
                    case '3':
                        niveau[j][i] = 3;
                        break;
                    case '4':
                        niveau[j][i] = 4;
                        break;
                    case '5':
                        niveau[j][i] = 5;
                        break;
                }
            }
        }
	}
    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl){
    FILE* fichier = NULL;
    int i = 0, j = 0;
    std::string path = "src/stage/niveau";
    path += std::to_string(lvl);
    path += ".lvl";

    fichier = fopen(path.c_str(), "w");
    if (fichier == NULL)
        return 0;

    for (i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }

    fclose(fichier);
    return 1;
}