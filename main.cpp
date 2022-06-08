#include <iostream>
#include <SDL.h> //sudo apt-get install libsdl2-dev
#include <SDL_image.h> //sudo apt-get install libsdl2-image-dev
#include <SDL_ttf.h> //sudo apt-get install libsdl2-ttf-dev
#include <string>
#include "snake.h"
#include "menu.h"
using namespace std;

int main(int argc,char** argv){

    //Initialisation des variables//

    //Position du centre de l'image
    point center;
    center.x = IMAGE_WIDTH/2;
    center.y = IMAGE_HEIGHT/2;

    //Creation du serpent
    chaine* liste=creer_liste();
    inserer_debut(liste,center);

    //Initialisation du jeu
    srand(time(NULL));
    int score = 0; //Score du jeu
    string score_str; //Score du jeu en string
    string msg; //Message du score
    const char* texte; //Changement de type : string msg en const char*
    unsigned int start_loop = 0; //Variable utile pour garder un nombre de fps constant
    pomme apple;
    random_apple(&apple); //Pomme
    cellule* avant; //Cellule temporaire qui pointe sur la cellule avant elle
    cellule* head = liste->debut; //Tete du serpent
    cellule* temp; //Cellule temporaire
    bool gameOver = true; //Status du jeu
    bool menuOn = true; //Status du menu
    bool mouseOnButton = false; //Status si le curseur est sur un des boutons
    bool programme = true; //Status si le programme tourne toujours

    //Gestion de SDL//

    //Initialisation de SDL
    Init_SDL();
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,IMAGE_WIDTH,IMAGE_HEIGHT,0); //Creer une fenetre
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED); //Creer un rendu

    //Initialise les rectangles
    SDL_Rect green{85,311,BUTTON_WIDTH,BUTTON_HEIGHT}; //Rectangle du bouton vert dans l'image Button.png (coordonnées du point recupéré grace a PAINT)
    SDL_Rect red{623,104,BUTTON_WIDTH,BUTTON_HEIGHT}; //Rectangle du bouton rouge dans l'image Button.png(coordonnées du point recupéré grace a PAINT)
    SDL_Rect grey{623,719,BUTTON_WIDTH,BUTTON_HEIGHT}; //Rectangle du bouton gris dans l'image Button.png(coordonnées du point recupéré grace a PAINT)
    SDL_Rect play_button{BUTTON_MENU_X,BUTTON_PLAY_Y,BUTTON_WIDTH,BUTTON_HEIGHT}; //Rectangle du bouton play dans mon rendu
    SDL_Rect exit_button{BUTTON_MENU_X,BUTTON_EXIT_Y,BUTTON_WIDTH,BUTTON_HEIGHT}; //Rectangle du bouton exit dans mon rendu
    SDL_Rect play_rect{BUTTON_MENU_X,BUTTON_PLAY_Y,BUTTON_WIDTH-20,BUTTON_HEIGHT}; //Rectangle du texte play dans mon rendu
    SDL_Rect exit_rect{BUTTON_MENU_X,BUTTON_EXIT_Y,BUTTON_WIDTH-20,BUTTON_HEIGHT}; //Rectangle du texte exit dans mon rendu
    SDL_Rect rect{0,0,WIDTH_RECT,HEIGHT_RECT}; //Rectangle permettant d'afficher le snake et la pomme

    //Initialise les couleurs
    SDL_Color blanc {255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color noir {0,0,0,SDL_ALPHA_OPAQUE};
    
    //Initialise le font
    TTF_Font* font = TTF_OpenFont("asset/Font.ttf",200);

    //Initialise les textures
    SDL_Texture* background_menu = Creer_Texture_Graph("asset/Snake_menu.png",renderer); //Texture graphique du background du menu
    SDL_Texture* button = Creer_Texture_Graph("asset/Button.png",renderer); //Texture graphique des boutons
    SDL_Texture* play_blanc = Creer_Texture_Texte(font,"Play",blanc,renderer); //Texture texte du Play en blanc
    SDL_Texture* exit_blanc = Creer_Texture_Texte(font,"Exit",blanc,renderer); //Texture texte du Exit en blanc
    SDL_Texture* play_noir = Creer_Texture_Texte(font,"Play",noir,renderer); //Texture texte du Play en noir
    SDL_Texture* exit_noir = Creer_Texture_Texte(font,"Exit",noir,renderer); //Texture texte du Exit en noir
    SDL_Texture* background_game = Creer_Texture_Graph("asset/Snake_game.png",renderer); //Texture graphique du background du jeu
    SDL_Texture* apple_texture = Creer_Texture_Graph("asset/apple.png",renderer); //Texture graphique de la pomme
    SDL_Texture* head_up = Creer_Texture_Graph("asset/head_up.png",renderer); //Texture graphique de la tete du serpent vers le haut
    SDL_Texture* head_right = Creer_Texture_Graph("asset/head_right.png",renderer); //Texture graphique de la tete du serpent vers la droite
    SDL_Texture* head_down = Creer_Texture_Graph("asset/head_down.png",renderer); //Texture graphique de la tete du serpent vers le bas
    SDL_Texture* head_left = Creer_Texture_Graph("asset/head_left.png",renderer); //Texture graphique de la tete du serpent vers la gauche
    SDL_Texture* body_horizontal = Creer_Texture_Graph("asset/body_horizontal.png",renderer); //Texture graphique du corps du serpent si deplacement horizontal
    SDL_Texture* body_vertical = Creer_Texture_Graph("asset/body_vertical.png",renderer); //Texture graphique du corps du serpent si deplacement vertical
    SDL_Texture* body_bottomleft = Creer_Texture_Graph("asset/body_bottomleft.png",renderer); //Texture graphique du corps du serpent si changement de direction
    SDL_Texture* body_bottomright = Creer_Texture_Graph("asset/body_bottomright.png",renderer); //Texture graphique du corps du serpent si changement de direction
    SDL_Texture* body_topleft = Creer_Texture_Graph("asset/body_topleft.png",renderer); //Texture graphique du corps du serpent si changement de direction
    SDL_Texture* body_topright = Creer_Texture_Graph("asset/body_topright.png",renderer); //Texture graphique du corps du serpent si changement de direction
    SDL_Texture* gameover = Creer_Texture_Graph("asset/gameover.png",renderer); //Texture graphique du gameover
    SDL_Texture* score_texture = NULL; //Texture texte du score

    //Gestion du programme//
    while(programme){

        //Gestion du menu//
        while(menuOn){

            //Clear window et affiche l'image
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,background_menu,NULL,NULL);

            //Effectue des actions en fonction des inputs menu
            Input_Menu(&menuOn,&mouseOnButton,&gameOver,&programme);
            
            if (mouseOnButton){ //Si on est sur l'un des boutons
                
                //Copie sur le rendu
                SDL_RenderCopy(renderer,button,&green,&play_button);
                SDL_RenderCopy(renderer,button,&red,&exit_button);
                SDL_RenderCopy(renderer,play_noir,NULL,&play_rect);
                SDL_RenderCopy(renderer,exit_noir,NULL,&exit_rect);
            }else{
            
                //Copie sur le rendu
                SDL_RenderCopy(renderer,button,&grey,&play_button);
                SDL_RenderCopy(renderer,button,&grey,&exit_button);
                SDL_RenderCopy(renderer,play_blanc,NULL,&play_rect);
                SDL_RenderCopy(renderer,exit_blanc,NULL,&exit_rect);
            }
            SDL_RenderPresent(renderer); //Affiche sur le rendu
        }
        //Gestion du jeu//
        while(!gameOver){ //Boucle infini tant que le jeu n'est pas fini

            //Reset des valeurs
            start_loop = SDL_GetTicks(); //Get time since Init
            temp=head;

            //Clear window et affiche l'image
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,background_game,NULL,NULL);

            //Deplacement du corps
            deplacement_corps_coord(liste);  
            
            //deplacement de la tete
            deplacement_head(liste);

            //Gestion de la tete//

            //Recupere les coordonnées de la tete
            rect.x = head->coord.x; 
            rect.y = head->coord.y;

            switch(head->sens){
                case HAUT : //Si la direction est vers le haut
                    SDL_RenderCopy(renderer,head_up,NULL,&rect);
                    break;
                case DROITE : //Si la direction est vers la droite
                    SDL_RenderCopy(renderer,head_right,NULL,&rect);
                    break;
                case BAS : //Si la direction est vers le bas
                    SDL_RenderCopy(renderer,head_down,NULL,&rect);
                    break;
                default : //Si la direction est vers la gauche ou sur stop
                    SDL_RenderCopy(renderer,head_left,NULL,&rect);
                    break;
            }
            avant = temp; //Pointe sur la tete
            temp=temp->suivant; //Pointe vers la 1ere cellule apres la tete du serpent

            //Gestion du corps//
            while (temp!=NULL){

                //Recupere les coordonnées de la cellule
                rect.x = temp->coord.x; 
                rect.y = temp->coord.y;

                switch(temp->sens){
                    case HAUT : //Si la direction est vers le haut
                        if(avant->sens==GAUCHE){
                            SDL_RenderCopy(renderer,body_bottomleft,NULL,&rect);
                        }else if (avant->sens==DROITE){
                            SDL_RenderCopy(renderer,body_bottomright,NULL,&rect);
                        }else{
                            SDL_RenderCopy(renderer,body_vertical,NULL,&rect);
                        }
                        break;
                    case DROITE : //Si la direction est vers la droite
                        if(avant->sens==HAUT){
                            SDL_RenderCopy(renderer,body_topleft,NULL,&rect);
                        }else if (avant->sens==BAS){
                            SDL_RenderCopy(renderer,body_bottomleft,NULL,&rect);
                        }else{
                            SDL_RenderCopy(renderer,body_horizontal,NULL,&rect);
                        }
                        break;
                    case BAS : //Si la direction est vers le bas
                        if(avant->sens==GAUCHE){
                            SDL_RenderCopy(renderer,body_topleft,NULL,&rect);
                        }else if (avant->sens==DROITE){
                            SDL_RenderCopy(renderer,body_topright,NULL,&rect);
                        }else{
                            SDL_RenderCopy(renderer,body_vertical,NULL,&rect);
                        }
                        break;
                    case GAUCHE : //Si la direction est vers la gauche
                        if(avant->sens==HAUT){
                            SDL_RenderCopy(renderer,body_topright,NULL,&rect);
                        }else if (avant->sens==BAS){
                            SDL_RenderCopy(renderer,body_bottomright,NULL,&rect);
                        }else{
                            SDL_RenderCopy(renderer,body_horizontal,NULL,&rect);
                        }
                        break;
                    default : //Le corps ne pourra jamais avoir STOP
                        break;
                }
                avant = temp;
                temp=temp->suivant;
            }

            //Copie la pomme sur le rendu
            rect.x = apple.coord.x;
            rect.y = apple.coord.y;
            SDL_RenderCopy(renderer,apple_texture,NULL,&rect);
            
            //Affiche sur le rendu
            SDL_RenderPresent(renderer);

            //Heritage du sens
            heritage_corps_sens(liste);  

            //Effectue des actions en fonctions des inputs game
            input_game(liste,&gameOver); //Bug : Possibilite de gameOver si on appuie tres vite sur 2 touches a la fois car la tete n'a pas eu le temps de se deplacer sur la 1ere touche
            
            //Detecte si il y a une collision
            collision(&gameOver,liste,&apple,&score);

            //Permet d'afficher a un fps constant
            limit_FPS(start_loop);
        }
        clean_liste(liste); //Clear la liste

        if(programme){ //Si on ne quitte pas le programme

            score_str=to_string(score); //Transforme le score en string
            msg = "Votre score est de : " + score_str; //Concatenation du msg de fin et du score
            texte = msg.c_str(); //Transforme le string en const char* car la fonction Creer_Texture_Texte prend un const char* (predefini par SDL)
            score_texture = Creer_Texture_Texte(font,texte,blanc,renderer);

            //Clear window et affiche l'image
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,gameover,NULL,NULL);

            //Copie sur le rendu
            SDL_RenderCopy(renderer,score_texture,NULL,&exit_rect);

            //Affiche sur le rendu
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);

            //Detruit la texture et reset la game
            SDL_DestroyTexture(score_texture);
            reset_game(&score,&menuOn,&gameOver,&apple,liste,center,&head);
        }
    }

    //Libere toute la memoire utilisée
    free(liste);
    SDL_DestroyTexture(background_menu);
    SDL_DestroyTexture(button);
    SDL_DestroyTexture(play_blanc);
    SDL_DestroyTexture(exit_blanc);
    SDL_DestroyTexture(play_noir);
    SDL_DestroyTexture(exit_noir);
    SDL_DestroyTexture(background_game);
    SDL_DestroyTexture(apple_texture);
    SDL_DestroyTexture(head_up);
    SDL_DestroyTexture(head_right);
    SDL_DestroyTexture(head_down);
    SDL_DestroyTexture(head_left);
    SDL_DestroyTexture(body_horizontal);
    SDL_DestroyTexture(body_vertical);
    SDL_DestroyTexture(body_bottomleft);
    SDL_DestroyTexture(body_bottomright);
    SDL_DestroyTexture(body_topleft);
    SDL_DestroyTexture(body_topright);
    SDL_DestroyTexture(gameover);
    Quit_SDL(font,renderer,window);
    return 0;
}