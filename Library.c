#include "Library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "Color.c"
#include "conio.c"


void datier(int *day,int *mois,int *an) /*Retourne la date courante*/
{
    time_t now;

    time(&now);
    struct tm *local = localtime(&now);
    *day = local->tm_mday;
    *mois = local->tm_mon + 1;
    *an = local->tm_year + 1900;
}

bool Leap_Year(int year) { /*Verifier si l'annee est bissextile ou non*/


   // leap year if perfectly divisible by 400
   if (year % 400 == 0) {
      return true;
   }
   // not a leap year if divisible by 100
   // but not divisible by 400
   else if (year % 100 == 0) {
      return false;
   }
   // leap year if not divisible by 100
   // but divisible by 4
   else if (year % 4 == 0) {
      return true;
   }
   // all other years are not leap years
   else {
      return false;
   }

}

int NumberOfDays(int N,int Year) /*Retourne le nombre de jours dans le mois*/
{

    // Check for 31 Days
    if (N == 1 || N == 3 || N == 5
        || N == 7 || N == 8 || N == 10
        || N == 12) {
        return 31;
    }

    // Check for 30 Days
    else if (N == 4 || N == 6
             || N == 9 || N == 11) {
        return 30;
    }

    // Check for 28/29 Days
    else if (N == 2) {

        if(Leap_Year(Year)== true){
            return 29;
        }
        else {
            return 28;
        }
    }

    // Else Invalid Input
    else {
        return -1;

    }

}


int Aleatoire (int minimum, int maximum){ /*Generer un nombre aleatoire entre minimum et maximum*/
    return ((rand() % (maximum - minimum + 1)) + minimum);
}

void Modification_Date (LOBF *F){ /*Mettre a jour la date de modification du fichier de donnees*/

    time_t now;

    /* Recuperer la date courante en une chaine de caracteres en utilisant la fonction "time" */

    time(&now);
    strcpy(F->TEn_Tete.Date_Modification,ctime(&now));

}

void Init_Tab_Ets() /* Charger les etablissements universitaires a partir d'un fichier texte */
{
    FILE *FTEU = fopen("Etablissement_Univ.txt","r+"); /* Ouvrir le fichier texte contenant les etablissements universitaires en mode lecture */

    char ligne [256];
    int i=0;

    while (!feof(FTEU)){

        fgets(ligne,sizeof(ligne),FTEU); /* Charger une ligne du fichier texte */
        ligne [strlen(ligne)-1]= '\0';
        if ((i>= 0)&& (i<=44)){ /* Etablissement se trouve dans la region centre */
            strcpy(Tab_ETS[i].Nom,ligne);
            strcpy(Tab_ETS[i].Region,"Centre");
        }
        if ((i>44)&&(i<=81)){ /* Etablissement se trouve dans la region est */
            strcpy(Tab_ETS[i].Nom,ligne);
            strcpy(Tab_ETS[i].Region,"Est");
        }
        if (i>81){  /* Etablissement se trouve dans la region est */
            strcpy(Tab_ETS[i].Nom,ligne);
            strcpy(Tab_ETS[i].Region,"Ouest");
        }
        i++;

    }

    fclose(FTEU); /* Fermeture du fichier texte */

}

/* Initialiser le tableau contenant les differentes wilayas */

void Init_Tab_Wilayas()
{
        char Wilaya [60][60] = {"Adrar","Chlef","Laghouat","Oum-El-Bouaghi","Batna","Bejaia","Biskra","Bechar","Blida","Bouira","Tamanrasset","Tebessa","Tlemcen","Tiaret","Tizi-Ouzou","Alger","Djelfa","Jijel","Setif","Saida","Skikda","Sidi-Bel-Abbes","Annaba","Guelma","Constantine","Medea","Mostaganem","Msila","Mascara","Ouargla","Oran","El-Bayadh","Illizi","Bordj-Bou-Arreridj","Boumerdes","El-Tarf","Tindouf","Tissemsilt","El-Oued","Khenchela","Souk-Ahras","Tipaza","Mila","Ain-Defla","Naama","Ain-Temouchent","Ghardaia","Relizane","Timimoun","Bordj-Badji-Mokhtar","Ouled-Djellal","Beni-Abbes","In-Salah","In-Guezzam","Touggourt","Djanet","El-Mghair","El-Meniaa"};
        int i;
        for(i=0;i<58;i++)
        {
            strcpy(Tab_Wilayas[i],Wilaya[i]);
        }
}


/*--------------------- Fonctions qui retournent le code de (Specialite, Region, Etablissment)------------*/



int Codage_Specialite (char Nom_Specialite []){ /*Retourne le code de la specialite*/

    char Tab_Specialite [50][80] = {"Informatique","Biologie","Geologie","Medecine","Pharmacie","Chirurgie Dentaire",

    "Science de la vie et de la nature","Science Islamique","Science Politique","Science Economique",

    "Science Humaine et Sociale","Science de la Matiere","Genie des Procedes","Genie Civil","Genie Mecanique",

    "Genie Electrique","Architecture","Droit","Mathematiques","Philosophie","Literature et Langues",

    "Archeologie","Aeronautique","Education physique et sportive","Hydraulique","Traduction",

    "Science de la communication et des medias","Science Agronomique","Veterinaire","Genie industriel"};

    int v,i;

    v = -1; /*Pour indiquer que la specialite n'existe pas*/

    i = 0; /*Un compteur permettant de parcourir sequentiellement le tableau des specialites*/

    bool stop=false;


    while ((stop == false)&&(i<30)){ /* TQ on n'a pas trouve la specialite correspondante et on n'est pas arrive a la derniere specialite */

        if (strcmpi(Nom_Specialite,Tab_Specialite[i])==0){ /*Comparer la chaine Nom_Specialite avec celle de la ieme specialite*/

                stop = true; /*Arreter la recherche*/

                v = i+1; /*Le code correspondant est i+1 (car en C les tableaux commencent a partir de la case d'indice 0*/
        }

        i++;

    }

    return v; /*Retourner le code de la spceialite correspondante*/

}

int Codage_Region (char Nom_Region []){ /* Retourne le code de la region. */

    int code;

    if (strcmpi(Nom_Region,"Ouest")==0){

        code = 1;

    }
    else {

        if (strcmpi(Nom_Region,"Centre")==0){

            code = 2;

        }
        else {

            code = 3;

        }

    }

    return code;

}

int Codage_Etablissement (char Nom_ETS[]){ /* Retourne le code de l'etablissement. Meme logique que le procedure qui retourne le code de la specialite */

    bool stop = false;

    int i,v;

    i = 0;

    v = -1;

    while ((stop==false)&&(i<112)){

        if (strcmpi(Nom_ETS,Tab_ETS[i].Nom)==0){

            stop = true;

            v = i+1;

        }

        i++;

    }

    return v;

}

/*----------------------------------- Implementation machine abstraite des listes -----------------------------*/

void Allouer_maillon(ptr* p)
{
    *p = (ptr)malloc(sizeof(maillon));
}

void Aff_adr(ptr p, ptr q)
{
    p->next=q;
}

void Aff_val(ptr p, long int v)
{
    p->matricule=v;
}

ptr Suivant(ptr p)
{
    if(p==NULL)
    {
        return NULL;
    }
    else
    {
        return p->next;
    }
}

void Insertion_LLC(long int val, ptr* tete)
{
    ptr p;
    Allouer_maillon(&p);
    Aff_val(p,val);
    if (*tete==NULL)
    {
        *tete=p;
        Aff_adr(*tete,NULL);
    }
    else
    {
        Aff_adr(p,*tete);
        *tete=p;
    }
}

void Suppression_LLC(long int val, ptr* tete)
{
    if(*tete!=NULL)
    {
        ptr p,q;
        p=*tete;
        if(p->matricule==val)
        {
            *tete=Suivant(*tete);
            free(p);
        }
        else
        {
            q=Suivant(p);
            while(q->matricule!=val)
            {
                p=Suivant(p);
                q=Suivant(q);
            }
            Aff_adr(p,Suivant(q));
            free(q);
        }
    }

}

void Init_LLc() /* Lors de la creation d'un nouveau fichier, il faut liberer les anciens maillons et mettre la tete des listes a NIL */
{
    ptr p,q;
    for(int j=0;j<3;j++)    /*Liberer les maillons des listes des regions et initialiser les tetes des listes a NIL*/
    {
        p=Tab_Region[j]; /*Recuperer la tete de la liste*/
        while(p!=NULL)
        {
            q=Suivant(p);   /*Sauvegarder le suivant du maillon*/
            free(p);    /*Liberer le maillon courant*/
            p=q;    /*Passer au prochain maillon*/
        }
        Tab_Region[j]=NULL; /*Initialiser les tetes des listes a NIL*/
    }

    for(int j=0;j<30;j++) /*Meme principe pour les listes des specialites*/
    {
        p=Tab_specialite[j];
        while(p!=NULL)
        {
            q=Suivant(p);
            free(p);
            p=q;
        }
        Tab_specialite[j]=NULL;
    }

    for(int j=0;j<112;j++) /*Ainsi que les listes des etablissements universitaires*/
    {
        p=Tab_Ets[j];
        while(p!=NULL)
        {
            q=Suivant(p);
            free(p);
            p=q;
        }
        Tab_Ets[j]=NULL;
    }
}


/*------------------------------------- Implementation Machine abstraite des listes Bi -----------------------------*/

void Allouer_maillon_bi(ptr_bi* p)
{
    *p = (ptr_bi)malloc(sizeof(maillon_bi));
}

ptr_bi Suivant_bi(ptr_bi p)
{
    if(p==NULL)
    {
        return NULL;
    }
    else
    {
        return p->suiv;
    }
}

ptr_bi Precedant_bi(ptr_bi p)
{
    if(p==NULL)
    {
        return NULL;
    }
    else
    {
        return p->prec;
    }
}

void Insertion_LLC_bi(TEnseignant ens, ptr_bi* tete)
{
    ptr_bi p;
    Allouer_maillon_bi(&p);
    p->ENS=ens;
    if (*tete==NULL)
    {
        *tete=p;
        p->prec=NULL;
        p->suiv=NULL;
    }
    else
    {
        (*tete)->prec=p;
        p->suiv=*tete;
        p->prec=NULL;
        *tete=p;
    }
}


/*-------------------------------------- Implementation Machine Abstraite Fichier LOBF ----------------------------------------------*/

void Ouvrir (LOBF *F, char Nom_Fich [ ], char Mode){

    if ((Mode == 'N') || (Mode == 'n')){
        F->Fichier = fopen(Nom_Fich,"wb+"); /*Creer le fichier de donnees*/
        if (F->Fichier == NULL){
            printf("-> Erreur lors de la creation du fichier!\n"); /*Si une erreur se produise lors de la creation du fichier, alors l'indiquer a l'utilisateur*/
        }
        else {

            time_t now;
            time(&now);

            /*Initialisation de l'en-tete du fichier*/

            strcpy(F->TEn_Tete.Date_Creation,ctime(&now));
            strcpy(F->TEn_Tete.Date_Modification,ctime(&now));
            F->TEn_Tete.Tete_LBV = -1;
            F->TEn_Tete.Tete = -1;
            F->TEn_Tete.nb_blocs_physiques = 0;

            /*Ecriture de l'en-tete dans le fichier*/

            fwrite(&F->TEn_Tete,sizeof(En_Tete),1,F->Fichier);

        }
    }
    else {
        if ((Mode == 'A') || (Mode == 'a')){
            F->Fichier = fopen(Nom_Fich,"rb+"); /*Ouvrir le fichier existant*/
            if (F->Fichier == NULL){
                printf("-> Erreur lors de l'ouverture du fichier!\n"); /*Si une erreur se produise lors de l'ouverture du fichier, alors l'indiquer a l'utilisateur*/
            }
            else {
                fread(&F->TEn_Tete,sizeof(En_Tete),1,F->Fichier); /*Chargement de l'en-tete en memoire centrale*/
            }
        }
        else {
            printf("-> Mode d'ouverture Errone!\n");
        }
    }

}

int Entete (LOBF F,int i){ /*Retourne la ieme caracteristique de l'en-tete*/

    int val=0;

    switch (i) {

        case 1:     val = F.TEn_Tete.Tete;
                    break;

        case 2:     val = F.TEn_Tete.Tete_LBV;
                    break;

        case 3:     val = F.TEn_Tete.nb_blocs_physiques;
                    break;

    }
    return val;
}

void Aff_Entete (LOBF *F,int i,int v){ /*Mettre a jour la ieme caracteristique de l'en-tete*/

    switch (i) {

        case 1: (F->TEn_Tete.Tete = v);
                break;

        case 2: (F->TEn_Tete.Tete_LBV = v);
                break;

        case 3: (F->TEn_Tete.nb_blocs_physiques = v);
                break;

    }
}

void Fermer (LOBF *F ){
    rewind(F->Fichier); /*Positionner le curseur en debut du fichier*/
    fwrite(&F->TEn_Tete,sizeof(En_Tete),1,F->Fichier); /*Ecrire le bloc en-tete dans le fichier*/
    fclose(F->Fichier); /*Fermeture du fichier*/
}

void EcrireDir(LOBF F,int i, TBloc Buffer){
    fseek(F.Fichier,sizeof(En_Tete)+(i-1)*sizeof(TBloc),SEEK_SET); /*Positionner le curseur dans le fichier*/
    fwrite(&Buffer,sizeof(TBloc),1,F.Fichier); /*Ecriture du bloc*/
}

void LireDir(LOBF F,int i, TBloc *Buffer){

    fseek(F.Fichier,sizeof(En_Tete)+(i-1)*sizeof(TBloc),SEEK_SET); /*Positionner le curseur dans le fichier*/
    fread(Buffer,sizeof(TBloc),1,F.Fichier); /*Chargement du bloc en memoire centrale dans la variable Buffer*/
}

int Alloc_Bloc (LOBF *F){ /*Allouer un nouveau bloc dans le fichier*/

    TBloc Buffer;

    int n;

    if (Entete(*F,2)== -1){ /*Si la tete de la liste des blocs vides est a nil*/

        Aff_Entete(F,3,Entete(*F,3)+1); /*Mettre a jour le nombre de blocs physiques existants dans le fichier*/

        n = Entete(*F,3);

    }

    else {

        n = Entete(*F,2); /* Recuperer la tete des blocs vides */

        LireDir(*F,n,&Buffer); /*Mettre a jour la tete de la liste des blocs vides*/

        nb_lect++;

        Aff_Entete(F,2,Buffer.lien);

    }

    return n; /*Retourner le numero du bloc alloue*/

}

/*---------------------------- Implementation Machine Abstraite Fichier_Index_Primaire TOBF ----------------*/

void Ouvrir_FIndex(F_Index *F,char Nom_Fich [ ],char Mode){

    if ((Mode == 'N') || (Mode == 'n')){
        F->Fichier = fopen(Nom_Fich,"wb+");
        if (F->Fichier == NULL){
            printf("-> Erreur lors de la creation du fichier!\n");
        }
        else {
            F->TIndex_En_Tete.Num_Dernier_Bloc = 1;
            F->TIndex_En_Tete.nb_enreg_inseres = 0;
            fwrite(&F->TIndex_En_Tete,sizeof(En_Tete_FIndex),1,F->Fichier);

        }
    }
    else {
        if ((Mode == 'A') || (Mode == 'a')){
            F->Fichier = fopen(Nom_Fich,"rb+");
            if (F->Fichier == NULL){
                printf("-> Erreur lors de l'ouverture du fichier!\n");
            }
            else {
                fread(&F->TIndex_En_Tete,sizeof(En_Tete_FIndex),1,F->Fichier);
            }
        }
        else {
            printf("-> Mode d'ouverture Errone!\n");
        }
    }

}

int Entete_FIndex (F_Index F,int i){

    int val=0;

    switch (i) {

        case 1:     val = F.TIndex_En_Tete.Num_Dernier_Bloc;
                    break;

        case 2:     val = F.TIndex_En_Tete.nb_enreg_inseres;
                    break;

    }

    return val;

}

void Aff_Entete_FIndex (F_Index *F,int i,int v){

    switch (i) {

        case 1: (F->TIndex_En_Tete.Num_Dernier_Bloc = v);
                break;

        case 2: (F->TIndex_En_Tete.nb_enreg_inseres = v);
                break;

    }

}

void Fermer_FIndex (F_Index *F ){

    rewind(F->Fichier);
    fwrite(&F->TIndex_En_Tete,sizeof(En_Tete_FIndex),1,F->Fichier);
    fclose(F->Fichier);

}

void EcrireDir_FIndex(F_Index F,int i, TBlocIndex Buffer){

    fseek(F.Fichier,sizeof(En_Tete_FIndex)+(i-1)*sizeof(TBlocIndex),SEEK_SET);
    fwrite(&Buffer,sizeof(TBlocIndex),1,F.Fichier);

}

void LireDir_FIndex(F_Index F,int i, TBlocIndex *Buffer){

    fseek(F.Fichier,sizeof(En_Tete_FIndex)+(i-1)*sizeof(TBlocIndex),SEEK_SET);
    fread(Buffer,sizeof(TBlocIndex),1,F.Fichier);

}

/*------------------------------------ Procedures  Index primaire -----------------------------*/

void Recherche_Index_Primaire(long int Matricule, bool *Trouv, int *k){ /*Recherche dichotomique usuelle*/

    int bi,bs;

    (*Trouv) = false;

    bi = 0;

    bs = nbE-1;

    while ((bi<=bs)&&((*Trouv)==false)){

        (*k) = (bi + bs) / 2;

        if (TabIndex[(*k)].Matricule == Matricule){

            (*Trouv) = true;

        }
        else{

            if (Matricule < TabIndex[(*k)].Matricule){

                bs = (*k) - 1;

            }
            else {

                bi = (*k) + 1;

            }

        }
    }

    if ((*Trouv)==false){

        (*k) = bi;

    }

}

void Insertion_Index_Primaire (TIndex e){ /*Insertion dans une table ordonnee usuelle*/

    bool trouv;

    int k,m;

    Recherche_Index_Primaire(e.Matricule,&trouv,&k);

    if (trouv == false){

        nbE++;

        m = nbE - 1;

        while (m>k){

            TabIndex[m] = TabIndex[m-1];

            m = m-1;

        }

        TabIndex[k] = e;

    }

}

void Suppression_Index_Primaire (long int Matricule){ /*Suppression dans une table ordonnee usuelle en effectuant des decalages*/

    bool trouv;

    int i;

    Recherche_Index_Primaire(Matricule,&trouv,&i);

    if(trouv==true) {

        for (int j = i;j<nbE;j++) {

            TabIndex[j] = TabIndex[j+1];

        }

        nbE = nbE - 1;

    }

}


void Modification_Index_Primaire (long int Matricule, int Nouveau_Bloc, int Nouveau_Depl){ /*Permet de mettre a jour le numero du bloc et le deplacement d'un enseignant au niveau de l'index primaire*/

    bool trouv;

    int i;

    Recherche_Index_Primaire(Matricule,&trouv,&i);

    if (trouv == true){

        TabIndex[i].Num_Bloc = Nouveau_Bloc;

        TabIndex[i].Depl = Nouveau_Depl;

    }

}

/*------------ Procedures de traitement de donnees au niveau de l'index primaire --------------------*/

void Chargement_IndexPrimaire(){ /*Charger la table d'index dans la memoire centrale*/

    nbE = 0; /*Initialiser le nombre d'elements dans la table d'index primaire a 0*/

    int i,j;

    F_Index F;

    TBlocIndex Buffer;

    Ouvrir_FIndex(&F,"Index_Primaire.bin",'A'); /*Ouverture du fichier de sauvegarde en mode ancien*/

    for (i=1;i<=Entete_FIndex(F,1);i++){ /*Parcourir le fichier de sauvegarde de l'index primaire*/

        LireDir_FIndex(F,i,&Buffer); /*Lecture du ieme bloc*/

        for (j=0;j<Buffer.nb;j++){ /*Parcourir le bloc*/

            TabIndex[nbE] = Buffer.Tab[j]; /*Remplissage de la table d'index primaire*/

            nbE++;

        }

    }

    Fermer_FIndex(&F); /*Fermer le fichier de sauvegarde de l'index primaire*/

}

void Sauvegarde_IndexPrimaire(){ /*Sauvegarder la table d'index primaire dans un fichier*/

    TBlocIndex Buffer;

    F_Index F;

    int i,n,j;

    j = 0;

    i = 1;

    Ouvrir_FIndex(&F,"Index_Primaire.bin",'N'); /*Creer le fichier Index_Primaire.bin*/

    for (n = 0;n<nbE;n++){ /*Parcourir la table d'index*/

        if (j<taille_indprimaire){ /*Remplissage du bloc*/

            Buffer.Tab[j] = TabIndex[n];

            j++;

        }
        else { /*Si le bloc est plein, il faut l'ecrire et passer au prochain bloc*/

            Buffer.nb = j;

            EcrireDir_FIndex(F,i,Buffer);

            Buffer.Tab[0] = TabIndex[n];

            j = 1;

            i++;

        }

    }

    /*Ecriture du dernier bloc*/

    Buffer.nb = j;

    EcrireDir_FIndex(F,i,Buffer);

    Aff_Entete_FIndex(&F,1,i);

    Aff_Entete_FIndex(&F,2,nbE);

    Fermer_FIndex(&F); /*Fermer le fichier de sauvegarde de l'index secondaire*/

}


/*---------------------------- Implementation Machine Abstraite Fichier_Index_Secondaire ----------------*/

void Ouvrir_IndSecond(LOBF_Index_Secondaire *F,char Nom_Fich [],char Mode){

    if ((Mode == 'N') || (Mode == 'n')){
        F->Fichier = fopen(Nom_Fich,"wb+");
        if (F->Fichier == NULL){
            printf("-> Erreur lors de la creation du fichier!\n");
        }
        else {

            if (strcmp(Nom_Fich,"Index_Secondaire_Specialite.bin")==0){

                F->TEn_Tete.nb_blocs_physiques = 30; /*Il y a 30 specialites*/

            }
            else {

                if (strcmp(Nom_Fich,"Index_Secondaire_Region.bin")==0){

                    F->TEn_Tete.nb_blocs_physiques = 3; /*Il y a 3 regions*/

                }
                else{

                    F->TEn_Tete.nb_blocs_physiques = 112; /*Il y a 112 etablissements universitaires*/

                }

            }

            fwrite(&F->TEn_Tete,sizeof(En_Tete_Index_Secondaire),1,F->Fichier);
        }
    }
    else {
        if ((Mode == 'A') || (Mode == 'a')){
            F->Fichier = fopen(Nom_Fich,"rb+");
            if (F->Fichier == NULL){
                printf("-> Erreur lors de l'ouverture du fichier!\n");
            }
            else {
                fread(&F->TEn_Tete,sizeof(En_Tete_Index_Secondaire),1,F->Fichier);
            }
        }
        else {
            printf("-> Mode d'ouverture Errone!\n");
        }
    }

}

int Entete_IndSecond (LOBF_Index_Secondaire F){

    return F.TEn_Tete.nb_blocs_physiques;

}

void Aff_Entete_IndSecond (LOBF_Index_Secondaire *F,int v){

    F->TEn_Tete.nb_blocs_physiques = v;

}

void Fermer_IndSecond (LOBF_Index_Secondaire *F ){

    rewind(F->Fichier);
    fwrite(&F->TEn_Tete,sizeof(En_Tete_Index_Secondaire),1,F->Fichier);
    fclose(F->Fichier);

}

void EcrireDir_IndSecond(LOBF_Index_Secondaire F,int i, Bloc_Index_Secondaire Buffer){


    fseek(F.Fichier,sizeof(En_Tete_Index_Secondaire)+(i-1)*sizeof(Bloc_Index_Secondaire),SEEK_SET);
    fwrite(&Buffer,sizeof(Bloc_Index_Secondaire),1,F.Fichier);

}

void LireDir_IndSecond(LOBF_Index_Secondaire F,int i, Bloc_Index_Secondaire *Buffer){

    fseek(F.Fichier,sizeof(En_Tete_Index_Secondaire)+(i-1)*sizeof(Bloc_Index_Secondaire),SEEK_SET);
    fread(Buffer,sizeof(Bloc_Index_Secondaire),1,F.Fichier);

}

int Alloc_Bloc_IndSecond (LOBF_Index_Secondaire *F){

    Aff_Entete_IndSecond(F,Entete_IndSecond(*F)+1);

    return Entete_IndSecond(*F);

}

/*----------------------------------- Procedures Index Secondaire --------------------------*/

void Init_IndexSecond (char Nom_Fich[]){ /*Initialiser le fichier d'index secondaire*/

    Bloc_Index_Secondaire Buffer;

    LOBF_Index_Secondaire F;

    int bs; /*bs etant le nombre de blocs physiques initiales dans le fichier d'index secondaire*/

    if (strcmp(Nom_Fich,"Index_Secondaire_Specialite.bin")==0){

        bs = 30; /*Comme il y a 30 specialites alors initialement il y aura 30 blocs*/

    }
    else {

        if (strcmp(Nom_Fich,"Index_Secondaire_Region.bin")==0){

            bs = 3; /*Comme il y a 3 regions alors initialement il y aura 3 blocs*/

        }
        else{

            bs = 112; /*Comme il y a 112 etablissements alors initialement il y aura 112 blocs*/

        }

    }

    Ouvrir_IndSecond(&F,Nom_Fich,'N'); /*Creer le fichier d'index secondaire*/

    for (int i = 1;i<=bs;i++){ /*Initialiser les "bs" blocs*/

        Buffer.nb = 0; /*Nombre d'enregistrements, initialement est a 0*/

        Buffer.lien = -1; /*le champ lien du bloc, initialement est a NIL*/

        EcrireDir_IndSecond(F,i,Buffer); /*Ecriture du ieme bloc*/
    }

    Fermer_IndSecond(&F); /*Fermer le fichier d'index secondaire*/

}

void Ajout_IndexSecond (long int Matricule, int cle, char Nom_Fich []){ /*Permet d'ajouter un nouveau matricule dans le fichier d'index secondaire*/

    LOBF_Index_Secondaire F;

    /*cle pouvant etre le code de la specialite, de la region ou bien de l'etablissement*/

    Bloc_Index_Secondaire Buffer;

    int i,n;

    Ouvrir_IndSecond(&F,Nom_Fich,'A'); /*Ouverture du fichier d'index secondaire*/

    i=cle;

    LireDir_IndSecond(F,i,&Buffer);

    while(Buffer.lien!=-1) /*Aller au dernier bloc de la liste*/
    {
        i=Buffer.lien;
        LireDir_IndSecond(F,i,&Buffer);
    }

    if (Buffer.nb < taille_indsecond){ /*S'il y a de la place dans le bloc*/

        Buffer.Tab[Buffer.nb] = Matricule; /*Ajouter le nouveau matricule*/

        Buffer.nb = Buffer.nb + 1; /*Mettre a jour le champ nb du bloc*/

        EcrireDir_IndSecond(F,i,Buffer); /*Ecriture du bloc*/

    }
    else
    {

        n = Alloc_Bloc_IndSecond(&F); /*Allouer un nouveau bloc*/

        Buffer.lien = n; /*Mettre a jour le chainage*/

        EcrireDir_IndSecond(F,i,Buffer); /*Ecrire l'ancienne tete de la liste*/

        Buffer.Tab[0] = Matricule; /*Inserer le nouveau matricule dans la premiere position*/

        Buffer.nb = 1; /*Il y a un seul enregistrement car c'est un nouveau bloc alloue*/

        Buffer.lien = -1; /*Mettre son champ lien a NIL*/

        EcrireDir_IndSecond(F,n,Buffer); /*Ecrire le bloc dans sa position adequate*/
    }

    Fermer_IndSecond(&F); /*Fermer le fichier d'index secondaire*/

}

void Chargement_IndexSecond() /*Charger les indexes secondaires en memoire centrale*/
{
    LOBF_Index_Secondaire F;
    Bloc_Index_Secondaire buff;
    int i,j,s;

    Init_LLc(); /*Liberer les anciens maillons et mettre la tete des listes a NIL*/

    /*Chargement de l'index secondaire selon la region*/

    Ouvrir_IndSecond(&F,"Index_Secondaire_Region.bin",'A'); /*Ouverture du fichier*/
    for(i=1;i<4;i++)
    {
        s=i;
        while(s!=-1) /*Parcourir la liste de la ieme region*/
        {
            j=0;
            LireDir_IndSecond(F,s,&buff); /*Chargement du bloc*/

            while(j<buff.nb) /*Parcourir le bloc en entier sequentiellement*/
            {
                Insertion_LLC(buff.Tab[j],&(Tab_Region[i-1])); /*Inserer la matricule dans la liste correspondante*/
                j++;
            }
            s=buff.lien; /*Passer au prochain bloc*/
        }

    }
    Fermer_IndSecond(&F); /*Fermeture du fichier*/

    /*Meme principe pour le chargement de l'index secondaire selon l'etablissement et selon la specialite*/

    /*Chargement de l'index secondaire selon la specialite*/

    Ouvrir_IndSecond(&F,"Index_Secondaire_Specialite.bin",'A');
    for(i=1;i<31;i++)
    {
        s=i;
        while(s!=-1)
        {
            j=0;
            LireDir_IndSecond(F,s,&buff);
            while(j<buff.nb)
            {
                Insertion_LLC(buff.Tab[j],&(Tab_specialite[i-1]));
                j++;
            }
            s=buff.lien;
        }
    }
    Fermer_IndSecond(&F);

    /*Chargement de l'index secondaire selon l'etablissement*/

    Ouvrir_IndSecond(&F,"Index_Secondaire_Etablissement.bin",'A');
    for(i=1;i<113;i++)
    {
        s=i;
        while(s!=-1)
        {
            j=0;
            LireDir_IndSecond(F,s,&buff);
            while(j<buff.nb)
            {
                Insertion_LLC(buff.Tab[j],&(Tab_Ets[i-1]));
                j++;
            }
            s=buff.lien;
        }

    }
    Fermer_IndSecond(&F);

}


void Sauvegarde_IndexSecond() /*Sauvegarder les indexes secondaires dans des fichiers*/
{
    /*Initialiser les trois fichiers de sauvegarde*/

    Init_IndexSecond("Index_Secondaire_Region.bin");
    Init_IndexSecond("Index_Secondaire_Specialite.bin");
    Init_IndexSecond("Index_Secondaire_Etablissement.bin");

    ptr p;

    /*Sauvegarder l'index secondaire selon la region*/

    LOBF_Index_Secondaire F;

    Bloc_Index_Secondaire Buffer;

    Ouvrir_IndSecond(&F,"Index_Secondaire_Region.bin",'A');

    int j,n,s;

    for(int i=0;i<3;i++) /*Parcourir la tableau qui contient les tetes des listes*/
    {
        j=0;
        n = i+1;
        p=Tab_Region[i]; /*Recuperer la tete de la liste de la ieme region*/
        while(p!=NULL) /*Parcourir la liste de la ieme region sequentiellement*/
        {

            if (j<taille_indsecond){

                Buffer.Tab[j] = p->matricule;

                j++;

            }
            else{

                Buffer.nb = j;

                s = Alloc_Bloc_IndSecond(&F);

                Buffer.lien = s;

                EcrireDir_IndSecond(F,n,Buffer);

                n = s;

                Buffer.Tab[0] = p->matricule;

                j = 1;

            }
            p=Suivant(p); /*Passer au prochain matricule*/
        }

        Buffer.lien = -1;

        Buffer.nb = j;

        EcrireDir_IndSecond(F,n,Buffer);
    }

    Fermer_IndSecond(&F);


    Ouvrir_IndSecond(&F,"Index_Secondaire_Specialite.bin",'A');

    /*Sauvegarder l'index secondaire selon la specialite*/

    for(int i=0;i<30;i++)
    {
        j=0;
        n = i+1;
        p=Tab_specialite[i];
        while(p!=NULL) /*Parcourir la liste de la ieme specialite sequentiellement*/
        {

            if (j<taille_indsecond){

                Buffer.Tab[j] = p->matricule;

                j++;

            }
            else{

                Buffer.nb = j;

                s = Alloc_Bloc_IndSecond(&F);

                Buffer.lien = s;

                EcrireDir_IndSecond(F,n,Buffer);

                n = s;

                Buffer.Tab[0] = p->matricule;

                j = 1;

            }
            p=Suivant(p); /*Passer au prochain matricule*/
        }

        Buffer.lien = -1;

        Buffer.nb = j;

        EcrireDir_IndSecond(F,n,Buffer);
    }

    Fermer_IndSecond(&F);

    /*Sauvegarder l'index secondaire selon l'etablissement*/

    Ouvrir_IndSecond(&F,"Index_Secondaire_Etablissement.bin",'A');

    for(int i=0;i<112;i++)
    {
        n = i+1;
        j=0;
        p=Tab_Ets[i];
        while(p!=NULL) /*Parcourir la liste de la ieme specialite sequentiellement*/
        {

            if (j<taille_indsecond){

                Buffer.Tab[j] = p->matricule;

                j++;

            }
            else{

                Buffer.nb = j;

                s = Alloc_Bloc_IndSecond(&F);

                Buffer.lien = s;

                EcrireDir_IndSecond(F,n,Buffer);

                n = s;

                Buffer.Tab[0] = p->matricule;

                j = 1;

            }
            p=Suivant(p); /*Passer au prochain matricule*/
        }

        Buffer.lien = -1;

        Buffer.nb = j;

        EcrireDir_IndSecond(F,n,Buffer);

    }

    Fermer_IndSecond(&F);
}


/*---------------- Procedures principales de traitement de donnees. -----------------*/

void Creation_ENS_FIC (int n){ /*Permet d'initialiser le fichier de donnees avec n enregistrements aleatoirement*/

    /*On a introduit l'epuration dans le module de chargement initial*/

    nbE=0; /*Initialiser le nombre d'enregistrements a 0*/

    Init_LLc(); /*Initialiser les indexes secondaires*/

    LOBF F;

    TIndex e;

    int num_bloc_prec,num_bloc_courant,i,j,Cur_Year,Cur_Month,Cur_Day,pos;

    bool trouv;

    num_bloc_prec = -1; /* le champ lien du premier bloc sera a NIL*/

    TEnseignant Enseignant;

    TBloc Buffer;

    datier(&Cur_Day,&Cur_Month,&Cur_Year); /*Recuperer la date courante pour introduire une date de naissance et une date de recrutement plus au moins "logique"*/

    /*Declaration des tableaux de chaines de caracteres qui nous seront utiles pour la generation des donnees*/

    char Groupe_Sanguin [10][5] = {"O+","A+","B+","O-","A-","AB+","B-","AB-"};

    char Alphabet [30] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    char Sexe [5][20] = {"Masculin","Feminin"};

    int NbCar_Prenom, NbCar_Nom; /*Contiendront respectivement le nombre de caracteres dans le prenom et dans le nom*/

    char Wilaya [60][60] = {"Adrar","Chlef","Laghouat","Oum-El-Bouaghi","Batna","Bejaia","Biskra","Bechar","Blida","Bouira","Tamanrasset","Tebessa","Tlemcen","Tiaret","Tizi-Ouzou","Alger","Djelfa","Jijel","Setif","Saida","Skikda","Sidi-Bel-Abbes","Annaba","Guelma","Constantine","Medea","Mostaganem","Msila","Mascara","Ouargla","Oran","El-Bayadh","Illizi","Bordj-Bou-Arreridj","Boumerdes","El-Tarf","Tindouf","Tissemsilt","El-Oued","Khenchela","Souk-Ahras","Tipaza","Mila","Ain-Defla","Naama","Ain-Temouchent","Ghardaia","Relizane","Timimoun","Bordj-Badji-Mokhtar","Ouled-Djellal","Beni-Abbes","In-Salah","In-Guezzam","Touggourt","Djanet","El-Mghair","El-Meniaa"};

    char Grade [10][50] = {"Professeur(e)","Maitre de conferences Rang A","Maitre de conferences Rang B","Maitre Assistant(e) Rang A","Maitre Assistant(e) Rang B","Assistant(e)"};

    char Dernier_Diplome [10][50] = {"Doctorat d'Etat","Doctorat en sciences","Doctorat D-LMD","PhD","Habilitation Universitaire","Magistere"};

    char Specialite [50][80] = {"Informatique","Biologie","Geologie","Medecine","Pharmacie","Chirurgie Dentaire",

    "Science de la vie et de la nature","Science Islamique","Science Politique","Science Economique",

    "Science Humaine et Sociale","Science de la Matiere","Genie des Procedes","Genie Civil","Genie Mecanique",

    "Genie Electrique","Architecture","Droit","Mathematiques","Philosophie","Literature et Langues",

    "Archeologie","Aeronautique","Education physique et sportive","Hydraulique","Traduction",

    "Science de la communication et des medias","Science Agronomique","Veterinaire","Genie industriel"};

    Ouvrir (&F,"ENSEIGNANT-MESRS.bin",'N'); /*Creer le fichier de donnees*/

    j = 0;

    num_bloc_courant = Alloc_Bloc(&F); /*Allouer le premier bloc pour le remplir par la suite*/


    for (i = 0; i<n ; i++ ){ /*Generer les n enseignants de facon aleatoire*/

        do{

            Enseignant.Matricule = Aleatoire(111,999)*1000+Aleatoire(111,999); /*Generer un matricule aleatoire*/
            Recherche_Index_Primaire(Enseignant.Matricule,&trouv,&pos);

        }
        while (trouv == true); /*Reboucler TQ le matricule genere existe deja dans notre fichier de donnes.*/

        NbCar_Nom = Aleatoire(4,30); NbCar_Prenom = Aleatoire (4,30); /*Genrer la taille du nom et celui du prenom*/

        int k;

        for (k = 0;k<NbCar_Nom;k++){ /*Genrer un nom aleatoire*/

            Enseignant.Nom[k] = Alphabet[Aleatoire(0,25)];
        }

        Enseignant.Nom[k] = '\0'; /*Fin de chaine de caracteres*/

        for (k = 0;k<NbCar_Prenom;k++){ /*Genrer un prenom aleatoire*/

            if (k== 0){

                Enseignant.Prenom[k] = Alphabet[Aleatoire(0,25)]; /*Mettre le premier caractere du prenom en majuscule*/

            }
            else {

                Enseignant.Prenom[k] = tolower(Alphabet[Aleatoire(0,25)]); /*Mettre les suivants en minuscule*/
            }

        }
        Enseignant.Prenom[k] = '\0'; /*Fin de chaine de caracteres*/

        /*Generer une date de naissance aleatoire de l'enseignant*/

        Enseignant.Date_Naissance.Year = Aleatoire(1953,1998);

        Enseignant.Date_Naissance.Month = Aleatoire (1,12);

        Enseignant.Date_Naissance.Day = Aleatoire(1,NumberOfDays(Enseignant.Date_Naissance.Month,Enseignant.Date_Naissance.Year));

        /*Generer une wilaya de naissance aleatoire de l'enseignant*/

        strcpy(Enseignant.Wilaya_Naissance,Wilaya[Aleatoire(0,57)]);

        /*Generer le sexe de l'enseignant*/

        strcpy(Enseignant.Sexe,Sexe[Aleatoire(0,1)]);

        /*Generer le groupe sanguin de l'enseignant*/

        strcpy(Enseignant.Groupe_Sanguin,Groupe_Sanguin[Aleatoire(0,7)]);

        /*Generer la date de recrutement de l'enseignant*/

        Enseignant.Date_Recrutement.Year = Aleatoire(1985,2022);

        if (Enseignant.Date_Recrutement.Year == Cur_Year){

            Enseignant.Date_Recrutement.Month = Aleatoire(1,Cur_Month);

            if (Enseignant.Date_Recrutement.Month == Cur_Month){

                Enseignant.Date_Recrutement.Day = Aleatoire(1,Cur_Day);
            }
            else {
                Enseignant.Date_Recrutement.Day = Aleatoire(1,NumberOfDays(Enseignant.Date_Recrutement.Month,Enseignant.Date_Recrutement.Year));
            }
        }
        else {

            Enseignant.Date_Recrutement.Month = Aleatoire(1,12);

            Enseignant.Date_Recrutement.Day = Aleatoire(1,NumberOfDays(Enseignant.Date_Recrutement.Month,Enseignant.Date_Recrutement.Year));
        }

        /*Generer le grade de l'enseignant*/

        strcpy(Enseignant.Grade,Grade[Aleatoire(0,5)]);

        /*Generer la specialite de l'enseignant*/

        strcpy(Enseignant.Specialite,Specialite[Aleatoire(0,29)]);

        /*Generer le dernier diplome obtenu par l'enseignant*/

        strcpy(Enseignant.Dernier_Diplome,Dernier_Diplome[Aleatoire(0,5)]);

        /*Generer l'etablissement ou exerce l'enseignant*/

        Enseignant.Ets = Tab_ETS[Aleatoire(0,111)];

        /*Inserer l'enseignant dans les indexes secondaires*/

        Insertion_LLC(Enseignant.Matricule,&(Tab_Region[Codage_Region(Enseignant.Ets.Region)-1]));
        Insertion_LLC(Enseignant.Matricule,&(Tab_specialite[Codage_Specialite(Enseignant.Specialite)-1]));
        Insertion_LLC(Enseignant.Matricule,&(Tab_Ets[Codage_Etablissement(Enseignant.Ets.Nom)-1]));


        if (j < taille){ /*S'il reste de la place dans le bloc courant*/

            Buffer.Tab[j] = Enseignant; /*Insertion du nouveau enseignant dans le bloc*/

            j++;

            /*Insertion dans l'index primaire*/

            e.Matricule = Enseignant.Matricule;

            e.Depl = j-1;

            e.Num_Bloc = num_bloc_courant;

            e.efface = false;

            Insertion_Index_Primaire(e);
        }

        else { /*Bloc plein, il faut l'ecrire*/

            Buffer.lien = num_bloc_prec; /*Mettre a jour le chainage*/

            Buffer.nb = j; /*Mettre a jour le nombre d'enregistrements dans le bloc*/

            EcrireDir(F,num_bloc_courant,Buffer); /*Ecriture du bloc*/

            nb_ecrt++; /*Incrementation du nombre de EcrireDir*/

            num_bloc_prec = num_bloc_courant; /*Pour garder trace du precedent pour mettre a jour le chainage dans la prochaine iteration*/

            /*Remplissage d'un nouveau bloc*/

            Buffer.Tab[0] = Enseignant;

            j = 1;

            e.Matricule = Enseignant.Matricule;

            e.Depl = j-1;

            e.efface = false;

            num_bloc_courant = Alloc_Bloc(&F); /*Allouer un nouveau bloc pour la prochaine insertion*/

            e.Num_Bloc = num_bloc_courant;

            /*Insertion dans l'index primaire*/

            Insertion_Index_Primaire(e);

        }


    }

    if (j>0){ /*Ecriture du dernier buffer*/

            Buffer.lien = num_bloc_prec;

            Buffer.nb = j;

            EcrireDir(F,num_bloc_courant,Buffer);

            nb_ecrt++;
    }

    Aff_Entete(&F,1,num_bloc_courant); /*Mettre a jour la tete de la liste*/

    Fermer(&F); /*Fermeture du fichier apres sa creation*/

}


void Ajout_ENS(TEnseignant ENS){ /*Permet d'ajouter un nouveau enseignant dans le fichier de donnees*/

    /*L'insertion se fait dans la tete de la liste*/

    LOBF Fic_ENS;

    TBloc Buffer;

    TIndex e;

    int n,i;

    bool trouv;

    Recherche_Index_Primaire(ENS.Matricule,&trouv,&i); /*Verifier si l'enseignant existe deja dans le fichier de donnees ou non*/

    if (trouv == false){ /*S'il n'existe pas*/

            Ouvrir(&Fic_ENS,"ENSEIGNANT-MESRS.bin",'A'); /*Ouvrir le fichier de donnees*/

            Modification_Date(&Fic_ENS); /*Mettre a jour la date de modification du fichier*/

            if (Entete(Fic_ENS,1)==-1){ /*Si le fichier est vide, alors allouer un nouveau bloc et le mettre comme en-tete*/

                Aff_Entete(&Fic_ENS,1,Alloc_Bloc(&Fic_ENS));

            }

            LireDir(Fic_ENS,Entete(Fic_ENS,1),&Buffer); /*Lecture de la tete de la liste*/

            nb_lect++; /*Incrementer le nombre de LireDir*/

            if (Buffer.nb == taille){ /*Si le bloc est plein*/

                n = Alloc_Bloc(&Fic_ENS); /*Allouer un nouveau bloc dans le fichier*/

                Buffer.lien = Entete(Fic_ENS,1); /*Chainer le nouveau bloc avec la tete de la liste*/

                /*Insertion de l'enseignant*/

                Buffer.Tab[0] = ENS;

                Buffer.nb = 1;

                Aff_Entete(&Fic_ENS,1,n); /*Mettre a jour la tete de la liste*/

            }
            else { /*S'il reste de la place dans le bloc */

                Buffer.nb = Buffer.nb + 1; /*Mettre a jour le nombre d'enregistrements dans le bloc*/

                Buffer.Tab[Buffer.nb - 1] = ENS; /*Ajouter l'enseignant a la fin*/

            }

            EcrireDir(Fic_ENS,Entete(Fic_ENS,1),Buffer); /*Ecrire le bloc qui contient le nouveau enseignant qui est dans notre cas toujours la tete de la liste*/

            nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

            e.Matricule = ENS.Matricule;

            e.Num_Bloc = Entete(Fic_ENS,1);

            e.efface = false;

            e.Depl = Buffer.nb - 1;

            Insertion_Index_Primaire(e); /*Insertion dans l'index primaire*/

            /*Insertion dans les indexes secondaires*/

            Insertion_LLC(ENS.Matricule,&(Tab_Region[Codage_Region(ENS.Ets.Region)-1]));
            Insertion_LLC(ENS.Matricule,&(Tab_specialite[Codage_Specialite(ENS.Specialite)-1]));
            Insertion_LLC(ENS.Matricule,&(Tab_Ets[Codage_Etablissement(ENS.Ets.Nom)-1]));

            Fermer(&Fic_ENS); /*Fermer le fichier de donnees apres traitement*/

    }

}


void Modification_ENS(long int Matricule, int code) /*Procedure permettant de modifier l'etablissement d'exercice d'un enseignant donne*/
{
    bool trouv;
    int i;
    LOBF F;
    TBloc Buffer1;

    Recherche_Index_Primaire(Matricule,&trouv,&i); /*Recherche de l'enseignant*/

    if(trouv==true) /*Si on trouve l'enseignant*/
    {
        Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A'); /*Ouvrir le fichier de donnees*/

        LireDir(F,TabIndex[i].Num_Bloc,&Buffer1); /*Charger le bloc ou se trouve l'enseignant*/

        nb_lect++; /*Incrementer le nombre de LireDir*/

        if(strcmp(Buffer1.Tab[TabIndex[i].Depl].Ets.Region,Tab_ETS[code-1].Region)!=0) /*Si la region ou se trouve le nouveau etablissement est differente de celle de l'ancien etablissment*/
        {
            /*Supprimer l'enseignant de la liste de l'ancienne region*/
            Suppression_LLC(Buffer1.Tab[TabIndex[i].Depl].Matricule,&(Tab_Region[Codage_Region(Buffer1.Tab[TabIndex[i].Depl].Ets.Region)-1]));
            /*Ajouter l'enseignant dans la liste de la nouvelle region*/
            Insertion_LLC(Buffer1.Tab[TabIndex[i].Depl].Matricule,&(Tab_Region[Codage_Region(Tab_ETS[code-1].Region)-1]));
        }

        /*Supprimer l'enseignant de la liste de l'ancien etablissement*/
        Suppression_LLC(Buffer1.Tab[TabIndex[i].Depl].Matricule,&(Tab_Ets[Codage_Etablissement(Buffer1.Tab[TabIndex[i].Depl].Ets.Nom)-1]));
        /*Inserer l'enseignant dans la liste du nouveau etablissement*/
        Insertion_LLC(Buffer1.Tab[TabIndex[i].Depl].Matricule,&(Tab_Ets[code-1]));

        Buffer1.Tab[TabIndex[i].Depl].Ets=Tab_ETS[code-1]; /*Mettre a jour l'etablissement ou exerce l'enseignant*/

        EcrireDir(F,TabIndex[i].Num_Bloc,Buffer1); /*Reecriture du bloc apres modification*/

        nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

        Fermer(&F); /*Fermer le fichier apres traitement*/
    }
}

void Suppression_ENS (long int Matricule) /*Cette procedure permet de supprimer un enseignant donne*/
{

    LOBF F;

    TBloc Buffer1,Buffer2;

    bool trouv;

    int i;

    Recherche_Index_Primaire(Matricule,&trouv,&i); /*Recherche de l'enseignant dans l'index primaire*/

    if (trouv == true){ /*Si l'enseignant existe dans notre fichier de donnees*/

            Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A'); /*Ouverture du fichier*/

            Modification_Date(&F); /*Mettre a jour la date de modification du fichier*/

            LireDir(F,Entete(F,1),&Buffer1); /*Charger la tete de la liste*/

            nb_lect++; /*Incremnter le nombre de LireDir*/

            if (TabIndex[i].Num_Bloc==Entete(F,1)){ /*Si l'enseignant se trouve dans la tete de la liste*/

                    /*Supprimer l'enseignant dans les indexes secondaires*/

                    Suppression_LLC(Matricule,&(Tab_Region[Codage_Region(Buffer1.Tab[TabIndex[i].Depl].Ets.Region)-1]));
                    Suppression_LLC(Matricule,&(Tab_specialite[Codage_Specialite(Buffer1.Tab[TabIndex[i].Depl].Specialite)-1]));
                    Suppression_LLC(Matricule,&(Tab_Ets[Codage_Etablissement(Buffer1.Tab[TabIndex[i].Depl].Ets.Nom)-1]));

                    Buffer1.Tab[TabIndex[i].Depl] = Buffer1.Tab[Buffer1.nb-1]; /*Remplacer l'enseignant par le dernier enregistrement du bloc*/

                    Buffer1.nb = Buffer1.nb - 1; /*Mettre a jour le nombre d'enregistrements dans le bloc*/

                    if (Buffer1.nb == 0){ /*Si le bloc de la tete devient vide*/

                            Aff_Entete(&F,1,Buffer1.lien); /*Mettre a jour la tete de la liste*/

                            /*Inserer le bloc supprime dans la liste des blocs vides*/

                            Buffer1.lien = Entete(F,2);

                            EcrireDir(F,TabIndex[i].Num_Bloc,Buffer1);

                            nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

                            Aff_Entete(&F,2,TabIndex[i].Num_Bloc); /*Mettre a jour la tete de la liste des blocs vides*/

                    }

                    else { /*Reecriture du bloc s'il ne devient pas vide*/

                        EcrireDir(F,Entete(F,1),Buffer1);

                        nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

                    }

            }

            else {

                    LireDir(F,TabIndex[i].Num_Bloc,&Buffer2); /*Lire le bloc ou se trouve l'enseignant*/

                    nb_lect++; /*Incremnter le nombre de LireDir*/

                    /*Supprimer l'enseignant dans les indexes secondaires*/

                    Suppression_LLC(Matricule,&(Tab_Region[Codage_Region(Buffer2.Tab[TabIndex[i].Depl].Ets.Region)-1]));
                    Suppression_LLC(Matricule,&(Tab_specialite[Codage_Specialite(Buffer2.Tab[TabIndex[i].Depl].Specialite)-1]));
                    Suppression_LLC(Matricule,&(Tab_Ets[Codage_Etablissement(Buffer2.Tab[TabIndex[i].Depl].Ets.Nom)-1]));

                    Buffer2.Tab[TabIndex[i].Depl] = Buffer1.Tab[Buffer1.nb -1]; /*Ecraser la donnee par le dernier enregistrement de la tete de la liste*/

                    Buffer1.nb = Buffer1.nb - 1; /*Mettre a jour le nombre d'enregistrements dans le bloc de la tete de la liste*/

                    if ((Buffer1.nb)==0){ /*Si le bloc devient vide, il faut le liberer cad l'inserer dans la liste des blocs vides*/

                            int sauv=Entete(F,1); /*Sauvegarder l'ancienne tete de la liste*/

                            Aff_Entete(&F,1,Buffer1.lien); /*Mettre a jour la tete de la liste*/

                            /*Inserer le bloc supprime dans la liste des blocs vides*/

                            Buffer1.lien = Entete(F,2);

                            EcrireDir(F,sauv,Buffer1);

                            nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

                            Aff_Entete(&F,2,sauv); /*Mettre a jour la tete de la liste des blocs vides*/



                    }
                    else { /*Reecriture du bloc de la tete de la liste s'il contient toujours des donnees*/

                        EcrireDir(F,Entete(F,1),Buffer1);

                        nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

                    }

                    EcrireDir(F,TabIndex[i].Num_Bloc,Buffer2); /*Reecriture du bloc ou se trouvait prealablement l'enseignant*/

                    nb_ecrt++; /*Incrementer le nombre de EcrireDir*/

            }

            Modification_Index_Primaire(Buffer1.Tab[Buffer1.nb].Matricule,TabIndex[i].Num_Bloc,TabIndex[i].Depl); /*Mettre a jour le numero du bloc et le deplacement de l'enregistrement qu'on a utilise pour ecraser l'enseignant desire*/

            Suppression_Index_Primaire(Matricule); /*Supprimer l'enseignant de l'index primaire*/

            Fermer(&F); /*Fermeture du fichier apres traitement*/

    }

}

void Suppression_ENS_Specialites(int Specialite){ /*Supprimer tous les enseignants relatifs a une specialite donnee*/

    ptr p;

    p=Tab_specialite[Specialite-1]; /*Recuperer la tete de la liste*/

    while(p!=NULL) /*Parcourir la liste*/
    {
        Suppression_ENS(p->matricule); /*Supprimer l'enseignant*/
        p=Tab_specialite[Specialite-1]; /*Passer au prochain enseignant*/
    }

}


void Affich_ENS_Ets(int inf,int sup,int ets){ /*Requete a intervalle*/

    ptr p;

    ptr_bi tete=NULL,queue1=NULL,queue2=NULL,q,s;

    LOBF F1;

    int i,j,cpt=0,day,month,year,max,sauv=-1;

    char c;

    TBloc buf;

    bool trouv,stop=false,pair=false,exist=false;

    p=Tab_Ets[ets-1]; /*Recuperer la tete de la liste*/

    Ouvrir(&F1,"ENSEIGNANT-MESRS.bin",'A');

    datier(&day,&month,&year); /*Recuperer l'annee courante*/

        while(p!=NULL) /*Parcourir la liste*/
        {
            Recherche_Index_Primaire(p->matricule,&trouv,&i); /*Recherche de l'enseignant pour recuperer le numero du bloc ainsi que son deplacement*/
            if(sauv!=TabIndex[i].Num_Bloc) /*Si on a face a un nouveau bloc alors il faut le charger*/
            {
                LireDir(F1,TabIndex[i].Num_Bloc,&buf); /*Lecture du bloc*/
                nb_lect++; /*Incrementer le nombre de LireDir*/
            }
            j=TabIndex[i].Depl; /*Sauvegarder la position ou se trouve l'enseignant*/
            if((year-buf.Tab[j].Date_Recrutement.Year<=sup) && (year-buf.Tab[j].Date_Recrutement.Year>=inf)) /*Tester si l'anciennete est comprise entre bi et bs*/
            {
                cpt++; /*Incrementer le nombre d'enseignants trouves*/
                exist=true; /*Il existe au moins un enseignant verifiant les criteres*/
                Insertion_LLC_bi(buf.Tab[j],&tete); /*Inserer les enseignants trouves dans une liste bi-directionnelle*/
                if(cpt==1)
                {
                    queue1=tete;
                }
                else
                {
                    if(cpt==2)
                    {
                        queue2=tete;
                    }
                }

            }
            sauv=TabIndex[i].Num_Bloc; /*Sauvegarder le numero du bloc pour eviter la lecture du meme bloc plusieurs fois*/
            p=Suivant(p); /*Passer au prochain bloc*/
        }

    /*Afficher les differentes informations des enseignants*/

    if(exist==true) /*Il existe au moins un enseignant verifiant les criteres*/
    {
        if(cpt%2==0)
        {
            max=cpt/2;
            pair=true;
        }
        else
        {
            max=cpt/2+1;
        }
        q=tete;
        cpt=1;
            while(stop==false)
            {
                system("cls");

                    textcolor(WHITE);printf("\n\n\n\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",q->ENS.Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",q->ENS.Matricule);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",q->ENS.Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",q->ENS.Dernier_Diplome);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",q->ENS.Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",q->ENS.Specialite);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",q->ENS.Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",q->ENS.Grade);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",q->ENS.Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",q->ENS.Date_Recrutement.Day,q->ENS.Date_Recrutement.Month,q->ENS.Date_Recrutement.Year);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",q->ENS.Date_Naissance.Day,q->ENS.Date_Naissance.Month,q->ENS.Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",q->ENS.Ets.Nom);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");

                s=Suivant_bi(q);
                if(s!=NULL)
                {
                    textcolor(WHITE);printf("\n\n\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",s->ENS.Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",s->ENS.Matricule);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",s->ENS.Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",s->ENS.Dernier_Diplome);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",s->ENS.Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",s->ENS.Specialite);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",s->ENS.Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",s->ENS.Grade);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",s->ENS.Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",s->ENS.Date_Recrutement.Day,s->ENS.Date_Recrutement.Month,s->ENS.Date_Recrutement.Year);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",s->ENS.Date_Naissance.Day,s->ENS.Date_Naissance.Month,s->ENS.Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",s->ENS.Ets.Nom);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                }
                else
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                }
                textcolor(YELLOW);
                printf("\t\t\t\t\t    Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour basculer entre les pages.\n\n");
                textcolor(WHITE);
                printf("\t\t\t\t\t                  Appuyez sur 'ENTRER' pour revenir au menu principal.\n");
                c=getch();
                if(c==-32)
                {
                    c=getch();
                    if(c==77)
                    {
                        q=Suivant_bi(q);
                        q=Suivant_bi(q);
                        cpt++;
                        if(q==NULL)
                        {
                            q=tete;
                            cpt=1;
                        }
                    }
                    else
                    {
                        if(c==75)
                        {
                            q=Precedant_bi(q);
                            q=Precedant_bi(q);
                            cpt--;
                            if(q==NULL)
                            {
                                if(pair==true)
                                {
                                    q=queue2;
                                }
                                else
                                {
                                    q=queue1;
                                }
                                cpt=max;
                            }

                        }
                    }
                }
                else
                {
                    if(c==13)
                    {
                        stop=true;
                    }
                }

        }
            q=tete;
            while(q!=NULL)
            {
                s=Suivant_bi(q);
                free(q);
                q=s;
            }
            tete=NULL;
    }
    else /*Il n'existe aucun enseignant verifiant les criteres de la requete*/
    {
        system("cls");
        textcolor(LIGHTRED);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t\t                                                ______                _                         _    \n");
        printf("\t\t\t\t\t                /%c                             |  ____|              (_)                       | |   \n",92);
        printf("\t\t\t\t\t               /  %c  _   _  ___ _   _ _ __     | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_  \n",92);
        printf("\t\t\t\t\t              / /%c %c| | | |/ __| | | | '_ %c    |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __| \n",92,92,92,92,92,92,92);
        printf("\t\t\t\t\t             / ____ %c |_| | (__| |_| | | | |   | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_  \n",92,92,92);
        printf("\t\t\t\t\t            /_/    %c_%c__,_|%c___|%c__,_|_| |_|   |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__| \n",92,92,92,92,92,92,92,92);
        printf("\t\t\t\t\t                                                                         __/ |                       \n");
        printf("\t\t\t\t\t                                                                        |___/                        \n");
        printf("\t\t\t\t\t                                       _______                     __   \n");
        printf("\t\t\t\t\t                                      |__   __|                   /_/   \n");
        printf("\t\t\t\t\t                                         | |_ __ ___  _   ___   _____   \n");
        printf("\t\t\t\t\t                                         | | '__/ _ %c| | | %c %c / / _ %c  \n",92,92,92,92);
        printf("\t\t\t\t\t                                         | | | | (_) | |_| |%c V /  __/     \n",92);
        printf("\t\t\t\t\t                                         |_|_|  %c___/ %c__,_| %c_/ %c___|  \n",92,92,92,92);
        textcolor(WHITE);
        printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     Appuyez sur une touche pour revenir au menu principal.\n\n");
        fflush(stdin);
        getch();
    }


    Fermer(&F1);


}

void Affich_ENS_Region(int region){ /*Afficher les enseignants exercant dans une region donnee*/

    ptr p;

    ptr_bi tete=NULL,q,queue1=NULL,queue2=NULL,s;

    LOBF F1;

    int i,j,cpt=0,max,sauv=-1;

    TBloc buf;

    char c;

    bool trouv,stop=false,pair=false;

    p=Tab_Region[region-1]; /*Recuperer la tete de la liste*/

    Ouvrir(&F1,"ENSEIGNANT-MESRS.bin",'A'); /*Ouvrir le fichier de donnees*/
    system("cls");
    if(p==NULL) /*Si la tete de la liste est vide cela signifie qu'il n'existe aucun enseignant exercant dans cette region*/
    {
        system("cls");
        textcolor(LIGHTRED);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t\t                                                ______                _                         _    \n");
        printf("\t\t\t\t\t                /%c                             |  ____|              (_)                       | |   \n",92);
        printf("\t\t\t\t\t               /  %c  _   _  ___ _   _ _ __     | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_  \n",92);
        printf("\t\t\t\t\t              / /%c %c| | | |/ __| | | | '_ %c    |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __| \n",92,92,92,92,92,92,92);
        printf("\t\t\t\t\t             / ____ %c |_| | (__| |_| | | | |   | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_  \n",92,92,92);
        printf("\t\t\t\t\t            /_/    %c_%c__,_|%c___|%c__,_|_| |_|   |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__| \n",92,92,92,92,92,92,92,92);
        printf("\t\t\t\t\t                                                                         __/ |                       \n");
        printf("\t\t\t\t\t                                                                        |___/                        \n");
        printf("\t\t\t\t\t                                       _______                     __   \n");
        printf("\t\t\t\t\t                                      |__   __|                   /_/   \n");
        printf("\t\t\t\t\t                                         | |_ __ ___  _   ___   _____   \n");
        printf("\t\t\t\t\t                                         | | '__/ _ %c| | | %c %c / / _ %c  \n",92,92,92,92);
        printf("\t\t\t\t\t                                         | | | | (_) | |_| |%c V /  __/     \n",92);
        printf("\t\t\t\t\t                                         |_|_|  %c___/ %c__,_| %c_/ %c___|  \n",92,92,92,92);
        textcolor(WHITE);
        printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     Appuyez sur une touche pour revenir au menu principal.\n\n");
        fflush(stdin);
        getch();
    }
    else /*Il existe au moins un enseignant exercant dans cette region*/
    {
        while(p!=NULL) /*Parcourir la liste*/
        {
            cpt++; /*Incrementer le nombre d'enseignants trouves*/
            Recherche_Index_Primaire(p->matricule,&trouv,&i); /*Recherche de l'enseignant pour recuperer le numero du bloc ainsi que son deplacement*/
            if(sauv!=TabIndex[i].Num_Bloc) /*On est face a un nouveau bloc*/
            {
                LireDir(F1,TabIndex[i].Num_Bloc,&buf); /*Charger le bloc dans buf*/
                nb_lect++; /*Incrementer le nombre de LireDir*/
            }
            j=TabIndex[i].Depl; /*Sauvegarder le deplacement ou se trouve l'enseignant dans le bloc*/
            Insertion_LLC_bi(buf.Tab[j],&tete); /*Inserer l'enseignant dans la liste bidirectionnelle*/
            if(cpt==1)
            {
                queue1=tete;
            }
            else
            {
                if(cpt==2)
                {
                    queue2=tete;
                }
            }
            sauv=TabIndex[i].Num_Bloc; /*Sauvegarder le numero du bloc pour ne pas relire le meme bloc a chaque iteration*/
            p=Suivant(p); /*Aller au prochain enseignant*/
        }

        if(cpt%2==0)
        {
            max=cpt/2;
            pair=true;
        }
        else
        {
            max=cpt/2+1;
        }
        q=tete;
        cpt=1;
            while(stop==false)
            {
                system("cls");

                    textcolor(WHITE);printf("\n\n\n\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",q->ENS.Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",q->ENS.Matricule);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",q->ENS.Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",q->ENS.Dernier_Diplome);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",q->ENS.Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",q->ENS.Specialite);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",q->ENS.Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",q->ENS.Grade);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",q->ENS.Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",q->ENS.Date_Recrutement.Day,q->ENS.Date_Recrutement.Month,q->ENS.Date_Recrutement.Year);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",q->ENS.Date_Naissance.Day,q->ENS.Date_Naissance.Month,q->ENS.Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",q->ENS.Ets.Nom);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");

                s=Suivant_bi(q);
                if(s!=NULL)
                {
                    textcolor(WHITE);printf("\n\n\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",s->ENS.Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",s->ENS.Matricule);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",s->ENS.Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",s->ENS.Dernier_Diplome);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",s->ENS.Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",s->ENS.Specialite);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",s->ENS.Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",s->ENS.Grade);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",s->ENS.Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",s->ENS.Date_Recrutement.Day,s->ENS.Date_Recrutement.Month,s->ENS.Date_Recrutement.Year);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",s->ENS.Date_Naissance.Day,s->ENS.Date_Naissance.Month,s->ENS.Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",s->ENS.Ets.Nom);
                    textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                }
                else
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                }
                textcolor(YELLOW);
                printf("\t\t\t\t\t    Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour basculer entre les pages.\n\n");
                textcolor(WHITE);
                printf("\t\t\t\t\t                  Appuyez sur 'ENTRER' pour revenir au des regions\n");
                c=getch();
                if(c==-32)
                {
                    c=getch();
                    if(c==77)
                    {
                        q=Suivant_bi(q);
                        q=Suivant_bi(q);
                        cpt++;
                        if(q==NULL)
                        {
                            q=tete;
                            cpt=1;
                        }
                    }
                    else
                    {
                        if(c==75)
                        {
                            q=Precedant_bi(q);
                            q=Precedant_bi(q);
                            cpt--;
                            if(q==NULL)
                            {
                                if(pair==true)
                                {
                                    q=queue2;
                                }
                                else
                                {
                                    q=queue1;
                                }
                                cpt=max;
                            }

                        }
                    }
                }
                else
                {
                    if(c==13)
                    {
                        stop=true;
                    }
                }

        }
        q=tete;
        while(q!=NULL)
        {
            s=Suivant_bi(q);
            free(q);
            q=s;
        }
        tete=NULL;

    }

    Fermer(&F1); /*Fermer le fichier apres traitement*/

}


void codage() /*Codage du fichier de donnees*/
{
    /*C'est la meme methode vu en TD donc ce n'est pas la peine de rentrer en detail dans l'implementation de cette procedure*/
    LOBF f,fic;
    TBloc buff,buff1;
    Ouvrir(&f,"ENSEIGNANT-MESRS.bin",'A'); /*Ouvrir le fichier de donnees*/
    Ouvrir(&fic,"FICHIER-CODE.bin",'N'); /*Creer le fichier code*/

    int i=Entete(f,1),s,avc=0,j; /*Recuperer la tete de la liste*/

    Aff_Entete(&fic,1,i); /*Mettre a jour la tete de la liste dans le fichier code*/

    while(i!=-1) /*Parcourir le fichier de donnees*/
    {
        LireDir(f,i,&buff); /*Lecture du ieme bloc*/
        nb_lect++; /*Incrementer le nombre de LireDir*/

        for(j=0;j<buff.nb;j++) /*Parcourir le bloc sequentiellement*/
        {
            avc=0;
            /*Codage du nom*/
            for(s=0;s<strlen(buff.Tab[j].Nom);s++)
            {
                buff1.Tab[j].Nom[s]=buff.Tab[j].Nom[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Nom[strlen(buff.Tab[j].Nom)]='\0';

            /*Codage du prenom*/
            for(s=0;s<strlen(buff.Tab[j].Prenom);s++)
            {
                buff1.Tab[j].Prenom[s]=buff.Tab[j].Prenom[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Prenom[strlen(buff.Tab[j].Prenom)]='\0';

            /*Codage du dernier diplome*/
            for(s=0;s<strlen(buff.Tab[j].Dernier_Diplome);s++)
            {
                buff1.Tab[j].Dernier_Diplome[s]=buff.Tab[j].Dernier_Diplome[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Dernier_Diplome[strlen(buff.Tab[j].Dernier_Diplome)]='\0';

            /*Codage du grade*/
            for(s=0;s<strlen(buff.Tab[j].Grade);s++)
            {
                buff1.Tab[j].Grade[s]=buff.Tab[j].Grade[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Grade[strlen(buff.Tab[j].Grade)]='\0';

            /*Codage du groupe sanguin*/
            for(s=0;s<strlen(buff.Tab[j].Groupe_Sanguin);s++)
            {
                buff1.Tab[j].Groupe_Sanguin[s]=buff.Tab[j].Groupe_Sanguin[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Groupe_Sanguin[strlen(buff.Tab[j].Groupe_Sanguin)]='\0';

            /*Codage de l'etablissement universitaire*/
            for(s=0;s<strlen(buff.Tab[j].Ets.Nom);s++)
            {
                buff1.Tab[j].Ets.Nom[s]=buff.Tab[j].Ets.Nom[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Ets.Nom[strlen(buff.Tab[j].Ets.Nom)]='\0';

            /*Codage du sexe*/
            for(s=0;s<strlen(buff.Tab[j].Sexe);s++)
            {
                buff1.Tab[j].Sexe[s]=buff.Tab[j].Sexe[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Sexe[strlen(buff.Tab[j].Sexe)]='\0';

            /*Codage de la specialite*/
            for(s=0;s<strlen(buff.Tab[j].Specialite);s++)
            {
                buff1.Tab[j].Specialite[s]=buff.Tab[j].Specialite[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Specialite[strlen(buff.Tab[j].Specialite)]='\0';

            /*Codage de la wilaya de naissance*/
            for(s=0;s<strlen(buff.Tab[j].Wilaya_Naissance);s++)
            {
                buff1.Tab[j].Wilaya_Naissance[s]=buff.Tab[j].Wilaya_Naissance[s]+cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Wilaya_Naissance[strlen(buff.Tab[j].Wilaya_Naissance)]='\0';

            /*Codage de la date de naissance*/
            buff1.Tab[j].Date_Naissance.Day=buff.Tab[j].Date_Naissance.Day+cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Naissance.Month=buff.Tab[j].Date_Naissance.Month+cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Naissance.Year=buff.Tab[j].Date_Naissance.Year+cle[avc % strlen(cle)];
            avc++;
            /*Codage de la date de recrutement*/
            buff1.Tab[j].Date_Recrutement.Day=buff.Tab[j].Date_Recrutement.Day+cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Recrutement.Month=buff.Tab[j].Date_Recrutement.Month+cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Recrutement.Year=buff.Tab[j].Date_Recrutement.Year+cle[avc % strlen(cle)];
            avc++;
            /*Codage du matricule*/
            buff1.Tab[j].Matricule=buff.Tab[j].Matricule+cle[avc % strlen(cle)]*111111;
            avc++;
            strcpy(buff1.Tab[j].Ets.Region,buff.Tab[j].Ets.Region);
        }
        /*Recopier les caracteristique du bloc du fichier de donnees dans le bloc du fichier code*/
        buff1.lien=buff.lien;
        buff1.nb=buff.nb;
        EcrireDir(fic,i,buff1); /*Ecrire le bloc dans le fichier code*/
        nb_ecrt++; /*Incrementer le nombre de EcrireDir*/
        i=buff.lien; /*Passer au prochain bloc*/
    }

    /*Fermeture des fichiers apres traitement*/
    Fermer(&f);
    Fermer(&fic);
    /*Sauvegarder la cle pour etre capable de dechiffrer le fichier code*/
    FILE *fc=fopen("cle.txt","w");
    fputs(cle,fc);
    fclose(fc);
}


void decodage() /*Decoder le fichier code*/
{
    /*Il suffira de faire le chemin inverse de celui du codage*/
    LOBF f,fic;
    TBloc buff,buff1;
    Ouvrir(&f,"FICHIER-CODE.bin",'A'); /*Ouvrir le fichier code*/
    Ouvrir(&fic,"FICHIER-DECODE.bin",'N'); /*Creer le fichier decode*/

    int i=Entete(f,1),s,avc=0,j; /*Recuperer la tete de la liste*/

    Aff_Entete(&fic,1,i); /*Mettre a jour la tete de la liste dans le fichier decode*/

    while(i!=-1) /*Parcourir le fichier code*/
    {
        LireDir(f,i,&buff); /*Lecture du ieme bloc*/

        nb_lect++; /*Incrementer le nombre de LireDir*/

        for(j=0;j<buff.nb;j++) /*Parcourir le bloc sequentiellement*/
        {
            avc=0;
            /*Decodage du nom*/
            for(s=0;s<strlen(buff.Tab[j].Nom);s++)
            {
                buff1.Tab[j].Nom[s]=buff.Tab[j].Nom[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Nom[strlen(buff.Tab[j].Nom)]='\0';

            /*Decodage du prenom*/
            for(s=0;s<strlen(buff.Tab[j].Prenom);s++)
            {
                buff1.Tab[j].Prenom[s]=buff.Tab[j].Prenom[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Prenom[strlen(buff.Tab[j].Prenom)]='\0';

            /*Decodage du dernier diplome*/
            for(s=0;s<strlen(buff.Tab[j].Dernier_Diplome);s++)
            {
                buff1.Tab[j].Dernier_Diplome[s]=buff.Tab[j].Dernier_Diplome[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Dernier_Diplome[strlen(buff.Tab[j].Dernier_Diplome)]='\0';

            /*Decodage du grade*/
            for(s=0;s<strlen(buff.Tab[j].Grade);s++)
            {
                buff1.Tab[j].Grade[s]=buff.Tab[j].Grade[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Grade[strlen(buff.Tab[j].Grade)]='\0';

            /*Decodage du groupe sanguin*/
            for(s=0;s<strlen(buff.Tab[j].Groupe_Sanguin);s++)
            {
                buff1.Tab[j].Groupe_Sanguin[s]=buff.Tab[j].Groupe_Sanguin[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Groupe_Sanguin[strlen(buff.Tab[j].Groupe_Sanguin)]='\0';

            /*Decodage du nom de l'etablissement*/
            for(s=0;s<strlen(buff.Tab[j].Ets.Nom);s++)
            {
                buff1.Tab[j].Ets.Nom[s]=buff.Tab[j].Ets.Nom[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Ets.Nom[strlen(buff.Tab[j].Ets.Nom)]='\0';

            /*Decodage du sexe*/
            for(s=0;s<strlen(buff.Tab[j].Sexe);s++)
            {
                buff1.Tab[j].Sexe[s]=buff.Tab[j].Sexe[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Sexe[strlen(buff.Tab[j].Sexe)]='\0';

            /*Decodage de la specialite*/
            for(s=0;s<strlen(buff.Tab[j].Specialite);s++)
            {
                buff1.Tab[j].Specialite[s]=buff.Tab[j].Specialite[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Specialite[strlen(buff.Tab[j].Specialite)]='\0';
            /*Decodage de la wilaya de naissance*/
            for(s=0;s<strlen(buff.Tab[j].Wilaya_Naissance);s++)
            {
                buff1.Tab[j].Wilaya_Naissance[s]=buff.Tab[j].Wilaya_Naissance[s]-cle[avc % strlen(cle)];
                avc++;
            }
            buff1.Tab[j].Wilaya_Naissance[strlen(buff.Tab[j].Wilaya_Naissance)]='\0';

            /*Decodage de la date de naissance*/
            buff1.Tab[j].Date_Naissance.Day=buff.Tab[j].Date_Naissance.Day-cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Naissance.Month=buff.Tab[j].Date_Naissance.Month-cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Naissance.Year=buff.Tab[j].Date_Naissance.Year-cle[avc % strlen(cle)];
            avc++;
            /*Decodage de la date de recrutement*/
            buff1.Tab[j].Date_Recrutement.Day=buff.Tab[j].Date_Recrutement.Day-cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Recrutement.Month=buff.Tab[j].Date_Recrutement.Month-cle[avc % strlen(cle)];
            avc++;
            buff1.Tab[j].Date_Recrutement.Year=buff.Tab[j].Date_Recrutement.Year-cle[avc % strlen(cle)];
            avc++;
            /*Decodage du matricule*/
            buff1.Tab[j].Matricule=buff.Tab[j].Matricule-cle[avc % strlen(cle)]*111111;
            avc++;
            strcpy(buff1.Tab[j].Ets.Region,buff.Tab[j].Ets.Region);
        }
        /*Recopier les caracteristiques du bloc courant du fichier code dans le nouveau bloc du fichier decode*/
        buff1.lien=buff.lien;
        buff1.nb=buff.nb;
        EcrireDir(fic,i,buff1); /*Ecrire le nouveau bloc*/
        nb_ecrt++; /*Incrementer le nombre de EcrireDir*/
        i=buff.lien; /*Passer au prochain bloc dans le fichier code*/
    }

    /*Fermeture des fichiers apres traitements*/
    Fermer(&f);
    Fermer(&fic);
}



/*--------------- Procedures permettant de gerer l'affichage au niveau de la console -------------------------*/


void Ecrire_chaine(char S[],int temps ,int couleurDuTexte, int couleurDeFond )
{
         int i;
         for ( i=0;S[i]!='\0';i++ ) {
            Color(couleurDuTexte,couleurDeFond);
            printf("%c",S[i]);
            Sleep(temps );
         }
}

void cadre()
{
       int i;

       for (i=2;i<=188;i++){
                             delay(1);
                             gotoxy(i,2) ;
                             textcolor (9);
                             printf("%c",176);
                             gotoxy(i,50) ;
                             printf("%c",176);

                           }

     for (i=3;i<=49;i++){
                           delay(1);
                           gotoxy(2,i) ;
                           textcolor (9);
                           printf("%c",219);
                           gotoxy(188,i);
                           textcolor (9);
                           printf("%c",219) ;
                         }
      textcolor (15);

}

void cadre2(){

       int i;

       for (i=2;i<=188;i++){
                             gotoxy(i,2) ;
                             textcolor (9);
                             printf("%c",176);
                             gotoxy(i,50) ;
                             printf("%c",176);

                           }

     for (i=3;i<=49;i++){
                           gotoxy(2,i) ;
                           textcolor (9);
                           printf("%c",219);
                           gotoxy(188,i);
                           textcolor (9);
                           printf("%c",219) ;
                         }
      textcolor (15);


}

void Aff_Wilayas()
{
        char c=92;
        textcolor(LIGHTCYAN);
        printf("          _______    _     _                        _                      _ _                                \n");
        printf("         |__   __|  | |   | |                      | |                    (_) |                        \n");
        printf("            | | __ _| |__ | | ___  __ _ _   _    __| | ___  ___  __      ___| | __ _ _   _  __ _ ___   \n");
        printf("            | |/ _` | '_ %c| |/ _ %c/ _` | | | |  / _` |/ _ %c/ __| %c %c /%c / / | |/ _` | | | |/ _` / __|  \n",c,c,c,c,c,c);
        printf("            | | (_| | |_) | |  __/ (_| | |_| | | (_| |  __/%c__ %c  %c V  V /| | | (_| | |_| | (_| %c__ %c  \n",c,c,c,c,c);
        printf("            |_|%c__,_|_.__/|_|%c___|%c__,_|%c__,_|  %c__,_|%c___||___/   %c_/%c_/ |_|_|%c__,_|%c__, |%c__,_|___/  \n",c,c,c,c,c,c,c,c,c,c,c);
        printf("                                                                                      __/ |            \n");
        printf("                                                                                     |___/             \n");
        textcolor(WHITE);
        printf("\t+------+---------------------+------+---------------------+------+---------------------+------+---------------------+------+---------------------+\n");
        printf("\t| Code |         Wilaya      | Code |         Wilaya      | Code |         Wilaya      | Code |         Wilaya      | Code |         Wilaya      |\n");
        printf("\t+------+---------------------+------+---------------------+------+---------------------+------+---------------------+------+---------------------+\n");
        for(int i=0;i<55;i=i+5)
        {
            printf("\t| %4d | %-19s | %4d | %-19s | %4d | %-19s | %4d | %-19s | %4d | %-19s |\n",i+1,Tab_Wilayas[i],i+2,Tab_Wilayas[i+1],i+3,Tab_Wilayas[i+2],i+4,Tab_Wilayas[i+3],i+5,Tab_Wilayas[i+4]);
            printf("\t+------+---------------------+------+---------------------+------+---------------------+------+---------------------+------+---------------------+\n");
        }
            printf("\t\t\t\t     |  56  | %-19s |  57  | %-19s |  58  | %-19s |\n",Tab_Wilayas[55],Tab_Wilayas[56],Tab_Wilayas[57]);
            printf("\t\t\t\t     +------+---------------------+------+---------------------+------+---------------------+\n\n\n");
}

void Aff_Specialite()
{
    char c=92;
    char Specialite [50][80] = {"Informatique","Biologie","Geologie","Medecine","Pharmacie","Chirurgie Dentaire",

    "Science de la vie et de la nature","Science Islamique","Science Politique","Science Economique",

    "Science Humaine et Sociale","Science de la Matiere","Genie des Procedes","Genie Civil","Genie Mecanique",

    "Genie Electrique","Architecture","Droit","Mathematiques","Philosophie","Literature et Langues",

    "Archeologie","Aeronautique","Education physique et sportive","Hydraulique","Traduction",

    "Science de la communication et des medias","Science Agronomique","Veterinaire","Genie industriel"};

    textcolor(LIGHTCYAN);
    printf("                  _______    _     _                        _                         __      _       _ _ _    __                   \n");
    printf("                 |__   __|  | |   | |                      | |                       /_/     (_)     | (_) |  /_/                   \n");
    printf("                    | | __ _| |__ | | ___  __ _ _   _    __| | ___  ___   ___ _ __   ___  ___ _  __ _| |_| |_ ___  ___              \n");
    printf("                    | |/ _` | '_ %c| |/ _ %c/ _` | | | |  / _` |/ _ %c/ __| / __| '_ %c / _ %c/ __| |/ _` | | | __/ _ %c/ __|       \n",c,c,c,c,c,c);
    printf("                    | | (_| | |_) | |  __/ (_| | |_| | | (_| |  __/%c__ %c %c__ %c |_) |  __/ (__| | (_| | | | ||  __/%c__ %c       \n",c,c,c,c,c,c);
    printf("                    |_|%c__,_|_.__/|_|%c___|%c__,_|%c__,_|  %c__,_|%c___||___/ |___/ .__/ %c___|%c___|_|%c__,_|_|_|%c__%c___||___/ \n",c,c,c,c,c,c,c,c,c,c,c);
    printf("                                                                             | |                                        \n");
    printf("                                                                             |_|                                        \n");
    textcolor(WHITE);
    printf("\t         +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    printf("\t         | Code |              Sp%ccialit%c             | Code |          Sp%ccialit%c         | Code |                   Sp%ccialit%c              |\n",130,130,130,130,130,130);
    printf("\t         +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    for(int i=0;i<30;i=i+3)
    {
        printf("\t         | %4d | %35s | %4d | %27s | %4d | %41s |\n",i+1,Specialite[i],i+2,Specialite[i+1],i+3,Specialite[i+2]);
    printf("\t         +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    }
}

void aff()
{
        char c=92;
        textcolor(LIGHTCYAN);
        printf("                       _             _       ______                _                         _   \n");
        printf("                 /%c   (_)           | |     |  ____|              (_)                       | |    \n",c);
        printf("                /  %c   _  ___  _   _| |_    | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_   \n",c);
        printf("               / /%c %c | |/ _ %c| | | | __|   |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __|  \n",c,c,c,c,c,c,c);
        printf("              / ____ %c| | (_) | |_| | |_    | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_   \n",c,c,c);
        printf("             /_/    %c_%c |%c___/ %c__,_|%c___|  |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__|  \n",c,c,c,c,c,c,c,c,c);
        printf("                     _/ |                                            __/ |                         \n");
        printf("                    |__/                                            |___/                          \n");
        textcolor(WHITE);
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |        ");textcolor(YELLOW);printf("Matricule");textcolor(WHITE);printf("       |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |          ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf("           |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |         ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf("         |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |                        | ");textcolor(YELLOW);printf("Jour");textcolor(WHITE);printf("  :                                                                                                    |\n");
        printf("    |                        +------------------------------------------------------------------------------------------------------------+\n");
        printf("    |    ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("   | ");textcolor(YELLOW);printf("Mois");Color(15,16);printf("  :                                                                                                    |\n");
        printf("    |                        +------------------------------------------------------------------------------------------------------------+\n");
        printf("    |                        | ");textcolor(YELLOW);printf("Ann%ce",130);textcolor(WHITE);printf(" :                                                                                                    |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |   ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf("  |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |          ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf("          |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |     ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf("     |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |         ");textcolor(YELLOW);printf("Grade");textcolor(WHITE);printf("          |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |       ");textcolor(YELLOW);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf("       |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |     ");textcolor(YELLOW);printf("Dernier dipl%cme",147);textcolor(WHITE);printf("    |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |                        | ");textcolor(YELLOW);printf("Jour");textcolor(WHITE);printf("  :                                                                                                    |\n");
        printf("    |                        +------------------------------------------------------------------------------------------------------------+\n");
        printf("    |   ");textcolor(YELLOW);printf("Date de recrutement");textcolor(WHITE);printf("  | ");textcolor(YELLOW);printf("Mois");textcolor(WHITE);printf("  :                                                                                                    |\n");
        printf("    |                        +------------------------------------------------------------------------------------------------------------+\n");
        printf("    |                        | ");textcolor(YELLOW);printf("Ann%ce",130);textcolor(WHITE);printf(" :                                                                                                    |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
        printf("    |      ");textcolor(YELLOW);printf("%ctablissement",144);textcolor(WHITE);printf("     |                                                                                                            |\n");
        printf("    +------------------------+------------------------------------------------------------------------------------------------------------+\n");
}

void Affich_Tab_Ets(int *ets)
{
    int i,j=13,cpt=1;
    char c;
    bool stop=false;


printf("      _______    _     _                        _               __ _        _     _ _                                   _       \n");
printf("     |__   __|  | |   | |                      | |             /_/| |      | |   | (_)                                 | |      \n");
printf("        | | __ _| |__ | | ___  __ _ _   _    __| | ___  ___    ___| |_ __ _| |__ | |_ ___ ___  ___ _ __ ___   ___ _ __ | |_ ___ \n");
printf("        | |/ _` | '_ %c| |/ _ %c/ _` | | | |  / _` |/ _ %c/ __|  / _ %c __/ _` | '_ %c| | / __/ __|/ _ %c '_ ` _ %c / _ %c '_ %c| __/ __|\n",92,92,92,92,92,92,92,92,92);
printf("        | | (_| | |_) | |  __/ (_| | |_| | | (_| |  __/%c__ %c |  __/ || (_| | |_) | | %c__ %c__ %c  __/ | | | | |  __/ | | | |_%c__ %c\n",92,92,92,92,92,92,92);
printf("        |_|%c__,_|_.__/|_%c___|%c__,_|%c__,_|  %c__,_|%c___||___/  %c___|%c__%c__,_|_.__/|_|_|___/___/%c___|_| |_| |_|%c___|_| |_|%c__|___/\n",92,92,92,92,92,92,92,92,92,92,92,92);



re: while(stop==false)
    {
        system("cls");
        textcolor(LIGHTCYAN);
        printf("                   _______    _     _                        _               __ _        _     _ _                                   _       \n");
        printf("                  |__   __|  | |   | |                      | |             /_/| |      | |   | (_)                                 | |      \n");
        printf("                     | | __ _| |__ | | ___  __ _ _   _    __| | ___  ___    ___| |_ __ _| |__ | |_ ___ ___  ___ _ __ ___   ___ _ __ | |_ ___ \n");
        printf("                     | |/ _` | '_ %c| |/ _ %c/ _` | | | |  / _` |/ _ %c/ __|  / _ %c __/ _` | '_ %c| | / __/ __|/ _ %c '_ ` _ %c / _ %c '_ %c| __/ __|\n",92,92,92,92,92,92,92,92,92);
        printf("                     | | (_| | |_) | |  __/ (_| | |_| | | (_| |  __/%c__ %c |  __/ || (_| | |_) | | %c__ %c__ %c  __/ | | | | |  __/ | | | |_%c__ %c\n",92,92,92,92,92,92,92);
        printf("                     |_|%c__,_|_.__/|_|%c___|%c__,_|%c__,_|  %c__,_|%c___||___/  %c___|%c__%c__,_|_.__/|_|_|___/___/%c___|_| |_| |_|%c___|_| |_|%c__|___/\n\n",92,92,92,92,92,92,92,92,92,92,92,92);
        textcolor(WHITE);

        if(j>=117)
        {
            for(i=104;i<112;i++)
            {
                printf("\t\t\t+-----+----------------------------------------------------------------------------------------------------------+\n");
                printf("\t\t\t| %3d | %-104s |\n",i+1,Tab_ETS[i].Nom);
            }

            printf("\t\t\t+----------------------------------------------------------------------------------------------------------------+\n");

            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
        }
        else
        {
            for(i=j-13;i<j;i++)
            {
                printf("\t\t\t+-----+----------------------------------------------------------------------------------------------------------+\n");
                printf("\t\t\t| %3d | %-104s |\n",i+1,Tab_ETS[i].Nom);
            }

            printf("\t\t\t+----------------------------------------------------------------------------------------------------------------+\n");

            printf("\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
        }



        textcolor(YELLOW);
        printf("\t\t\t\t\t    Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour basculer entre les pages.\n");
        textcolor(WHITE);
        printf("\n\t\t\t\t\t\t     Appuyez sur 'ENTRER' pour introduire le code de l'%ctablissement.\n\n",130);
        c=getch();
        if(c==-32)
        {
            c=getch();

            if(c==77)
            {
                if(j>=117)
                {
                    j=13;
                    cpt=1;
                }
                else
                {
                    j=j+13;
                    cpt++;
                }
            }
            else
            {
                if(c==75)
                {
                    if(j<=13)
                    {
                        j=117;
                        cpt=9;
                    }
                    else
                    {
                        j=j-13;
                        cpt--;
                    }
                }
            }
         }
         else
         {
             if(c==13)
             {
                 stop=true;
             }
         }
    }
    printf("\n\t\t\t\t\t\t\t   Veuillez introduire le code de l'%ctablissement: ",130);
    textcolor(LIGHTCYAN);
    scanf("%d",&(*ets));
    if((*ets)<1||(*ets)>112)
    {
        delline();
        textcolor(LIGHTRED);
        printf("\n\n\t\t\t\t\t       Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 112.\n\n");
        textcolor(WHITE);
        printf("\n\t\t\t\t\t\t       Pour cela veuillez d'abord appuyez sur une touche quelconque.");
        getch();
        textcolor(WHITE);
        system("cls");
        j=13;
        stop=false;
        goto re;
    }


}

void affich_eng(int i, int j)
{
        LOBF F;
        TBloc buf;
        Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A');
        LireDir(F,i,&buf);
        nb_lect++;

        textcolor(WHITE);printf("\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",buf.Tab[j].Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",buf.Tab[j].Matricule);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",buf.Tab[j].Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",buf.Tab[j].Dernier_Diplome);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",buf.Tab[j].Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",buf.Tab[j].Specialite);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",buf.Tab[j].Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",buf.Tab[j].Grade);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",buf.Tab[j].Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",buf.Tab[j].Date_Recrutement.Day,buf.Tab[j].Date_Recrutement.Month,buf.Tab[j].Date_Recrutement.Year);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",buf.Tab[j].Date_Naissance.Day,buf.Tab[j].Date_Naissance.Month,buf.Tab[j].Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",buf.Tab[j].Ets.Nom);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");

        Fermer(&F);
}

void logo_ESI()
{

    int x,y;
    textcolor(YELLOW);
    gotoxy(6,4);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
    printf(" ______  _____  __ ");
    gotoxy(x,y+1);
    printf("|  ____|/ ____||__|");
    gotoxy(x,y+2);
    printf("| |__  | (___   __ ");
    gotoxy(x,y+3);
    printf("|  __|  \\___ \\ |  |");
    gotoxy(x,y+4);
    printf("| |____ ____) ||  |");
    gotoxy(x,y+5);
    printf("|______|_____/ |__|");
    textcolor(9);
    gotoxy(x+15,y);
    printf(" __");
    gotoxy(x+15,y+1);
    printf("|__|");
    textcolor(15);
    gotoxy(x+21,y+1);
    printf("%ccole nationale",144);
    gotoxy(x+21,y+3);
    printf("Sup%crieure",130);
    gotoxy(x+21,y+5);
    printf("d'Informatique");


}

void loading(){

    int i;
    for(i=1;i<86;i++)
    {
        textcolor(BLUE);
        gotoxy( wherex() , 43 );
        printf("%c",219);
        gotoxy( wherex()-1 , 44 );
        printf("%c",219);
        Sleep(11);
    }


}

int Maximum (int a,int b){

    if (a<b){

        return b;

    }

    else{

        return a;

    }

}

void Permuter(int *a,int *b){ /*Procedure permettant de permuter deux entiers*/

    int i;

    i = (*a); /*Sauvegarder la valeur de a dans une variable intermediaire*/

    (*a) = (*b);

    (*b) = i;

}

long int Taille_Fichier(){ /*Retourne la taille du fichier*/

    FILE* fp = fopen("ENSEIGNANT-MESRS.bin", "rb+");

    fseek(fp, 0L, SEEK_END);

    long int res = ftell(fp);

    fclose(fp);

    return res;

}

void Welcome(){

    printf("Pour une meilleure exp%crience, veuillez ouvrir la console en mode plein %ccran.\n\n",130,130);
    printf("Appuyez sur une touche pour continuer.");
    fflush(stdin);
    getch();
    system("cls");
    cadre();
    gotoxy(75,6);
    char ligne[256];
    strcpy(ligne,"Republique Algerienne Democratique et Populaire\n\n\n");
    ligne [1] = 130;
    ligne [14] = 130;
    ligne [23] = 130;
    Ecrire_chaine(ligne,10,WHITE,BLACK);
    gotoxy(63,8);
    strcpy(ligne,"Ministere de l'Enseignement Superieure et de la Recherche Scientifique");
    ligne[6] = 138;
    ligne[31] = 130;
    Ecrire_chaine(ligne,10,WHITE,BLACK);
    logo_ESI();
    gotoxy(76,22);
    printf("         ,..........   ..........,");
    gotoxy(76,23);
    printf("     ,..,'          '.'          ',..,");
    gotoxy(76,24);
    printf("    ,' ,'            :            ', ',");
    gotoxy(76,25);
    printf("   ,' ,'             :             ', ',");
    gotoxy(76,26);
    printf("  ,' ,'              :              ', ',");
    gotoxy(76,27);
    printf(" ,' ,'............., : ,.............', ',");
    gotoxy(76,28);
    printf(",'  '............   '.'   ............'  ',");
    gotoxy(76,29);
    printf(" '''''''''''''''''';''';''''''''''''''''''");
    gotoxy(76,30);
    printf("                    '''");
    gotoxy(76,14);
    printf("  _____ ____    ____  _____ ____  ____");
    gotoxy(76,15);
    printf(" |_   _|  _ \\  / ___||  ___/ ___||  _ \\");
    gotoxy(76,16);
    printf("   | | | |_) | \\___ \\| |_  \\___ \\| | | |");
    gotoxy(76,17);
    printf("   | | |  __/   ___) |  _|  ___) | |_| |");
    gotoxy(76,18);
    printf("   |_| |_|     |____/|_|   |____/|____/");
    gotoxy(20,31);
    printf("R%calis%c par:",130,130);
    /*gotoxy(20,35);
    printf("-----------");*/
    gotoxy(22,33);
    printf("-> BOUYAKOUB Rayane");
    gotoxy(22,35);
    printf("-> OUIKENE Youcef");
    gotoxy(157,33);
    printf("Section: A");
    gotoxy(157,35);
    printf("Groupe: 1");
    gotoxy(85,38);
    printf("Enseignant: Dr.KERMI Adel");
    gotoxy(82,40);
    printf("Ann%ce Universitaire: 2022/2023",130);
    gotoxy(57,43);
    loading();
    gotoxy(66,47);
    textcolor(LIGHTGREEN);
    printf("Programme charg%c avec succ%cs, Appuyuez sur une touche pour continuer.",130,138);
    getchar();
}

void Menu(){
 start:

    system("cls");
    textbackground(BLACK);
    cadre2();
    textcolor(LIGHTCYAN);
    gotoxy(78,5);
    printf("   __  __   ______   _   _   _    _");
    gotoxy(78,6);
    printf("  |  \\/  | |  ____| | \\ | | | |  | |");
    gotoxy(78,7);
    printf("  | \\  / | | |__    |  \\| | | |  | |");
    gotoxy(78,8);
    printf("  | |\\/| | |  __|   | . ` | | |  | |");
    gotoxy(78,9);
    printf("  | |  | | | |____  | |\\  | | |__| |");
    gotoxy(78,10);
    printf("  |_|  |_| |______| |_| \\_|  \\____/");
    gotoxy(51,14);
    textcolor(WHITE);
    printf("Veuillez s%clectionner l'op%cration %c ex%ccuter en utilisant les touches 'UP ARROW' et 'DOWN ARROW'.",130,130,133,130);
    gotoxy(73,16);
    textcolor(YELLOW);
    printf("Appuyez sur 'Entrer' pour confirmer votre choix.");
    char Menu_Choices[15][256] = {"1  ->  Creer le fichier ENSEIGNANT-MESRS.bin.",
                                  "2  ->  Afficher le contenu du fichier ENSEIGNANT-MESRS.bin (Organisation Interne).",
                                  "3  ->  Afficher les differentes informations d'un enseignant donne.",
                                  "4  ->  Ajouter un nouvel enseignant.",
                                  "5  ->  Modifier l'etablissement universitaire d'un enseignant.",
                                  "6  ->  Supprimer un enseignant.",
                                  "7  ->  Supprimer tous les enseignants relatifs a une specialite donnee.",
                                  "8  ->  Afficher les enseignants exercant dans un etablissement donne ayant une anciennete entre deux valeurs donnees.",
                                  "9  ->  Consulter les enseignants exercant dans une region donnee.",
                                  "10 ->  Coder et decoder le fichier ENSEIGNANT-MESRS.bin.",
                                  "11 ->  Afficher l'entete du fichier ainsi que le nombre de LireDir et EcrireDir.",
                                  "12 ->  Representation graphique de l'organisation globale des trois premiers blocs du fichier."};
    int i,j;
    Menu_Choices[0][9] = 130;
    Menu_Choices[2][strlen(Menu_Choices[2])-2]=130;
    Menu_Choices[2][24] = 130;
    Menu_Choices[4][18] = 130;
    Menu_Choices[6][47] = 133;
    Menu_Choices[6][62] = 130;
    Menu_Choices[6][68] = 130;
    Menu_Choices[6][55] = 130;
    Menu_Choices[7][36] = 135;
    Menu_Choices[7][49] = 130;
    Menu_Choices[7][67] = 130;
    Menu_Choices[7][88] = 130;
    Menu_Choices[7][strlen(Menu_Choices[7])-4]=130;
    Menu_Choices[8][37]=135;
    Menu_Choices[8][strlen(Menu_Choices[2])-5]=130;
    Menu_Choices[9][17]=130;
    Menu_Choices[10][21]=136;
    Menu_Choices[11][11]=130;
    textcolor(LIGHTRED);
    gotoxy(73,50);
    printf("Appuyez sur ESC/%cchapper pour quitter le programme.",144);
    textcolor(WHITE);
    i = 0;
    j = 21;
    bool quit=false;
    char c;
    textbackground(BLUE);
    gotoxy(25,21);
    printf("%s",Menu_Choices[0]);
    textbackground(BLACK);
    gotoxy(25,23);
    printf("%s",Menu_Choices[1]);
    gotoxy(25,25);
    printf("%s",Menu_Choices[2]);
    gotoxy(25,27);
    printf("%s",Menu_Choices[3]);
    gotoxy(25,29);
    printf("%s",Menu_Choices[4]);
    gotoxy(25,31);
    printf("%s",Menu_Choices[5]);
    gotoxy(25,33);
    printf("%s",Menu_Choices[6]);
    gotoxy(25,35);
    printf("%s",Menu_Choices[7]);
    gotoxy(25,37);
    printf("%s",Menu_Choices[8]);
    gotoxy(25,39);
    printf("%s",Menu_Choices[9]);
    gotoxy(25,41);
    printf("%s",Menu_Choices[10]);
    gotoxy(25,43);
    printf("%s",Menu_Choices[11]);
    while (!quit){

        c = getch();

        switch (c){

            case 80:

                textbackground(BLACK);
                gotoxy(25,i+j);
                printf("%s",Menu_Choices[i]);
                i++;
                j++;
                textbackground(BLUE);
                gotoxy(25,i+j);
                printf("%s",Menu_Choices[i]);
                textbackground(BLACK);

                if (i>11){

                    i = 0;
                    j = 21;
                    gotoxy(25,21);
                    textbackground(BLUE);
                    printf("%s",Menu_Choices[0]);
                    textbackground(BLACK);

                }
                break;



            case 72:

                textbackground(BLACK);
                gotoxy(25,i+j);
                printf("%s",Menu_Choices[i]);
                i--;
                j--;

                if (i<0){

                    i =11;
                    j = 32;
                    gotoxy(25,43);
                    textbackground(BLUE);
                    printf("%s",Menu_Choices[11]);
                    textbackground(BLACK);

                }
                else {

                    textbackground(BLUE);
                    gotoxy(25,i+j);
                    printf("%s",Menu_Choices[i]);
                    textbackground(BLACK);

                }

                break;





            case 13:

                    system("cls");
                    textbackground(BLACK);
                    if((nbE==0)&&(i!=3)&&(i!=10)&&(i!=0))
                    {
                        system("cls");
                        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t      Le fichier ENSEIGNANT-MESRS est vide, vous ne pouvez pas effectuer cette op%cration.",130);
                        textcolor(RED);
                        gotoxy(74,13);
                        printf("            uuuuuuuuuuuuuuuuuuuu");
                        gotoxy(74,14);
                        printf("          u%c uuuuuuuuuuuuuuuuuu %cu",34,34);
                        gotoxy(74,15);
                        printf("        u%c u$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
                        gotoxy(74,16);
                        printf("      u%c u$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
                        gotoxy(74,17);
                        printf("    u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
                        gotoxy(74,18);
                        printf("  u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
                        gotoxy(74,19);
                        printf("u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
                        gotoxy(74,20);
                        printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
                        gotoxy(74,21);
                        printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
                        gotoxy(74,22);
                        printf("$ $$$%c ... %c$...  ...$%c ... %c$$$  ... %c$$$ $",34,34,34,34,34);
                        gotoxy(74,23);
                        printf("$ $$$u `%c$$$$$$$  $$$  $$$$$  $$  $$$  $$$ $",34);
                        gotoxy(74,24);
                        printf("$ $$$$$$uu %c$$$$  $$$  $$$$$  $$  %c%c%c u$$$ $",34,34,34,34);
                        gotoxy(74,25);
                        printf("$ $$$%c%c$$$  $$$$  $$$u %c$$$%c u$$  $$$$$$$$ $",34,34,34,34);
                        gotoxy(74,26);
                        printf("$ $$$$....,$$$$$..$$$$$....,$$$$..$$$$$$$$ $");
                        gotoxy(74,27);
                        printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
                        gotoxy(74,28);
                        printf("%cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
                        gotoxy(74,29);
                        printf("  %cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u",34,34,34);
                        gotoxy(74,30);
                        printf("    %cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
                        gotoxy(74,31);
                        printf("      %cu %c$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
                        gotoxy(74,32);
                        printf("        %cu %c$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
                        gotoxy(74,33);
                        printf("          %cu %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c u%c",34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34);
                        gotoxy(74,34);
                        printf("            %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34);
                        textcolor(WHITE);
                        printf("\n\n\n\n\n\t\t\t\t\t\t           Essayez d'abord de cr%cer le fichier ou bien de rajouter des enseignants.\n",130);
                        textcolor(YELLOW);
                        printf("\n\n\n\t\t\t\t\t\t                    Appuyez sur une touche pour revenir au menu principal.\n");
                        fflush(stdin);
                        getch();
                        textcolor(WHITE);
                    }
                    else
                    {
                        switch (i) {

                            case 0:
                                    Affich_Creation_ENS_FIC();
                                    break;

                            case 1: Affich_Fic("ENSEIGNANT-MESRS.bin");
                                    break;

                            case 2: Affich_ENS();
                                    break;

                            case 3: Affich_Ajout_ENS();
                                    break;

                            case 4: Affich_Modification_ENS();
                                    break;

                            case 5: Affich_Suppression_ENS();
                                    break;

                            case 6: Affich_Suppression_Specialite();
                                    break;

                            case 7: Consultation_Multicles();
                                    break;

                            case 8: Affich_Region();
                                    break;

                            case 9: Affich_Codage_Decodage();
                                    break;

                            case 10: Affich_Entete_LEDir();
                                    break;

                            case 11: Organisation_Globale();
                                    break;


                            default: break;


                        }
                    }


                    goto start;


            case 27: quit = true;
                     break;


            default: break;


        }



    }



}

void Affich_Creation_ENS_FIC(){
    textcolor(LIGHTCYAN);
    gotoxy(55,1);
    printf("   _____                         _     _");
    gotoxy(55,2);
    printf("  / ____|                       | |   (_)");
    gotoxy(55,3);
    printf(" | |       _ __    ___    __ _  | |_   _    ___    _ __");
    gotoxy(55,4);
    printf(" | |      | '__|  / _ \\  / _` | | __| | |  / _ \\  | '_ \\");
    gotoxy(55,5);
    printf(" | |____  | |    |  __/ | (_| | | |_  | | | (_) | | | | |");
    gotoxy(55,6);
    printf("  \\_____| |_|     \\___|  \\__,_|  \\__| |_|  \\___/  |_| |_|");
    gotoxy(115,1);
    printf("  _____");
    gotoxy(115,2);
    printf(" |  __ \\");
    gotoxy(115,3);
    printf(" | |  | |  _   _");
    gotoxy(115,4);
    printf(" | |  | | | | | |");
    gotoxy(115,5);
    printf(" | |__| | | |_| |");
    gotoxy(115,6);
    printf(" |_____/   \\__,_|");
    gotoxy(72,8);
    printf("  ______   _          _       _");
    gotoxy(72,9);
    printf(" |  ____| (_)        | |     (_)");
    gotoxy(72,10);
    printf(" | |__     _    ___  | |__    _    ___   _ __");
    gotoxy(72,11);
    printf(" |  __|   | |  / __| | '_ \\  | |  / _ \\ | '__|");
    gotoxy(72,12);
    printf(" | |      | | | (__  | | | | | | |  __/ | |");
    gotoxy(72,13);
    printf(" |_|      |_|  \\___| |_| |_| |_|  \\___| |_|");
    gotoxy(22,17);
    textcolor(LIGHTRED);
    printf("En effectuant cette op%cration, l'ancien fichier sera %ccras%c d%cfinitvement et vous ne pourrez plus le r%ccup%crer. Etes-vous s%cr de vouloir continuer ?",130,130,130,130,130,130,150);
    char Choix[3][10] = {"-> Oui","-> Non"};
    textcolor(YELLOW);
    gotoxy(36,19);
    printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appuyez sur 'Entrer' pour le valider.",130,130);
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(40,21);
    printf("%s",Choix[0]);
    gotoxy(144,21);
    textbackground(BLACK);
    printf("%s",Choix[1]);
    int i;
    i=0;
    bool continu = true;
    char c;
    while (continu){

        c = getch();

        switch(c){

            case -32:

                    c = getch();

                    if (c==77){

                        if (i==0){

                            textbackground(BLACK);
                            gotoxy(40,21);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,21);
                            printf("%s",Choix[1]);
                            i++;
                            textbackground(BLACK);

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(144,21);
                            printf("%s",Choix[1]);
                            textbackground(BLUE);
                            gotoxy(40,21);
                            printf("%s",Choix[0]);
                            i = 0;
                            textbackground(BLACK);

                        }

                    }
                    if (c==75){

                        if (i==1){

                            textbackground(BLUE);
                            gotoxy(40,21);
                            printf("%s",Choix[0]);
                            textbackground(BLACK);
                            gotoxy(144,21);
                            printf("%s",Choix[1]);
                            i--;

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(40,21);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,21);
                            printf("%s",Choix[1]);
                            i=1;
                            textbackground(BLACK);


                        }


                    }

                    break;

            case 13:

                    continu = false;

                    break;

            default:

                    break;

        }


    }
    if (i==0){

            gotoxy(39,24);
            textcolor(WHITE);
            textbackground(BLACK);
            printf(">> Veuillez introduire le nombre d'enregistrements %c ins%crer, ce nombre doit %ctre compris entre 1 et 700000: ",133,130,136);
            gotoxy(52,26);
            printf("Si vous ins%crez un nombre important de donn%ces, vous serez oblig%c d'attendre un moment.",130,130,130);
            gotoxy(148,24);
            int num_data;
            textcolor(LIGHTCYAN);
            scanf("%d",&num_data);
            while ((num_data>700000)||(num_data<1)){

                system("cls");
                textcolor(LIGHTCYAN);
                gotoxy(55,1);
                printf("   _____                         _     _");
                gotoxy(55,2);
                printf("  / ____|                       | |   (_)");
                gotoxy(55,3);
                printf(" | |       _ __    ___    __ _  | |_   _    ___    _ __");
                gotoxy(55,4);
                printf(" | |      | '__|  / _ \\  / _` | | __| | |  / _ \\  | '_ \\");
                gotoxy(55,5);
                printf(" | |____  | |    |  __/ | (_| | | |_  | | | (_) | | | | |");
                gotoxy(55,6);
                printf("  \\_____| |_|     \\___|  \\__,_|  \\__| |_|  \\___/  |_| |_|");
                gotoxy(115,1);
                printf("  _____");
                gotoxy(115,2);
                printf(" |  __ \\");
                gotoxy(115,3);
                printf(" | |  | |  _   _");
                gotoxy(115,4);
                printf(" | |  | | | | | |");
                gotoxy(115,5);
                printf(" | |__| | | |_| |");
                gotoxy(115,6);
                printf(" |_____/   \\__,_|");
                gotoxy(72,8);
                printf("  ______   _          _       _");
                gotoxy(72,9);
                printf(" |  ____| (_)        | |     (_)");
                gotoxy(72,10);
                printf(" | |__     _    ___  | |__    _    ___   _ __");
                gotoxy(72,11);
                printf(" |  __|   | |  / __| | '_ \\  | |  / _ \\ | '__|");
                gotoxy(72,12);
                printf(" | |      | | | (__  | | | | | | |  __/ | |");
                gotoxy(72,13);
                printf(" |_|      |_|  \\___| |_| |_| |_|  \\___| |_|");
                gotoxy(22,17);
                textcolor(LIGHTRED);
                printf("En eff%cctuant cette op%cration, l'ancien fichier sera %ccras%c d%cfinitvement et vous ne pourrez plus le r%ccup%crer. Etes-vous s%cr de vouloir continuer ?",130,130,130,130,130,130,130,150);
                textcolor(YELLOW);
                gotoxy(36,19);
                printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appuyez sur 'Entrer' pour le valider.",130,130);
                textcolor(WHITE);
                textbackground(BLUE);
                gotoxy(40,21);
                printf("%s",Choix[0]);
                gotoxy(144,21);
                textbackground(BLACK);
                printf("%s",Choix[1]);
                gotoxy(39,24);
                textcolor(WHITE);
                textbackground(BLACK);
                printf(">> Veuillez introduire le nombre d'enregistrements %c ins%crer, ce nombre doit %ctre compris entre 1 et 700000: ",133,130,136);
                gotoxy(52,26);
                printf("Si vous inserez un nombre important de donn%ces, vous serez oblig%c d'attendre un moment.",130,130);
                gotoxy(59,28);
                textbackground(RED);
                printf("Erreur, Le nombre d'enregistrements doit %ctre compris entre 1 et 700000.",136);
                textbackground(BLACK);
                gotoxy(148,24);
                textcolor(LIGHTCYAN);
                scanf("%d",&num_data);


            }
                textcolor(BROWN);
                gotoxy(110,32);
                printf("(  )   (   )  )");
                gotoxy(110,33);
                printf(" ) (   )  (  (");
                gotoxy(110,34);
                printf(" ( )  (    ) )");
                gotoxy(110,35);
                printf(" _____________");
                gotoxy(110,36);
                printf("<_____________> ___");
                gotoxy(110,37);
                printf("|             |/ _ \\");
                gotoxy(110,38);
                printf("|               | | |");
                gotoxy(110,39);
                printf("|               |_| |");
                gotoxy(110,40);
                printf("|             |\\___/");
                gotoxy(100,40);
                printf("       ___");
                gotoxy(106,41);
                printf("/    \\___________/    \\");
                gotoxy(106,42);
                printf("\\_____________________/");
                gotoxy(71,35);
                printf("D%ctendez-vous",130);
                gotoxy(62,37);
                printf("Avec ce merveilleux caf%c virtuel",130);
                gotoxy(59,39);
                printf("Lors de la cr%cation de votre fichier!",130);
                Creation_ENS_FIC(num_data);
                textcolor(LIGHTGREEN);
                gotoxy(80,47);
                printf("Cr%cation effectu%ce avec succ%cs!",130,130,138);



    }
    else{
         textbackground(BLACK);
         textcolor(GREEN);
         gotoxy(126,31);
         printf("        _    _");
         gotoxy(126,32);
         printf("       | |  | |");
         gotoxy(126,33);
         printf("      -| |  | |-");
         gotoxy(126,34);
         printf("  _    | |- | |");
         gotoxy(126,35);
         printf("-| |   | |  | |-");
         gotoxy(126,36);
         printf(" |.|  -| ||/  |");
         gotoxy(126,37);
         printf(" | |-  |  ___/");
         gotoxy(126,38);
         printf("-|.|   | | |");
         gotoxy(126,39);
         printf(" |  \\_|| |");
         gotoxy(126,40);
         printf("  \\____  |");
         gotoxy(126,41);
         printf("   |   | |-");
         gotoxy(126,42);
         printf("       | |");
         gotoxy(126,43);
         printf("      -| |");
         gotoxy(126,44);
         printf("       |_|");
         textcolor(LIGHTGRAY);
         gotoxy(64,26);
         printf(",#################");
         gotoxy(62,27);
         printf("####,  ################");
         gotoxy(62,28);
         printf("#######################");
         gotoxy(62,29);
         printf("#######################");
         gotoxy(62,30);
         printf("#######################");
         gotoxy(62,31);
         printf("###########");
         gotoxy(62,32);
         printf("#########");
         gotoxy(40,33);
         printf("##               ##############");
         gotoxy(40,34);
         printf("####/         #####################");
         gotoxy(40,35);
         printf("#######    .###################  ##");
         gotoxy(40,36);
         printf("###############################");
         gotoxy(40,37);
         printf("###############################");
         gotoxy(42,38);
         printf(",**########################");
         gotoxy(49,39);
         printf("#################");
         gotoxy(49,40);
         printf("###############");
         gotoxy(51,41);
         printf("#######  ####");
         gotoxy(51,42);
         printf("####(      ##");
         gotoxy(51,43);
         printf("##         ##");
         gotoxy(51,44);
         printf("#####      (####");
         gotoxy(67,48);
         textbackground(RED);
         textcolor(WHITE);
         printf("Vous avez choisi d'annuler l'ex%ccution de cette op%cration!",130,130);


    }
    gotoxy(69,50);
    textbackground(BLACK);
    textcolor(YELLOW);
    printf("Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();

}

void Affich_ENS(){

    textcolor(LIGHTCYAN);
    gotoxy(114,6);
    printf("   ____________________________________________________");
    gotoxy(114,7);
    printf("  |____________________________________________________|");
    gotoxy(114,8);
    printf("  | __     __   ____   ___ ||  ____    ____     _  __  |");
    gotoxy(114,9);
    printf("  ||  |__ |--|_| || |_|   |||_|**|*|__|+|+||___| ||  | |");
    gotoxy(114,10);
    printf("  ||==|^^||--| |=||=| |=*=||| |~~|~|  |=|=|| | |~||==| |");
    gotoxy(114,11);
    printf("  ||  |##||  | | || | |JRO|||-|  | |==|+|+||-|-|~||__| |");
    gotoxy(114,12);
    printf("  ||__|__||__|_|_||_|_|___|||_|__|_|__|_|_||_|_|_||__|_|");
    gotoxy(114,13);
    printf("  ||_______________________||__________________________|");
    gotoxy(114,14);
    printf("  | _____________________  ||      __   __  _  __    _ |");
    gotoxy(114,15);
    printf("  ||=|=|=|=|=|=|=|=|=|=|=| __..\\/ |  |_|  ||#||==|  / /|");
    gotoxy(114,16);
    printf("  || | | | | | | | | | | |/\\ \\  \\\\|++|=|  || ||==| / / |");
    gotoxy(114,17);
    printf("  ||_|_|_|_|_|_|_|_|_|_|_/_/\\_.___\\__|_|__||_||__|/_/__|");
    gotoxy(114,18);
    printf("  |____________________ /\\~()/()~//\\ __________________|");
    gotoxy(114,19);
    printf("  | __   __    _  _     \\_  (_ .  _/ _    ___     _____|");
    gotoxy(114,20);
    printf("  ||~~|_|..|__| || |_ _   \\ //\\\\ /  |=|__|~|~|___| | | |");
    gotoxy(114,21);
    printf("  ||--|+|^^|==|1||2| | |__/\\ __ /\\__| |==|x|x|+|+|=|=|=|");
    gotoxy(114,22);
    printf("  ||__|_|__|__|_||_|_| /  \\ \\  / /  \\_|__|_|_|_|_|_|_|_|");
    gotoxy(114,23);
    printf("  |_________________ _/    \\/\\/\\/    \\_ _______________|");
    gotoxy(114,24);
    printf("  | _____   _   __  |/      \\../      \\|  __   __   ___|");
    gotoxy(114,25);
    printf("  ||_____|_| |_|##|_||   |   \\/ __|   ||_|==|_|++|_|-|||");
    gotoxy(114,26);
    printf("  ||______||=|#|--| |\\   \\   o    /   /| |  |~|  | | |||");
    gotoxy(114,27);
    printf("  ||______||_|_|__|_|_\\   \\  o   /   /_|_|__|_|__|_|_|||");
    gotoxy(114,28);
    printf("  |_________ __________\\___\\____/___/___________ ______|");
    gotoxy(114,29);
    printf("  |__    _  /    ________     ______           /| _ _ _|");
    gotoxy(114,30);
    printf("  |\\ \\  |=|/   //    /| //   /  /  / |        / ||%c|%c|%c|",37,37,37);
    gotoxy(114,31);
    printf("  | \\/\\ |*/  .//____//.//   /__/__/ (_)      /  ||=|=|=|");
    gotoxy(114,32);
    printf("__|  \\/\\|/   /(____|/ //                    /  /||~|~|~|__");
    gotoxy(114,33);
    printf("  |___\\_/   /________//   ________         /  / ||_|_|_|");
    gotoxy(114,34);
    printf("  |___ /   (|________/   |\\_______\\       /  /| |______|");
    gotoxy(114,35);
    printf("      /                  \\|________)     /  / | |");
    gotoxy(25,11);
    printf("    _      __    __   _        _                    _");
    gotoxy(25,12);
    printf("   /_\\    / _|  / _| (_)  __  | |_    ___   _ _    | |  ___   ___");
    gotoxy(25,13);
    printf("  / _ \\  |  _| |  _| | | / _| | ' \\  / -_) | '_|   | | / -_) (_-<");
    gotoxy(25,14);
    printf(" /_/ \\_\\ |_|   |_|   |_| \\__| |_||_| \\___| |_|     |_| \\___| /__/");
    gotoxy(25,16);
    printf("     _   _    __    __    __                      _");
    gotoxy(25,17);
    printf("  __| | (_)  / _|  / _|  /_/   _ _   ___   _ _   | |_   ___   ___");
    gotoxy(25,18);
    printf(" / _` | | | |  _| |  _| / -_) | '_| / -_) | ' \\  |  _| / -_) (_-<");
    gotoxy(25,19);
    printf(" \\__,_| |_| |_|   |_|   \\___| |_|   \\___| |_||_|  \\__| \\___| /__/");
    gotoxy(22,21);
    printf("  _           __                              _     _");
    gotoxy(22,22);
    printf(" (_)  _ _    / _|  ___   _ _   _ __    __ _  | |_  (_)  ___   _ _    ___");
    gotoxy(22,23);
    printf(" | | | ' \\  |  _| / _ \\ | '_| | '  \\  / _` | |  _| | | / _ \\ | ' \\  (_-<");
    gotoxy(22,24);
    printf(" |_| |_||_| |_|   \\___/ |_|   |_|_|_| \\__,_|  \\__| |_| \\___/ |_||_| /__/");
    gotoxy(13,26);
    printf("     _   _                                           _                               _");
    gotoxy(13,27);
    printf("  __| | ( )  _  _   _ _      ___   _ _    ___  ___  (_)  __ _   _ _    __ _   _ _   | |_");
    gotoxy(13,28);
    printf(" / _` | |/  | || | | ' \\    / -_) | ' \\  (_-< / -_) | | / _` | | ' \\  / _` | | ' \\  |  _|");
    gotoxy(13,29);
    printf(" \\__,_|      \\_,_| |_||_|   \\___| |_||_| /__/ \\___| |_| \\__, | |_||_| \\__,_| |_||_|  \\__|");
    gotoxy(13,30);
    printf("                                                        |___/");
    textcolor(WHITE);
    gotoxy(66,41);
    printf("   Veuillez introduire le matricule de l'enseignant:");
    long int Matricule;
    gotoxy(119,41);
    textcolor(LIGHTGREEN);
    scanf("%ld",&Matricule);
    bool trouv;
    int i;
    Recherche_Index_Primaire(Matricule,&trouv,&i);
    if (trouv == false){

        textcolor(LIGHTRED);
        gotoxy(83,44);
        printf("Enseignant non trouv%c!",130);


    }
    else{


        system("cls");
        textcolor(LIGHTGREEN);
        gotoxy(60,4);
        printf("  ______                        _                                   _");
        gotoxy(60,5);
        printf(" |  ____|                      (_)                                 | |");
        gotoxy(60,6);
        printf(" | |__     _ __    ___    ___   _    __ _   _ __     __ _   _ __   | |_");
        gotoxy(60,7);
        printf(" |  __|   | '_ \\  / __|  / _ \\ | |  / _` | | '_ \\   / _` | | '_ \\  | __|");
        gotoxy(60,8);
        printf(" | |____  | | | | \\__ \\ |  __/ | | | (_| | | | | | | (_| | | | | | | |_");
        gotoxy(60,9);
        printf(" |______| |_| |_| |___/  \\___| |_|  \\__, | |_| |_|  \\__,_| |_| |_|  \\__|");
        gotoxy(60,10);
        printf("                                     __/ |");
        gotoxy(60,11);
        printf("                                    |___/");
        gotoxy(60,12);
        printf("             _______                                    __");
        gotoxy(60,13);
        printf("            |__   __|                                  /_/");
        gotoxy(60,14);
        printf("               | |     _ __    ___    _   _  __   __   ___");
        gotoxy(60,15);
        printf("               | |    | '__|  / _ \\  | | | | \\ \\ / /  / _ \\");
        gotoxy(60,16);
        printf("               | |    | |    | (_) | | |_| |  \\ V /  |  __/");
        gotoxy(60,17);
        printf("               |_|    |_|     \\___/   \\__,_|   \\_/    \\___|");
        gotoxy(64,22);
        textcolor(WHITE);
        printf("L'enseignant cherch%c se trouve dans le bloc num%cro %d, position %d.",130,130,TabIndex[i].Num_Bloc,TabIndex[i].Depl);
        gotoxy(55,24);
        printf("Voici les diff%crentes informations personnelles et professionnelles de ce dernier.",130);
        gotoxy(1,27);
        LOBF F;
        TBloc buf;
        int j = TabIndex[i].Depl;

        Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A');
        LireDir(F,TabIndex[i].Num_Bloc,&buf);
        nb_lect++;
        textcolor(WHITE);printf("\n+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                 |\n");
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",buf.Tab[j].Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-108ld|\n",buf.Tab[j].Matricule);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",buf.Tab[j].Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-102s|\n",buf.Tab[j].Dernier_Diplome);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",buf.Tab[j].Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-107s|\n",buf.Tab[j].Specialite);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",buf.Tab[j].Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-112s|\n",buf.Tab[j].Grade);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",buf.Tab[j].Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                        |\n",buf.Tab[j].Date_Recrutement.Day,buf.Tab[j].Date_Recrutement.Month,buf.Tab[j].Date_Recrutement.Year);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",buf.Tab[j].Date_Naissance.Day,buf.Tab[j].Date_Naissance.Month,buf.Tab[j].Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-104s|\n",buf.Tab[j].Ets.Nom);
        textcolor(WHITE);printf("+-------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+\n");
        Fermer(&F);



    }

    textcolor(YELLOW);
    gotoxy(67,47);
    printf("Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();

}

void Affich_Fic(char Nomf[])
{
    LOBF F;
    TBloc buf;
    Ouvrir(&F,Nomf,'A');
    int i,cpt,j,e,max,ets=1;
    bool stop=false;
    char c;
    LireDir(F,Entete(F,1),&buf);
    nb_lect++;
    max=taille*(Entete(F,1)-1)+buf.nb;
    //max = nbE;
    if(buf.nb%2==0)
    {
        i=Entete(F,1);

            cpt=1;
            e=2;
            while(stop==false)
            {
                system("cls");
                for(j=e-2;j<e;j++)
                {
                        textcolor(WHITE);printf("\n+-------------------------+\n");
                        if(j==e-2)
                        {
                            textcolor(WHITE);printf("|    Enseignant  %-6d   |\n",ets);
                        }
                        else
                        {
                            textcolor(WHITE);printf("|    Enseignant  %-6d   |\n",ets+1);
                        }
                        textcolor(WHITE);printf("+-------------------------+-----------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                |\n");
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",buf.Tab[j].Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-107ld|\n",buf.Tab[j].Matricule);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",buf.Tab[j].Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-101s|\n",buf.Tab[j].Dernier_Diplome);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",buf.Tab[j].Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-106s|\n",buf.Tab[j].Specialite);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",buf.Tab[j].Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-111s|\n",buf.Tab[j].Grade);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",buf.Tab[j].Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                       |\n",buf.Tab[j].Date_Recrutement.Day,buf.Tab[j].Date_Recrutement.Month,buf.Tab[j].Date_Recrutement.Year);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",buf.Tab[j].Date_Naissance.Day,buf.Tab[j].Date_Naissance.Month,buf.Tab[j].Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-103s|\n",buf.Tab[j].Ets.Nom);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                }


                printf("\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                textcolor(YELLOW);
                printf("\t\t\t\t\t    Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour basculer entre les pages.\n\n");
                textcolor(WHITE);
                printf("\t\t\t\t\t                  Appuyez sur 'ENTRER' pour revenir au menu principal.\n");


                c=getch();
                if(c==-32)
                {
                    c=getch();
                    if(c==77)
                    {
                        if(e>=buf.nb)
                        {
                            i=buf.lien;
                            cpt++;
                            ets=ets+2;
                            if(i==-1)
                            {
                                i=Entete(F,1);
                                cpt=1;
                                ets=1;
                            }
                            LireDir(F,i,&buf);
                            e=2;
                        }
                        else
                        {
                            e=e+2;
                            cpt++;
                            ets=ets+2;
                        }

                    }
                    else
                    {

                        if(c==75)
                        {
                            if(e<=2)
                            {
                                i++;
                                cpt--;
                                ets=ets-2;
                                if(i==Entete(F,1)+1)
                                {
                                    i=1;
                                    cpt=max/2;
                                    ets=max-1;
                                }
                                LireDir(F,i,&buf);
                                nb_lect++;
                                e=buf.nb;
                            }
                            else
                            {
                                e=e-2;
                                cpt--;
                                ets=ets-2;
                            }

                        }
                    }

            }
            else
            {
                if(c==13)
                {
                    stop=true;
                }
            }
        }
    }
    else
    {
        i=1;
        LireDir(F,i,&buf);
        nb_lect++;

            cpt=1;
            e=2;
            while(stop==false)
            {
                system("cls");
                if(e==1)
                {
                    e=2;
                }
                if((i==Entete(F,1))&&(e>=buf.nb))
                {
                        textcolor(WHITE);printf("\n+-------------------------+\n");
                        textcolor(WHITE);printf("|    Enseignant  %-6d   |\n",ets);
                        textcolor(WHITE);printf("+-------------------------+-----------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                |\n");
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",buf.Tab[buf.nb-1].Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-107ld|\n",buf.Tab[buf.nb-1].Matricule);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",buf.Tab[buf.nb-1].Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-101s|\n",buf.Tab[buf.nb-1].Dernier_Diplome);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",buf.Tab[buf.nb-1].Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-106s|\n",buf.Tab[buf.nb-1].Specialite);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",buf.Tab[buf.nb-1].Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-111s|\n",buf.Tab[buf.nb-1].Grade);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",buf.Tab[buf.nb-1].Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                       |\n",buf.Tab[buf.nb-1].Date_Recrutement.Day,buf.Tab[buf.nb-1].Date_Recrutement.Month,buf.Tab[buf.nb-1].Date_Recrutement.Year);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",buf.Tab[buf.nb-1].Date_Naissance.Day,buf.Tab[buf.nb-1].Date_Naissance.Month,buf.Tab[buf.nb-1].Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-103s|\n",buf.Tab[buf.nb-1].Ets.Nom);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                                      }
                else
                {
                    for(j=e-2;j<e;j++)
                    {
                        textcolor(WHITE);printf("\n+-------------------------+\n");
                        if(j==e-2)
                        {
                            textcolor(WHITE);printf("|    Enseignant  %-6d   |\n",ets);
                        }
                        else
                        {
                            textcolor(WHITE);printf("|    Enseignant  %-6d   |\n",ets+1);
                        }
                        textcolor(WHITE);printf("+-------------------------+-----------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("|         ");textcolor(YELLOW);printf("Informations personnelles");textcolor(WHITE);printf("         |                                            ");textcolor(LIGHTCYAN);printf("Informations professionnelles");textcolor(WHITE);printf("                                                |\n");
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Nom");textcolor(WHITE);printf(" : %-30s      |  ",buf.Tab[j].Nom);textcolor(LIGHTCYAN);printf("Matricule");textcolor(WHITE);printf(" : %-107ld|\n",buf.Tab[j].Matricule);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Pr%cnom",130);textcolor(WHITE);printf(" : %-30s   |  ",buf.Tab[j].Prenom);textcolor(LIGHTCYAN);printf("Dernier dipl%cme",147);textcolor(WHITE);printf(" : %-101s|\n",buf.Tab[j].Dernier_Diplome);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Sexe");textcolor(WHITE);printf(" : %-29s      |  ",buf.Tab[j].Sexe);textcolor(LIGHTCYAN);printf("Sp%ccialit%c",130,130);textcolor(WHITE);printf(" : %-106s|\n",buf.Tab[j].Specialite);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Groupe sanguin");textcolor(WHITE);printf(" : %-25s|  ",buf.Tab[j].Groupe_Sanguin);textcolor(LIGHTCYAN);printf("Grade");textcolor(WHITE);printf(" : %-111s|\n",buf.Tab[j].Grade);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Wilaya de naissance");textcolor(WHITE);printf(" : %-20s|  ",buf.Tab[j].Wilaya_Naissance);textcolor(LIGHTCYAN);printf("Date de recrutement");textcolor(WHITE);printf(" : %-2d/%-2d/%-4d                                                                                       |\n",buf.Tab[j].Date_Recrutement.Day,buf.Tab[j].Date_Recrutement.Month,buf.Tab[j].Date_Recrutement.Year);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                        printf("| ");textcolor(YELLOW);printf("Date de naissance");textcolor(WHITE);printf("  : %-2d/%-2d/%-4d           |  ",buf.Tab[j].Date_Naissance.Day,buf.Tab[j].Date_Naissance.Month,buf.Tab[j].Date_Naissance.Year);textcolor(LIGHTCYAN);printf("%ctablissement",144);textcolor(WHITE);printf(" : %-103s|\n",buf.Tab[j].Ets.Nom);
                        textcolor(WHITE);printf("+-------------------------------------------+-------------------------------------------------------------------------------------------------------------------------+\n");
                     }
                    printf("\n\n\n\t\t\t\t\t\t\t\t\t      <  Page %d  >\n\n",cpt);
                }
                textcolor(YELLOW);
                printf("\t\t\t\t\t    Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour basculer entre les pages.\n\n");
                textcolor(WHITE);
                printf("\t\t\t\t\t                  Appuyez sur 'ENTRER' pour revenir au menu principal.\n");






                c=getch();
                if(c==-32)
                {
                    c=getch();
                    if(c==77)
                    {
                        if(e>=buf.nb)
                        {
                            i++;
                            e=2;
                            cpt++;
                            ets=ets+2;
                            if(i==Entete(F,1)+1)
                            {
                                i=1;
                                cpt=1;
                                ets=1;
                            }
                            LireDir(F,i,&buf);
                            nb_lect++;
                        }
                        else
                        {
                            e=e+2;
                            cpt++;
                            ets=ets+2;
                        }

                    }
                    else
                    {

                        if(c==75)
                        {
                            if(e<=2)
                            {
                                i=buf.lien;
                                cpt--;
                                ets=ets-2;
                                if(i==-1)
                                {
                                    i=Entete(F,1);
                                    cpt=max/2+1;
                                    ets=max;
                                }
                                LireDir(F,i,&buf);
                                nb_lect++;
                                e=buf.nb;
                            }
                            else
                            {
                                e=e-2;
                                cpt--;
                                ets=ets-2;
                            }

                        }
                    }

            }
            else
            {
                if(c==13)
                {
                    stop=true;
                }
            }

        }
    }

    Fermer(&F);
}

void Affich_Ajout_ENS()
{
    bool continu=true;
    char c=92;
    int day,month,year;
    char Specialite [50][80] = {"Informatique","Biologie","Geologie","Medecine","Pharmacie","Chirurgie Dentaire",

    "Science de la vie et de la nature","Science Islamique","Science Politique","Science Economique",

    "Science Humaine et Sociale","Science de la Matiere","Genie des Procedes","Genie Civil","Genie Mecanique",

    "Genie Electrique","Architecture","Droit","Mathematiques","Philosophie","Literature et Langues",

    "Archeologie","Aeronautique","Education physique et sportive","Hydraulique","Traduction",

    "Science de la communication et des medias","Science Agronomique","Veterinaire","Genie industriel"};


    char Groupe_Sanguin [10][5] = {"O+","A+","B+","O-","A-","AB+","B-","AB-"};
    char Grade [10][50] = {"Professeur(e)","Maitre de conferences Rang A","Maitre de conferences Rang B","Maitre Assistant(e) Rang A","Maitre Assistant(e) Rang B","Assistant(e)"};
    char Dernier_Diplome [10][50] = {"Doctorat d'Etat","Doctorat en sciences","Doctorat D-LMD","PhD","Habilitation Universitaire","Magistere"};
    TEnseignant ENS;
    int code,pos;
    bool trouv;
    datier(&day,&month,&year);
    system("cls");
    do{
            ENS.Matricule = Aleatoire(111,999)*1000+Aleatoire(111,999);
            Recherche_Index_Primaire(ENS.Matricule,&trouv,&pos);
    }
    while (trouv == true);
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    fflush(stdin);
    gotoxy(32,12);gets(ENS.Nom);
    fflush(stdin);
    gotoxy(32,14);gets(ENS.Prenom);

fvr: age: gotoxy(40,16);scanf("%d",&ENS.Date_Naissance.Day);
    if(continu==false)
    {
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    }
    while((ENS.Date_Naissance.Day<1)||(ENS.Date_Naissance.Day>31))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, Le jour doit %ctre compris entre 1 et 31.\n",136);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        if(continu==false)
        {
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        }
        gotoxy(40,16);scanf("%d",&ENS.Date_Naissance.Day);
    }
    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    if(continu==false)
    {
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    }
    gotoxy(40,18);scanf("%d",&ENS.Date_Naissance.Month);
    while((ENS.Date_Naissance.Month<1)||(ENS.Date_Naissance.Month>12))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, Le mois doit %ctre compris entre 1 et 12.\n",136);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        if(continu==false)
        {
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        }
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);scanf("%d",&ENS.Date_Naissance.Month);
    }
    if((ENS.Date_Naissance.Month==2)&&(ENS.Date_Naissance.Day>29))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, le mois de F%cvrier contient au maximum 29 jours.\n",130);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        if(continu==false)
        {
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        }

        goto fvr;
    }
    if((NumberOfDays(ENS.Date_Naissance.Month,2022)<ENS.Date_Naissance.Day)&&(ENS.Date_Naissance.Month!=2))
    {
            system("cls");
            aff();
            textcolor(LIGHTRED);
            printf("\n\t\t\t\t\t\t    Erreur, le jour choisi est incompatible avec le mois choisi.\n");
            textcolor(WHITE);
            gotoxy(32,10);printf("%ld",ENS.Matricule);
            gotoxy(32,12);printf("%s",ENS.Nom);
            gotoxy(32,14);printf("%s",ENS.Prenom);
            if(continu==false)
            {
                gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
                gotoxy(32,24);printf("%s",ENS.Sexe);
                gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
                gotoxy(32,28);printf("%s",ENS.Grade);
                gotoxy(32,30);printf("%s",ENS.Specialite);
                gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
            }

            goto fvr;
    }

    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    if(continu==false)
    {
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    }
    gotoxy(40,20);scanf("%d",&ENS.Date_Naissance.Year);
    while((ENS.Date_Naissance.Year<(year-70))||(ENS.Date_Naissance.Year>(year-23)))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, l'ann%ce doit %ctre comprise entre %d et %d.\n",130,136,year-70,year-23);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        if(continu==false)
        {
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        }
        gotoxy(40,20);scanf("%d",&ENS.Date_Naissance.Year);
    }
    if((ENS.Date_Naissance.Month==2)&&(ENS.Date_Naissance.Day>NumberOfDays(2,ENS.Date_Naissance.Year)))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        //textbackground(15);
        printf("\n\t\t\t\t\t    Erreur, le nombre de jours du mois de F%cvrier de l'ann%ce %d est de %d.\n",130,130,ENS.Date_Naissance.Year,NumberOfDays(2,ENS.Date_Naissance.Year));
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        if(continu==false)
        {
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        }
        goto fvr;
    }
    if(continu==true)
    {
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);

        gotoxy(32,22);delay(1000);//getch();
        system("cls");
        Aff_Wilayas();
        printf("\n        Veuillez introduire le code de la wilaya: ");
        textcolor(LIGHTGREEN);
        scanf("%d",&code);
        textcolor(WHITE);
        while((code<1)||(code>58))
        {
            system("cls");
            Aff_Wilayas();
            textcolor(LIGHTRED);
            printf("\t\t\t\t\tErreur. Code invalide, veuillez introduire un autre compris entre 1 et 58.\n\n");
            textcolor(WHITE);
            printf("       Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&code);
            textcolor(WHITE);
        }
        strcpy(ENS.Wilaya_Naissance,Tab_Wilayas[code-1]);
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",ENS.Wilaya_Naissance);
        gotoxy(32,24);delay(1000);
        system("cls");
        textcolor(LIGHTCYAN);
        printf("       _____                \n");
        printf("      / ____|               \n");
        printf("     | (___   ___  __  __  ___  \n");
        printf("      %c___ %c / _ %c %c %c/ / / _ %c \n",c,c,c,c,c,c);
        printf("      ____) |  __/  >  < |  __/ \n");
        printf("     |_____/ %c___| /_/%c_%c %c___| \n\n",c,c,c,c);
        textcolor(WHITE);

        printf("     +------+-----------------------------------+\n");
        printf("     | Code |                 Sexe              |\n");
        printf("     +------+-----------------------------------+\n");
        printf("     |  1   |               Masculin            |\n");
        printf("     +------+-----------------------------------+\n");
        printf("     |  2   |               Feminin             |\n");
        printf("     +------+-----------------------------------+\n\n");
        int sexe;
        printf("     Veuillez introduire le code du sexe: ");
        textcolor(LIGHTGREEN);
        scanf("%d",&sexe);
        textcolor(WHITE);
        while((sexe<1)||(sexe>2))
        {
            system("cls");
            textcolor(LIGHTCYAN);
            printf("       _____                \n");
            printf("      / ____|               \n");
            printf("     | (___   _____  _____  \n");
            printf("      %c___ %c / _ %c %c/ / _ %c \n",c,c,c,c,c);
            printf("      ____) |  __/>  <  __/ \n");
            printf("     |_____/ %c___/_/%c_%c___| \n\n",c,c,c);
            textcolor(WHITE);
            printf("     +------+-----------------------------------+\n");
            printf("     | Code |                 Sexe              |\n");
            printf("     +------+-----------------------------------+\n");
            printf("     |  1   |               Masculin            |\n");
            printf("     +------+-----------------------------------+\n");
            printf("     |  2   |               Feminin             |\n");
            printf("     +------+-----------------------------------+\n\n");
            textcolor(LIGHTRED);
            printf("     Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 2.\n\n");
            textcolor(WHITE);
            printf("     Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&sexe);
            textcolor(WHITE);
        }
        if(sexe==1)
        {
            strcpy(ENS.Sexe,"Masculin");
        }
        else
        {
            strcpy(ENS.Sexe,"Feminin");
        }
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);delay(1000);
        system("cls");

        textcolor(LIGHTCYAN);
        printf("       _____                                                          _         \n");
        printf("      / ____|                                                        (_)        \n");
        printf("     | |  __ _ __ ___  _   _ _ __   ___    ___  __ _ _ __   __ _ _   _ _ _ __   \n");
        printf("     | | |_ | '__/ _ %c| | | | '_ %c / _ %c  / __|/ _` | '_ %c / _` | | | | | '_ %c  \n",c,c,c,c,c);
        printf("     | |__| | | | (_) | |_| | |_) |  __/  %c__ %c (_| | | | | (_| | |_| | | | | | \n",c,c);
        printf("      %c_____|_|  %c___/ %c__,_| .__/ %c___|  |___/%c__,_|_| |_|%c__, |%c__,__|_|_| |_| \n",c,c,c,c,c,c,c);
        printf("                            | |                            __/ |                \n");
        printf("                            |_|                           |___/                 \n");
        textcolor(WHITE);
        printf("     +------+----------------------------------+------+----------------------------------+\n");
        printf("     | Code |          Groupe sanguin          | Code |          Groupe sanguin          |\n");
        printf("     +------+----------------------------------+------+----------------------------------+\n");
        printf("     |  1   |                O+                |  2   |                A+                |\n");
        printf("     +------+----------------------------------+------+----------------------------------+\n");
        printf("     |  3   |                B+                |  4   |                O-                |\n");
        printf("     +------+----------------------------------+------+----------------------------------+\n");
        printf("     |  5   |                A-                |  6   |                AB+               |\n");
        printf("     +------+----------------------------------+------+----------------------------------+\n");
        printf("     |  7   |                B-                |  8   |                AB-               |\n");
        printf("     +------+----------------------------------+------+----------------------------------+\n\n");

        int gs;
        printf("     Veuillez introduire le code du groupe sanguin: ");
        textcolor(LIGHTGREEN);
        scanf("%d",&gs);
        textcolor(WHITE);
        while((gs<1)||(gs>8))
        {
            system("cls");
            textcolor(LIGHTCYAN);
            printf("       _____                                                          _         \n");
            printf("      / ____|                                                        (_)        \n");
            printf("     | |  __ _ __ ___  _   _ _ __   ___    ___  __ _ _ __   __ _ _   _ _ _ __   \n");
            printf("     | | |_ | '__/ _ %c| | | | '_ %c / _ %c  / __|/ _` | '_ %c / _` | | | | | '_ %c  \n",c,c,c,c,c);
            printf("     | |__| | | | (_) | |_| | |_) |  __/  %c__ %c (_| | | | | (_| | |_| | | | | | \n",c,c);
            printf("      %c_____|_|  %c___/ %c__,_| .__/ %c___|  |___/%c__,_|_| |_|%c__, |%c__,__|_|_| |_| \n",c,c,c,c,c,c,c);
            printf("                            | |                            __/ |                \n");
            printf("                            |_|                           |___/                 \n");
            textcolor(WHITE);
            printf("     +------+----------------------------------+------+----------------------------------+\n");
            printf("     | Code |          Groupe sanguin          | Code |          Groupe sanguin          |\n");
            printf("     +------+----------------------------------+------+----------------------------------+\n");
            printf("     |  1   |                O+                |  2   |                A+                |\n");
            printf("     +------+----------------------------------+------+----------------------------------+\n");
            printf("     |  3   |                B+                |  4   |                O-                |\n");
            printf("     +------+----------------------------------+------+----------------------------------+\n");
            printf("     |  5   |                A-                |  6   |                AB+               |\n");
            printf("     +------+----------------------------------+------+----------------------------------+\n");
            printf("     |  7   |                B-                |  8   |                AB-               |\n");
            printf("     +------+----------------------------------+------+----------------------------------+\n\n");
            textcolor(LIGHTRED);
            printf("     Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 8.\n\n");
            textcolor(WHITE);
            printf("     Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&gs);
            textcolor(WHITE);
        }
        strcpy(ENS.Groupe_Sanguin,Groupe_Sanguin[gs-1]);
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28); delay(1000);
        system("cls");
        textcolor(LIGHTCYAN);
        printf("       _____               _        \n");
        printf("      / ____|             | |       \n");
        printf("     | |  __ _ __ __ _  __| | ___   \n");
        printf("     | | |_ | '__/ _` |/ _` |/ _ %c  \n",c);
        printf("     | |__| | | | (_| | (_| |  __/  \n");
        printf("      %c_____|_|  %c__,_|%c__,_|%c___|  \n\n",c,c,c,c);
        textcolor(WHITE);
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     | Code |              Grade             | Code |              Grade             |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  1   |           Professeur(e)        |  2   |  Maitre de conferences Rang A  |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  3   |  Maitre de conferences Rang B  |  4   |   Maitre Assistant(e) Rang A   |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  5   |   Maitre Assistant(e) Rang B   |  6   |           Assistant(e)         |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n\n");
        textcolor(WHITE);
        int grade;
        printf("     Veuillez introduire le code du grade: ");
        textcolor(LIGHTGREEN);
        scanf("%d",&grade);
        textcolor(WHITE);
        while((grade<1)||(grade>6))
        {
            system("cls");
            textcolor(LIGHTCYAN);
            printf("       _____               _        \n");
            printf("      / ____|             | |       \n");
            printf("     | |  __ _ __ __ _  __| | ___   \n");
            printf("     | | |_ | '__/ _` |/ _` |/ _ %c  \n",c);
            printf("     | |__| | | | (_| | (_| |  __/  \n");
            printf("      %c_____|_|  %c__,_|%c__,_|%c___|  \n\n",c,c,c,c);
            textcolor(WHITE);
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     | Code |              Grade             | Code |              Grade             |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  1   |           Professeur(e)        |  2   |  Maitre de conferences Rang A  |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  3   |  Maitre de conferences Rang B  |  4   |   Maitre Assistant(e) Rang A   |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  5   |   Maitre Assistant(e) Rang B   |  6   |           Assistant(e)         |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n\n");
            textcolor(LIGHTRED);
            printf("     Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 6.\n\n");
            textcolor(WHITE);
            printf("     Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&grade);
            textcolor(WHITE);
        }
        strcpy(ENS.Grade,Grade[grade-1]);
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);delay(1000);

        system("cls");
        Aff_Specialite();
        int special;
        printf("\n                 Veuillez introduire le code de la sp%ccialit%c: ",130,130);
        textcolor(LIGHTGREEN);
        scanf("%d",&special);
        textcolor(WHITE);
        while((special<1)||(special>30))
        {
            system("cls");
            Aff_Specialite();
            textcolor(LIGHTRED);
            printf("\n                                              Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 30.\n\n");
            textcolor(WHITE);
            printf("                 Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&special);
            textcolor(WHITE);
        }
        strcpy(ENS.Specialite,Specialite[special-1]);
        system("cls");
        aff();
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);delay(1000);

        system("cls");
        textcolor(LIGHTCYAN);
        printf("      _____                  _                 _ _       _                       \n");
        printf("     |  __ %c                (_)               | (_)     | |                      \n",c);
        printf("     | |  | | ___ _ __ _ __  _  ___ _ __    __| |_ _ __ | | ___  _ __ ___   ___  \n");
        printf("     | |  | |/ _ %c '__| '_ %c| |/ _ %c '__|  / _` | | '_ %c| |/ _ %c| '_ ` _ %c / _ %c \n",c,c,c,c,c,c,c);
        printf("     | |__| |  __/ |  | | | | |  __/ |    | (_| | | |_) | | (_) | | | | | |  __/ \n");
        printf("     |_____/ %c___|_|  |_| |_|_|%c___|_|     %c__,_|_| .__/|_|%c___/|_| |_| |_|%c___| \n",c,c,c,c,c);
        printf("                                                  | |                            \n");
        printf("                                                  |_|                            \n");
        textcolor(WHITE);
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     | Code |         Dernier dipl%cme        | Code |         Dernier dipl%cme        |\n",147,147);
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  1   |         Doctorat d'Etat        |  2   |       Doctorat en sciences     |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  3   |         Doctorat D-LMD         |  4   |               PhD              |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n");
        printf("     |  5   |    Habilitation Universitaire  |  6   |            Magistere           |\n");
        printf("     +------+--------------------------------+------+--------------------------------+\n\n");
        int dp;
        printf("     Veuillez introduire le code du dipl%cme: ",147);
        textcolor(LIGHTGREEN);
        scanf("%d",&dp);
        textcolor(WHITE);
        while((dp<1)||(dp>6))
        {
            system("cls");
            textcolor(LIGHTCYAN);
            printf("      _____                  _                 _ _       _                       \n");
            printf("     |  __ %c                (_)               | (_)     | |                      \n",c);
            printf("     | |  | | ___ _ __ _ __  _  ___ _ __    __| |_ _ __ | | ___  _ __ ___   ___  \n");
            printf("     | |  | |/ _ %c '__| '_ %c| |/ _ %c '__|  / _` | | '_ %c| |/ _ %c| '_ ` _ %c / _ %c \n",c,c,c,c,c,c,c);
            printf("     | |__| |  __/ |  | | | | |  __/ |    | (_| | | |_) | | (_) | | | | | |  __/ \n");
            printf("     |_____/ %c___|_|  |_| |_|_|%c___|_|     %c__,_|_| .__/|_|%c___/|_| |_| |_|%c___| \n",c,c,c,c,c);
            printf("                                                  | |                            \n");
            printf("                                                  |_|                            \n");
            textcolor(WHITE);
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     | Code |         Dernier dipl%cme        | Code |         Dernier dipl%cme        |\n",147,147);
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  1   |         Doctorat d'Etat        |  2   |       Doctorat en sciences     |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  3   |         Doctorat D-LMD         |  4   |               PhD              |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n");
            printf("     |  5   |    Habilitation Universitaire  |  6   |            Magistere           |\n");
            printf("     +------+--------------------------------+------+--------------------------------+\n\n");
            textcolor(LIGHTRED);
            printf("     Erreur. Code invalide, veuillez introduire un autre compris entre 1 et 6.\n\n");
            textcolor(WHITE);
            printf("     Veuillez r%cintroduire le code: ",130);
            textcolor(LIGHTGREEN);
            scanf("%d",&dp);
            textcolor(WHITE);
        }
        strcpy(ENS.Dernier_Diplome,Dernier_Diplome[dp-1]);
    }

    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
    gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
    gotoxy(32,24);printf("%s",ENS.Sexe);
    gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
    gotoxy(32,28);printf("%s",ENS.Grade);
    gotoxy(32,30);printf("%s",ENS.Specialite);
    gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
fvr2: gotoxy(40,34);scanf("%d",&ENS.Date_Recrutement.Day);
    while((ENS.Date_Recrutement.Day<1)||(ENS.Date_Recrutement.Day>31))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, le jour doit %ctre compris entre 1 et 31.\n",136);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        gotoxy(40,34);scanf("%d",&ENS.Date_Recrutement.Day);
    }
    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
    gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
    gotoxy(32,24);printf("%s",ENS.Sexe);
    gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
    gotoxy(32,28);printf("%s",ENS.Grade);
    gotoxy(32,30);printf("%s",ENS.Specialite);
    gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
    gotoxy(40,36);scanf("%d",&ENS.Date_Recrutement.Month);
    while((ENS.Date_Recrutement.Month<1)||(ENS.Date_Recrutement.Month>12))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, le mois doit %ctre compris entre 1 et 12.\n",136);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
        gotoxy(40,36);scanf("%d",&ENS.Date_Recrutement.Month);
    }
    if((ENS.Date_Recrutement.Month==2)&&(ENS.Date_Recrutement.Day>29))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, le mois de F%cvrier contient au maximum 29 jours.\n",130);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        goto fvr2;
    }
    if((NumberOfDays(ENS.Date_Recrutement.Month,2022)<ENS.Date_Recrutement.Day)&&(ENS.Date_Recrutement.Month!=2))
    {
            system("cls");
            aff();
            textcolor(LIGHTRED);
            printf("\n\t\t\t\t\t\t    Erreur, le jour choisi est incompatible avec le mois choisi.\n");
            textcolor(WHITE);
            gotoxy(32,10);printf("%ld",ENS.Matricule);
            gotoxy(32,12);printf("%s",ENS.Nom);
            gotoxy(32,14);printf("%s",ENS.Prenom);
            gotoxy(32,10);printf("%ld",ENS.Matricule);
            gotoxy(32,12);printf("%s",ENS.Nom);
            gotoxy(32,14);printf("%s",ENS.Prenom);
            gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
            gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
            gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
            gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
            gotoxy(32,24);printf("%s",ENS.Sexe);
            gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
            gotoxy(32,28);printf("%s",ENS.Grade);
            gotoxy(32,30);printf("%s",ENS.Specialite);
            gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);

            goto fvr2;
    }

    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
    gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
    gotoxy(32,24);printf("%s",ENS.Sexe);
    gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
    gotoxy(32,28);printf("%s",ENS.Grade);
    gotoxy(32,30);printf("%s",ENS.Specialite);
    gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
    gotoxy(40,36);printf("%d",ENS.Date_Recrutement.Month);
    gotoxy(40,38);scanf("%d",&ENS.Date_Recrutement.Year);
    while((ENS.Date_Recrutement.Year<(year-47))||(ENS.Date_Recrutement.Year>year))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, l'ann%ce doit %ctre comprise entre %d et %d.\n",130,136,(year-47),year);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
        gotoxy(40,36);printf("%d",ENS.Date_Recrutement.Month);
        gotoxy(40,38);scanf("%d",&ENS.Date_Recrutement.Year);
    }
    if((ENS.Date_Recrutement.Month==2)&&(ENS.Date_Recrutement.Day>NumberOfDays(2,ENS.Date_Recrutement.Year)))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t    Erreur, le nombre de jours du mois de F%cvrier de l'ann%ce %d est de %d.\n",130,130,ENS.Date_Recrutement.Year,NumberOfDays(2,ENS.Date_Recrutement.Year));
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);

        goto fvr2;
    }
    if((ENS.Date_Recrutement.Year*10000+ENS.Date_Recrutement.Month*100+ENS.Date_Recrutement.Day)>(year*10000+month*100+day))
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, la date choisie est invalide. \n");
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
        gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
        gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);

        goto fvr2;;
    }
    if(ENS.Date_Recrutement.Year-ENS.Date_Naissance.Year<23)
    {
        system("cls");
        aff();
        textcolor(LIGHTRED);
        printf("\n\t\t\t\t\t\t    Erreur, l'%cge minimum de l'enseignant est 23 ans.\n",131);
        textcolor(WHITE);
        gotoxy(32,10);printf("%ld",ENS.Matricule);
        gotoxy(32,12);printf("%s",ENS.Nom);
        gotoxy(32,14);printf("%s",ENS.Prenom);
        gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
        gotoxy(32,24);printf("%s",ENS.Sexe);
        gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
        gotoxy(32,28);printf("%s",ENS.Grade);
        gotoxy(32,30);printf("%s",ENS.Specialite);
        gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
        continu=false;
        goto age;
    }
    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
    gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
    gotoxy(32,24);printf("%s",ENS.Sexe);
    gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
    gotoxy(32,28);printf("%s",ENS.Grade);
    gotoxy(32,30);printf("%s",ENS.Specialite);
    gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
    gotoxy(40,36);printf("%d",ENS.Date_Recrutement.Month);
    gotoxy(40,38);printf("%d",ENS.Date_Recrutement.Year);
    gotoxy(32,40);delay(1000);
    system("cls");
    int ets;
    Affich_Tab_Ets(&ets);
    ENS.Ets=Tab_ETS[ets-1];
    system("cls");
    aff();
    gotoxy(32,10);printf("%ld",ENS.Matricule);
    gotoxy(32,12);printf("%s",ENS.Nom);
    gotoxy(32,14);printf("%s",ENS.Prenom);
    gotoxy(40,16);printf("%d",ENS.Date_Naissance.Day);
    gotoxy(40,18);printf("%d",ENS.Date_Naissance.Month);
    gotoxy(40,20);printf("%d",ENS.Date_Naissance.Year);
    gotoxy(32,22);printf("%s",Tab_Wilayas[code-1]);
    gotoxy(32,24);printf("%s",ENS.Sexe);
    gotoxy(32,26);printf("%s",ENS.Groupe_Sanguin);
    gotoxy(32,28);printf("%s",ENS.Grade);
    gotoxy(32,30);printf("%s",ENS.Specialite);
    gotoxy(32,32);printf("%s",ENS.Dernier_Diplome);
    gotoxy(40,34);printf("%d",ENS.Date_Recrutement.Day);
    gotoxy(40,36);printf("%d",ENS.Date_Recrutement.Month);
    gotoxy(40,38);printf("%d",ENS.Date_Recrutement.Year);
    gotoxy(32,40);printf("%s",ENS.Ets.Nom);
    textbackground(RED);
    printf("\n\n\n\t\t\t\t\t\tEtes-vous s%cr de vouloir ajouter cet enseignant ?\n",150);
    textbackground(BLACK);
    char Choix[3][10] = {"-> Oui","-> Non"};
    textcolor(YELLOW);
    printf("\n          Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(36,47);
    printf("%s",Choix[0]);
    gotoxy(106,47);
    textbackground(BLACK);
    printf("%s",Choix[1]);
    int i;
    i=0;
    continu = true;
    while (continu){

            c = getch();

            switch(c){

                case -32:

                        c = getch();

                        if (c==77){

                            if (i==0){

                                textbackground(BLACK);
                                gotoxy(36,47);
                                printf("%s",Choix[0]);
                                textbackground(BLUE);
                                gotoxy(106,47);
                                printf("%s",Choix[1]);
                                i++;
                                textbackground(BLACK);

                            }
                            else{

                                textbackground(BLACK);
                                gotoxy(106,47);
                                printf("%s",Choix[1]);
                                textbackground(BLUE);
                                gotoxy(36,47);
                                printf("%s",Choix[0]);
                                i = 0;
                                textbackground(BLACK);

                            }

                        }
                        if(c==75) {

                            if (i==1){

                                textbackground(BLUE);
                                gotoxy(36,47);
                                printf("%s",Choix[0]);
                                textbackground(BLACK);
                                gotoxy(106,47);
                                printf("%s",Choix[1]);
                                i--;

                            }
                            else{

                                textbackground(BLACK);
                                gotoxy(36,47);
                                printf("%s",Choix[0]);
                                textbackground(BLUE);
                                gotoxy(106,47);
                                printf("%s",Choix[1]);
                                i=1;
                                textbackground(BLACK);


                            }


                        }

                        break;

                case 13:

                        continu = false;

                        break;

                default:

                        break;

            }
    }
    if(i==0)
    {
        Ajout_ENS(ENS);
        textbackground(BLACK);
        textcolor(LIGHTGREEN);
        printf("\n\n\t\t\t\t\t\t\t   Donn%ce inser%ce avec succ%cs!\n",130,130,138);
    }
    textcolor(WHITE);
    printf("\n\n\t\t\t\t\t     Appuyez sur une touche pour revenir au menu principal.\n");
    fflush(stdin);
    getch();
}

void Affich_Modification_ENS()
{
    long int matricule;
    bool trouv;
    int k;
re: textcolor(LIGHTCYAN);
    printf("\n\t\t\t      __  __           _ _  __ _           _   _                  ______                _                         _     \n");
    printf("\t\t\t     |  %c/  |         | (_)/ _(_)         | | (_)                |  ____|              (_)                       | |   \n",92);
    printf("\t\t\t     | %c  / | ___   __| |_| |_ _  ___ __ _| |_ _  ___  _ __      | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_  \n",92);
    printf("\t\t\t     | |%c/| |/ _ %c / _` | |  _| |/ __/ _` | __| |/ _ %c| '_ %c     |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __| \n",92,92,92,92,92,92,92,92);
    printf("\t\t\t     | |  | | (_) | (_| | | | | | (_| (_| | |_| | (_) | | | |    | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_  \n",92,92);
    printf("\t\t\t     |_|  |_|%c___/ %c__,_|_|_| |_|%c___%c__,_|%c__|_|%c___/|_| |_|    |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__| \n",92,92,92,92,92,92,92,92,92,92);
    printf("\t\t\t                                                                                           __/ |                       \n");
    printf("\t\t\t                                                                                          |___/                       \n\n");
    textcolor(WHITE);
    printf("\t\t\t\t   Veuillez introduire le matricule de l'enseignant %c qui vous souhaiterez changer d'%ctablissement: ",133,130);
    textcolor(LIGHTGREEN);
    scanf("%ld",&matricule);
    textcolor(WHITE);
    Recherche_Index_Primaire(matricule,&trouv,&k);
    if(trouv==true)
    {
        system("cls");
        int code;
        Affich_Tab_Ets(&code);
        system("cls");
        textcolor(LIGHTCYAN);
        printf("\n\t\t\t      __  __           _ _  __ _           _   _                  ______                _                         _     \n");
        printf("\t\t\t     |  %c/  |         | (_)/ _(_)         | | (_)                |  ____|              (_)                       | |   \n",92);
        printf("\t\t\t     | %c  / | ___   __| |_| |_ _  ___ __ _| |_ _  ___  _ __      | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_  \n",92);
        printf("\t\t\t     | |%c/| |/ _ %c / _` | |  _| |/ __/ _` | __| |/ _ %c| '_ %c     |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __| \n",92,92,92,92,92,92,92,92);
        printf("\t\t\t     | |  | | (_) | (_| | | | | | (_| (_| | |_| | (_) | | | |    | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_  \n",92,92);
        printf("\t\t\t     |_|  |_|%c___/ %c__,_|_|_| |_|%c___%c__,_|%c__|_|%c___/|_| |_|    |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__| \n",92,92,92,92,92,92,92,92,92,92);
        printf("\t\t\t                                                                                           __/ |                       \n");
        printf("\t\t\t                                                                                          |___/                       \n\n");
        textcolor(WHITE);
        printf("\n Voici toutes les informaions de l'enseignant qui correspond au matricule ");textcolor(LIGHTGREEN);printf("%ld",matricule);textcolor(WHITE);printf(":\n");
        affich_eng(TabIndex[k].Num_Bloc,TabIndex[k].Depl);
        printf("\n\t\t  Etes-vous s%cr de vouloir changer l'%ctablissement actuel de l'enseignant correspondant au matricule %ld avec l'%ctablissement:\n\n",150,130,matricule,130);
        printf("\t\t  %ctablissement :",144);textcolor(LIGHTGREEN);printf("   %-104s \n",Tab_ETS[code-1].Nom);
        textcolor(WHITE);
        char Choix[3][10] = {"-> Oui","-> Non"};
        textcolor(YELLOW);
        gotoxy(26,35);
        printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
        textcolor(WHITE);
        textbackground(BLUE);
        gotoxy(30,37);
        printf("%s",Choix[0]);
        gotoxy(134,37);
        textbackground(BLACK);
        printf("%s",Choix[1]);
        char c;
        int i=0;
        bool continu = true;
        while (continu){

                c = getch();

                 switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(30,37);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,37);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(134,37);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(30,37);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if(c==75) {

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(30,37);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(134,37);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(30,37);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,37);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }

        }
        textbackground(BLACK);
        if(i==0)
        {
            Modification_ENS(matricule,code);
            textcolor(LIGHTGREEN);
            printf("\n\n\n\t\t\t\t\t\t\tLa modification de l'%ctablissement a %ct%c effectu%ce avec succ%cs!\n",130,130,130,130,138);
            textcolor(WHITE);
        }
    }
    else
    {
        textcolor(LIGHTRED);
        printf("\n\n\t\t\t\t\t\t\t\t        Erreur, matricule inexistant.\n\n\n");
        textcolor(WHITE);
        printf("\t\t\t\t\t\t\t       Voulez-vous r%cessayer avec un autre matricule ?",130);
        textcolor(WHITE);
        char Choix[3][10] = {"-> Oui","-> Non"};
        textcolor(YELLOW);
        gotoxy(26,20);
        printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
        textcolor(WHITE);
        textbackground(BLUE);
        gotoxy(30,23);
        printf("%s",Choix[0]);
        gotoxy(134,23);
        textbackground(BLACK);
        printf("%s",Choix[1]);
        char c;
        int i=0;
        bool continu = true;
        while (continu){

                c = getch();

                 switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(30,23);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,23);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(134,23);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(30,23);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if(c==75) {

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(30,23);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(134,23);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(30,23);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,23);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }

        }
        textbackground(BLACK);
        if(i==0)
        {
            system("cls");
            goto re;

        }
    }
    printf("\n\n\n\t\t\t\t\t\t\t    Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();
}

void Affich_Suppression_ENS()
{
    char c=92;
    long int Matricule;
    bool trouv;
    int k;
re: c=92;
    textcolor(LIGHTCYAN);
    printf("\n\t\t             _____                                     _                 ______                _                         _     \n");
    printf("\t\t            / ____|                                   (_)               |  ____|              (_)                       | |    \n");
    printf("\t\t           | (___  _   _ _ __  _ __  _ __ ___  ___ ___ _  ___  _ __     | |__   _ __  ___  ___ _  __ _ _ __   __ _ _ __ | |_   \n");
    printf("\t\t            %c___ %c| | | | '_ %c| '_ %c| '__/ _ %c/ __/ __| |/ _ %c| '_ %c    |  __| | '_ %c/ __|/ _ %c |/ _` | '_ %c / _` | '_ %c| __|  \n",c,c,c,c,c,c,c,c,c,c,c);
    printf("\t\t            ____) | |_| | |_) | |_) | | |  __/%c__ %c__ %c | (_) | | | |   | |____| | | %c__ %c  __/ | (_| | | | | (_| | | | | |_   \n",c,c,c,c,c);
    printf("\t\t           |_____/ %c__,_| .__/| .__/|_|  %c___||___/___/_|%c___/|_| |_|   |______|_| |_|___/%c___|_|%c__, |_| |_|%c__,_|_| |_|%c__|  \n",c,c,c,c,c,c,c);
    printf("\t\t                        | |   | |                                                                 __/ |                        \n");
    printf("\t\t                        |_|   |_|                                                                |___/                         \n\n\n");
    textcolor(WHITE);
    printf("\n\t\t\t\t\t   Veuillez introduire le matricule de l'enseignant que vous souhaiterez supprimer: ");
    textcolor(LIGHTGREEN);
    scanf("%ld",&Matricule);
    textcolor(WHITE);
    if((Matricule<111111)||(Matricule>999999))
    {
        textcolor(LIGHTRED);
        printf("\n\n\t\t\t\t\t\t\t\t       Erreur, matricule inexistant.\n\n\n");
        textcolor(WHITE);
        printf("\t\t\t\t\t\t\t      Voulez-vous r%cessayer avec un autre matricule ?",130);
        textcolor(WHITE);
        char Choix[3][10] = {"-> Oui","-> Non"};
        textcolor(YELLOW);
        gotoxy(22,22);
        printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
        textcolor(WHITE);
        textbackground(BLUE);
        gotoxy(30,25);
        printf("%s",Choix[0]);
        gotoxy(134,25);
        textbackground(BLACK);
        printf("%s",Choix[1]);
        int i;
        i=0;
        bool continu = true;
        while (continu){

                c = getch();

                switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if(c==75) {

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }

            }
            textbackground(BLACK);
            if(i==0)
            {
                system("cls");
                goto re;
            }
    }
    else
    {
        Recherche_Index_Primaire(Matricule,&trouv,&k);
        if(trouv==false)
        {
        textcolor(LIGHTRED);
        printf("\n\n\t\t\t\t\t\t\t\t       Erreur, matricule inexistant.\n\n\n");
        textcolor(WHITE);
        printf("\t\t\t\t\t\t\t      Voulez-vous r%cessayer avec un autre matricule ?",130);
        textcolor(WHITE);
        char Choix[3][10] = {"-> Oui","-> Non"};
        textcolor(YELLOW);
        gotoxy(22,22);
        printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
        textcolor(WHITE);
        textbackground(BLUE);
        gotoxy(30,25);
        printf("%s",Choix[0]);
        gotoxy(134,25);
        textbackground(BLACK);
        printf("%s",Choix[1]);
        int i;
        i=0;
        bool continu = true;
        while (continu){

                c = getch();

                switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if(c==75) {

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(30,25);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,25);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }

            }
            textbackground(BLACK);
            if(i==0)
            {
                system("cls");
                goto re;
            }

        }
        else
        {
            printf("\n\n Voici toutes les informaions de l'enseignant qui correspond au matricule ");textcolor(LIGHTGREEN);printf("%ld",Matricule);textcolor(WHITE);printf(":\n");
            affich_eng(TabIndex[k].Num_Bloc,TabIndex[k].Depl);
            printf("\n\n\t\t\t\t\t\t\t     ");
            textbackground(RED);
            printf("Etes-vous s%cr de vouloir supprimer cet enseignant ?",150);
            textbackground(BLACK);
            char Choix[3][10] = {"-> Oui","-> Non"};
            textcolor(YELLOW);
            gotoxy(26,38);
            printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appyuez sur 'Entrer' pour le valider.",130,130);
            textcolor(WHITE);
            textbackground(BLUE);
            gotoxy(30,40);
            printf("%s",Choix[0]);
            gotoxy(134,40);
            textbackground(BLACK);
            printf("%s",Choix[1]);
            int i;
            i=0;
            bool continu = true;
            while (continu){

                c = getch();

                 switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(30,40);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,40);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(134,40);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(30,40);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if(c==75) {

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(30,40);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(134,40);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(30,40);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(134,40);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }

            }
            textbackground(BLACK);
            if(i==0)
            {
                Suppression_ENS(Matricule);
                textcolor(LIGHTGREEN);
                printf("\n\n\n\t\t\t\t\t\t\t La suppression de l'enseignant a %ct%c eff%cctu%ce avec succ%cs!\n",130,130,130,130,138);
                textcolor(WHITE);
            }
        }
    }
    printf("\n\n\n\t\t\t\t\t\t\t    Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();
}

void Affich_Suppression_Specialite(){

    char Specialite [50][80] = {"Informatique","Biologie","Geologie","Medecine","Pharmacie","Chirurgie Dentaire",

    "Science de la vie et de la nature","Science Islamique","Science Politique","Science Economique",

    "Science Humaine et Sociale","Science de la Matiere","Genie des Procedes","Genie Civil","Genie Mecanique",

    "Genie Electrique","Architecture","Droit","Mathematiques","Philosophie","Literature et Langues",

    "Archeologie","Aeronautique","Education physique et sportive","Hydraulique","Traduction",

    "Science de la communication et des medias","Science Agronomique","Veterinaire","Genie industriel"};

    int n;

    textcolor(LIGHTCYAN);
    gotoxy(56,1);
    printf("  ___                              _                         _");
    gotoxy(56,2);
    printf(" / __|  _  _   _ __   _ __   _ _  (_)  _ __    ___   _ _    | |_   ___   _  _   ___");
    gotoxy(56,3);
    printf(" \\__ \\ | || | | '_ \\ | '_ \\ | '_| | | | '  \\  / -_) | '_|   |  _| / _ \\ | || | (_-<");
    gotoxy(56,4);
    printf(" |___/  \\_,_| | .__/ | .__/ |_|   |_| |_|_|_| \\___| |_|      \\__| \\___/  \\_,_| /__/");
    gotoxy(56,5);
    printf("              |_|    |_|");
    gotoxy(55,6);
    printf("  _                                        _                               _");
    gotoxy(55,7);
    printf(" | |  ___   ___    ___   _ _    ___  ___  (_)  __ _   _ _    __ _   _ _   | |_   ___");
    gotoxy(55,8);
    printf(" | | / -_) (_-<   / -_) | ' \\  (_-< / -_) | | / _` | | ' \\  / _` | | ' \\  |  _| (_-<");
    gotoxy(55,9);
    printf(" |_| \\___| /__/   \\___| |_||_| /__/ \\___| |_| \\__, | |_||_| \\__,_| |_||_|  \\__| /__/");
    gotoxy(55,10);
    printf("                                              |___/");
    gotoxy(60,11);
    printf("              _          _     _    __          __");
    gotoxy(60,12);
    printf("  _ _   ___  | |  __ _  | |_  (_)  / _|  ___    \\_\\_     _  _   _ _    ___");
    gotoxy(60,13);
    printf(" | '_| / -_) | | / _` | |  _| | | |  _| (_-<   / _` |   | || | | ' \\  / -_)");
    gotoxy(60,14);
    printf(" |_|   \\___| |_| \\__,_|  \\__| |_| |_|   /__/   \\__,_|    \\_,_| |_||_| \\___|");
    gotoxy(48,15);
    printf("               __        _          _   _   _      __        _                        __");
    gotoxy(48,16);
    printf("  ___  _ __   /_/   __  (_)  __ _  | | (_) | |_   /_/     __| |  ___   _ _    _ _    /_/   ___");
    gotoxy(48,17);
    printf(" (_-< | '_ \\ / -_) / _| | | / _` | | | | | |  _| / -_)   / _` | / _ \\ | ' \\  | ' \\  / -_) / -_)");
    gotoxy(48,18);
    printf(" /__/ | .__/ \\___| \\__| |_| \\__,_| |_| |_|  \\__| \\___|   \\__,_| \\___/ |_||_| |_||_| \\___| \\___|");
    gotoxy(48,19);
    printf("      |_|");
    gotoxy(1,21);
    textcolor(WHITE);

    printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    printf("                            | Code |              Sp%ccialit%c             | Code |          Sp%ccialit%c         | Code |                   Sp%ccialit%c              |\n",130,130,130,130,130,130);
    printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    for(int i=0;i<30;i=i+3)
    {
        printf("                            | %4d | %35s | %4d | %27s | %4d | %41s |\n",i+1,Specialite[i],i+2,Specialite[i+1],i+3,Specialite[i+2]);
        printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
    }
    gotoxy(72,46);
    printf("   Veuillez introduire le code de sp%ccialit%c: ",130,130);
    textcolor(LIGHTCYAN);
    scanf("%d",&n);
    while ((n<1)||(n>30)){

        system("cls");
        textcolor(LIGHTCYAN);
        gotoxy(56,1);
        printf("  ___                              _                         _");
        gotoxy(56,2);
        printf(" / __|  _  _   _ __   _ __   _ _  (_)  _ __    ___   _ _    | |_   ___   _  _   ___");
        gotoxy(56,3);
        printf(" \\__ \\ | || | | '_ \\ | '_ \\ | '_| | | | '  \\  / -_) | '_|   |  _| / _ \\ | || | (_-<");
        gotoxy(56,4);
        printf(" |___/  \\_,_| | .__/ | .__/ |_|   |_| |_|_|_| \\___| |_|      \\__| \\___/  \\_,_| /__/");
        gotoxy(56,5);
        printf("              |_|    |_|");
        gotoxy(55,6);
        printf("  _                                        _                               _");
        gotoxy(55,7);
        printf(" | |  ___   ___    ___   _ _    ___  ___  (_)  __ _   _ _    __ _   _ _   | |_   ___");
        gotoxy(55,8);
        printf(" | | / -_) (_-<   / -_) | ' \\  (_-< / -_) | | / _` | | ' \\  / _` | | ' \\  |  _| (_-<");
        gotoxy(55,9);
        printf(" |_| \\___| /__/   \\___| |_||_| /__/ \\___| |_| \\__, | |_||_| \\__,_| |_||_|  \\__| /__/");
        gotoxy(55,10);
        printf("                                              |___/");
        gotoxy(61,11);
        printf("              _          _     _    __     __");
        gotoxy(61,12);
        printf("  _ _   ___  | |  __ _  | |_  (_)  / _|    \\_\\_     _  _   _ _    ___");
        gotoxy(61,13);
        printf(" | '_| / -_) | | / _` | |  _| | | |  _|   / _` |   | || | | ' \\  / -_)");
        gotoxy(61,14);
        printf(" |_|   \\___| |_| \\__,_|  \\__| |_| |_|     \\__,_|    \\_,_| |_||_| \\___|");
        gotoxy(48,15);
        printf("               __        _          _   _   _      __        _                        __");
        gotoxy(48,16);
        printf("  ___  _ __   /_/   __  (_)  __ _  | | (_) | |_   /_/     __| |  ___   _ _    _ _    /_/   ___");
        gotoxy(48,17);
        printf(" (_-< | '_ \\ / -_) / _| | | / _` | | | | | |  _| / -_)   / _` | / _ \\ | ' \\  | ' \\  / -_) / -_)");
        gotoxy(48,18);
        printf(" /__/ | .__/ \\___| \\__| |_| \\__,_| |_| |_|  \\__| \\___|   \\__,_| \\___/ |_||_| |_||_| \\___| \\___|");
        gotoxy(48,19);
        printf("      |_|");
        gotoxy(1,21);
        textcolor(WHITE);
        //24

        printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
        printf("                            | Code |              Sp%ccialit%c             | Code |          Sp%ccialit%c         | Code |                   Sp%ccialit%c              |\n",130,130,130,130,130,130);
        printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
        for(int i=0;i<30;i=i+3)
        {
            printf("                            | %4d | %35s | %4d | %27s | %4d | %41s |\n",i+1,Specialite[i],i+2,Specialite[i+1],i+3,Specialite[i+2]);
            printf("                            +------+-------------------------------------+------+-----------------------------+------+-------------------------------------------+\n");
        }
        textcolor(LIGHTRED);
        gotoxy(73,49);
        printf("Erreur, le code doit %ctre compris entre 1 et 30.",136);
        textcolor(WHITE);
        gotoxy(72,46);
        printf("   Veuillez introduire le code de sp%ccialit%c: ",130,130);
        textcolor(LIGHTCYAN);
        scanf("%d",&n);

    }
    gotoxy(1,46);
    delline();
    gotoxy(1,48);
    delline();
    gotoxy(49,45);
    textbackground(RED);
    textcolor(WHITE);
    printf("Voulez-vous vraiment supprimer tous les enseignants relatifs %c la sp%ccialit%c %s ?",133,130,130,Specialite[n-1]);
    textbackground(BLACK);
    char Choix[3][10] = {"-> Oui","-> Non"};
    textcolor(WHITE);
    gotoxy(36,47);
    printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appuyez sur 'Entrer' pour le valider.",130,130);
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(40,49);
    printf("%s",Choix[0]);
    gotoxy(144,49);
    textbackground(BLACK);
    printf("%s",Choix[1]);
    int i;
    i=0;
    bool continu = true;
    char c;
    while (continu){

        c = getch();

        switch(c){

            case -32:

                    c = getch();

                    if (c==77){

                        if (i==0){

                            textbackground(BLACK);
                            gotoxy(40,49);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,49);
                            printf("%s",Choix[1]);
                            i++;
                            textbackground(BLACK);

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(144,49);
                            printf("%s",Choix[1]);
                            textbackground(BLUE);
                            gotoxy(40,49);
                            printf("%s",Choix[0]);
                            i = 0;
                            textbackground(BLACK);

                        }

                    }
                    if (c==75){

                        if (i==1){

                            textbackground(BLUE);
                            gotoxy(40,49);
                            printf("%s",Choix[0]);
                            textbackground(BLACK);
                            gotoxy(144,49);
                            printf("%s",Choix[1]);
                            i--;

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(40,49);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,49);
                            printf("%s",Choix[1]);
                            i=1;
                            textbackground(BLACK);


                        }


                    }

                    break;

            case 13:

                    continu = false;

                    break;

            default:

                    break;

        }


    }

    if (i==0){

        Suppression_ENS_Specialites(n);
        textcolor(LIGHTGREEN);
        gotoxy(75,51);
        textbackground(BLACK);
        printf("Suppression effectu%ce avec succ%cs!",130,138);

    }

    textbackground(BLACK);
    textcolor(YELLOW);
    gotoxy(65,54);
    printf("Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();

}

void Consultation_Multicles(){
    textcolor(LIGHTCYAN);
    gotoxy(70,2);
    printf("  _____                            //\\   _");
    gotoxy(70,3);
    printf(" |  __ \\                          |/ \\| | |");
    gotoxy(70,4);
    printf(" | |__) |   ___    __ _   _   _    ___  | |_    ___");
    gotoxy(70,5);
    printf(" |  _  /   / _ \\  / _` | | | | |  / _ \\ | __|  / _ \\");
    gotoxy(70,6);
    printf(" | | \\ \\  |  __/ | (_| | | |_| | |  __/ | |_  |  __/");
    gotoxy(70,7);
    printf(" |_|  \\_\\  \\___|  \\__, |  \\__,_|  \\___|  \\__|  \\___|");
    gotoxy(70,8);
    printf("                     | |");
    gotoxy(70,9);
    printf("                     |_|");
    gotoxy(73,10);
    printf("         _.-----._");
    gotoxy(73,11);
    printf("       .'.-'''''-.'._");
    gotoxy(73,12);
    printf("      //`.:#:'    `\\\\\\");
    gotoxy(73,13);
    printf("     ;; '           ;;'.__.===============,");
    gotoxy(73,14);
    printf("     ||             ||  __                 )");
    gotoxy(73,15);
    printf("     ;;             ;;.'  '==============='");
    gotoxy(73,16);
    printf("      \\\\           ///");
    gotoxy(73,17);
    printf("       ':.._____..:'~");
    gotoxy(73,18);
    printf("         `'-----'`");
    gotoxy(59,19);
    printf("   __       _           _                                   _   _");
    gotoxy(59,20);
    printf("   \\_\\     (_)         | |                                 | | | |");
    gotoxy(59,21);
    printf("   __ _     _   _ __   | |_    ___   _ __  __   __   __ _  | | | |   ___");
    gotoxy(59,22);
    printf("  / _` |   | | | '_ \\  | __|  / _ \\ | '__| \\ \\ / /  / _` | | | | |  / _ \\");
    gotoxy(59,23);
    printf(" | (_| |   | | | | | | | |_  |  __/ | |     \\ V /  | (_| | | | | | |  __/");
    gotoxy(59,24);
    printf("  \\__,_|   |_| |_| |_|  \\__|  \\___| |_|      \\_/    \\__,_| |_| |_|  \\___|");
    gotoxy(28,27);
    textcolor(YELLOW);
    printf("Cette proc%cdure permet d'afficher tous les enseignants exer%cant dans un %ctablissement donn%c ayant une anciennet%c entre deux valeurs donn%ces.",130,135,130,130,130,130);
    gotoxy(74,29);
    printf("Veuillez remplir soigneusement votre requ%cte.",136);
    gotoxy(1,32);
    textcolor(WHITE);
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | Valeur 1        |                                                                                                                         |\n");
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | Valeur 2        |                                                                                                                         |\n");
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | %ctablissement   |                                                                                                                         |\n",144);
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    int bi,bs;
    gotoxy(48,33);
    textcolor(LIGHTCYAN);
    scanf("%d",&bi);
    while (bi<=0){

        gotoxy(71,41);
        textcolor(LIGHTRED);
        printf("Veuillez introduire un entier strictement positif.");
        textcolor(WHITE);
        gotoxy(1,32);
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | Valeur 1        |                                                                                                                         |\n");
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | Valeur 2        |                                                                                                                         |\n");
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | %ctablissement   |                                                                                                                         |\n",144);
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        gotoxy(48,33);
        textcolor(LIGHTCYAN);
        scanf("%d",&bi);

    }
    gotoxy(1,41);
    delline();
    gotoxy(48,35);
    scanf("%d",&bs);
    while (bs<=0){

        gotoxy(71,41);
        textcolor(LIGHTRED);
        printf("Veuillez introduire un entier strictement positif.");
        textcolor(WHITE);
        gotoxy(1,32);
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | Valeur 1        |                                                                                                                         |\n");
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | Valeur 2        |                                                                                                                         |\n");
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("                          | %ctablissement   |                                                                                                                         |\n",144);
        printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
        gotoxy(48,33);
        textcolor(LIGHTCYAN);
        printf("%d",bi);
        gotoxy(48,35);
        scanf("%d",&bs);

    }
    gotoxy(1,41);
    delline();
    int ets;
    delay(1000);
    system("cls");
    Affich_Tab_Ets(&ets);
    system("cls");
    textcolor(LIGHTCYAN);
    gotoxy(70,2);
    printf("  _____                            //\\   _");
    gotoxy(70,3);
    printf(" |  __ \\                          |/ \\| | |");
    gotoxy(70,4);
    printf(" | |__) |   ___    __ _   _   _    ___  | |_    ___");
    gotoxy(70,5);
    printf(" |  _  /   / _ \\  / _` | | | | |  / _ \\ | __|  / _ \\");
    gotoxy(70,6);
    printf(" | | \\ \\  |  __/ | (_| | | |_| | |  __/ | |_  |  __/");
    gotoxy(70,7);
    printf(" |_|  \\_\\  \\___|  \\__, |  \\__,_|  \\___|  \\__|  \\___|");
    gotoxy(70,8);
    printf("                     | |");
    gotoxy(70,9);
    printf("                     |_|");
    gotoxy(73,10);
    printf("         _.-----._");
    gotoxy(73,11);
    printf("       .'.-'''''-.'._");
    gotoxy(73,12);
    printf("      //`.:#:'    `\\\\\\");
    gotoxy(73,13);
    printf("     ;; '           ;;'.__.===============,");
    gotoxy(73,14);
    printf("     ||             ||  __                 )");
    gotoxy(73,15);
    printf("     ;;             ;;.'  '==============='");
    gotoxy(73,16);
    printf("      \\\\           ///");
    gotoxy(73,17);
    printf("       ':.._____..:'~");
    gotoxy(73,18);
    printf("         `'-----'`");
    gotoxy(59,19);
    printf("   __       _           _                                   _   _");
    gotoxy(59,20);
    printf("   \\_\\     (_)         | |                                 | | | |");
    gotoxy(59,21);
    printf("   __ _     _   _ __   | |_    ___   _ __  __   __   __ _  | | | |   ___");
    gotoxy(59,22);
    printf("  / _` |   | | | '_ \\  | __|  / _ \\ | '__| \\ \\ / /  / _` | | | | |  / _ \\");
    gotoxy(59,23);
    printf(" | (_| |   | | | | | | | |_  |  __/ | |     \\ V /  | (_| | | | | | |  __/");
    gotoxy(59,24);
    printf("  \\__,_|   |_| |_| |_|  \\__|  \\___| |_|      \\_/    \\__,_| |_| |_|  \\___|");
    gotoxy(28,27);
    textcolor(YELLOW);
    printf("Cette proc%cdure permet d'afficher tous les enseignants exer%cant dans un %ctablissement donn%c ayant une anciennet%c entre deux valeurs donn%ces.",130,135,130,130,130,130);
    gotoxy(74,29);
    printf("Veuillez remplir soigneusement votre requ%cte.",136);
    gotoxy(1,32);
    textcolor(WHITE);
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | Valeur 1        |                                                                                                                         |\n");
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | Valeur 2        |                                                                                                                         |\n");
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("                          | %ctablissement   |                                                                                                                         |\n",144);
    printf("                          +-------------------------------------------------------------------------------------------------------------------------------------------+\n");
    textcolor(LIGHTCYAN);
    gotoxy(48,33);
    printf("%d",bi);
    gotoxy(48,35);
    printf("%d",bs);
    gotoxy(48,37);
    printf("%s",Tab_ETS[ets-1].Nom);
    if (bi>bs){

        Permuter(&bi,&bs);

    }
    gotoxy(75,41);
    textcolor(LIGHTGREEN);
    printf("Voulez-vous vraiment lancer cette requ%cte ?",136);
    char Choix[3][10] = {"-> Oui","-> Non"};
    textcolor(WHITE);
    gotoxy(36,43);
    printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appuyez sur 'Entrer' pour le valider.",130,130);
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(40,45);
    printf("%s",Choix[0]);
    gotoxy(144,45);
    textbackground(BLACK);
    printf("%s",Choix[1]);
    int i;
    i=0;
    bool continu = true;
    char c;
    while (continu){

        c = getch();

        switch(c){

            case -32:

                    c = getch();

                    if (c==77){

                        if (i==0){

                            textbackground(BLACK);
                            gotoxy(40,45);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,45);
                            printf("%s",Choix[1]);
                            i++;
                            textbackground(BLACK);

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(144,45);
                            printf("%s",Choix[1]);
                            textbackground(BLUE);
                            gotoxy(40,45);
                            printf("%s",Choix[0]);
                            i = 0;
                            textbackground(BLACK);

                        }

                    }
                    if (c==75){

                        if (i==1){

                            textbackground(BLUE);
                            gotoxy(40,45);
                            printf("%s",Choix[0]);
                            textbackground(BLACK);
                            gotoxy(144,45);
                            printf("%s",Choix[1]);
                            i--;

                        }
                        else{

                            textbackground(BLACK);
                            gotoxy(40,45);
                            printf("%s",Choix[0]);
                            textbackground(BLUE);
                            gotoxy(144,45);
                            printf("%s",Choix[1]);
                            i=1;
                            textbackground(BLACK);


                        }


                    }

                    break;

            case 13:

                    continu = false;

                    break;

            default:

                    break;

        }


    }

    if (i==0){

            textbackground(BLACK);
            Affich_ENS_Ets(bi,bs,ets);

    }
    else{

        textbackground(BLACK);
        textcolor(YELLOW);
        gotoxy(67,48);
        printf("Appuyez sur une touche pour revenir au programme principal.");
        fflush(stdin);
        getch();

    }

}

void Affich_Region(){
    start:
            system("cls");
            textbackground(BLACK);
            textcolor(LIGHTCYAN);
            gotoxy(61,5);
            printf("   ___                            _   _                   _");
            gotoxy(61,6);
            printf("  / __|  ___   _ _    ___  _  _  | | | |_   ___   _ _    | |  ___   ___");
            gotoxy(61,7);
            printf(" | (__  / _ \\ | ' \\  (_-< | || | | | |  _| / -_) | '_|   | | / -_) (_-<");
            gotoxy(61,8);
            printf("  \\___| \\___/ |_||_| /__/  \\_,_| |_|  \\__| \\___| |_|     |_| \\___| /__/");
            gotoxy(37,9);
            printf("                          _                               _                                                       _");
            gotoxy(37,10);
            printf("  ___   _ _    ___  ___  (_)  __ _   _ _    __ _   _ _   | |_   ___    ___  __ __  ___   _ _   __   __ _   _ _   | |_");
            gotoxy(37,11);
            printf(" / -_) | ' \\  (_-< / -_) | | / _` | | ' \\  / _` | | ' \\  |  _| (_-<   / -_) \\ \\ / / -_) | '_| / _| / _` | | ' \\  |  _|");
            gotoxy(37,12);
            printf(" \\___| |_||_| /__/ \\___| |_| \\__, | |_||_| \\__,_| |_||_|  \\__| /__/   \\___| /_\\_\\ \\___| |_|   \\__| \\__,_| |_||_|  \\__|");
            gotoxy(37,13);
            printf("                             |___/                                                             )_)");
            gotoxy(32,14);
            printf("     _                                                     __          _                     _                        __");
            gotoxy(32,15);
            printf("  __| |  __ _   _ _    ___    _  _   _ _    ___     _ _   /_/   __ _  (_)  ___   _ _      __| |  ___   _ _    _ _    /_/   ___");
            gotoxy(32,16);
            printf(" / _` | / _` | | ' \\  (_-<   | || | | ' \\  / -_)   | '_| / -_) / _` | | | / _ \\ | ' \\    / _` | / _ \\ | ' \\  | ' \\  / -_) / -_)");
            gotoxy(32,17);
            printf(" \\__,_| \\__,_| |_||_| /__/    \\_,_| |_||_| \\___|   |_|   \\___| \\__, | |_| \\___/ |_||_|   \\__,_| \\___/ |_||_| |_||_| \\___| \\___|");
            gotoxy(32,18);
            printf("                                                               |___/");
            gotoxy(80,22);
            textcolor(WHITE);
            printf("Veuillez s%clectionner la r%cgion.",130,130);
            gotoxy(35,26);
            textcolor(YELLOW);
            gotoxy(35,26);
            printf("Utilisez les touches 'UP ARROW' et 'DOWN ARROW' pour choisir la r%cgion puis appuyez sur 'Entrer' pour valider votre choix.",130);
            textcolor(LIGHTGREEN);
            gotoxy(67,43);
            printf("Appuyez sur ESC/%cchapper pour revenir au menu principal.",144);
            char Choix[4][20] = {"1-> Ouest",
                                 "2-> Centre",
                                 "3-> Est"};
            textcolor(WHITE);
            gotoxy(90,31);
            textbackground(BLUE);
            textcolor(WHITE);
            printf("%s",Choix[0]);
            gotoxy(90,34);
            textbackground(BLACK);
            printf("%s",Choix[1]);
            gotoxy(90,37);
            textbackground(BLACK);
            printf("%s",Choix[2]);
            int i,j;
            char c;
            i = 0;
            j = 31;
            bool continu;
            continu = true;
            while (continu){

                fflush(stdin);

                c = getch();

                switch(c){

                    case 80:

                            textbackground(BLACK);
                            gotoxy(90,i+j);
                            printf("%s",Choix[i]);
                            i++;
                            j=j+2;
                            textbackground(BLUE);
                            gotoxy(90,i+j);
                            printf("%s",Choix[i]);
                            textbackground(BLACK);
                            if (i>2){

                                i = 0;
                                j = 31;
                                gotoxy(90,31);
                                textbackground(BLUE);
                                printf("%s",Choix[0]);
                                textbackground(BLACK);

                            }

                            break;


                    case 72:

                            textbackground(BLACK);
                            gotoxy(90,i+j);
                            printf("%s",Choix[i]);
                            i--;
                            j=j-2;
                            if (i<0){

                                i =2;
                                j = 35;
                                gotoxy(90,37);
                                textbackground(BLUE);
                                printf("%s",Choix[2]);
                                textbackground(BLACK);

                            }
                            else {

                                textbackground(BLUE);
                                gotoxy(90,i+j);
                                printf("%s",Choix[i]);
                                textbackground(BLACK);

                            }

                            break;


                    case 13:
                            textbackground(BLACK);
                            Affich_ENS_Region(i+1);
                            goto start;


                    case 27:

                            continu = false;

                            break;


                    default: break;

                }

            }

}

void Affich_Codage(){
    textcolor(LIGHTCYAN);
    gotoxy(145,4);
    printf("            .-%c%c-.",34,34);
    gotoxy(145,5);
    printf("           / .--. \\");
    gotoxy(145,6);
    printf("          / /    \\ \\");
    gotoxy(145,7);
    printf("          | |    | |");
    gotoxy(145,8);
    printf("          | |.-%c%c-.|",34,34);
    gotoxy(145,9);
    printf("         ///`.::::.`\\");
    gotoxy(145,10);
    printf("        ||| ::/  \\:: ;");
    gotoxy(145,11);
    printf("        ||; ::\\__/:: ;");
    gotoxy(145,12);
    printf("         \\\\\\ '::::' /");
    gotoxy(145,13);
    printf("          `=':-..-'`");
    gotoxy(17,5);
    printf("(\\");
    gotoxy(17,6);
    printf("\\'\\");
    gotoxy(17,7);
    printf(" \\'\\     __________");
    gotoxy(17,8);
    printf(" / '|   ()_________)");
    gotoxy(17,9);
    printf(" \\ '/    \\ ~~~~~~~~ \\");
    gotoxy(17,10);
    printf("   \\       \\ ~~~~~~   \\");
    gotoxy(17,11);
    printf("   ==).      \\__________\\");
    gotoxy(17,12);
    printf("  (__)       ()__________)");
    gotoxy(49,8);
    printf("   ___            _                            _             __   _        _      _");
    gotoxy(49,9);
    printf("  / __|  ___   __| |  __ _   __ _   ___     __| |  _  _     / _| (_)  __  | |_   (_)  ___   _ _");
    gotoxy(49,10);
    printf(" | (__  / _ \\ / _` | / _` | / _` | / -_)   / _` | | || |   |  _| | | / _| | ' \\  | | / -_) | '_|");
    gotoxy(49,11);
    printf("  \\___| \\___/ \\__,_| \\__,_| \\__, | \\___|   \\__,_|  \\_,_|   |_|   |_| \\__| |_||_| |_| \\___| |_|");
    gotoxy(49,12);
    printf("                            |___/");
    gotoxy(70,18);
    textcolor(WHITE);
    printf("   Veuillez introduire la cl%c du chiffrement:\n",130);
    gotoxy(116,18);
    textcolor(LIGHTGREEN);
    fflush(stdin);
    gets(cle);
    textcolor(WHITE);
    gotoxy(58,27);
    printf("Veuillez patienter quelques instants");
    gotoxy(63,29);
    printf("Jusqu'%c ce qu'on finalise",133);
    gotoxy(52,31);
    printf("La codification du fichier ENSEIGNANT-MESRS.bin");
    textcolor(LIGHTCYAN);
    gotoxy(114,22);
    printf("         _nnnn_");
    gotoxy(114,23);
    printf("         dGGGGMMb");
    gotoxy(114,24);
    printf("        @p~qp~~qMb");
    gotoxy(114,25);
    printf("        M|@||@) M|");
    gotoxy(114,26);
    printf("        @,----.JM|");
    gotoxy(114,27);
    printf("       JS^\\__/  qKL");
    gotoxy(114,28);
    printf("      dZP        qKRb");
    gotoxy(114,29);
    printf("     dZP          qKKb");
    gotoxy(114,30);
    printf("    fZP            SMMb");
    gotoxy(114,31);
    printf("    HZM            MMMM");
    gotoxy(114,32);
    printf("    FqM            MMMM");
    gotoxy(114,33);
    printf("  __| %c.        |\\dS%cqML",34,34);
    gotoxy(114,34);
    printf("  |    `.       | `' \\Zq");
    gotoxy(114,35);
    printf(" _)      \\.___.,|     .'");
    gotoxy(114,36);
    printf(" \\____   )MMMMMP|   .'");
    gotoxy(114,37);
    printf("      `-'       `--'");
    codage();
    char ligne[256];
    gotoxy(74,41);
    strcpy(ligne,"La codification a ete effectuee avec succes!");
    ligne[18] = 130;
    ligne[20] = 130;
    ligne[29] = 130;
    ligne[41] = 138;
    Ecrire_chaine(ligne,10,WHITE,BLACK);
    gotoxy(79,43);
    strcpy(ligne,"Fichier resultant: FICHIER-CODE.bin");
    ligne [9] = 130;
    Ecrire_chaine(ligne,10,LIGHTGREEN,BLACK);
    gotoxy(54,45);
    strcpy(ligne,"Le fichier apres codification se trouve dans le meme repertoire que celui du projet.");
    ligne[14] = 138;
    ligne [49] = 136;
    ligne[54] = 130;
    Ecrire_chaine(ligne,10,WHITE,BLACK);
    gotoxy(70,49);
    textbackground(BLACK);
    textcolor(YELLOW);
    printf("Appuyez sur une touche pour revenir au menu principal.");
    fflush(stdin);
    getch();
}

void Affich_Decodage(){
 start:
        system("cls");
        textbackground(BLACK);
        textcolor(LIGHTCYAN);
        FILE *fc=fopen("cle.txt","r+");
        fgets(cle,sizeof(cle),fc);
        cle[strlen(cle)]= '\0';
        fclose(fc);
        gotoxy(10,3);
        printf("(\\");
        gotoxy(10,4);
        printf("\\'\\");
        gotoxy(10,5);
        printf(" \\'\\     __________");
        gotoxy(10,6);
        printf(" / '|   ()_________)");
        gotoxy(10,7);
        printf(" \\ '/    \\ ~~~~~~~~ \\");
        gotoxy(10,8);
        printf("   \\       \\ ~~~~~~   \\");
        gotoxy(10,9);
        printf("   ==).      \\__________\\");
        gotoxy(10,10);
        printf("  (__)       ()__________)");
        gotoxy(144,7);
        printf("     8 8 8 8                     ,ooo.");
        gotoxy(144,8);
        printf("     8a8 8a8                    oP   ?b");
        gotoxy(144,9);
        printf("    d888a888zzzzzzzzzzzzzzzzzzzz8     8b");
        gotoxy(144,10);
        printf("     `%c%c^%c%c'                    ?o___oP'",34,34,34,34);
        gotoxy(38,6);
        printf("  ___                        _                            _             __   _        _      _");
        gotoxy(38,7);
        printf(" |   \\   ___   __   ___   __| |  __ _   __ _   ___     __| |  _  _     / _| (_)  __  | |_   (_)  ___   _ _");
        gotoxy(38,8);
        printf(" | |) | / -_) / _| / _ \\ / _` | / _` | / _` | / -_)   / _` | | || |   |  _| | | / _| | ' \\  | | / -_) | '_|");
        gotoxy(38,9);
        printf(" |___/  \\___| \\__| \\___/ \\__,_| \\__,_| \\__, | \\___|   \\__,_|  \\_,_|   |_|   |_| \\__| |_||_| |_| \\___| |_|");
        gotoxy(38,10);
        printf("                                       |___/");
        char cle_entree[256];
        gotoxy(69,14);
        textcolor(WHITE);
        printf("   Veuillez introduire la cl%c de d%cchiffrement:",130,130);
        gotoxy(117,14);
        textcolor(LIGHTGREEN);
        fflush(stdin);
        gets(cle_entree);
        if(strcmp(cle_entree,cle)==0){

            textcolor(WHITE);
            gotoxy(58,25);
            printf("Veuillez patienter quelques instants");
            gotoxy(63,27);
            printf("Jusqu'%c ce qu'on finalise",133);
            gotoxy(56,29);
            printf("Le d%ccodage du fichier FICHIER-CODE.bin",130);
            textcolor(LIGHTCYAN);
            gotoxy(114,20);
            printf("         _nnnn_");
            gotoxy(114,21);
            printf("         dGGGGMMb");
            gotoxy(114,22);
            printf("        @p~qp~~qMb");
            gotoxy(114,23);
            printf("        M|@||@) M|");
            gotoxy(114,24);
            printf("        @,----.JM|");
            gotoxy(114,25);
            printf("       JS^\\__/  qKL");
            gotoxy(114,26);
            printf("      dZP        qKRb");
            gotoxy(114,27);
            printf("     dZP          qKKb");
            gotoxy(114,28);
            printf("    fZP            SMMb");
            gotoxy(114,29);
            printf("    HZM            MMMM");
            gotoxy(114,30);
            printf("    FqM            MMMM");
            gotoxy(114,31);
            printf("  __| %c.        |\\dS%cqML",34,34);
            gotoxy(114,32);
            printf("  |    `.       | `' \\Zq");
            gotoxy(114,33);
            printf(" _)      \\.___.,|     .'");
            gotoxy(114,34);
            printf(" \\____   )MMMMMP|   .'");
            gotoxy(114,35);
            printf("      `-'       `--'");
            decodage();
            char ligne[256];
            gotoxy(78,41);
            strcpy(ligne,"Le decodage a ete effectue avec succes!");
            ligne[4] = 130;
            ligne[14] = 130;
            ligne [16] = 130;
            ligne [25] = 130;
            ligne [36] = 138;
            Ecrire_chaine(ligne,10,WHITE,BLACK);
            gotoxy(79,43);
            strcpy(ligne,"Fichier resultant: FICHIER-DECODE.bin");
            ligne [9] = 130;
            Ecrire_chaine(ligne,10,LIGHTGREEN,BLACK);
            gotoxy(59,45);
            strcpy(ligne,"Le fichier apres decodage se trouve dans le meme repertoire que celui du projet.");
            ligne [14] = 138;
            ligne[18] = 130;
            ligne[45] = 136;
            ligne[50] = 130;
            Ecrire_chaine(ligne,10,WHITE,BLACK);
            gotoxy(71,50);
            textbackground(BLACK);
            textcolor(YELLOW);
            printf("Appuyez sur une touche pour revenir au menu principal.");
            fflush(stdin);
            getch();


        }
        else{
            textcolor(RED);
            gotoxy(71,17);
            printf("            uuuuuuuuuuuuuuuuuuuu");
            gotoxy(71,18);
            printf("          u%c uuuuuuuuuuuuuuuuuu %cu",34,34);
            gotoxy(71,19);
            printf("        u%c u$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
            gotoxy(71,20);
            printf("      u%c u$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
            gotoxy(71,21);
            printf("    u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
            gotoxy(71,22);
            printf("  u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
            gotoxy(71,23);
            printf("u%c u$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$u %cu",34,34);
            gotoxy(71,24);
            printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
            gotoxy(71,25);
            printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
            gotoxy(71,26);
            printf("$ $$$%c ... %c$...  ...$%c ... %c$$$  ... %c$$$ $",34,34,34,34,34);
            gotoxy(71,27);
            printf("$ $$$u `%c$$$$$$$  $$$  $$$$$  $$  $$$  $$$ $",34);
            gotoxy(71,28);
            printf("$ $$$$$$uu %c$$$$  $$$  $$$$$  $$  %c%c%c u$$$ $",34,34,34,34);
            gotoxy(71,29);
            printf("$ $$$%c%c$$$  $$$$  $$$u %c$$$%c u$$  $$$$$$$$ $",34,34,34,34);
            gotoxy(71,30);
            printf("$ $$$$....,$$$$$..$$$$$....,$$$$..$$$$$$$$ $");
            gotoxy(71,31);
            printf("$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $");
            gotoxy(71,32);
            printf("%cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
            gotoxy(71,33);
            printf("  %cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u",34,34,34);
            gotoxy(71,34);
            printf("    %cu %c$$$$$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
            gotoxy(71,35);
            printf("      %cu %c$$$$$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
            gotoxy(71,36);
            printf("        %cu %c$$$$$$$$$$$$$$$$$$$$%c u%c",34,34,34,34);
            gotoxy(71,37);
            printf("          %cu %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c u%c",34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34);
            gotoxy(71,38);
            printf("            %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34);
            gotoxy(76,40);
            textcolor(RED);
            printf("Cl%c de d%cchiffrement incoh%crente!",130,130,130);
            gotoxy(72,43);
            textcolor(LIGHTGREEN);
            printf("Voulez-vous essayer une autre tentative?");
            char Choix[3][10] = {"-> Oui","-> Non"};
            textcolor(WHITE);
            gotoxy(36,45);
            printf("Utilisez les touches 'LEFT ARROW' et 'RIGHT ARROW' pour s%cl%cctionner votre choix puis appuyez sur 'Entrer' pour le valider.",130,130);
            textcolor(WHITE);
            textbackground(BLUE);
            gotoxy(40,47);
            printf("%s",Choix[0]);
            gotoxy(144,47);
            textbackground(BLACK);
            printf("%s",Choix[1]);
            int i;
            i=0;
            bool continu = true;
            char c;
            while (continu){

                c = getch();

                switch(c){

                    case -32:

                            c = getch();

                            if (c==77){

                                if (i==0){

                                    textbackground(BLACK);
                                    gotoxy(40,47);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(144,47);
                                    printf("%s",Choix[1]);
                                    i++;
                                    textbackground(BLACK);

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(144,47);
                                    printf("%s",Choix[1]);
                                    textbackground(BLUE);
                                    gotoxy(40,47);
                                    printf("%s",Choix[0]);
                                    i = 0;
                                    textbackground(BLACK);

                                }

                            }
                            if (c==75){

                                if (i==1){

                                    textbackground(BLUE);
                                    gotoxy(40,47);
                                    printf("%s",Choix[0]);
                                    textbackground(BLACK);
                                    gotoxy(144,47);
                                    printf("%s",Choix[1]);
                                    i--;

                                }
                                else{

                                    textbackground(BLACK);
                                    gotoxy(40,47);
                                    printf("%s",Choix[0]);
                                    textbackground(BLUE);
                                    gotoxy(144,47);
                                    printf("%s",Choix[1]);
                                    i=1;
                                    textbackground(BLACK);


                                }


                            }

                            break;

                    case 13:

                            continu = false;

                            break;

                    default:

                            break;

                }


            }

            if (i==0){

                goto start;

            }
            else{

                gotoxy(65,50);
                textbackground(BLACK);
                textcolor(YELLOW);
                printf("Appuyez sur une touche pour revenir au menu principal.");
                fflush(stdin);
                getch();

            }
        }

}

void Affich_Codage_Decodage(){
start:
        system("cls");
        textbackground(BLACK);
        textcolor(LIGHTCYAN);
        gotoxy(36,8);
        printf("   _____               _");
        gotoxy(36,9);
        printf("  / ____|             | |");
        gotoxy(36,10);
        printf(" | |        ___     __| |   __ _    __ _    ___");
        gotoxy(36,11);
        printf(" | |       / _ \\   / _` |  / _` |  / _` |  / _ \\");
        gotoxy(36,12);
        printf(" | |____  | (_) | | (_| | | (_| | | (_| | |  __/");
        gotoxy(36,13);
        printf("  \\_____|  \\___/   \\__,_|  \\__,_|  \\__, |  \\___|");
        gotoxy(36,14);
        printf("                                    __/ |");
        gotoxy(36,15);
        printf("                                   |___/");
        gotoxy(86,8);
        printf("       __");
        gotoxy(86,9);
        printf("      / /");
        gotoxy(86,10);
        printf("     / /");
        gotoxy(86,11);
        printf("    / /");
        gotoxy(86,12);
        printf("   / /");
        gotoxy(86,13);
        printf("  /_/");
        gotoxy(97,8);
        printf("  _____                              _");
        gotoxy(97,9);
        printf(" |  __ \\                            | |");
        gotoxy(97,10);
        printf(" | |  | |   ___    ___    ___     __| |   __ _    __ _    ___");
        gotoxy(97,11);
        printf(" | |  | |  / _ \\  / __|  / _ \\   / _` |  / _` |  / _` |  / _ \\");
        gotoxy(97,12);
        printf(" | |__| | |  __/ | (__  | (_) | | (_| | | (_| | | (_| | |  __/");
        gotoxy(97,13);
        printf(" |_____/   \\___|  \\___|  \\___/   \\__,_|  \\__,_|  \\__, |  \\___|");
        gotoxy(97,14);
        printf("                                                  __/ |");
        gotoxy(97,15);
        printf("                                                 |___/");
        gotoxy(97,16);
        gotoxy(45,19);
        textcolor(YELLOW);
        printf("Veuillez s%cl%cctionner l'op%cration %c ex%ccuter. Pour cela, utilisez les touches 'UP ARROW' et 'DOWN ARROW'.",130,130,130,133,130);
        gotoxy(72,21);
        printf("Appuyez sur 'Entrer' pour confirmer votre choix.");
        char Choix[10][100] = {"1-> Coder le fichier ENSEIGNANT-MESRS.bin .",
                               "2-> Decoder le fichier code.",
                               "3-> Afficher le fichier code.",
                               "4-> Afficher le fichier decode."};
        Choix[1][5] = 130;
        Choix[1][26] = 130;
        Choix[2][27] = 130;
        Choix[3][29] = 130;
        Choix[3][25] = 130;
        textcolor(LIGHTGREEN);
        gotoxy(68,45);
        printf("Appuyez sur ESC/%cchapper pour revenir au menu principal.",144);
        textbackground(BLUE);
        textcolor(WHITE);
        gotoxy(78,27);
        printf("%s",Choix[0]);
        textbackground(BLACK);
        gotoxy(78,31);
        printf("%s",Choix[1]);
        gotoxy(78,35);
        printf("%s",Choix[2]);
        gotoxy(78,39);
        printf("%s",Choix[3]);
        bool quit;
        quit = false;
        int i,j;
        char c;
        i = 0;
        j = 27;
        while(!quit){

            c = getch();

            switch(c){

                case 80:
                            textbackground(BLACK);
                            gotoxy(78,i+j);
                            printf("%s",Choix[i]);
                            i++;
                            j=j+3;
                            textbackground(BLUE);
                            gotoxy(78,i+j);
                            printf("%s",Choix[i]);
                            textbackground(BLACK);
                            if (i>3){

                                i = 0;
                                j = 27;
                                gotoxy(78,27);
                                textbackground(BLUE);
                                printf("%s",Choix[0]);
                                textbackground(BLACK);

                            }
                            break;

                case 72:
                            textbackground(BLACK);
                            gotoxy(78,i+j);
                            printf("%s",Choix[i]);
                            i--;
                            j=j-3;
                            if (i<0){

                                i =3;
                                j = 36;
                                gotoxy(78,39);
                                textbackground(BLUE);
                                printf("%s",Choix[3]);
                                textbackground(BLACK);

                            }
                            else {

                                textbackground(BLUE);
                                gotoxy(78,i+j);
                                printf("%s",Choix[i]);
                                textbackground(BLACK);

                            }

                            break;

                case 13:
                            system("cls");
                            textbackground(BLACK);

                            switch(i){

                                case 0:
                                        Affich_Codage();
                                        break;

                                case 1: Affich_Decodage();
                                        break;

                                case 2: Affich_Fic("FICHIER-CODE.bin");
                                        break;

                                case 3: Affich_Fic("FICHIER-DECODE.bin");
                                        break;

                                default: break;

                            }

                            goto start;

                case 27:    quit = true;
                            break;


                default:    break;


            }

        }


}

void Affich_Entete_LEDir(){

    LOBF F;
    Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A');
    textcolor(YELLOW);
    gotoxy(67,50);
    printf("Appuyez sur une touche pour revenir au programme principal.");
    textcolor(WHITE);
    gotoxy(11,5);
    printf("  _      _                      _           _");
    gotoxy(11,6);
    printf(" | |    ( )  ___   _ _    ___  | |_   ___  | |_   ___");
    gotoxy(11,7);
    printf(" | |__  |/  / -_) | ' \\  |___| |  _| / -_) |  _| / -_)");
    gotoxy(11,8);
    printf(" |____|     \\___| |_||_|        \\__| \\___|  \\__| \\___|");
    gotoxy(11,12);
    printf("     _             __   _        _      _");
    gotoxy(11,13);
    printf("  __| |  _  _     / _| (_)  __  | |_   (_)  ___   _ _");
    gotoxy(11,14);
    printf(" / _` | | || |   |  _| | | / _| | ' \\  | | / -_) | '_|");
    gotoxy(11,15);
    printf(" \\__,_|  \\_,_|   |_|   |_| \\__| |_||_| |_| \\___| |_|");
    gotoxy(75,3);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(75,4);
    printf("|                 ENSEIGNANT-MESRS.bin                                                                |\n");
    gotoxy(77,4);
    textcolor(LIGHTGREEN);
    printf("Nom du fichier:");
    gotoxy(75,5);
    textcolor(WHITE);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(75,6);
    printf("|");
    gotoxy(76,6);
    textcolor(LIGHTGREEN);
    printf(" Date de cr%cation:\n",130);
    gotoxy(95,6);
    textcolor(WHITE);
    printf("%s",F.TEn_Tete.Date_Creation);
    gotoxy(177,6);
    printf("|");
    gotoxy(75,7);
    textcolor(WHITE);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(75,8);
    printf("|");
    gotoxy(177,8);
    printf("|");
    textcolor(LIGHTGREEN);
    gotoxy(77,8);
    printf("Date de modification:");
    textcolor(WHITE);
    gotoxy(99,8);
    printf("%s",F.TEn_Tete.Date_Modification);
    gotoxy(75,9);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    textcolor(LIGHTGREEN);
    gotoxy(77,10);
    printf("Taille du fichier (en bytes):");
    textcolor(WHITE);
    gotoxy(177,10);
    printf("|");
    gotoxy(75,10);
    printf("|");
    gotoxy(107,10);
    printf("%ld",Taille_Fichier());
    gotoxy(75,11);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(75,12);
    gotoxy(177,12);
    printf("|");
    gotoxy(177,12);
    printf("|");
    gotoxy(98,12);
    printf("%d",Entete(F,1));
    gotoxy(75,12);
    printf("|");
    gotoxy(75,13);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(77,12);
    textcolor(LIGHTGREEN);
    printf("La t%cte de la liste:",136);
    textcolor(WHITE);
    gotoxy(75,15);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(177,14);
    printf("|");
    gotoxy(75,14);
    printf("|");
    textcolor(LIGHTGREEN);
    printf(" La t%cte de la liste des blocs vides: ",136);
    textcolor(WHITE);
    gotoxy(114,14);
    printf("%d",Entete(F,2));
    gotoxy(75,17);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(177,16);
    printf("|");
    gotoxy(75,16);
    printf("|");
    textcolor(LIGHTGREEN);
    printf(" Nombre de blocs physiques existant dans le fichier: ");
    textcolor(WHITE);
    gotoxy(129,16);
    printf("%d",Entete(F,3));
    gotoxy(75,19);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    gotoxy(177,18);
    printf("|");
    gotoxy(75,18);
    printf("|");
    textcolor(LIGHTGREEN);
    printf(" Nombre d'enregistrements dans le fichier: ");
    textcolor(WHITE);
    gotoxy(119,18);
    printf("%d",nbE);
    textcolor(WHITE);
    gotoxy(49,23);
    printf("  _  _                 _                       _           _      _               ___    _");
    gotoxy(49,24);
    printf(" | \\| |  ___   _ __   | |__   _ _   ___     __| |  ___    | |    (_)  _ _   ___  |   \\  (_)  _ _");
    gotoxy(49,25);
    printf(" | .` | / _ \\ | '  \\  | '_ \\ | '_| / -_)   / _` | / -_)   | |__  | | | '_| / -_) | |) | | | | '_|");
    gotoxy(49,26);
    printf(" |_|\\_| \\___/ |_|_|_| |_.__/ |_|   \\___|   \\__,_| \\___|   |____| |_| |_|   \\___| |___/  |_| |_|");
    gotoxy(49,28);
    printf("                        _       ___              _               ___    _");
    gotoxy(49,29);
    printf("                  ___  | |_    | __|  __   _ _  (_)  _ _   ___  |   \\  (_)  _ _");
    gotoxy(49,30);
    printf("                 / -_) |  _|   | _|  / _| | '_| | | | '_| / -_) | |) | | | | '_|");
    gotoxy(49,31);
    printf("                 \\___|  \\__|   |___| \\__| |_|   |_| |_|   \\___| |___/  |_| |_|");
    Fermer(&F);
    int value[2];
    int i,j,n;
    int diviseur;
    diviseur = (Maximum(nb_lect,nb_ecrt)/145)+1;
    value[0] = nb_lect;
    value[1] = nb_ecrt;
    gotoxy(1,34);
    textcolor(YELLOW);
    for(n=0;n<2;n++)
        {
            printf("\n          |\n");
            for(i=1;i<=3;i++)
            {
                if(i==2)
                    if(n==0){
                        printf(" LireDir  |");
                    }
                    else{
                        printf("EcrireDir |");
                    }
                else
                    printf("          |");

                for(j=1;j<=(value[n]/diviseur);++j)
                    printf("#");
                if(i==2)
                    printf(" (%d)\n",value[n]);
                else
                    printf("\n");
            }
            printf("          |\n\n");

            textcolor(LIGHTCYAN);
        }


        fflush(stdin);

        getch();

}

void Organisation_Globale()
{
    LOBF F;
    TBloc  buf;
    Ouvrir(&F,"ENSEIGNANT-MESRS.bin",'A');
    int i=Entete(F,1);
    LireDir(F,i,&buf);
    nb_lect++;
    int nb=buf.nb;
    int lien0=buf.lien;
    LireDir(F,buf.lien,&buf);
    nb_lect++;
    int lien1=buf.lien;
    LireDir(F,buf.lien,&buf);
    nb_lect++;
    int lien2=buf.lien;
    textcolor(LIGHTCYAN);
    printf("\t\t\t\t\t       ____                        _           _   _                     _       _           _      \n");
    printf("\t\t\t\t\t      / __ %c                      (_)         | | (_)                   | |     | |         | |     \n",92);
    printf("\t\t\t\t\t     | |  | |_ __ __ _  __ _ _ __  _ ___  __ _| |_ _  ___  _ __     __ _| | ___ | |__   __ _| | ___ \n");
    printf("\t\t\t\t\t     | |  | | '__/ _` |/ _` | '_ %c| / __|/ _` | __| |/ _ %c| '_ %c   / _` | |/ _ %c| '_ %c / _` | |/ _ %c\n",92,92,92,92,92,92);
    printf("\t\t\t\t\t     | |__| | | | (_| | (_| | | | | %c__ %c (_| | |_| | (_) | | | | | (_| | | (_) | |_) | (_| | |  __/\n",92,92);
    printf("\t\t\t\t\t      %c____/|_|  %c__, |%c__,_|_| |_|_|___/%c__,_|%c__|_|%c___/|_| |_|  %c__, |_|%c___/|_.__/ %c__,_|_|%c___|\n",92,92,92,92,92,92,92,92,92,92);
    printf("\t\t\t\t\t                  __/ |                                             __/ |                           \n");
    printf("\t\t\t\t\t                 |___/                                             |___/                            \n");
    textcolor(WHITE);
    if(lien0!=-1)
    {
        if(lien1!=-1)
        {
            if(lien2==-1)
            {
                if(nb!=1)
                {
                    printf("\n\n+------------+-----------------------+----------+        +------------+                       +----------+        +------------+-----------------------+----------+\n");
                    printf("|  Bloc %2d   |         ",lien1);textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("         | NB  1024 |        |  Bloc %2d   |                       | NB  1024 |        |  Bloc %2d   |         ",lien0,i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf("          | NB  %4d |\n",nb);
                    printf("+------------+-----------------------+----------+        +------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" %4d            |\n",nb);
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                                               |\n");
                    printf("|                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+\n");
                    printf("|                             |   Lien  %2d      |   ",lien2);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |   ",lien1);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |\n",lien0);
                    printf("+-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                    __|__");textcolor(LIGHTGREEN);printf("           |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                   |  |  |");textcolor(LIGHTGREEN);printf("          +----------------------------------------+               +--------------------------------------------+\n");

                }
                else
                {
                    printf("\n\n+------------+-----------------------+----------+        +------------+                       +----------+        +------------+-----------------------+----------+\n");
                    printf("|  Bloc %2d   |         ",lien1);textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("         | NB  1024 |        |  Bloc %2d   |                       | NB  1024 |        |  Bloc %2d   |         ",lien0,i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf("          | NB  %4d |\n",nb);
                    printf("+------------+-----------------------+----------+        +------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("             ");textcolor(WHITE);printf("                  |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        +-----------------------------------------------+\n");
                    printf("|                      .                        |        |                      .                        |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              ");
                    printf("|                      .                        |        |                      .                        |        +-----------------------------------------------+\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("|                      .                        |        |                      .                        |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("              ");textcolor(WHITE);printf("                 |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                                               |\n");
                    printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                    printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                                               |\n");
                    printf("|                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+\n");
                    printf("|                             |   Lien  %2d      |   ",lien2);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |   ",lien1);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |\n",lien0);
                    printf("+-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                      |");textcolor(LIGHTGREEN);printf("             |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                    __|__");textcolor(LIGHTGREEN);printf("           |                                        |               |                                            |\n");
                    textcolor(LIGHTRED);printf("                                   |  |  |");textcolor(LIGHTGREEN);printf("          +----------------------------------------+               +--------------------------------------------+\n");

                }

            }
            else
            {
                printf("+------------+                       +----------+        +------------+                       +----------+        +------------+-----------------------+----------+\n");
                printf("|  Bloc %2d   |                       | NB  1024 |        |  Bloc %2d   |                       | NB  1024 |        |  Bloc %2d   |         ",lien1,lien0,i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf("          | NB  %4d |\n",nb);
                printf("+------------+-----------------------+----------+        +------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enragistrement");textcolor(WHITE);printf(" 01              |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                printf("|                      .                        |        |                      .                        |        |                                               |\n");
                printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                printf("|                      .                        |        |                      .                        |        |                                               |\n");
                printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                printf("|                      .                        |        |                      .                        |        |                                               |\n");
                printf("|                      .                        |        |                      .                        |        |                      .                        |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("|               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020             |        |               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020             |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" %4d            |\n",nb);
                printf("+-----------------------------------------------+        +-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("|               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021             |        |               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021             |        |                                               |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022             |        |               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022             |        |                                               |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023             |        |               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023             |        |                                               |\n");
                printf("+-----------------------------------------------+        +-----------------------------------------------+        |                                               |\n");
                printf("|               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024             |        |               ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024             |        |                                               |\n");
                printf("|                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+\n");
                printf("|                             |   Lien  %2d      |   ",lien2);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |   ",lien1);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |\n",lien0);
                printf("+-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+\n");
                textcolor(LIGHTGREEN);printf("                                      |             |                                        |               |                                            |\n");
                textcolor(LIGHTGREEN);printf("                                      |             |                                        |               |                                            |\n");
                textcolor(LIGHTGREEN);printf("                                      |             |                                        |               |                                            |\n");
                textcolor(LIGHTGREEN);printf("                                      |             |                                        |               |                                            |\n");
                textcolor(LIGHTGREEN);printf("<-------------------------------------+             +----------------------------------------+               +--------------------------------------------+\n");
            }
        }
        else
        {
            if(nb!=1)
            {
                printf("\n\n\t\t\t\t\t+------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t|  Bloc %2d   |         ",lien0);textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("         | NB  1024 |        |  Bloc %2d   |         ",i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf("          | NB  %4d |\n",nb);
                printf("\t\t\t\t\t+------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                      .                        |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                      .                        |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                      .                        |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                      .                        |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" %4d            |\n",nb);
                printf("\t\t\t\t\t+-----------------------------------------------+        +-----------------------------------------------+\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                                               |\n");
                printf("\t\t\t\t\t|                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+\n");
                printf("\t\t\t\t\t|                             |   Lien  %2d      |   ",lien1);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |\n",lien0);
                printf("\t\t\t\t\t+-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                    __|__ ");textcolor(LIGHTGREEN);printf("          |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                   |  |  |");textcolor(LIGHTGREEN);printf("          +----------------------------------------+\n");
                textcolor(WHITE);
            }
            else
            {
                printf("\n\n\t\t\t\t\t+------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t|  Bloc %2d   |         ",lien0);textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("         | NB  1024 |        |  Bloc %2d   |         ",i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf("          | NB  %4d |\n",nb);
                printf("\t\t\t\t\t+------------+-----------------------+----------+        +------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |        |                ");textcolor(YELLOW);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 02              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 03              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 04              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 05              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 06              |        |                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        +-----------------------------------------------+\n");
                printf("\t\t\t\t\t|                      .                        |        |                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |\n");
                printf("\t\t\t\t\t|                      .                        |        +-----------------------------------------------+\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t|                      .                        |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1020            |        |                ");textcolor(YELLOW);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1021            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1022            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1023            |        |                                               |\n");
                printf("\t\t\t\t\t+-----------------------------------------------+        |                                               |\n");
                printf("\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 1024            |        |                                               |\n");
                printf("\t\t\t\t\t|                             +-----------------+");textcolor(LIGHTGREEN);printf("<--+");textcolor(WHITE);printf("    |                             +-----------------+\n");
                printf("\t\t\t\t\t|                             |   Lien  %2d      |   ",lien1);textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    |                             |   Lien  %2d      |\n",lien0);
                printf("\t\t\t\t\t+-----------------------------+-----------------+   ");textcolor(LIGHTGREEN);printf("|");textcolor(WHITE);printf("    +-----------------------------+-----------------+\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                      |");textcolor(LIGHTGREEN);printf("             |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                    __|__ ");textcolor(LIGHTGREEN);printf("          |                                        |\n");
                textcolor(LIGHTRED);printf("\t\t\t\t\t                                   |  |  |");textcolor(LIGHTGREEN);printf("          +----------------------------------------+\n");
                textcolor(WHITE);
            }
        }
    }
    else
    {
        if(nb!=1)
        {
                printf("\n\n\t\t\t\t\t\t\t\t+------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t\t\t\t|  Bloc %2d   |     ",i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf(" / ");textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("      | NB  %4d |\n",nb);
                printf("\t\t\t\t\t\t\t\t+------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" 01              |\n");
                printf("\t\t\t\t\t\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("      .       ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                      .                        |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                      .                        |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                      .                        |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                      .                        |\n");
                printf("\t\t\t\t\t\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" %4d            |\n",nb);
                printf("\t\t\t\t\t\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                             +-----------------+\n");
                printf("\t\t\t\t\t\t\t\t|                             |   ");textcolor(WHITE);printf("Lien");textcolor(WHITE);printf("  %2d      |\n",lien0);
                printf("\t\t\t\t\t\t\t\t+-----------------------------+-----------------+\n");
                textcolor(LIGHTRED);
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                    __|__ \n");
                printf("\t\t\t\t\t\t\t\t                                   |  |  |\n");
                textcolor(WHITE);
        }
        else
        {
                printf("\n\n\t\t\t\t\t\t\t\t+------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t\t\t\t|  Bloc %2d   |     ",i);textcolor(LIGHTGREEN);printf("T%cte",136);textcolor(WHITE);printf(" / ");textcolor(LIGHTRED);printf("Queue");textcolor(WHITE);printf("      | NB  %4d |\n",nb);
                printf("\t\t\t\t\t\t\t\t+------------+-----------------------+----------+\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(YELLOW);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(WHITE);printf("              ");textcolor(WHITE);printf("                 |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t\t\t\t\t\t|                ");textcolor(YELLOW);printf("Enregistrement");textcolor(WHITE);printf(" %4d            |\n",nb);
                printf("\t\t\t\t\t\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                                               |\n");
                printf("\t\t\t\t\t\t\t\t|                             +-----------------+\n");
                printf("\t\t\t\t\t\t\t\t|                             |   ");textcolor(WHITE);printf("Lien");textcolor(WHITE);printf("  %2d      |\n",lien0);
                printf("\t\t\t\t\t\t\t\t+-----------------------------+-----------------+\n");
                textcolor(LIGHTRED);
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                      |\n");
                printf("\t\t\t\t\t\t\t\t                                    __|__ \n");
                printf("\t\t\t\t\t\t\t\t                                   |  |  |\n");
                textcolor(WHITE);
        }
    }
    textcolor(WHITE);
    printf("\n\n\t\t\t\t\t\t\t      Appuyez sur une touche pour revenir au menu principale.\n");
    fflush(stdin);
    getch();
    Fermer(&F);

}

void Quitter(){

    system("cls");
    textcolor(YELLOW);
    gotoxy(77,2);
    printf("   __  __                        _");delay(50);
    gotoxy(77,3);
    printf("  |  \\/  |                      (_)");delay(50);
    gotoxy(77,4);
    printf("  | \\  / |   ___   _ __    ___   _");delay(50);
    gotoxy(77,5);
    printf("  | |\\/| |  / _ \\ | '__|  / __| | |");delay(50);
    gotoxy(77,6);
    printf("  | |  | | |  __/ | |    | (__  | |");delay(50);
    gotoxy(77,7);
    printf("  |_|  |_|  \\___| |_|     \\___| |_|");delay(50);
    gotoxy(62,9);
    printf("                              _     _");delay(50);
    gotoxy(62,10);
    printf("                             ( \\---/ )");delay(50);
    gotoxy(62,11);
    printf("                              ) . . (");delay(50);
    gotoxy(62,12);
    printf("________________________,--._(___Y___)_,--._______________________");delay(50);
    gotoxy(62,13);
    printf("                        `--'           `--'");delay(50);
    gotoxy(40,14);
    printf("  _____                                             _                             _         _   _              _");delay(50);
    gotoxy(40,15);
    printf(" |  __ \\                                           | |                           (_)       (_) | |            | |");delay(50);
    gotoxy(40,16);
    printf(" | |__) |   ___    _   _   _ __    __   __   ___   | |_   _ __    ___    __   __  _   ___   _  | |_    ___    | |");delay(50);
    gotoxy(40,17);
    printf(" |  ___/   / _ \\  | | | | | '__|   \\ \\ / /  / _ \\  | __| | '__|  / _ \\   \\ \\ / / | | / __| | | | __|  / _ \\   | |");delay(50);
    gotoxy(40,18);
    printf(" | |      | (_) | | |_| | | |       \\ V /  | (_) | | |_  | |    |  __/    \\ V /  | | \\__ \\ | | | |_  |  __/   |_|");delay(50);
    gotoxy(40,19);
    printf(" |_|       \\___/   \\__,_| |_|        \\_/    \\___/   \\__| |_|     \\___|     \\_/   |_| |___/ |_|  \\__|  \\___|   (_)");
    textcolor(WHITE);
    gotoxy(91,23);
    printf("Contactez");
    gotoxy(84,24);
    printf("  .----------------.");
    gotoxy(84,25);
    printf(" /    _H______H_    \\@,");
    gotoxy(84,26);
    printf(" \\____/        \\____/ @,");
    gotoxy(84,27);
    printf("    /            \\    `@");
    gotoxy(84,28);
    printf("    |  LI LI LI  |    ,@");
    gotoxy(84,29);
    printf("    |  LI LI LI  |   ,@'");
    gotoxy(84,30);
    printf("    |  LI LI LI  |  ,@'");
    gotoxy(84,31);
    printf("    |  LI LI LI  |@@'");
    gotoxy(84,32);
    printf("    \\            /'");
    gotoxy(84,33);
    printf("     `----------'");
    gotoxy(93,34);
    printf("nous!");
    textcolor(WHITE);
    gotoxy(5,24);
    printf("+-------------------------------------------------------------------------+");
    gotoxy(5,25);
    printf("|                                                                         |");
    gotoxy(5,26);
    printf("---------------------------------------------------------------------------");
    gotoxy(5,27);
    printf("|                                                                         |");
    gotoxy(5,28);
    printf("---------------------------------------------------------------------------");
    gotoxy(5,29);
    printf("|                                                                         |");
    gotoxy(5,30);
    printf("---------------------------------------------------------------------------");
    gotoxy(5,31);
    printf("|                                                                         |");
    gotoxy(5,32);
    printf("---------------------------------------------------------------------------");
    gotoxy(5,33);
    printf("|                                                                         |");
    gotoxy(5,34);
    printf("---------------------------------------------------------------------------");

    gotoxy(112,24);
    printf("+-------------------------------------------------------------------------+");
    gotoxy(112,25);
    printf("|                                                                         |");
    gotoxy(112,26);
    printf("---------------------------------------------------------------------------");
    gotoxy(112,27);
    printf("|                                                                         |");
    gotoxy(112,28);
    printf("---------------------------------------------------------------------------");
    gotoxy(112,29);
    printf("|                                                                         |");
    gotoxy(112,30);
    printf("---------------------------------------------------------------------------");
    gotoxy(112,31);
    printf("|                                                                         |");
    gotoxy(112,32);
    printf("---------------------------------------------------------------------------");
    gotoxy(112,33);
    printf("|                                                                         |");
    gotoxy(112,34);
    printf("---------------------------------------------------------------------------");
    textcolor(LIGHTGREEN);
    gotoxy(7,25);
    printf("Nom:");
    gotoxy(7,27);
    printf("Pr%cnom:",130);
    gotoxy(7,29);
    printf("E-Mail:");
    gotoxy(7,31);
    printf("Num%cro de t%cl%cphone:",130,130,130);

    gotoxy(7,33);
    printf("Lien Linkedin:");

    gotoxy(114,25);
    printf("Nom:");
    gotoxy(114,27);
    printf("Pr%cnom:",130);
    gotoxy(114,29);
    printf("E-Mail:");
    gotoxy(114,31);
    printf("Num%cro de t%cl%cphone:",130,130,130);
    gotoxy(114,33);
    printf("Lien Linkedin:");
    gotoxy(12,25);
    textcolor(WHITE);
    printf("BOUYAKOUB");
    gotoxy(15,27);
    printf("Rayane");
    gotoxy(15,29);
    printf("lr_bouyakoub@esi.dz");
    gotoxy(28,31);
    printf("+213 38 51 15 81");
    gotoxy(22,33);
    printf("https://www.linkedin.com/in/rayane-bouyakoub");
    gotoxy(119,25);
    printf("OUIKENE");
    gotoxy(122,27);
    printf("Youcef");
    gotoxy(122,29);
    printf("ly_ouikene@esi.dz");
    gotoxy(135,31);
    printf("+213 21 36 15 35");
    gotoxy(129,33);
    printf("https://www.linkedin.com/in/youcef-ouikene");
    textcolor(LIGHTCYAN);
    gotoxy(83,38);
    printf("  * %c%c%c%c    %c%c%c   %c%c%c *",219,219,219,219,219,219,219,219,219,219);
    gotoxy(83,39);
    printf("    %c      %c       %c       ",219,219,219);
    gotoxy(83,40);
    printf(" *  %c%c%c%c    %c%c     %c   *",219,219,219,219,219,219,219);
    gotoxy(83,41);
    printf("    %c         %c    %c        ",219,219,219);
    gotoxy(83,42);
    printf("  * %c%c%c%c   %c%c%c    %c%c%c *",219,219,219,219,219,219,219,219,219,219);
    gotoxy(58,46);
    char ligne[100] = "Ecole Nationale Superieure d'Informatique (ESI ex.INI), Alger, Oued Smar 16309.";
    ligne [0] = 144;
    ligne [19] = 130;
    Ecrire_chaine(ligne,10,LIGHTCYAN,BLACK);
    textcolor(WHITE);
    gotoxy(62,49);
    printf("Veuillez patienter un instant lors de la sauvegarde des tables d'index.");
    gotoxy(1,1);

}
