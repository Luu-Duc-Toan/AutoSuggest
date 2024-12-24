#include "Header.h"


int main() {
	//--------------------------------------------------------------------------------------
	//									UI Initialization
	int input = 0;
	float startTimer = 0.0f;
	bool wait = false;
	bool ctrl = false;

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Dictionary");
	int mode = 0; // 0: search, 1: insert, 2: delete
	
	//Icons
	Icon icons;
	icons.Insert("Images/search.png");
	icons.Insert("Images/insert.png");
	icons.Insert("Images/delete.png");
	Rectangle toolBarBackground = { 0, 0, SCREENWIDTH, ICONSIZE + MARGIN / 2 };

	//Search bar
	SearchBar searchBar;
	Rectangle searchBarBackground = { 0, toolBarBackground.height, SCREENWIDTH,  searchBar.searchBarHeight + MARGIN };

	//Suggestions
	Suggestion suggestion(searchBar);

	//Result
	Result result(int(searchBar.searchBarBoxPos.y), searchBar.searchBarHeight);
	//--------------------------------------------------------------------------------------
	//							Dictionary Initialization
	vector<pair<string, vector<string>>> dic;
	Load(dic);
	cout << "DICTIONARY LOADED" << endl;
	//--------------------------------------------------------------------------------------
	//									Main Loop
	while (!WindowShouldClose()) {
		int input = GetKeyPressed();
		if (ctrl) {
			if (input == KEY_V) {
				const char* clipboardText = GetClipboardText();
				
				if (clipboardText != NULL) {
					string text = clipboardText;
					for (auto& x : text) {
						if (x >= 'A' && x <= 'Z') {
							x += 32;
						}
					}
					if (mode == 0) {
						searchBar.key += text;
						//Search for suggestions in dictionary
						vector<string> suggestions = Search(dic, searchBar.key);
						suggestion.SetSuggestions(suggestions);
					}
					else if (mode == 1) {
						if (searchBar.enter) searchBar.meaning += text;
						else searchBar.key += text;
					}
					else {
						searchBar.key += text;
					}
				}
			}
			else if (input == KEY_S) {
				mode = 0;
				suggestion.Reset();
				searchBar.Reset();
			}
			else if (input == KEY_I) {
				mode = 1;
				suggestion.Reset();
				searchBar.Reset();
			}
			else if (input == KEY_D) {
				mode = 2;
				suggestion.Reset();
				searchBar.Reset();
			}
			ctrl = false;
		}
		else if (input == KEY_BACKSPACE) {
			if (searchBar.meaning.size() > 0 && mode == 1) {
				searchBar.meaning.pop_back();
			}
			if (searchBar.key.size() > 0)
			{
				searchBar.key.pop_back();
				//Search again
				if (mode == 0) {
					vector<string> suggestions = {};
					if (searchBar.key.size() > 0)
						suggestions = Search(dic, searchBar.key);
					suggestion.SetSuggestions(suggestions);
				}
			}
		}
		//Choose suggestion
		else if (input == KEY_UP) {
			suggestion.DecreaseHightlight();
		}
		else if (input == KEY_DOWN) {
			suggestion.IncreseHightlight();
		}
		//Type
		else if ((input >= 'A' && input <= 'Z')) {
			input += 32;
			if (searchBar.key.empty()) {
				result.Reset();
			}
			if (mode == 0) {
				searchBar.key += input;
				//Search for suggestions in dictionary
				vector<string> suggestions = Search(dic, searchBar.key);
				suggestion.SetSuggestions(suggestions);
			}
			if (mode == 1) {
				if (searchBar.enter) searchBar.meaning += input;
				else searchBar.key += input;
			}
			if (mode == 2) {
				searchBar.key += input;
			}
		}
		else if (input == KEY_SPACE) {
			if (mode == 1 && searchBar.enter) {
				searchBar.meaning += input;
			}
		}
		else if (input == KEY_ENTER) {
			//Search
			if (mode == 0) {
				if (suggestion.hightlightSuggestion < 0) {
					//Unvalid search
				}
				else {
					vector<string> meaning = GetMeaning(dic, suggestion.suggestions[suggestion.hightlightSuggestion]);
					result.SetResult(suggestion.suggestions[suggestion.hightlightSuggestion], meaning);
					searchBar.Reset();
					suggestion.Reset();
				}
			}
			else if (mode == 1) {
				if (searchBar.key.size() == 0 && searchBar.meaning.size() == 0) {
					//Unvalid insertion
				}
				else if (searchBar.key.size() > 0 && !searchBar.enter && searchBar.meaning.size() == 0) {
					searchBar.enter = true;
				}
				else if (searchBar.key.size() > 0 && searchBar.meaning.size() == 0) {
					//Unvalid insertion
				}
				else {
					Insert(dic, searchBar.key, searchBar.meaning);
					searchBar.Reset();
				}
			}
			else if (mode == 2) {
				if (searchBar.key.size() == 0) {
					//Unvalid delete
				}
				else {
					Delete(dic, searchBar.key);
					searchBar.Reset();
				}
			}
			
		}
		else if (input == KEY_LEFT_CONTROL || input == KEY_RIGHT_CONTROL) {
			startTimer = GetTime();
			while (GetTime() - startTimer < 0.2) {
			}
			ctrl = true;
		}
		//Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);
		if (result.key.size() == 0 && result.meanings.size() == 0)
			DrawTutorial();

		DrawRectangleRec(toolBarBackground, toolbarColor);
		icons.Draw(mode);

		DrawRectangleRec(searchBarBackground, searchBarColor);
		searchBar.Draw(mode);
		
		suggestion.Draw();
		
		result.Draw();

		EndDrawing();
	}
	//--------------------------------------------------------------------------------------
	//									Exit
	Save(dic);
}

//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <algorithm>
//#include <ctime>
//using namespace std;
//bool com(const vector<string> a, const vector<string> b) {
//	return a[0] < b[0];
//}
//void C(int index, int div, vector<int> &res) {
//    if (div <= 2) return;
//    res.push_back(index - div);
//    C(index - div, div / 2, res);
//	res.push_back(index + div);
//	C(index + div, div / 2, res);
//}
//void Shuffle(int start, vector<vector<string>>& dic) {
//	for (int i = start; i < dic.size(); i++) {
//		int j = rand() % (dic.size() - start - 1) + start + 1;
//		vector<string> tmp = dic[j];
//		dic[j] = dic[i];
//		dic[j] = tmp;
//	}
//}
//int main() {
//	srand(time(NULL));
//	fstream inputFile;
//	inputFile.open("Data/data.txt", ios::in);
//    string word, meaning;
//    string line;
//    vector<vector<string>> dic;
//    while (!inputFile.eof()) {
//        getline(inputFile, line);
//        if (line == "") break;
//        int start = 0;
//        int end = line.find_first_of(',', start);
//        word = line.substr(start, end - start);
//		dic.push_back({ word });
//        while (end != -1) {
//            start = end + 1;
//            end = line.find(',', start);
//            meaning = line.substr(start, end - start);
//            dic.back().push_back(meaning);
//        }
//    }
//	/*vector<int> res = { int(dic.size()) / 2 };
//	C(int(dic.size()) / 2, int(dic.size()) / 4, res);
//	for (int i = 0; i < 4; i++) Shuffle(res.size(), dic);
//	fstream output("Data/data.txt", ios::out);
//	for (auto& x : dic) {
//		output << x[0];
//		for (int i = 1; i < x.size(); i++) {
//			output << "," << x[i];
//		}
//		output << endl;
//	}
//	output.close();*/
//	sort(dic.begin(), dic.end(), com);
//    fstream output("Data/data.txt", ios::out);
//    for (auto& x : dic) {
//        output << x[0];
//		for (int i = 1; i < x.size(); i++) {
//			output << "," << x[i];
//		}
//        output << endl;
//    }
//	output.close();
//}
