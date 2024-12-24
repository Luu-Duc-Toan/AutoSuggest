#include "Header.h"


int main() {
	//--------------------------------------------------------------------------------------
	//									UI Initialization
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Dictionary");
	int mode = 0; // 0: search, 1: insert, 2: delete

	//for icons
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

	int input = 0;
	float startTimer = 0.0f;
	bool wait = false;
	bool ctrl = false;
	//--------------------------------------------------------------------------------------
	//								Dictionary Initialization
	Trie* trie = new Trie();
	trie->Load();
	cout << "DICTIONARY LOADED" << endl;
	//--------------------------------------------------------------------------------------
	//										Main loop
	while (!WindowShouldClose()) {
		int input = GetKeyPressed();
		if (ctrl) {
			if (input == KEY_V) {
				const char* clipboardText = GetClipboardText();

				if (clipboardText != NULL) {
					string text(clipboardText);
					for (char& x : text) {
						if (x >= 'A' && x <= 'Z') x += 32;
					}
					if (mode == 0) {
						searchBar.key += text;
						vector<string> suggestions = trie->Search(searchBar.key);
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
				if (mode == 0) {
					vector<string> suggestions = {};
					if (searchBar.key.size() > 0)
						suggestions = trie->Search(searchBar.key);
					suggestion.SetSuggestions(suggestions);
				}
			}

		}
		//Choose sugestion 
		else if (input == KEY_UP) {
			suggestion.DecreaseHightlight();
		}
		else if (input == KEY_DOWN) {
			suggestion.IncreseHightlight();
		}
		//Type
		else if ((input >= 'A' && input <= 'Z')) {
			if (searchBar.key.empty()) {
				result.Reset();
			}
			if (mode == 0) {
				searchBar.key += input + 32;
				vector<string> suggestions = trie->Search(searchBar.key);
				suggestion.SetSuggestions(suggestions);
			}
			if (mode == 1) {
				if (searchBar.enter) searchBar.meaning += input + 32;
				else searchBar.key += input + 32;
			}
			if (mode == 2) {
				searchBar.key += input + 32;
			}
		}
		else if (input == KEY_SPACE) {
			if (mode == 1 && searchBar.enter) {
				searchBar.meaning += input;
			}
		}
		else if (input == KEY_ENTER) {
			if (mode == 0) {
				if (suggestion.hightlightSuggestion < 0) {
					//Unvalid search
				}
				else {
					//Get meaning function here
					vector<string> meaning = trie->GetMeaning(suggestion.suggestions[suggestion.hightlightSuggestion]);
					result.SetResult(suggestion.suggestions[suggestion.hightlightSuggestion], meaning);
					//Reset key
					searchBar.Reset();
					suggestion.Reset();
				}
			}
			else if (mode == 1) {
				if (searchBar.key.size() == 0 && searchBar.meaning.size() == 0) {
					//Unvalid insert
				}
				else if (searchBar.key.size() > 0 && !searchBar.enter && searchBar.meaning.size() == 0) {
					searchBar.enter = true;
				}
				else if (searchBar.key.size() > 0 && searchBar.meaning.size() == 0) {
					//Unvalid insert
				}
				else {
					trie->Insert(searchBar.key, searchBar.meaning);
					searchBar.Reset();
				}
			}
			else if (mode == 2) {
				if (searchBar.key.size() == 0) {
					//Unvalid delete
				}
				else {
					trie->Delete(searchBar.key);
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
	//										Exit
	trie->Save();
	return 0;
}