#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recursiveHelper(string& currWord, int indx, const string& in, vector<int>& xFloating, const string& floating, set<string>& results, const set<string>& dict);
bool wordValidity(const string& word, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    string currWord = in;
    vector<int> xFloating(floating.length(), 0); 
    set<string> results;
    recursiveHelper(currWord, 0, in, xFloating, floating, results, dict);
    return results;

}

//Define any helper functions here
void recursiveHelper(string& currWord, int indx, const string& in, vector<int>& xFloating, const string& floating, set<string>& results, const set<string>& dict) {
    if (indx == currWord.size()) {
        for (int count : xFloating) {
            if (count == 0) {
              return;
            }
        }
        if (wordValidity(currWord, dict)) {
            results.insert(currWord);
        } return;
    }
    int dashes = 0;
    int floatLeft = 0;
    for(int i = 0; i < xFloating.size(); i++) {
        if(xFloating[i] == 0) {
            floatLeft++;
        }
    }
    for(int i = 0; i < currWord.size(); i++) {
        if(currWord[i] == '-') {
            dashes++;
        }
    }
    if(dashes < floatLeft) {
        return;
    }
    if (currWord[indx] != '-') {
        recursiveHelper(currWord, indx + 1, in, xFloating, floating, results, dict);
    } else {
        int index = 0;
        for (char c = 'a'; c <= 'z'; ++c) {
            currWord[indx] = c;
            bool isFloat = false;
            for (size_t i = 0; i < floating.size(); ++i) {
                if (floating[i] == c && xFloating[i] < 1) {
                    xFloating[i]++;
                    index = i;
                    isFloat = true;
                    break;
                }
            }
            recursiveHelper(currWord, indx + 1, in, xFloating, floating, results, dict);
            if (isFloat) {
                xFloating[index]--;
            }
            currWord[indx] = '-';
        }
    }
}

bool wordValidity(const string& word, const set<string>& dict) {
    return dict.find(word) != dict.end();
}

