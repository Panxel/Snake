#ifndef SNAKE_H
#define SNAKE_H
#include <iostream>
#include <SDL.h> //sudo apt-get install libsdl2-dev
#include "menu.h"
#define APPLE_BORDER_REDUCE 150 //Permet de reduire la fenetre d'apparition de la pomme
#define FPS 10 //Nbr de FPS
#define ADDSCORE 100 //Nbr de points qu'on ajoute au score
#define ROWS 32 //Nbr de cases sur une ligne
#define COLS 18 //Nbr de cases sur une colonne
#define WIDTH_RECT IMAGE_WIDTH/ROWS //Largeur du rectangle (Il faut une division avec 0 en reste !!)
#define HEIGHT_RECT IMAGE_HEIGHT/COLS //Hauteur du rectangle (Il faut une division avec 0 en reste !!)
using namespace std;

typedef enum direction_{ //Direction de la tete du serpent
    STOP,
    HAUT,
    DROITE,
    BAS,
    GAUCHE
} direction;
typedef struct point_{ //Structure de point
    int x;
    int y;
} point;
typedef struct cellule_{ //Structure d'une cellule du serpent 
    point coord;
    struct cellule_* suivant;
    direction sens;
} cellule;
typedef struct chaine_{ //Structure de la chaine de liste
    cellule* debut;
    cellule* fin;
} chaine;
typedef struct pomme_{ //Structure de la pomme
    point coord;
} pomme;


chaine* creer_liste(); //Fonction qui creer une liste
cellule* creer_cellule(point pos); //Fonction qui creer une cellule
void inserer_debut(chaine* liste,point pos); //Fonction qui insere une cellule au debut de la liste
void inserer_fin(chaine* liste,point pos); //Fonction qui insere une cellule a la fin de la liste
void affiche_liste(chaine* liste); //Fonction qui affiche les coordonnées de la liste
void clean_liste(chaine* liste); //Fonction qui free la liste
void input_game(chaine* liste,bool* gameOver); //Fonction qui gere tous nos inputs game
void deplacement_head (chaine* liste); //Fonction qui gere le deplacement de la tete du serpent
void deplacement_corps_coord(chaine* liste); //Fonction qui gere le deplacement du corps du serpent
void heritage_corps_sens(chaine* liste); //Fonction qui pour chaque cellule herite du sens de la cellule avant elle
void random_apple(pomme* apple); //Fonction qui change les coordonnées de la pomme de maniere aleatoire
void collision (bool* gameOver,chaine* liste,pomme* apple,int* score); //Fonction realisant des actions si il y a collision
void limit_FPS(unsigned int start_loop); //Fonction limitant le nombre de fps
void reset_game(int* score,bool* menu,bool* gameOver,pomme* apple,chaine* liste,point center,cellule** head); //Reset les valeurs pour pouvoir rejouer
#endif