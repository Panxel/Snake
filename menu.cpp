#include <iostream>
#include "menu.h"
using namespace std;

void Init_SDL(){ //Initialise les 3 librairies de la SDL

    SDL_Init(SDL_INIT_VIDEO); //Initialise SDL
    IMG_Init(IMG_INIT_PNG); //Initialise IMG
    TTF_Init(); //Initialise TTF
}

void Quit_SDL(TTF_Font* font,SDL_Renderer* renderer, SDL_Window* window){ //Libere l'espace memoire pour le font, le rendu, la fenetre et quitte les 3 librairies de la SDL

    SDL_DestroyRenderer(renderer); //Detruit le rendu
    SDL_DestroyWindow(window); //Detruit la fenetre
    TTF_CloseFont(font); //Detruit le front
    TTF_Quit(); //Quitte TTF
    IMG_Quit(); //Quitte IMG
    SDL_Quit(); //Quitte SDL
}

SDL_Texture* Creer_Texture_Texte(TTF_Font* font,const char texte[],SDL_Color color,SDL_Renderer* renderer){ //Creer une texture texte

    SDL_Surface* surface = TTF_RenderText_Solid(font,texte,color); //Creer la surface du texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface); //Creer la texture a partir de la surface
    SDL_FreeSurface(surface); //Libere la surface
    return texture;
}

SDL_Texture* Creer_Texture_Graph(const char path[],SDL_Renderer* renderer){

    SDL_Surface* surface = IMG_Load(path); //Creer la surface de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface); //Creer la texture a partir de la surface
    SDL_FreeSurface(surface); //Libere la surface
    return texture;
}

void Input_Menu(bool* menu, bool* button, bool* gameOver, bool* programme){ //Fonction qui gere tous nos inputs menu

    SDL_Event event; //Variable d'event
    SDL_WaitEvent(&event); //Attend un event (Reste ici tant qu'un event n'est pas survenu)
    switch(event.type){ //Permet de savoir quel type d'event
        case SDL_MOUSEBUTTONUP : //Si on relache le click gauche sur l'un des boutons
            if ((event.button.x >= BUTTON_MENU_X) && (event.button.x <= (BUTTON_MENU_X + BUTTON_WIDTH)))
            {
                if((event.button.y >=BUTTON_PLAY_Y) && (event.button.y <= (BUTTON_PLAY_Y+BUTTON_HEIGHT))){ //Bouton Play
                    if (event.button.button == SDL_BUTTON_LEFT){ //Si c'est un click gauche
                        *menu = false;
                        *gameOver = false;
                    }
                }else if ((event.button.y >= BUTTON_EXIT_Y) && (event.button.y <= (BUTTON_EXIT_Y+BUTTON_HEIGHT))){ //Bouton Exit
                    if (event.button.button == SDL_BUTTON_LEFT){
                        *menu = false;
                        *gameOver = true;
                        *programme = false;
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION : //Si on deplace la souris
            if ((event.motion.x >= BUTTON_MENU_X) && (event.motion.x <= (BUTTON_MENU_X + BUTTON_WIDTH))){
                if(((event.motion.y >=BUTTON_PLAY_Y) && (event.motion.y <= (BUTTON_PLAY_Y+BUTTON_HEIGHT))) || ((event.motion.y >= BUTTON_EXIT_Y) && (event.motion.y <= (BUTTON_EXIT_Y+BUTTON_HEIGHT)))){ //Si on est soit dans le bouton Play soit dans le bouton Exit
                    *button = true;
                }else{
                    *button = false;
                }
            }else{
                *button = false;
            }
            break;
        case SDL_QUIT : //Si on clique sur la croix de la fenetre
            *menu = false;
            *gameOver = true;
            *programme = false;
            break;
    }
}