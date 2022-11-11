Jeu du Snake avec SDL

=====================

    Plusieurs points à préciser :

-----------------------------------


- Prérequis Package : Il faut installer les librairies SDL

    + SDL : sudo apt-get install libsdl2-dev

    + SDL_image : sudo apt-get install libsdl2-image-dev

    + SDL_ttf : sudo apt-get install libsdl2-ttf-dev


1. Snake :


- Pour piloter le Snake, nous utilisons les touches Z (Haut), Q (Gauche), S (Bas), D (Droite).

>   `Remarque :` Il se peut également que quand vous appuyez sur 2 touches à la suite très rapidement que le snake meurt (c'est un **BUG**).


- Si vous voulez changer la taille du jeu, il faut changer dans le fichier snake.h les valeurs de ROWS_ et de COLS_. Par exemple mettre 64 pour ROWS_ et 36 pour COLS_

>   `Warning` Il faut respecter les 2 conditions de WIDTH_RECT et de HEIGHT_RECT


- Vous pouvez également changer le nombre de FPS du jeu dans le fichier snake.h.

>   `Warning` Il faut respecter la condition de COMPTEUR