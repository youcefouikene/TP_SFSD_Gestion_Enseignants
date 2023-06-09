#include <stdio.h>
#include <stdlib.h>
#include "Library.h"
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main()
{

    srand(time(NULL)); /*Pour generer des nombres aleatoires a chaque execution du programme*/

    nb_ecrt=0; /*Initialiser le nombre de EcrireDir a 0.*/

    nb_lect=0; /*Initialiser le nombre de LireDir a 0.*/

    Init_Tab_Ets(); /*Initialiser le tableau contenant les differents etablissements universitaires.*/

    Init_Tab_Wilayas(); /*Initialiser le tableau contenant les codes des wilayas avec leurs libelles.*/

    Chargement_IndexPrimaire(); /*Chargement de la table d'index primaire.*/

    Chargement_IndexSecond(); /*Chargement des indexes secondaires.*/

    Welcome();

    Menu();

    Quitter();

    Sauvegarde_IndexPrimaire(); /*Sauvegarde de l'index primaire.*/

    Sauvegarde_IndexSecond(); /*Sauvegarde des indexes secondaires.*/

    return 0;

}
