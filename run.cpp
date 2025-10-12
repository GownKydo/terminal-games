#include <iostream>
#include <cstdlib>

#include "headers/hangman.h"
#include "headers/mineDetector.h"

using namespace std;

// Function prototypes
void menu();
void menu_games();
void clearScreen();

// function games
void playHangman();
void playMineDetector();

int main() {    
    short choose;
    clearScreen();
    menu();

    cout << "\n[*] Select a choose: ";
    cin >> choose;
    switch (choose) {
        case 1:
            clearScreen();
            playHangman();
        break;
            
        case 2:
            clearScreen();
            playMineDetector();
        break;

        default:
            clearScreen();
            cout << "\n\tGood bye :)\n\n";
        return 0;
    }
}

void menu() {
    cout << "\t   #############################\n" << 
            "\t   ##\t\t\t      ##\n"                 <<
            "\t   ##\t     MAIN MENU\t   ##\n"        <<
            "\t   ##\t\t\t      ##\n"                 <<
            "\t   #############################\n\n";
    cout << "\t[1] Hangman \t [2] Mine Detector";    
    cout << "\n\t[0] Exit\n";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}