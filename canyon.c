"**********************************************************************************************
TP3 : Le canyon de la mort
@Authors : Daniel KHO
**********************************************************************************************"
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

// Variables definies a la compilation
#ifndef WIDTH
#define WIDTH 20
#endif

#ifndef REFRESH
#define REFRESH 50
#endif

//structure du cycliste avec ses caractéristiques
struct {
    unsigned short int x;
    char display;
    char dead;
} cyclist;

void game() {

    initscr();              // initialisation de l'affichage
    keypad(stdscr, true);   // Autorise les flèches
    nodelay(stdscr, true);  // rend getch non bloquant
    noecho();               // désactive la répétition à l'écran des caractères tapées au clavier
    curs_set(0);            // cache le curseur

    //Preconditions
    if(WIDTH > COLS) {
        printf("La taille du terminal n'est pas assez grande pour une largeur de %d\n", WIDTH);
        return;
    }

    // le decalage a gauche initial
    int left = COLS / 2 - (WIDTH + 2) / 2;

    // la position du cycliste initiale et sa representation
    cyclist.x = left + (WIDTH + 2) / 2;
    cyclist.display = '^';
    cyclist.dead = 'X';
    
    // les LINES dernieres lignes sont stockees dans l'ordre decroissant de leur arrivee
    // la ligne tout en haut de l'ecran est la ligne borders[LINES - 1]
    // On initialise les valeurs a un canyon random
    int borders[LINES];
    for(int i = 0; i < LINES; ++i)
        borders[i] = left;

    // initialisation
    int keypress;
    bool stop = false;
    bool dead = false;
    int score = 0;

    while(true) {
        //recuperation de la touche appuyee si elle existe
        keypress = wgetch(stdscr);

        //suppression de la position du cycliste a la frame precedente
        mvaddch(LINES - 1, cyclist.x, ' ');

        //suppressions des lignes de la frame precedente
        for(int i = 0; i < LINES; ++i) {
            mvaddch(i, borders[LINES - i - 1], ' ');
            mvaddch(i, borders[LINES - i - 1] + WIDTH + 1,' ');
        }

        switch(keypress) {      //calcul de la nouvelle position selon la touche appuyee
            case KEY_LEFT:
                cyclist.x = (cyclist.x - 1);
                break;
            case KEY_RIGHT:
                cyclist.x = (cyclist.x + 1);
                break;
            case 'q':           //cela permet de quitter le programme avec la touche q
                stop = true;
                break;
            default:
                break;
        }

        //affichage des lignes
        for(int i = 0; i < LINES; ++i) {
            mvaddch(i, borders[LINES - i], '*');
            mvaddch(i, (borders[LINES - i] + WIDTH + 1), '*');
        }

        //est-ce que la nouvelle position tue le cycliste ?
        if(cyclist.x <= borders[0] || cyclist.x >= borders[0] + WIDTH + 1) {
            //affichage du cycliste mort
            mvaddch(LINES - 1, cyclist.x, cyclist.dead);
            char* msg = (char*) malloc (30 * sizeof(char));;
            sprintf(msg, "You died! Score: %d", score);
            mvprintw(LINES / 2, COLS / 2 - sizeof(msg), msg);
            refresh();
            usleep(3000000);
            break;
        }
        //affichage de la nouvelle position du cycliste
        mvaddch(LINES - 1, cyclist.x, cyclist.display);

        // insertion dans l'historique
        // memmove copie le tableau de l'indice 1 a LINES (le nombre de lignes affichees a l'ecran)
        // cela permet decaler l'ensemble du tableau d'un indice plus bas,
        // et de supprimer l'indice 0 (qui correspond a la ligne qui n'est plus affichee a la prochaine frame)
        memmove(&borders[0], &borders[1], (LINES - 1) * sizeof(int));
        borders[LINES - 1] = borders[LINES - 2] + (
                        (borders[LINES - 2] == 0)           // si le canyon touche l'ecran gauche
                        ? (rand() % 3 == 0)                 // 2.3 -> 0, 1/3 -> 1
                        : (borders[LINES - 2] + WIDTH + 2 == COLS)  // si le canyon touche l'ecran droite
                        ? -(rand() % 3 == 0)                // 2.3 -> 0, 1/3 -> -1
                        : rand() % 3 - 1                    // sinon
                    );

        score++;
        refresh();
        if(stop) break;
        usleep(1./REFRESH * 1000000);
    }
    endwin();
}

int main() {
    game();
    return 0;
}