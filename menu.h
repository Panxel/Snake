#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h> //sudo apt-get install libsdl2-image-dev
#include <SDL_ttf.h> //sudo apt-get install libsdl2-ttf-dev
#define IMAGE_WIDTH 1280 //Largeur de l'image
#define IMAGE_HEIGHT 720 //Hauteur de l'image
#define BUTTON_WIDTH 390 //Largeur du bouton deduit grace a PAINT
#define BUTTON_HEIGHT 90 //Hauteur du bouton deduit grace a PAINT
#define BUTTON_MENU_X IMAGE_WIDTH/2-BUTTON_WIDTH/2 //Position sur l'axe_x des boutons a placer
#define BUTTON_PLAY_Y IMAGE_HEIGHT/3-BUTTON_HEIGHT/2 //Position sur l'axe_y du bouton Play a placer
#define BUTTON_EXIT_Y 2*IMAGE_HEIGHT/3-BUTTON_HEIGHT/2 //Position sur l'axe_y du bouton Exit a placer

void Init_SDL(); //Initialise les 3 librairies de la SDL
void Quit_SDL(TTF_Font* font,SDL_Renderer* renderer, SDL_Window* window); //Libere l'espace memoire pour le font, le rendu, la fenetre et quitte les 3 librairies de la SDL
SDL_Texture* Creer_Texture_Texte(TTF_Font* font,const char texte[],SDL_Color color,SDL_Renderer* renderer); //Creer une texture texte
SDL_Texture* Creer_Texture_Graph(const char path[],SDL_Renderer* renderer); //Creer une texture graphique
void Input_Menu(bool* menu, bool* button, bool* gameOver, bool* programme); //Fonction qui gere tous nos inputs menu

#endif