#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hangman.h"

using namespace std;

void playHangman() {
    cout << "\t-------------------" << endl
         << "\tWelcome to Hangman!" << endl
         << "\t-------------------" << endl << endl
         << " 0. Back to menu." << endl
         << " 1. Play Alone." << endl
         << " 2. Play with a friend." << endl
         << " 3. Create a word list." << endl
         << " 4. Delete wordlist." << endl
         << endl << endl;

    int choose;
    cout << "[*] Choose an option: ";
    cin >> choose;

    switch (choose) {
        case 1:
            playAlone();
            break;
        case 2:
            playWithFriend();
            break;
        case 3:
            createWordList();
            break;
        case 4:
            deleteWordlist();
            break;
    }
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void drawHangman(int wrongGuesses) {
    cout << "\t +---+" << endl;
    cout << "\t |   |" << endl;

    if (wrongGuesses >= 1) 
        cout << "\t O   |" << endl; // head
    else 
        cout << "\t     |" << endl;

    if (wrongGuesses == 2) 
        cout << "\t |   |" << endl; // body
    else if (wrongGuesses == 3) 
        cout << "\t" << "/|   |" << endl; // One arm
    else if (wrongGuesses >= 4) 
        cout << "\t" << "/|\\  |" << endl; // both arms
    else 
        cout << "\t     |" << endl;

    if (wrongGuesses == 5) 
        cout << "\t" << "/    |" << endl; // One leg
    else if (wrongGuesses >= 6) 
        cout << "\t" << "/ \\  |" << endl; // Both legs
    else 
        cout << "\t     |" << endl;

    cout << "\t     |" << endl;
    cout << "\t=========" << endl;
}

void playAlone() {
    string directory = "src/hangman/wordlist";      // Directory to store the wordlist file
    string filename = "wordlist.txt";               // Default filename
    string filePath = directory + "/" + filename;   // Full file path

    ifstream file(filePath);
    if (!file) {
        cout << "--> /src/hangman/wordlist/wordlist.txt now found";
        file.close(); 
        return;
    }

    // Read words from the file into a vector
    vector<string> words;
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    file.close();

    if (words.empty()) {
        cout << "No words available to play. Please create a word list first." << endl;
        return;
    }

    // Select a random word from the list
    srand(static_cast<unsigned int>(time(0)));
    string selectedWord = words[rand() % words.size()];

    string guessedWord(selectedWord.length(), '_');
    int wrongGuesses = 0;
    const int maxWrongGuesses = 6;
    char guess;

    while (wrongGuesses < maxWrongGuesses && guessedWord != selectedWord) {     
        drawHangman(wrongGuesses);
        cout << "\n- Word: " << guessedWord << endl;
        cout << "- Guess a letter: ";
        cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < selectedWord.length(); ++i) {
            if (selectedWord[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            wrongGuesses++;
            cout << "\n[*] Wrong guess! You have " << (maxWrongGuesses - wrongGuesses) << " guesses left.\n\n";
        }
        clear();
    }

    drawHangman(wrongGuesses);
    if (guessedWord == selectedWord) {
        cout << " --> Congratulations! You've guessed the word: " << selectedWord << "\n\n";
    } else {
        cout << " --> Game over! The correct word was: " << selectedWord << "\n\n";
    }
}

void playWithFriend() {
    cout << "\n[!] Feature under development. Please check back later.\n";
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

                cout << "Do you want to add another word? (y/n): ";
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
