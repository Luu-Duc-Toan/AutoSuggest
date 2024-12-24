#pragma once
#ifndef UI_H
#define UI_H
#include "Header.h"

extern Color toolbarColor;
extern Color searchBarColor;

#define SCREENWIDTH 1000
#define SCREENHEIGHT 1000
#define PAGEMARGINLEFT 50
#define PAGEMARGINTOP 10
#define MARGIN 50
#define ICONSIZE 60

struct Result {
	int resultMargin = 20;
	int resultWidth = 600;
	int resultHeight = 600;
	int resultStartPosX = PAGEMARGINLEFT;
	int resultStartPosY;
	int keySize = 80;
	int meaningSize = keySize / 2;
	string key = "";
	vector<string> meanings = {};

	Result(const int searchBarBoxPosY, const int searchBarHeight);
	void SetStartPosY(const int searchBarBoxPosY, const int& searchBarHeight);
	void SetResult(const string key, const vector<string> meanings);
	void Draw();
	void Reset();
};

struct Icon {
	int iconPosX;
	int iconPosY;
	vector<Vector2> positions;
	vector<Rectangle> boxes;
	vector<Texture2D> icons;
	Icon();
	void Insert(const char* path);
	void Draw(int highlight);
	~Icon();
};


struct SearchBar {
	int searchBarWidth;
	int searchBarHeight;
	int searchBarFontSize;
	double cursorTimer;
	bool showCursor;
	bool enter = false;
	string key;
	string meaning;
	Rectangle searchBarBoxPos;
	int searchCursorX;
	int searchCursorY;
	SearchBar();
	void Draw(int mode);
	void Reset();
};

struct Suggestion {
	SearchBar* searchBar = NULL;
	int hightlightSuggestion; //-1 for no hightlight
	int suggestionFontSize;
	int suggestionMargin;
	int suggestionBoxWidth;
	int suggestionBoxHeight;
	vector<string> suggestions;

	Suggestion(SearchBar& searchBar);
	void SetSuggestions(vector<string>& suggestions);
	bool isEmpty();
	void FirstType();
	void IncreseHightlight();
	void DecreaseHightlight();
	void Draw();
	void Reset();
};
void DrawTutorial();


#endif