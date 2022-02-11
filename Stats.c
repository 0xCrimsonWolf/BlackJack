#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

#include "Stats.h"

#define FILENAME "Statistiques.dat"

// return value : 1 si OK , 0 si KO
int writeEnr(STATS* EnrStats)
{
    FILE* streamfile;
    int taille, test;
    streamfile=fopen(FILENAME, "ab");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    fseek(streamfile, 0, SEEK_END);
    taille=ftell(streamfile);
    fseek(streamfile, taille, SEEK_SET);

    test=fwrite(EnrStats, sizeof(STATS), 1, streamfile);
    if (test!=1)
    {
        perror("Erreur de frwite.\n");
        fclose(streamfile);
        return 0;
    }
    else
    {
        fclose(streamfile);
        return 1;
    }
    fclose(streamfile);
}

// return value : 1 si OK , 0 si KO
int readEnr(STATS* EnrStats, int pos)
{
    FILE* streamfile;
    int taille, test;
    streamfile=fopen(FILENAME, "rb");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    pos=pos-1;                                          // Car sinon, si l'user veut l'enr 1 ca lui donnera le deuxième
    fseek(streamfile, pos*sizeof(STATS), SEEK_SET);     // et non le premier car on commence à 0

    test=fread(EnrStats, sizeof(STATS), 1, streamfile);
    if (test!=1)
    {
        perror("Erreur de fread.\n");
        fclose(streamfile);
        return 0;
    }
    else
    {
        fclose(streamfile);
        return 1;
    }
}

// return value : 1 si OK , 0 si KO
int affichAllEnr()
{
    FILE* streamfile;
    STATS Enr;
    int i, taille;
    char c;

    system("cls");

    streamfile=fopen(FILENAME, "rb");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    fseek(streamfile, 0, SEEK_END);
    taille=ftell(streamfile);               // Nombre en octets
    taille=taille/sizeof(STATS);            // Nombre en blocs d'enr

    printf("----------------------------------- Database of all players -----------------------------------\n\n\
   ID         PSEUDO       PASSWORD         WIN      DEFEAT        DRAW               TIMING\n\n");     // Entête d'affichage

    for (i=0;i<taille;i++)
    {
        fseek(streamfile, i*sizeof(STATS), SEEK_SET);
        fread(&Enr, sizeof(STATS), 1, streamfile);
        printf("%5d", Enr.id);
        printf("%15s", Enr.nom);
        printf("%15s", Enr.mdp);
        printf("%12d", Enr.win);
        printf("%12d", Enr.defeat);
        printf("%12d", Enr.draw);
        printf("%15.2d:%.2dmin\n", (int)Enr.timing/60, (int)Enr.timing%60);
    }

    printf("\n-----------------------------------------------------------------------------------------------\n");

    fclose(streamfile);

    printf("\nAppuyez sur ENTER pour revenir au menu. ");
    fflush(stdin);
    scanf("%c", &c);

    return 1;
}

// return value : 1 si OK , 0 si KO
int affichStatsJoueur(char* nom)
{
    FILE* streamfile;
    STATS Enr;
    int i, pos;
    char c;

    system("cls");

    streamfile=fopen(FILENAME, "rb");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    pos=searchEnr(nom);

    printf("-------------------------- Vos statistiques --------------------------\n\n");
    printf("   PSEUDO         WIN      DEFEAT        DRAW               TIMING\n\n");     // Entête d'affichage

    fseek(streamfile, pos*sizeof(STATS), SEEK_SET);
    fread(&Enr, sizeof(STATS), 1, streamfile);
    printf("%9s", Enr.nom);
    printf("%12d", Enr.win);
    printf("%12d", Enr.defeat);
    printf("%12d", Enr.draw);
    printf("%14.2d:%.2d min\n", (int)Enr.timing/60, ((int)Enr.timing-( ((int)Enr.timing/60) * 60)));

    printf("\n----------------------------------------------------------------------\n");

    fclose(streamfile);

    printf("\nAppuyez sur ENTER pour revenir au menu. ");
    fflush(stdin);
    scanf("%c", &c);

    return 1;
}

// return value : >=0 (= la pos de l'enregistrement dans le fichier) si OK , <0 si KO
int searchEnr(char* chaine)
{
    FILE* streamfile;
    STATS EnrStats;
    int taille, test, k, i, found=0;

    streamfile=fopen(FILENAME, "ab");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen (creation).\n");
        return -1;
    }
    fclose(streamfile);

    streamfile=fopen(FILENAME, "rb");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return -1;
    }

    fseek(streamfile, 0, SEEK_END);     // Position à la fin du fichier
    taille=ftell(streamfile);           // Taille en octets du fichier
    k=taille/sizeof(STATS);             // Nombre de blocs d'enr

    for (i=0;i<=k && found==0;i++)      // Passage en revue de tout le fichier
    {
        fseek(streamfile, i*sizeof(STATS), SEEK_SET);
        test=fread(&EnrStats, sizeof(STATS), 1, streamfile);
        if (test!=1)
        {
            found=-1;
        }
        if (strcmp(chaine, EnrStats.nom)==0)    // Si c'est le bon nom
        {
            found=1;
        }
    }
    fclose(streamfile);
    if (found==-1)
    {
        return -9;
    }

    else
    {
        return i-1;
    }

}

// return value : 1 si OK , 0 si KO
int modifyEnr(STATS* EnrStats, int pos)
{
    FILE* streamfile;

    streamfile=fopen(FILENAME, "rb+");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    pos=pos-1;
    fseek(streamfile, pos*sizeof(STATS), SEEK_SET);

    fwrite(EnrStats, sizeof(STATS), 1, streamfile);

    fclose(streamfile);
    return 1;
}

// return value : 1 si OK , 0 si KO
int addEnr(char* nom, char* mdp)
{
    FILE* streamfile;
    STATS Enr;
    int err, taille, nbr_blocs;

    streamfile=fopen(FILENAME, "rb");
    if (streamfile==NULL)
    {
        perror("Erreur de fopen.\n");
        return 0;
    }

    /*do
    {
        printf("Quel est votre pseudo ?\n\n\t> ");
        err=checkchaineAlpha(nom, 30);
    }while(err==-1);*/

    fseek(streamfile, 0, SEEK_END);
    taille=ftell(streamfile);
    nbr_blocs=taille/sizeof(STATS);     // Calcul pour trouver le quantième id c'est qu'on va ajouter

    Enr.id=nbr_blocs+1;
    strcpy(Enr.nom, nom);
    strcpy(Enr.mdp, mdp);
    Enr.win=0;
    Enr.defeat=0;
    Enr.draw=0;
    Enr.timing=0.0;                     // Enregistrement par défaut avec le nom saisit

    writeEnr(&Enr);
    fclose(streamfile);

    return 1;
}
