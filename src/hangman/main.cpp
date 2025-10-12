#include <iostream>
#include <string>
#include <fstream>
#include "hangman.h"

using namespace std;

void playHangman() {
    cout << "\t-------------------" << endl
         << "\tWelcome to Hangman!" << endl
         << "\t-------------------" << endl << endl
         << " 0. Back to menu." << endl
         << " 1. Start Game." << endl
         << " 2. Create a word list." << endl
         << " 3. Delete wordlist." << endl
         << endl << endl;

    int choose;
    cout << "[*] Choose an option: ";
    cin >> choose;

    switch ( choose) {
        case 0:

        break;
        case 1:
            startGame();
            break;
        case 2:
            createWordList();
        break;
        case 3:
            deleteWordlist();
        break;
    }
}

void startGame() {
    cout << "Feature to start the game is under development." << endl;
}

void createWordList() {
    string directory = "src/hangman/wordlist";      // Directory to store the wordlist file
    string filename = "wordlist.txt";               // Default filename
    string filePath = directory + "/" + filename;   // Full file path

    // Open the file in append mode
    ofstream file(filePath, ios::app); // Open in append mode to add to existing file

    if (!file) {
        cout << "--> /src/hangman/wordlist/wordlist.txt now found";
        file.close(); 
    }
    else {
        if (file.is_open()) {
            string word;
            char addAnother;

            // loop for add words
            do {
                cout << "\n\n[*] Enter a word: ";
                cin >> word;
                file << word << endl;  // Add word to the file

                cout << "\nDo you want to add another word? (y/n): ";
                cin >> addAnother;
            } while (addAnother == 'y' || addAnother == 'Y');

            file.close();
            cout << "\n--> Words added successfully to " << filePath << endl;
        } 
        else {
            cout << "Error opening file " << filePath << endl;
        }
    }
}

void deleteWordlist() {
    string directory = "src/hangman/wordlist";   // Directory where the wordlist file is stored
    string filename = "wordlist.txt";             // Default filename
    string filePath = directory + "/" + filename; // Full file path

    // Check if the file exists before trying to delete it
    if (remove(filePath.c_str()) != 0) {
        cout << "Error deleting the wordlist file: " << filePath << endl;
    } else {
        cout << "--> Wordlist file deleted successfully." << endl;
    }
}
