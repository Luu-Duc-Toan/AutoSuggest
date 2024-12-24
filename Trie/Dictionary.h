#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Header.h"
#define MAXSUGGESTION 15
extern long long count_assignments;

struct Trie {
    bool endOfWord;
    vector<string> meanings;
    unordered_map<char, Trie*> map;
    void DFS(vector<string>& suggestions, Trie*& cur, string &suggest);
    void Insert(string& word, string& meaning);
    vector<string> Search(string& s);
    vector<string> GetMeaning(string& s);
    void Delete(string& s);
    void Load();
    void Save(Trie* node, string& word, fstream& file);
    void Save();
    Trie();
    ~Trie();
};

#endif // ! DICTIONARY_H
