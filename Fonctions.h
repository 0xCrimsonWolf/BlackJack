
// Prototype des fonctions utiles dans le main "BlackJack.c"

void menuJoueur(char*, int);
void menuAdmin(char*, int);
int cc_carte(int);
float rdm_carte(float *);
void lancerPartie(float *, char*, int);
void gestionJoueur();
void read_carte(float *);
int condition_bj(float, float *, float, float *);
void read_Croupier(float *, float *, int*, int*, int cls);
void read_Joueur(float *, float *, int*, int*, int cls);
void affich_Jeu(float *, int, float *, int, int);
void affichRules();

// Fonctions de check

int checkchaineAlpha(char *, int);
int checkchaineAlphaAndNum(char* Chaine, int max);
