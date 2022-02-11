
// Prototype des fonctions utiles dans le "Stats.c"

typedef struct
{
    int id;
    char nom[30];
    char mdp[30];
    int win;
    int defeat;
    int draw;
    float timing;

}STATS;

int writeEnr(STATS*);           // Adresse de l'enr � �crire
int readEnr(STATS*, int);       // Adresse de l'enr qui va recevoir ce qui va �tre lu + la position par nbr d'enr
int affichAllEnr();             // Lit tous les enregistrements
int searchEnr(char*);           // Adresse de la chaine "nom" � chercher RETURN : l'id de l'enr // RETURN : -1 si pas trouv�
STATS* searchEnrSTATS(char*);   // Retourne un pointeur vers l'enr
int modifyEnr();
int addEnr(char*, char*);              // Ajoute un enr avec le nom saisit + l'id automatiquement calcul� + le reste par d�faut (0)
int affichStatsJoueur(char*);   // Affiche les stats que d'un seul joueur sur base de son nom
