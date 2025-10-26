#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

#include "mineDetector.h"

using namespace std;

const int FILAS = 15;
const int COLUMNAS = 15;
const int MINAS = 10;

struct Casilla {
    bool mina;
    bool destapada;
    int minasVecinas;
};

vector<vector<Casilla>> tablero(FILAS, vector<Casilla>(COLUMNAS));
int posX = 0, posY = 0;

void inicializarTablero() {
    srand(time(0));
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j].mina = false;
            tablero[i][j].destapada = false;
            tablero[i][j].minasVecinas = 0;
        }
    }

    for (int i = 0; i < MINAS; i++) {
        int x = rand() % FILAS;
        int y = rand() % COLUMNAS;
        if (tablero[x][y].mina) {
            i--;
        } else {
            tablero[x][y].mina = true;
        }
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].mina) continue;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int ni = i + dx;
                    int nj = j + dy;
                    if (ni >= 0 && ni < FILAS && nj >= 0 && nj < COLUMNAS && tablero[ni][nj].mina) {
                        tablero[i][j].minasVecinas++;
                    }
                }
            }
        }
    }
}

void mostrarTablero() {
    clear();
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == posX && j == posY) {
                attron(A_REVERSE);
            }

            if (tablero[i][j].destapada) {
                if (tablero[i][j].mina) {
                    printw("* ");
                } else {
                    if (tablero[i][j].minasVecinas == 0) {
                        printw(". ");
                    } else {
                        printw("%d ", tablero[i][j].minasVecinas);
                    }
                }
            } else {
                printw("# ");
            }

            if (i == posX && j == posY) {
                attroff(A_REVERSE);
            }
        }
        printw("\n");
    }
    refresh();
}

void jugar() {
    initscr();
    noecho();
    cbreak();

    keypad(stdscr, TRUE);
    timeout(100); 

    inicializarTablero();

    while (true) {
        mostrarTablero();

        int tecla = getch();

        switch (tecla) {
            case KEY_UP:
                if (posX > 0) posX--;
                break;
            case KEY_DOWN:
                if (posX < FILAS - 1) posX++;
                break;
            case KEY_LEFT:
                if (posY > 0) posY--;
                break;
            case KEY_RIGHT:
                if (posY < COLUMNAS - 1) posY++;
                break;
            case 10: // Enter
                if (tablero[posX][posY].destapada) break;

                tablero[posX][posY].destapada = true;

                if (tablero[posX][posY].mina) {
                    clear();
                    printw("¡BOOM! Has pisado una mina. Game Over.\n");
                    refresh();
                    getch();
                    endwin();
                    return;
                }

                if (tablero[posX][posY].minasVecinas == 0) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            int nx = posX + dx;
                            int ny = posY + dy;
                            if (nx >= 0 && nx < FILAS && ny >= 0 && ny < COLUMNAS && !tablero[nx][ny].destapada) {
                                tablero[nx][ny].destapada = true;
                            }
                        }
                    }
                }
                break;
            case 'q':
                endwin();
                return;
            default:
                break;
        }
    }

    endwin();
}

void playMineDetector() {
    cout << "Juego de Mine Detector\n";
    jugar();
}
