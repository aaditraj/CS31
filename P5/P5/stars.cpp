//
//  main.cpp
//  P5
//
//  Created by Aaditya Raj on 11/14/24.
//

#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>

using namespace std;

const char WORDFILENAME[] = "/Users/aadityaraj/Desktop/UCLA/CS_31/P5/P5/words.txt";
const int MAXWORDS = 8000;

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) return -1;
    
    char secretWord[MAXWORDLEN+1];
    char tempSecretWord[MAXWORDLEN+1]; // declaring a temp secret word that can be changed every time the user guesses to keep track of the stars/planets
    
    strcpy(secretWord, words[wordnum]);
        
    strcpy(tempSecretWord, secretWord);
    
    // cout << secretWord << endl;
    
    char trialWord[100];
    
    int tries = 0, stars = 0, planets = 0;
        
    bool found = false; // changes to true when trial word is contained in words list
    bool validFormat = true;
    
    while (stars != strlen(secretWord)) { // stars must be equal to length of secret word for a correct guess
        found = false;
        
        while (!found) {
            cout << "Trial word: ";
            
            cin.getline(trialWord, 100, '\n');
            
            validFormat = true;
            
            if (strlen(trialWord) < 4 || strlen(trialWord) > 6) {
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                validFormat = false;
            } else {
                for (int i = 0; i < strlen(trialWord); i++) {
                    if (!islower(trialWord[i])) {
                        cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                        validFormat = false;
                        break;
                    }
                }
            }
            
            if (validFormat) {
                for (int i = 0; i < nWords; i++) {
                    if (strcmp(words[i], trialWord) == 0) {
                        found = true;
                    }
                }
                
                if (!found) {
                    cout << "I don't know that word." << endl;
                }
            }
            
        }
                
        stars = 0;
        planets = 0;
        
        int shorter = (strlen(secretWord) < strlen(trialWord)) ? strlen(secretWord) : strlen(trialWord);
        
        // count the stars
        for (int i = 0; i < shorter; i++) {
            if (trialWord[i] == secretWord[i]) {
            
                tempSecretWord[i] = '*'; // replace the letter with a non-letter character so that it cannot be matched when counting planets
                stars++;
            }
        }
        
        // count the planets
        for (int i = 0; i < strlen(trialWord); i++) {
            
            for (int j = 0; j < strlen(secretWord); j++) { // check every letter of secret word for a match
                if (trialWord[i] == tempSecretWord[j]) {
                    tempSecretWord[j] = '*'; // replace the letter with a non-letter character so that it isn't double counted
                    planets++;
                    break;
                    
                }
            }
        }
        
        strcpy(tempSecretWord, secretWord); // 'reset' the tempSecretWord so it can be used for next guess
        
        if (stars != strlen(secretWord)) cout << "Stars: " << stars << ", Planets: " << planets << endl;
        
        tries++;
    }
    
    
    
    return tries;
}

int main()
{
    char w[MAXWORDS][MAXWORDLEN+1];
    int n = getWords(w, MAXWORDS, WORDFILENAME);
    
    double avgTries = 0;
    int minTries = INT_MAX;
    int maxTries = 0;
    
    if (n < 1) {
        cout << "No words were loaded, so I can't play the game.";
        return -1;
    }
    
    int rounds;
    
    cout << "How many rounds do you want to play? ";
    
    cin >> rounds;
    cin.ignore();
        
    if (rounds <= 0) {
        cout << "The number of rounds must be positive.";
        return -1;
    }
    
    for (int i = 0; i < rounds; i++) {
        cout << endl << "Round " << i+1 << endl;
        
        int randomNum = randInt(0, n-1);
        cout << "The secret word is " << strlen(w[randomNum]) << " letters long." << endl;
        int tries = runOneRound(w, n, randomNum);
        
        if (tries == -1) {
            cout << "Failed to run one round." << endl;
            return -1;
        }
        
        
        minTries = (tries < minTries) ? tries : minTries;
        
        maxTries = (tries > maxTries) ? tries : maxTries;
        
        // update average: multiply by the number of previous rounds, add recent tries, and divide by total rounds
        avgTries *= (i);
        avgTries += tries;
        avgTries /= (i+1);
        
        
        if (tries == 1) {
            cout << "You got it in " << tries << " try." << endl;
        } else {
            cout << "You got it in " << tries << " tries." << endl;
        }
        
        cout << "Average: " << fixed << setprecision(2) << avgTries << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
        
    }

    
    
    
}
