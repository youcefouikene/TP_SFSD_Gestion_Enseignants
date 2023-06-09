#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define taille 1024
#define taille_indsecond 5
#define taille_indprimaire 3


typedef struct {

    int Day;
    int Month;
    int Year;

}Date;

typedef struct {

    char Nom [200];
    char Region [20];

}Etablissement;

/*---------------------------------------- Structure LOBF --------------------------------------------*/

typedef struct {

    long int Matricule;
    char Nom[50];
    char Prenom [50];
    Date Date_Naissance;
    char Wilaya_Naissance [50];
    char Sexe [10];
    char Groupe_Sanguin [10];
    Date Date_Recrutement;
    char Grade [40];
    char Specialite [100];
    char Dernier_Diplome [30];
    Etablissement Ets;

}TEnseignant;

typedef struct {

    TEnseignant Tab[taille];
    int nb;
    int lien;

}TBloc;

typedef struct {

    int Tete;
    int Tete_LBV;
    int nb_blocs_physiques;
    char Date_Creation[100];
    char Date_Modification[100];

}En_Tete;

typedef struct {

    FILE *Fichier;
    En_Tete TEn_Tete;

}LOBF;

/*------------------------------------ Structure Index Primaire ----------------------------------*/


typedef struct {

    long int Matricule;
    int Num_Bloc;
    int Depl;
    bool efface;

}TIndex;

typedef struct {

    TIndex Tab[taille_indprimaire];
    int nb;

}TBlocIndex;

typedef struct {

    int Num_Dernier_Bloc;
    int nb_enreg_inseres;

}En_Tete_FIndex;

typedef struct {

    FILE *Fichier;
    En_Tete_FIndex TIndex_En_Tete;

}F_Index;

/*----------------------------------- Structure Index Secondaire ----------------------------------------*/

typedef struct {

    long int Tab[taille_indsecond];
    int lien;
    int nb;

}Bloc_Index_Secondaire;


typedef struct {

    int nb_blocs_physiques;

}En_Tete_Index_Secondaire;


typedef struct {

    FILE *Fichier;
    En_Tete_Index_Secondaire TEn_Tete;

}LOBF_Index_Secondaire;

/*---------------------------------------- Structure liste -------------------------------------------*/

typedef struct maillon{

    long int matricule;
    struct maillon* next;

}maillon;

typedef maillon* ptr;

/*------------------------------------ Structure liste bidirectionnelle -----------------------------*/

typedef struct maillon_bi{

    TEnseignant ENS;
    struct maillon_bi* suiv;
    struct maillon_bi* prec;

}maillon_bi;

typedef maillon_bi* ptr_bi;


/*---------------- Declarations des variables globales ------------------*/


int nb_lect,nb_ecrt; /*Nombre de LireDir et EcrireDir*/

char cle[256]; /*Cle de chiffrement et de dechiffrement*/

char Tab_Wilayas[58][58]; /*Tableau contenant les libelles des wilayas ordonnes selon leurs codes*/

Etablissement Tab_ETS[120]; /*Tableau contenant les differents etablissements universitaires*/

TIndex TabIndex[888889]; /*L'Index Primaire*/

int nbE; /*Nombre d'elements existants dans la table d'index primaire*/

/*Tables d'index secondaires contenant la tete des listes*/

ptr Tab_specialite[30];
ptr Tab_Region[3];
ptr Tab_Ets[112];

/*--------------------- Machine abstraite pour manipuler les listes -------------------*/

void Allouer_maillon(ptr* p);
void Aff_adr(ptr p, ptr q);
void Aff_val(ptr p, long int v);
ptr Suivant(ptr p);
void Insertion_LLC(long int val, ptr* tete);
void Suppression_LLC(long int val, ptr* tete);
void Init_LLc();

/*---------------- Machine abstraite pour manipuler les listes bidirectionnelles ----------------*/

void Allouer_maillon_bi(ptr_bi* p);
ptr_bi Suivant_bi(ptr_bi p);
ptr_bi Precedant_bi(ptr_bi p);
void Insertion_LLC_bi(TEnseignant ens, ptr_bi* tete);

/*------------- Machine abstraite pour manipuler le fichier de donnees ---------------*/

void Ouvrir(LOBF *F,char Nom_Fich [ ],char Mode);
int Entete (LOBF F,int i);
void Aff_Entete (LOBF *F,int i,int v);
void Fermer (LOBF *F );
void EcrireDir(LOBF F,int i, TBloc Buffer);
void LireDir(LOBF F,int i, TBloc *Buffer);
int Alloc_Bloc (LOBF *F);

/*------------ Machine abstraite pour manipuler le fichier de l'index primaire --------------------*/

void Ouvrir_FIndex(F_Index *F,char Nom_Fich [ ],char Mode);
int Entete_FIndex (F_Index F,int i);
void Aff_Entete_FIndex (F_Index *F,int i,int v);
void Fermer_FIndex (F_Index *F );
void EcrireDir_FIndex(F_Index F,int i, TBlocIndex Buffer);
void LireDir_FIndex(F_Index F,int i, TBlocIndex *Buffer);
void Sauvegarde_IndexPrimaire();
void Chargement_IndexPrimaire();

/*--------------- Machine abstraite pour manipuler les fichiers des indexes secondaires ----------------*/

void Ouvrir_IndSecond(LOBF_Index_Secondaire *F,char Nom_Fich [ ],char Mode);
int Entete_IndSecond (LOBF_Index_Secondaire F);
void Aff_Entete_IndSecond (LOBF_Index_Secondaire *F,int v);
void Fermer_IndSecond (LOBF_Index_Secondaire *F );
void EcrireDir_IndSecond(LOBF_Index_Secondaire F,int i, Bloc_Index_Secondaire Buffer);
void LireDir_IndSecond(LOBF_Index_Secondaire F,int i, Bloc_Index_Secondaire *Buffer);
int Alloc_Bloc_IndSecond (LOBF_Index_Secondaire *F);

/*------------ Procedures de traitement de donnees au niveau de l'index primaire --------------------*/

void Recherche_Index_Primaire(long int Matricule, bool *Trouv, int *k);
void Insertion_Index_Primaire (TIndex e);
void Suppression_Index_Primaire (long int Matricule);
void Modification_Index_Primaire(long int Matricule, int Nouveau_Bloc, int Nouveau_Depl);

/*--------- Procedures de traitement de donnees au niveau de l'index secondaire -------------*/

void Init_IndexSecond (char Nom_Fich[]);
void Ajout_IndexSecond (long int Matricule, int cle,char Nom_Fich[]);
void Chargement_IndexSecond();
void Sauvegarde_IndexSecond();

/*---------------- Procedures frequemment utilisees lors du traitement de donnees -------------*/

void datier(int *day,int *mois,int *an);
bool Leap_Year(int year);
int NumberOfDays(int N,int Year);
int Aleatoire (int minimum,int maximum);
void Modification_Date (LOBF *F);
void Init_Tab_Wilayas();
void Init_Tab_Ets();

/*------------------ Procedures qui retournent le code de (Specialite, Region, Etablissment) ---------*/

int Codage_Specialite (char Nom_Specialite []);
int Codage_Region (char Nom_Region []);
int Codage_Etablissement (char Nom_ETS[]);

/*---------------- Procedures principales de traitement de donnees. -----------------*/

void Creation_ENS_FIC (int n);
void Ajout_ENS (TEnseignant ENS);
void Modification_ENS(long int Matricule, int code);
void Affich_Ajout_ENS ();
void Suppression_ENS (long int Matricule);
void Suppression_ENS_Specialites(int Specialite);
void Affich_ENS_Ets(int inf,int sup,int ets);
void Affich_ENS_Region(int region);
void codage();
void decodage();

/*------------ Procedures permettant de gerer l'affichage au niveau de la console. ----------------*/

void Ecrire_chaine(char S[],int temps ,int couleurDuTexte, int couleurDeFond );
void cadre();
void cadre2();
void Aff_Wilayas();
void Aff_Specialite();
void aff();
void Affich_Tab_Ets(int *ets);
void affich_eng(int i, int j);
void logo_ESI();
void loading();
int Maximum (int a,int b);
void Permuter(int *a,int *b);
long int Taille_Fichier();
void Welcome();
void Menu();
void Affich_Creation_ENS_FIC();
void Affich_ENS();
void Affich_Fic(char Nomf[]);
void Affich_Ajout_ENS();
void Affich_Modification_ENS();
void Affich_Suppression_ENS();
void Affich_Suppression_Specialite();
void Consultation_Multicles();
void Affich_Region();
void Affich_Codage();
void Affich_Decodage();
void Affich_Codage_Decodage();
void Affich_Entete_LEDir();
void Organisation_Globale();
void Quitter();






#endif // LIBRARY_H_INCLUDED

