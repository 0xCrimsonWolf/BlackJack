#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

#include "Fonctions.h"
#include "Stats.h"

#define TAILLE_CARTE 52

void menuJoueur(char* nom, int pos)
{
    char menu;

    srand(time(NULL));
    fflush(stdin);

    float jeu[52] = {-1,1.1,1.2,1.3,1.4,2.1,2.2,2.3,2.4,3.1,3.2,3.3,3.4,4.1,4.2,4.3,4.4,5.1,5.2,5.3,5.4,6.1,6.2,6.3,6.4,7.1,7.2,7.3,7.4,8.1,8.2,8.3,8.4,9.1,9.1,9.2,9.3,9.4,10.1,10.2,10.3,10.4,11.1,11.2,11.3,11.4,12.1,12.2,12.3,12.4,13.1,13.2,13.3,13.4};

    do
    {
        system("cls");
        printf("-------------- Menu BlackJack --------------\n\n\
    1. Lancer une partie de BlackJack !\n\
    2. Afficher vos statistiques.\n\
    3. Afficher les r%cgles.\n\
    4. Quitter.\n\n\
--------------------------------------------\n\n", 138);

        fflush(stdin);
        scanf("%c", &menu);

        switch(menu)
        {
            case '1':
                lancerPartie(jeu, nom, pos);     // Le jeu de carte (vecteur au dessus) + le nom du joueur (pour les stats)
                break;
            case '2':
            {
                affichStatsJoueur(nom);
                break;
            }
            case '3':
                affichRules();
                break;
            case '4':
            {
                system("cls");
                printf("\nMerci, et %c bient%ct %s !\n\n%c Debarsy William, 2020.", 133, 147, nom, 184);
                return;
                break;
            }
        }
    }while(menu!=('1'|'2'|'3'|'4'));
}

void menuAdmin(char* nom, int pos)
{
    char menu;

    srand(time(NULL));
    fflush(stdin);

    float jeu[52] = {-1,1.1,1.2,1.3,1.4,2.1,2.2,2.3,2.4,3.1,3.2,3.3,3.4,4.1,4.2,4.3,4.4,5.1,5.2,5.3,5.4,6.1,6.2,6.3,6.4,7.1,7.2,7.3,7.4,8.1,8.2,8.3,8.4,9.1,9.1,9.2,9.3,9.4,10.1,10.2,10.3,10.4,11.1,11.2,11.3,11.4,12.1,12.2,12.3,12.4,13.1,13.2,13.3,13.4};

    do
    {
        system("cls");
        printf("-------------- Menu BlackJack (ADMIN) --------------\n\n\
    1. Lancer une partie de BlackJack !\n\
    2. Afficher vos statistiques.\n\
    3. Afficher les r%cgles.\n\
    4. Quitter.\n\n\
    5. Afficher la BDD\n\
    6. Gestion des joueurs\n\n\
----------------------------------------------------\n\n", 138);

        fflush(stdin);
        scanf("%c", &menu);

        switch(menu)
        {
        case '1':
            lancerPartie(jeu, nom, pos);     // Le jeu de carte (vecteur au dessus) + le nom du joueur (pour les stats)
            break;
        case '2':
        {
            printf("-------------------------- Vos statistiques --------------------------\n\n");

            affichStatsJoueur(nom);

            printf("\n----------------------------------------------------------------------\n");

            break;
        }
        case '3':
            affichRules();
            break;
        case '4':
        {
            system("cls");
            printf("\nMerci, et %c bient%ct %s !\n\n%c Debarsy William, 2020.", 133, 147, nom, 184);
            return;
            break;
        }
        case '5':
            affichAllEnr();
            break;
        case '6':
            gestionJoueur();
            break;
        }
    }while(menu!=('1'|'2'|'3'|'4'));
}

void gestionJoueur()
{
    char menu;

    do
    {
        system("cls");
        printf("-------------- Gestion des joueurs (ADMIN) --------------\n\n\
    1. Ajouter un utilisateur.\n\
    2. Modifier un utilisateur.\n\
    3. Supprimer un utilisateur.\n\
    4. Quitter.\n\n\
---------------------------------------------------------\n\n");

        fflush(stdin);
        scanf("%c", &menu);

        switch(menu)
        {
            case '1':
            {
                char pseudo[30], mdp[30];
                int test;
                system("cls");
                printf("Quel est votre pseudo ?\n\n\t> ");
                checkchaineAlphaAndNum(pseudo, 30);
                system("cls");
                printf("Quel est votre mot de passe ?\n\n\t> ");
                checkchaineAlphaAndNum(mdp, 30);
                test=addEnr(pseudo, mdp);
                system("cls");
                if (test==0)
                    printf("\n\tErreur: addEnr. ");
                else
                    printf("\n\tAjout de l'utilisateur avec succ%cs. ", 138);
                Sleep(2000);
                break;
            }
            case '2':

                break;
            case '3':

                break;
            case '4':
                return;
                break;
        }

    }while(menu!=('1'|'2'|'3'|'4'));
}

void lancerPartie(float *jeu, char* Nom_Joueur, int Position_EnrStats_Joueur)   // Lance une partie + vérifie les conditions du BJ + affiche si gagné, perdu, égalité, ou BJ, ...
{
    STATS EnrStats_Joueur;
    float Croupier;
    float Joueur_tab[10]={0}, Croupier_tab[10]={0};
    int zzz=0, compteur=-1, i=0, j=0, l=0, nb_joueur=0, nb_croupier=0, cls=0, nbr_j, cond=-123, compt=2, test, first=1;
    char c;
    clock_t temps;

    system("cls");

    printf("D%cbut de la partie", 130);

    Sleep(400);
    printf(" . ");
    Sleep(400);
    printf(". ");
    Sleep(400);
    printf(". \n");
    Sleep(400);

    temps=clock();
    fflush(stdin);

    do {

        system("cls");
        printf("-------------- Partie en cours --------------\n\n");

        compteur++;

        printf("Croupier :   ");    // Carte du croupier

        if (i==0)
        {
            read_Croupier(jeu, Croupier_tab, &i, &nb_croupier, cls);
            printf("\n\t     ???");             // Permet de ne pas voir la carte avec les "???"
                Croupier=rdm_carte(jeu);        // Choisit et stock quand même la carte dans le carte_tab mais ne l'affiche pas
                Croupier_tab[i]=Croupier;
                nb_croupier=nb_croupier + cc_carte((int)Croupier);
                printf("\t(%d)", cc_carte((int)Croupier_tab[0]));
                i++;
        }
        if (c=='R' || c=='r')     // Si le joueur décide de rester
        {
            affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nb_joueur, 0);

            while (condition_bj(nb_croupier, Croupier_tab, nb_joueur, Joueur_tab) == -17)
            {
                printf("\n\t     ");
                Sleep(700);
                Croupier_tab[compt]=rdm_carte(jeu);
                nb_croupier = nb_croupier + cc_carte((int)Croupier_tab[compt]);
                affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nb_joueur, 0);

                compt++;
            }
            if (condition_bj(nb_croupier, Croupier_tab, nb_joueur, Joueur_tab) == 17)
            {
                if (nb_croupier > nb_joueur)
                    cond=0;
                else
                    if (nb_croupier < nb_joueur)
                        cond=1;
                    else
                        if (nb_croupier == nb_joueur)
                            cond=-1;
                zzz=1;
            }
        }
        if (c=='T' || c=='t')     // Si le joueur décide de tirer
        {
            read_carte(&Croupier_tab[0]);
            printf("\n\t     ???");
            printf("\t(%d)", cc_carte((int)Croupier_tab[0]));
        }


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        if (zzz!=1)
        {
            printf("\n\nVos cartes : ");    // Carte du joueur

            if (j==0)
            {
                read_Joueur(jeu, Joueur_tab, &j, &nb_joueur, cls);
                read_Joueur(jeu, Joueur_tab, &j, &nb_joueur, cls);
            }
            if (c=='T' || c=='t')       // Si TIRER
            {
                read_Joueur(jeu, Joueur_tab, &j, &nb_joueur, cls);
            }
            if (c=='R' || c=='r')       // Si RESTER
            {
                l=0;
                read_carte(&Joueur_tab[l]);
                nbr_j = cc_carte((int)Joueur_tab[l]);
                l++;
                while ((int)Joueur_tab[l]!=0)
                {
                    printf("\n\t     ");
                    read_carte(&Joueur_tab[l]);
                    nbr_j=nbr_j + cc_carte((int)Joueur_tab[l]);
                    l++;
                }
                printf("\t(%d)", nbr_j);
            }
        }

        if (cond==0 || cond==1 || cond==-1)
            Sleep(1);
        else
            if (cond==-123 || cond==456)
                cond=condition_bj(nb_croupier, Croupier_tab, nb_joueur, Joueur_tab);

        if ((c=='R' || c=='r') && zzz==0)
            affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nbr_j, 0);

        if (compteur==0)
        {
            if (cond==21)
            {
                printf("\n\n\nVous avez un BlackJack ! Bien jou%c !\n\n", 130);
                cond=1;
            }
            else
                cond=456;
        }
        if (compteur>=1 && (c=='T' || c=='t'))
        {
            if (cond==999)
            {
                affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nb_joueur, 0);
                printf("\n\n\nVous avez perdu, vous avez bust...\n\n");
            }
            else
                cond=456;
        }
        if (compteur>=1 && (c=='R' || c=='r'))
        {
            if (cond==-21 || cond==17 ||cond==-999 ||cond==-1 || cond==1 || cond==0)
            {
                if (cond==-21)
                    printf("\n\n\nLe Croupier a un BlackJack ! Vous avez perdu ...\n\n");
                if (cond==17)
                    printf("\n\n\nVous avez gagn%c !\n\n", 130);
                if (cond==1)
                    printf("\n\n\nVous avez gagn%c !\n\n", 130);
                if (cond==0)
                {
                    affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nb_joueur, 0);
                    printf("\n\n\nVous avez perdu...\n\n");
                }
                if (cond==-1)
                    printf("\n\n\nC'est une %cgalit%c.\n\n", 130, 130);
                if (cond==-999)
                    printf("\n\n\nVous avez gagn%c, le croupier a bust !\n\n", 130);
            }
            else
                cond=456;
        }

        if (cond==456)      // Premier tour où l'on propose de tirer ou bien de rester au joueur
        {
            do
            {
                system("cls");
                affich_Jeu(Croupier_tab, nb_croupier, Joueur_tab, nb_joueur, first);    // Le paramètre first sert à afficher les ??? pour les cartes du croupier

                printf("\n\nTirer ou Rester (T ou R)\n\n");
                fflush(stdin);

                c=getchar();
                if (c=='T' || c=='R' || c=='t' || c=='r')   // Forcage de boucle pour bien avoir T,R,t ou r
                {
                    test=1;     // Caractère entré sont bien : OK
                }
                else
                    test=0;     // Caractère entré pas bien  : KO

                cls=1;

            }while(test==0);
        }
        else
            c=0;

    }while (c=='T' || c=='R' || c=='t' || c=='r' );  // Condition = les conditions de refus (bust, etc)

    fflush(stdin);

    // Connaitre le temps en secondes de la partie (pour les stats)

    temps=clock()-temps;
    float secondes;
    secondes=((float)temps/CLOCKS_PER_SEC);

    // Prendre l'enr dans le fichier & l'incrémenter du nbr (win, defeats, timing) et ensuite le remettre (modify)
    // Savoir si défaite / victoire via les cond

    readEnr(&EnrStats_Joueur, Position_EnrStats_Joueur+1);

    if (cond==21||cond==1||cond==-999)                // Le joueur gagne
    {
        EnrStats_Joueur.win++;
    }
    else if (cond==-21||cond==0||cond==999)           // Le joueur perd
    {
        EnrStats_Joueur.defeat++;
    }
    else if (cond==-1)
    {
        EnrStats_Joueur.draw++;
    }

    EnrStats_Joueur.timing=EnrStats_Joueur.timing+secondes;

    printf("---------------------------------------------\n\n\
Appuyez sur ENTER pour retourner au menu. ");

    modifyEnr(&EnrStats_Joueur, Position_EnrStats_Joueur+1);

    scanf("%c", &c);
}

int cc_carte(int carte) // Permet de mettre les valets (11), dames (12) et rois (13) à une valeur de 10
{
    if (carte > 10)
        return 10;
    else
        return carte;
}

float rdm_carte(float *jeu)     // Randomize une carte dans le jeu[]
{
    float a;;
    int Carte;

    do
    {
        Carte=rand() % 52;
    }while(Carte==0);

    a=jeu[Carte];

    return a;
}

void read_carte(float *carte)    // Permet de lire le float qui est égal à une carte (7.4 = 7 de Trèfle)
{
    float a, b;

    if ((int)*carte==1)
        printf("As de ");
    else
    {
        if ((int)*carte==11)
            printf("Valet de ");
        else
        {
            if ((int)*carte==12)
                printf("Dame de ");
            else
            {
                if ((int)*carte==13)
                    printf("Roi de ");
                else
                    printf("%d ", (int)*carte);
            }
        }
    }

    a=(float)*carte*10;    // Calcul pour connaitre le type de la carte
    b=a-(int)*carte*10;    // ===> Coeur = 0.1  Carreau = 0.2  Pique = 0.3  Trèfle = 0.4

    if ((int)b==1)
        printf("%c", 3);
    else
    {
        if ((int)b==2)
            printf("%c", 4);
        else
        {
            if ((int)b==3)
                printf("%c", 6);
            else
                if ((int)b==4)
                    printf("%c", 5);
        }
    }
}

void read_Croupier(float *jeu, float *Croupier_tab, int *i, int *nb_croupier, int cls)       // Permet de lire les cartes du croupier
{
    float Croupier;
    int x;

    Croupier=rdm_carte(jeu);
    Croupier_tab[*i]=Croupier;   // Le Croupier_tab = Historique des cartes tirées
    if (*i==0)
    {
        Sleep(1500);
        read_carte(&Croupier);
        *nb_croupier=cc_carte((int)Croupier_tab[*i]);
    }
    if (*i>=1 && cls==1)
    {
        for (x=1;x<=*i;x++)
        {
            if (x>1)
                printf("\n\t     ");
            read_carte(&Croupier_tab[x-1]);
        }
    }
    if (*i>=1)
    {
        printf("\n\t     ");
        read_carte(&Croupier);
        *nb_croupier = *nb_croupier + cc_carte((int)Croupier);
        printf("\t(%d)", *nb_croupier);   // Total entre parenthèse
    }

    *i=*i+1;
}

void read_Joueur(float *jeu, float *Joueur_tab, int *j, int *nb_Joueur, int cls)     // Permet de lire les cartes du joueurs
{
    float Joueur;
    int y;

    Joueur=rdm_carte(jeu);
    Joueur_tab[*j]=Joueur;   // Le Joueur_tab = Historique des cartes tirées
    if (*j==0)
    {
        Sleep(1500);
        read_carte(&Joueur);
        *nb_Joueur=cc_carte((int)Joueur_tab[*j]);
    }
    if (*j>=1 && cls==1)
    {
        for (y=1;y<=*j;y++)
        {
            if (y>1)
                printf("\n\t     ");
            read_carte(&Joueur_tab[y-1]);
        }
    }
    if (*j>=1)
    {
        printf("\n\t     ");
        read_carte(&Joueur);
        *nb_Joueur = *nb_Joueur + cc_carte((int)Joueur);
        printf("\t(%d)", *nb_Joueur);   // Total entre parenthèse
    }

    *j=*j+1;
}

void affich_Jeu(float *croupier_tab, int nb_croupier, float *joueur_tab, int nb_joueur, int first)     // Affiche le jeu (lancement d'une partie)
{
    int i;
    system("cls");
    printf("-------------- Partie en cours --------------\n\n");
    printf("Croupier :   ");

    if (first==1)                           // Si première fois (pour les ???)
    {
        read_carte(&croupier_tab[0]);
        printf("\n\t     ???");
        printf("\t(%d)", cc_carte((int)croupier_tab[0]));
    }
    else                                    // Sinon on affiche comme d'habitude
    {
        read_carte(&croupier_tab[0]);
        printf("\n\t     ");
        for (i=1;croupier_tab[i]!=0;i++)
        {
            read_carte(&croupier_tab[i]);
            if (croupier_tab[i+1]!=0)
                printf("\n\t     ");
        }
        printf("\t(%d)", nb_croupier);
    }

    printf("\n\nVos cartes : ");
    read_carte(&joueur_tab[0]);
    printf("\n\t     ");
    for (i=1;joueur_tab[i]!=0;i++)
    {
        read_carte(&joueur_tab[i]);
        if (joueur_tab[i+1]!=0)
            printf("\n\t     ");
    }
    printf("\t(%d)", nb_joueur);
}

int condition_bj(float nb_croupier, float *croupier_tab, float nb_joueur, float *joueur_tab)    // Vérifie les conditions
{
    /* Return :     21   =  Joueur BlackJack
                    -21  =  Croupier BlackJack
                    17   =  Croupier ne peut plus tirer
                    0    =  Le croupier gagne
                    1    =  Le joueur gagne
                    -1   =  Égalité
                    999  =  Joueur Busted
                    -999 =  Croupier Busted
    */

    if (joueur_tab[2] == 0 && nb_joueur == 21)
        return 21;
    if (croupier_tab[2] == 0 && nb_croupier == 21)
        return -21;
    if (nb_croupier>21)
        return -999;
    if (nb_joueur>21)
        return 999;
    if (nb_croupier >= 17)
        return 17;
    if (nb_croupier <= 17)
        return -17;

    return 0;
}

void affichRules()      // Permet d'afficher les règles du jeu
{
    char menu;

    system("cls");
    printf("------------- R%cgles BlackJack -------------\n\n\
Bienvenue dans les r%cgles !\n\n\
Le but du BlackJack est de battre le croupier sans que la valeur de vos cartes d%cpassent 21.\n\
Si votre score est au-del%c de 21, on dira que vous %ctes br%cl%c.\n\n\
Voici donc les valeurs des diff%crentes cartes du jeu :\n\n\
    De 2 %c 9, c'est la valeur de la carte elle-m%cme.\n\
    De 10 au Roi, la carte vaut 10.\n\
    Et enfin l'As, vaut 1.\n\n\
On parlera de 'Blackjack' lorsque vous aurez avec les deux premi%cres cartes la somme de 21.\n\n\
--------------------------------------------\n", 138, 138, 130, 133, 136, 150, 130, 130, 133, 136, 138);
    printf("\nAppuyez sur ENTER pour revenir au menu. ");
    fflush(stdin);
    scanf("%c", &menu);
}

int checkchaineAlpha(char* Chaine, int max)     // Fonction qui check si la chaine entrée est bien un alpha (prénom, nom, marquen ville,...)
{                                               // Pointeur de la chaine rempli + le nbr de caractère de cette chaine (à forcer)
    int compt=0, rc=0;                          // Return : -1 = mauvais et 0 si c'est bon
    unsigned char c;

    fflush(stdin);

    do
    {
        c=getchar();

        if (compt==0)
        {
            if (c=='\n')        // Si le premier caractère entré est un "\n" ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c=='-')    // Si le premier caractère entré est un "-" ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c==32)     // Si le premier caractère entré est un " " ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c==39)     // Si le premier caractère entré est un " ' " ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
        }
        if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c==32 || c==39 || c=='-' || (c>=128 && c<=154) || (c>=160 && c<=165) || (c>=233 && c<=237) || c==181 || c==182 || c==183 || c==198 || c==199 || c==210 || c==211 || c==212 || c==214 || c==215 || c==216)
        {
            *Chaine=c;
            Chaine++;
        }
        else if (c!='\n')       // Si le caractère entré n'est ni de "a" à "z", ni de "A" à "Z", ni de "-", ni de " " et ni de "\n" ==> Erreur
        {
            //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
            rc=-1;
            return rc;
        }
        *Chaine=0;
        compt++;

    }while (c!='\n' && compt<=max+1);

    if (compt>max+1)            // Si la chaine dépasse max ==> Erreur
    {
        //printf("\nErreur: la chaine entr%ce depasse les caract%cres max (%d).\n\n", 130, 138, max);
        rc=-1;
    }
    else                        // On décrémente la chaine pour ne pas avoir le "\n"
    {
        Chaine--;
    }

    return rc;
}

int checkchaineAlphaAndNum(char* Chaine, int max)       // Fonction qui check si la chaine entrée est bien un alpha et un num
{                                                       // Pointeur de la chaine rempli + le nbr de caractère de cette chaine (à forcer)
    int compt=0, rc=0;                                  // Return : -1 = mauvais et 0 si c'est bon
    unsigned char c;

    fflush(stdin);

    do
    {
        c=getchar();

        if (compt==0)
        {
            if (c=='\n')        // Si le premier caractère entré est un "\n" ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c=='-')    // Si le premier caractère entré est un "-" ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c==32)     // Si le premier caractère entré est un " " ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
            else if (c==39)     // Si le premier caractère entré est un " ' " ==> Erreur
            {
                //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
                rc=-1;
            }
        }
        if ((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z') || c==32 || c==39 || c=='-' || (c>=128 && c<=154) || (c>=160 && c<=165) || (c>=233 && c<=237) || c==181 || c==182 || c==183 || c==198 || c==199 || c==210 || c==211 || c==212 || c==214 || c==215 || c==216)
        {
            *Chaine=c;
            Chaine++;
        }
        else if (c!='\n')       // Si le caractère entré n'est ni de 0 à 9 "a" à "z", ni de "A" à "Z", ni de "-", ni de " " et ni de "\n" ==> Erreur
        {
            //printf("\nErreur: la chaine entr%ce n'est pas valide.\n\n", 130);
            rc=-1;
            return rc;
        }
        *Chaine=0;
        compt++;

    }while (c!='\n' && compt<=max+1);

    if (compt>max+1)            // Si la chaine dépasse max ==> Erreur
    {
        //printf("\nErreur: la chaine entr%ce depasse les caract%cres max (%d).\n\n", 130, 138, max);
        rc=-1;
    }
    else                        // On décrémente la chaine pour ne pas avoir le "\n"
    {
        Chaine--;
    }

    return rc;
}

