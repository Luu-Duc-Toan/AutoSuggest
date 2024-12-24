#include "Dictionary.h"
long long count_assignments = 0;

Trie::Trie() {
	endOfWord = false;
}

void Trie::Insert(string& word, string& meaning) {
	count_assignments = 0;
	auto start = chrono::high_resolution_clock::now();
	Trie* cur = this; count_assignments++;
	for (char& x : word) {
		count_assignments++;
		if (cur->map.find(x) == cur->map.end()) {
			cur->map[x] = new Trie(); count_assignments++;
		}
		cur = cur->map[x]; count_assignments++;
	}
	if (cur->endOfWord) {
		for (string& dicMeaning : meanings) {
			count_assignments++;
			if (dicMeaning == meaning) {
				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
				cout << "Runtime: " << duration.count() << endl;
				cout << "Count_assignments: " << count_assignments << endl;
				return;
			}
		}
		cur->meanings.push_back(meaning);
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Runtime: " << duration.count() << endl;
		cout << "Count_assignments: " << count_assignments << endl;
		return;
	}
	cur->endOfWord = true; count_assignments++;
	cur->meanings.push_back(meaning);
}
void Trie::DFS(vector<string>& suggestions, Trie*& cur, string& suggest) {
	if (suggestions.size() >= MAXSUGGESTION) return;
	if (cur->endOfWord) {
		suggestions.push_back(suggest);
	}
	for (auto& x : cur->map) {
		count_assignments++;
		suggest.push_back(x.first);
		DFS(suggestions, x.second, suggest);
		suggest.pop_back();
		if (suggestions.size() >= MAXSUGGESTION) return;
	}
}
vector<string> Trie::Search(string& s) {
	count_assignments = 0;
	auto start = chrono::high_resolution_clock::now();
	Trie* cur = this; count_assignments++;
	vector<string> suggestions = {}; count_assignments++;
	for (char& x : s) {
		count_assignments++;
		if (cur->map.find(x) != cur->map.end()) {
			cur = cur->map[x]; count_assignments++;
		}
		else {
			auto end = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
			cout << "Runtime: " << duration.count() << endl;
			cout << "Count_assignments: " << count_assignments << endl;
			return {};
		}
	}
	DFS(suggestions, cur, s);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Runtime: " << duration.count() << endl;
	cout << "Count_assignments: " << count_assignments << endl;
	return suggestions;
}

vector<string> Trie::GetMeaning(string& s) {
	Trie* cur = this;
	for (char& x : s) {
		if (cur->map.find(x) != cur->map.end())
			cur = cur->map[x];
		else {
			return {};
		}
	}
	if (cur->endOfWord) return cur->meanings;
	else return {};
}
void Trie::Delete(string& s) {
	count_assignments = 0;
	auto start = chrono::high_resolution_clock::now();
	Trie* cur = this; count_assignments++;
	stack <pair<Trie*, char>> st; count_assignments++;
	for (char& x : s) {
		count_assignments++;
		if (cur->map.find(x) != cur->map.end()) {
			st.push({ cur,x });
			cur = cur->map[x]; count_assignments++;
		}
		else {
			auto end = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
			cout << "Runtime: " << duration.count() << endl;
			cout << "Count_assignments: " << count_assignments << endl;
			return;
		}
	}
	cur->endOfWord = false; count_assignments++;
	while (!cur->endOfWord && cur->map.size() == 0) {
		Trie* par = st.top().first; count_assignments++;
		char c = st.top().second; count_assignments++;
		st.pop();
		delete par->map[c];
		par->map.erase(c);
		cur = par; count_assignments++;
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Runtime: " << duration.count() << endl;
	cout << "Count_assignments: " << count_assignments << endl;
}
void Trie::Load() {
	fstream inputFile;
	inputFile.open("Data/data.txt", ios::in);

	string word, meaning;
	string line;

	while (!inputFile.eof()) {
		getline(inputFile, line);
		if (line.empty()) break;
		int start = 0;
		int end = line.find_first_of(',', start);
		word = line.substr(start, end - start);
		while (end != -1) {
			start = end + 1;
			end = line.find(',', start);
			meaning = line.substr(start, end - start);
			Insert(word, meaning);
		}
	}
	inputFile.close();
}
void Trie::Save(Trie* node, string& word, fstream& file) {
	if (!node) return;
	if (node->endOfWord) {
		file << word;
		for (int i = 0; i < node->meanings.size(); i++) {
			file << "," << node->meanings[i];
		}
		file << endl;
	}
	for (auto it = node->map.begin(); it != node->map.end(); it++) {
		word.push_back(it->first);
		Save(it->second, word, file);
		word.pop_back();
	}
}
void Trie::Save() {
	fstream file("Data/data.txt", ios::out);
	string word = "";
	Save(this, word, file);
	file.close();
}
Trie::~Trie() {
	for (auto& x : map) {
		if (x.second) continue;
		delete x.second;
	}
}
