#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Header.h"
#define MAXSUGGESTION 15
extern int maxKeySize;
extern long long count_assignments;
extern chrono::steady_clock::time_point start;

int Comparator(string& s1, string& s2);

//Insert
void Insert(vector<pair<string, vector<string>>>& dic, string& key, string& meaning);

//Delete
void Delete(vector<pair<string, vector<string>>>& dic, string& key);

//Get Meaning
vector<string> GetMeaning(vector<pair<string, vector<string>>>& dic, string& key);

//Search
void Zfunction(vector<int>& z, string& key);
bool CheckKey(string& inputKey, string& key);
int GetStartIndex(vector<pair<string, vector<string>>>& dic, string& inputKey);
void CheckKeys(vector<pair<string, vector<string>>>& dic, int& start, string& inputKey, vector<string>& suggestions);
vector<string> Search(vector<pair<string, vector<string>>>& dic, string& inputKey);

//Save & Load
void Load(vector<pair<string, vector<string>>> &dic);
void Save(vector<pair<string, vector<string>>> &dic);
#endif // ! DICTIONARY_H
