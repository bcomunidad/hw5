#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void permutations(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string word, std::set<std::string>& results, unsigned index);
bool isValid(const std::string& in, const std::string& floating, std::string word);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {
    std::set<std::string> results;
    std::string word = in;
    permutations(in, floating, dict, word, results, 0);
    return results;
}

// Define any helper functions here

void permutations(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string word, std::set<std::string>& results, unsigned index) {
    if(index == in.length()) {
        if(dict.find(word) != dict.end()) {
            if(isValid(in, floating, word)) {
                results.insert(word);
            }
        }
        return;
    }
    if(in[index] == '-') {
        for(char i = 'a'; i <= 'z'; i++) {
            word[index] = i;
            permutations(in, floating, dict, word, results, index+1);
        }
    }
    else {
        word[index] = in[index];
        permutations(in, floating, dict, word, results, index+1);
    }
}

bool isValid(const std::string& in, const std::string& floating, std::string word) {
    for(unsigned int i = 0; i < in.length(); i++) {
        if(in[i] != word[i] && in[i] != '-') {
            return false;
        }
    } 
    for(unsigned int i = 0; i < floating.size(); i++) {
        char c = floating[i];
        size_t pos = word.find(c);
        if(pos == std::string::npos) {
            return false;
        }
        word[pos] = '*';
    }
    return true;
}

