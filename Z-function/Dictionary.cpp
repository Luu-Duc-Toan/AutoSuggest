#include "Dictionary.h"
int maxKeySize = 0;
long long count_assignments = 0;

int Comparator(string& s1, string& s2) {
    int n = min(s1.size(), s2.size()); count_assignments++;
    count_assignments++;
    for (int i = 0; i < n; i++) {
        if (s1[i] < s2[i]) return -1;
        else if (s1[i] > s2[i]) return 1;
        count_assignments++;
    }
    if (s1.size() == s2.size()) return 0;
    else if (s1.size() > s2.size()) return 1;
    else return -1;
}

//Insert
void Insert(vector<pair<string, vector<string>>>& dic, string& key, string& meaning) {
    count_assignments = 0;
    auto start = chrono::high_resolution_clock::now();
    int l = 0; count_assignments++;
    int r = dic.size(); count_assignments++;
    int n = dic.size(); count_assignments++;
    maxKeySize = max(maxKeySize, (int)key.size());
    while (l < r) {
        int mid = l + (r - l) / 2; count_assignments++;
        int com = Comparator(dic[mid].first, key); count_assignments++;
        if (com == 0) {
            bool meaningFound = false;
            for (string& alvailableMeaning : dic[mid].second) {
                count_assignments++;
                if (alvailableMeaning == meaning) {
                    meaningFound = true;
                    break;
                }
            }
            if (!meaningFound) dic[mid].second.push_back(meaning);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Time: " << duration.count() << "ms" << endl;
            cout << "Assignments: " << count_assignments << endl;
            return;
        }
        else if (com < 0) {
            l = mid + 1; count_assignments++;
        }
        else {
            r = mid; count_assignments++;
        }
    }
    dic.push_back({});
    for (int i = n; i > l; i--) {
        count_assignments++;
        dic[i] = dic[i - 1]; count_assignments++;
    }
    dic[l] = { key, {meaning} }; count_assignments++;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration.count() << "ms" << endl;
    cout << "Assignments: " << count_assignments << endl;
}

//Delete
void Delete(vector<pair<string, vector<string>>>& dic, string& key) {
    count_assignments = 0;
    auto start = chrono::high_resolution_clock::now();
    int l = 0; count_assignments++;
    int r = dic.size(); count_assignments++;
    int n = dic.size(); count_assignments++;
    while (l <= r) {
        int mid = l + (r - l) / 2; count_assignments++;
        int com = Comparator(dic[mid].first, key); count_assignments++;
        if (com == 0) {
            for (int i = mid; i < n - 1; i++) {
				dic[i] = dic[i + 1]; count_assignments++;
            }
			dic.pop_back();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Time: " << duration.count() << "ms" << endl;
            cout << "Assignments: " << count_assignments << endl;
			return;
        }
        else if (com < 0) {
            l = mid + 1; count_assignments++;
        }
        else {
            r = mid - 1; count_assignments++;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration.count() << "ms" << endl;
    cout << "Assignments: " << count_assignments << endl;
}

//Get Meaning
vector<string> GetMeaning(vector<pair<string, vector<string>>>& dic, string& key) {
    count_assignments = 0;
    auto start = chrono::high_resolution_clock::now();
	int l = 0; count_assignments++;
    int r = dic.size(); count_assignments++;
    while (l <= r) {
        int mid = l + (r - l) / 2; count_assignments++;
        int com = Comparator(dic[mid].first, key); count_assignments++;
        if (com == 0) {
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Time: " << duration.count() << "ms" << endl;
            cout << "Assignments: " << count_assignments << endl;
            return dic[mid].second;
        }
        else if (com < 0) {
            l = mid + 1; count_assignments++;
        }
        else {
            r = mid - 1; count_assignments++;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration.count() << "ms" << endl;
    cout << "Assignments: " << count_assignments << endl;
	return {};
}

//Search
void Zfunction(vector<int>& z, string& key) {
	int n = key.size(); count_assignments++;
	z = vector<int>(n, 0); count_assignments += n;
    int l = 0; count_assignments++;
    int r = 0; count_assignments++;

    count_assignments++;
    for (int i = 0; i < n; i++) {
        if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]); count_assignments++;
        }
        while (i + z[i] < n && key[i + z[i]] == key[z[i]]) {
			z[i]++; count_assignments++;
        }
        if (i + z[i] - 1 > r) {
			l = i; count_assignments++;
			r = i + z[i] - 1; count_assignments++;
        }
        count_assignments++;
    }
}
bool CheckKey(string& inputKey, string& key) {
	string s = inputKey + '#' + key; count_assignments++;
	vector<int> z; count_assignments++;
    Zfunction(z, s);
	int n1 = inputKey.size(); count_assignments++;
    for (auto& size : z) {
        count_assignments++;
        if (size == n1) return true;
    }
    return false;
}
int GetStartIndex(vector<pair<string, vector<string>>>& dic, string& inputKey) {
    int l = 0; count_assignments++;
    int r = dic.size(); count_assignments++;
    while (l < r) {
        int mid = l + (r - l) / 2; count_assignments++;
        int com = Comparator(dic[mid].first, inputKey); count_assignments++;
        if (com == 0) return mid;
        else if (com > 0) {
            r = mid; count_assignments++;
        }
        else {
            l = mid + 1; count_assignments++;
        }
    }
    return l;
}
void CheckKeys(vector<pair<string, vector<string>>>& dic, int &start, string& inputKey, vector<string>& suggestions) {
    count_assignments++;
    for(int i = start; i < dic.size(); i++) {
        if (CheckKey(inputKey, dic[i].first)) {
           suggestions.push_back(dic[i].first);
        }
        if (suggestions.size() == MAXSUGGESTION) return;
        count_assignments++;
    }
}
vector<string> Search(vector<pair<string, vector<string>>>& dic, string& inputKey) {
    count_assignments = 0;
    auto start = chrono::high_resolution_clock::now();
    if (inputKey.size() > maxKeySize) return {};
    int startIndex = GetStartIndex(dic, inputKey); count_assignments++;
    vector<string> suggestions; count_assignments++;
    CheckKeys(dic, startIndex, inputKey, suggestions);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration.count() << "ms" << endl;
    cout << "Assignments: " << count_assignments << endl;
    return suggestions;
}

//Save & Load
void Load(vector<pair<string, vector<string>>> &dic) {
    fstream inputFile;
    inputFile.open("Data/data.txt", ios::in);

    string word, meaning;
    string line;

    while (!inputFile.eof()) {
        getline(inputFile, line);
		if (line == "") break;
        int start = 0;
        int end = line.find_first_of(L',', start);
        word = line.substr(start, end - start);
		maxKeySize = max(maxKeySize, (int)word.size());
        dic.push_back({ word, {} });
        while (end != -1) {
            start = end + 1;
            end = line.find(L',', start);
            meaning = line.substr(start, end - start);
            dic.back().second.push_back(meaning);
        }
    }
    inputFile.close();
}
void Save(vector<pair<string, vector<string>>> &dic) {
	fstream output("Data/data.txt", ios::out);
    for (auto& x : dic) {
        output << x.first;
        for (auto& meaning : x.second) {
            output << "," << meaning;
        }
        output << endl;
    }
	output.close();
}