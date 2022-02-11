#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

#include "Fonctions.h"
#include "Stats.h"

#define FILENAME "Statistiques.dat"
#define TAILLE_CARTE 52

/*  ------ Conventions du code ------

    Ordre de distribution : Joueur - Croupier - Joueur - Croupier (non-visible) (4 premières cartes)

    Coeur = 0.1  Carreau = 0.2  Pique = 0.3  Trèfle = 0.4

    Avoir un BlackJack = 10(roi dame valet 10) et 1 (as)

*/

int main()
{
    STATS Enr;
    int pos, test;
    char c;
    char nom[30], password[30];


    // Partie login et création de compte       !!! A FAIRE : Système de mot de passe avec conio.h pour cacher la saisie !!!


    if (searchEnr("admin")==-9)       // Pour ne pas tout le temps ajouter admin on va check si le premier enr == bien l'admin
    {                                 // Si -1 : on le crée sinon on ne le crée pas, il existe déjà
        Enr.id=1;
        strcpy(Enr.nom, "admin");
        strcpy(Enr.mdp, "999");
        Enr.timing=6039;
        Enr.win=999;
        Enr.defeat=999;
        Enr.draw=999;

        writeEnr(&Enr);
    }

    do
    {
        fflush(stdin);
        printf("Avez-vous un compte [Y/N] ? ");
        scanf("%c", &c);
        fflush(stdin);
        system("cls");
        if (c=='Y' || c=='y')                           // Login du compte dont le pseudo est la saisie
        {
            do
            {
                system("cls");
                printf("Quel est votre pseudo ?\n\n\t> ");
                test=checkchaineAlphaAndNum(nom, 30);
                if (test==-1)
                {
                    test=test;          // Useless
                }
                else
                {
                    test=searchEnr(nom);
                    if (test<0)    // Si la recherche n'est pas bonne
                    {
                        test=-1;
                    }
                    else            // Si elle est bonne alors on vérif le mdp
                    {
                        pos=test;   // On stock la position de l'enregistrement pour le modifié plus tard
                        do
                        {
                            system("cls");
                            printf("Quel est votre mot de passe ?\n\n\t> ");
                            test=checkchaineAlphaAndNum(password, 30);

                                                      // Recherche pour le mot de passe
                                FILE* sf;
                                STATS EnrStats;

                                sf=fopen(FILENAME, "rb");
                                if (sf==NULL)
                                {
                                    perror("Erreur de fopen.\n");
                                    return -1;
                                }

                                fseek(sf, pos*sizeof(STATS), SEEK_SET);
                                test=fread(&EnrStats, sizeof(STATS), 1, sf);
                                fclose(sf);

                            if (strcmp(EnrStats.mdp, password)==0)    // Si les mots de passes correspondent
                            {
                                test=999;
                            }

                        } while(test!=999);
                        test=0;     // Permet de sortir de la boucle do (avez vous un compte)
                    }
                }

            }while(test==-1);
        }
        else if (c=='N' || c=='n')          // Création du compte dont le pseudo est la saisie
        {
            do
            {
                do
                {
                    system("cls");
                    printf("Entrez un pseudo :\n\n\t> ");
                    test=checkchaineAlphaAndNum(nom, 30);
                    if (test==-1)
                    {
                        test=test;
                    }
                    else
                    {
                        test=searchEnr(nom);
                        if (test>=0)            // Pseudo déjà existant
                        {
                            test=-1;
                            system("cls");
                            printf("Entrez un pseudo :\n\n\t Erreur: pseudo deja existant...");
                            Sleep(3500);
                        }
                        else                    // Pseudo non-existant (donc le pseudo est good)
                        {
                            system("cls");
                            printf("Entrez un mot de passe :\n\n\t> ");
                            test=checkchaineAlphaAndNum(password, 30);
                            if (test==-1)
                            {
                                test=test;
                            }
                            else
                            {
                                system("cls");
                                addEnr(nom, password);      // Ajout de l'enregistrement avec le nom saisi
                                test=searchEnr(nom);
                                pos=test;                   // On stock la position de l'enregistrement pour le modifié plus tard
                                printf("\nBonjour %s, votre compte vient d'etre cree.\n\n", nom);
                                test=0;
                                Sleep(1600);
                            }
                        }
                    }

                } while(test==-1);

            }while(test==-1);
        }

    }while(c!='N'|'n'|'Y'|'y' && test!=0);


    // Partie menu et choix


    if (strcmp(nom, "admin")==0)
        menuAdmin(nom, pos);        // Menu de l'admin
    else
    {
        system("cls");
        printf("\nBonjour %s !\n\n", nom);
        Sleep(1000);
        menuJoueur(nom, pos);       // Menu pour les joueurs
    }
    return 0;
}
