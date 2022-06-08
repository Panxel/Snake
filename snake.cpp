#include <iostream>
#include "snake.h"
using namespace std;

chaine* creer_liste(){ //Fonction qui creer une liste
    
    chaine* liste= (chaine*)malloc(sizeof(chaine));
    liste->debut = NULL;
    liste->fin = NULL;
    return liste;
}

cellule* creer_cellule(point pos){ //Fonction qui creer une cellule

    cellule* cell = (cellule*)malloc(sizeof(cellule));
    cell-> coord.x = pos.x;
    cell-> coord.y = pos.y;
    cell-> suivant = NULL;
    cell -> sens = STOP;
    return cell;
}

void inserer_debut(chaine* liste,point pos){ //Fonction qui insere une cellule au debut de la liste

    cellule* cell=creer_cellule(pos);

    if (liste->debut == NULL){

        liste->fin = cell;
    }
    cell->suivant=liste->debut;
    liste->debut=cell;
}

void inserer_fin(chaine* liste,point pos){ //Fonction qui insere une cellule a la fin de la liste

    cellule* cell = creer_cellule(pos);
    liste->fin->suivant = cell;
    liste->fin = cell;
}

void affiche_liste(chaine* liste){ //Fonction qui affiche les coordonnées de la liste

    cellule* temp=liste->debut;

    while(temp!=NULL){

        cout << temp->coord.x << "\t" << temp->coord.y << endl;
        temp=temp->suivant;
    }
}

void clean_liste(chaine* liste){ //Fonction qui free la liste

    cellule* temp=liste->debut;
    cellule* temp2= temp;

    while(temp!=NULL){

        temp=temp->suivant;
        free(temp2);
        temp2=temp;
    }
}

void input_game(chaine* liste,bool* gameOver){ //Fonction qui gere tous nos inputs game

    SDL_Event event; //Variable d'event

    while(SDL_PollEvent(&event)){ //Si on effectue un event
        switch(event.type){ //Permet de savoir quel type d'event
            case SDL_KEYDOWN : //Si on appuie sur une touche du clavier
                switch(event.key.keysym.scancode){ //Touche physique --> Par rapport a un qwerty
                    case SDL_SCANCODE_W : //Si on appuie sur Z
                        if(liste->debut->sens!=BAS){ //Exception sur BAS (Un snake ne peut pas bouger dans le sens oppose)
                            liste->debut->sens = HAUT;    
                        }
                        break;
                    case SDL_SCANCODE_A : //Si on appuie sur Q
                        if(liste->debut->sens!=DROITE){ //Exception sur DROITE (Un snake ne peut pas bouger dans le sens oppose)
                            liste->debut->sens = GAUCHE;    
                        }
                        break;
                    case SDL_SCANCODE_D : //Si on appuie sur D
                        if(liste->debut->sens!=GAUCHE){ //Exception sur GAUCHE (Un snake ne peut pas bouger dans le sens oppose)
                            liste->debut->sens = DROITE;    
                        }
                        break;
                    case SDL_SCANCODE_S : //Si on appuie sur S
                        if(liste->debut->sens!=HAUT){ //Exception sur HAUT (Un snake ne peut pas bouger dans la direction oppose)
                            liste->debut->sens = BAS;    
                        }
                        break;
                    default : //On ne fait rien
                        break;
                }
                break;
            case SDL_QUIT : //Si on clique sur la croix de la fenetre
                *gameOver = true;
                break;
        }
    }
}

void deplacement_head (chaine* liste){ //Fonction qui gere le deplacement de la tete du serpent

    switch (liste->debut->sens){
        case GAUCHE : //Si la direction est a gauche
            liste->debut->coord.x-=WIDTH_RECT;
            break;
        case HAUT : //Si la direction est en haut
            liste->debut->coord.y-=HEIGHT_RECT;
            break;
        case DROITE : //Si la direction est a droite
            liste->debut->coord.x+=WIDTH_RECT;
            break;
        case BAS : //Si la direction est en bas
            liste->debut->coord.y+=HEIGHT_RECT;
            break;
        case STOP : //Si la direction est sur stop (On ne bouge pas -> On ne fait rien)
            break;
    }
}

void deplacement_corps_coord(chaine* liste){ //Fonction qui gere le deplacement du corps du serpent
    
    //Variables temporaires
    int prev_x,prev_y,actual_x,actual_y;

    //Pointe vers la tete du serpent
    cellule* temp = liste->debut;

    //Prend les coordonnées de la tete du serpent
    prev_x = temp->coord.x;
    prev_y = temp->coord.y;

    //Pointe vers la 1ere cellule apres la tete du serpent
    temp=temp->suivant;

    while(temp!=NULL){ //Parcourt tout le corps du serpent

        //Sauvegarde les coordonnées de la cellule actuelle
        actual_x = temp->coord.x;
        actual_y = temp->coord.y;

        //Remplace les coordoonées de la cellule actuelle par celles de la cellule avant elle
        temp->coord.x = prev_x;
        temp->coord.y = prev_y;

        //Sauvegarde les coordonnées de la cellule actuelle
        prev_x = actual_x;
        prev_y = actual_y;

        //Acces a la cellule suivante
        temp=temp->suivant;
    }
}

void heritage_corps_sens(chaine* liste){ //Fonction qui pour chaque cellule herite du sens de la cellule avant elle
    
    //Variables temporaires
    direction prev_s,actual_s;

    //Pointe vers la tete du serpent
    cellule* temp = liste->debut;

    //Prend le sens de la tete du serpent
    prev_s = temp->sens;

    //Pointe vers la 1ere cellule apres la tete du serpent
    temp=temp->suivant;

    while(temp!=NULL){ //Parcourt tout le corps du serpent

        //Sauvegarde le sens de la cellule actuelle
        actual_s = temp->sens;

        //Remplace le sens de la cellule actuelle par celle de la cellule avant elle
        temp->sens = prev_s;

        //Sauvegarde le sens de la cellule actuelle
        prev_s = actual_s;

        //Acces a la cellule suivante
        temp=temp->suivant;
    }
}

void random_apple(pomme* apple){ //Fonction qui change les coordonnées de la pomme de maniere aleatoire

    //Il faut que la coordonnée en x soit divisible par WIDTH_RECT pour pouvoir coincider avec notre tableau 2D fictif
    int r = rand()%IMAGE_WIDTH;

    while (r%(WIDTH_RECT)!= 0 || r > IMAGE_WIDTH-APPLE_BORDER_REDUCE || r < APPLE_BORDER_REDUCE){ //Conditions supplémentaires pour que la pomme ne soit pas trop proche de la bordure

        r = rand()%IMAGE_WIDTH;
    }
    apple->coord.x = r;

    //Il faut que la coordonnée en y soit divisible par HEIGHT_RECT pour pouvoir coincider avec notre tableau 2D fictif
    r = rand()%IMAGE_HEIGHT;

    while (r%(HEIGHT_RECT)!= 0 || r > IMAGE_HEIGHT-APPLE_BORDER_REDUCE || r < APPLE_BORDER_REDUCE){ //Conditions supplémentaires pour que la pomme ne soit pas trop proche de la bordure

        r = rand()%IMAGE_HEIGHT;
    }
    apple->coord.y = r;
}

void collision (bool* gameOver,chaine* liste,pomme* apple,int* score){ //Fonction realisant des actions si il y a collision

    cellule* head = liste->debut; //Tete du serpent
    cellule* temp = head->suivant; //Pointe vers la 1ere cellule apres la tete du serpent

    //Configuration de gameOver si on touche les bordures 
    if (head->coord.x < 0 || head->coord.x >= IMAGE_WIDTH){ 

        *gameOver = true;
        cout << "Le serpent a touche la bordure" << endl;
    }
    if (head->coord.y < 0 || head->coord.y >= IMAGE_HEIGHT){

        *gameOver = true;
        cout << "Le serpent a touche la bordure" << endl;
    }

    //Configuration si la tete mange la pomme
    if (head->coord.x == apple->coord.x && head->coord.y == apple->coord.y){

        //Position d'un point hors de la fenetre
        point out_border; 
        out_border.x = -WIDTH_RECT;
        out_border.y = -HEIGHT_RECT;

        //Actions
        *score += ADDSCORE; //Augmente le score
        random_apple(apple); //La pomme change de coordonnées
        inserer_fin(liste,out_border); //La position du point est a l'exterieur de la fenetre car il ne faut pas que le point soit visible sur une frame de la fenetre
    }

    //Configuration de gameOver si la tete touche son corps
    while(temp!=NULL){ //Parcourt tout le corps du serpent

        if(head->coord.x == temp->coord.x && head->coord.y == temp->coord.y){

            *gameOver = true;
            cout << "Le serpent a touche son corps" << endl;
        }
        temp=temp->suivant;
    }
}

void limit_FPS(unsigned int start_loop){ //Fonction limitant le nombre de fps

    unsigned int actual_delay = SDL_GetTicks() - start_loop; //Temps ecoule entre nos deux GetTicks()
    unsigned int desired_delay = 1000/FPS; //Delay ideal entre chaque frame en ms pour notre fps

    if (actual_delay<desired_delay){ //Si le delay ecoule est plus rapide que le delay ideal

        SDL_Delay(desired_delay-actual_delay); //Delay de l'avance de temps
    }
}

void reset_game(int* score,bool* menu,bool* gameOver,pomme* apple,chaine* liste,point center,cellule** head){ //Reset les valeurs pour pouvoir rejouer
    *score = 0;
    *menu = true;
    *gameOver = true;
    random_apple(apple);
    liste->debut = NULL;
    inserer_debut(liste,center);
    *head = liste->debut;
}
