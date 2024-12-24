#include "UI.h"
Color toolbarColor = { 29, 42, 87, 255 };
Color searchBarColor = { 15, 23, 59, 255 };

Result::Result(const int searchBarBoxPosY, const int searchBarHeight) {
	SetStartPosY(searchBarBoxPosY, searchBarHeight);
}
void Result::SetStartPosY(const int searchBarBoxPosY, const int& searchBarHeight) {
	resultStartPosY = searchBarBoxPosY + searchBarHeight + MARGIN;
}
void Result::SetResult(const string key, const vector<string> meanings) {
	this->key = key;
	this->meanings = meanings;
}
void Result::Draw() {
	int resultPosX = resultStartPosX;
	int resultPosY = resultStartPosY;
	DrawText(key.c_str(), resultPosX, resultPosY, keySize, BLACK);
	resultPosX += resultMargin;
	resultPosY += keySize;
	for (string& meaning : meanings) {
		resultPosY += meaningSize + resultMargin;
		DrawText(meaning.c_str(), resultPosX, resultPosY, meaningSize, BLACK);
	}
}
void Result::Reset() {
	key = "";
	meanings.clear();
}

Icon::Icon() {
	iconPosX = PAGEMARGINLEFT;
	iconPosY = PAGEMARGINTOP;
}
void Icon::Insert(const char* path) {
	icons.emplace_back(LoadTexture(path));
	boxes.push_back({ float(iconPosX + (icons.size() - 1) * 60), float(iconPosY), ICONSIZE, ICONSIZE });
	positions.push_back({ float(boxes.back().x + (ICONSIZE - icons.back().width) / 2),
		float(boxes.back().y + (ICONSIZE - icons.back().height) / 2) });
}
void Icon::Draw(int highlight) {
	for (int i = 0; i < icons.size(); i++) {
		if(i != highlight)
			DrawRectangleRec(boxes[i], WHITE);
		else 
			DrawRectangleRec(boxes[i], GRAY);
		DrawRectangleLinesEx(boxes[i], 3, BLACK);
		DrawTextureEx(icons[i], positions[i], 0, 1, WHITE);
	}
}
Icon::~Icon() {
	for (Texture2D& icon : icons) UnloadTexture(icon);
}
SearchBar::SearchBar() {
	searchBarWidth = 600;
	searchBarHeight = 80;
	searchBarFontSize = 40;
	cursorTimer = 0.0f;
	showCursor = false;
	key = "";
	searchBarBoxPos = { (SCREENWIDTH - searchBarWidth) / 2.0f, PAGEMARGINTOP + ICONSIZE + MARGIN, (float)searchBarWidth, (float)searchBarHeight };
	searchCursorX = searchBarBoxPos.x + 10;
	searchCursorY = searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2;
}
void SearchBar::Draw(int mode) {
	DrawRectangleRec(searchBarBoxPos, WHITE);
	if (mode != 1) {
		if(key.size() == 0) 
			DrawText("Type key", searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2, searchBarFontSize, GRAY);
	}
	else {
		if (!enter && key.size() == 0) {
			DrawText("Type key", searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2, searchBarFontSize, GRAY);
		}
		else if (enter && meaning.size() == 0) {
			DrawText("Type meaning", searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2, searchBarFontSize, GRAY);
		}
	}
	cursorTimer += GetFrameTime();
	if (cursorTimer >= 0.5f) {
		showCursor = !showCursor;
		cursorTimer = 0.0f;
	}
	int textWidth;
	if (mode == 1 && enter) {
		DrawText(meaning.c_str(), searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2,searchBarFontSize, BLACK);
		textWidth = MeasureText(meaning.c_str(), searchBarFontSize);
	}
	else {
		DrawText(key.c_str(), searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2, 
			searchBarFontSize, BLACK);
		textWidth = MeasureText(key.c_str(), searchBarFontSize);
	}
	if (showCursor) {
		DrawText("|", searchCursorX + textWidth, searchCursorY, 50, BLACK);
	}
}
void SearchBar::Reset() {
	enter = false;
	key = "";
	meaning = "";
}

Suggestion::Suggestion(SearchBar& searchBar) {
	this->searchBar = &searchBar;
	hightlightSuggestion = -1;
	suggestionFontSize = 30;
	suggestionMargin = 3;
	suggestionBoxWidth = searchBar.searchBarWidth;
	suggestionBoxHeight = 50;
}
void Suggestion::SetSuggestions(vector<string>& suggestions) {
	this->suggestions = suggestions;
	if (suggestions.empty()) hightlightSuggestion = -1;
	else hightlightSuggestion = 0;
}
bool Suggestion::isEmpty() {
	return suggestions.empty();
}
void Suggestion::FirstType() {
	if (!suggestions.empty() && hightlightSuggestion == -1)
		hightlightSuggestion = 0;
}
void Suggestion::IncreseHightlight() {
	if (++hightlightSuggestion >= suggestions.size())
		hightlightSuggestion = 0;
}
void Suggestion::DecreaseHightlight() {
	if (--hightlightSuggestion <= -1)
		hightlightSuggestion = suggestions.size() - 1;
}
void Suggestion::Draw() {
	int i = 0;
	int suggestionPosY = searchBar->searchBarBoxPos.y + searchBar->searchBarHeight + suggestionMargin + (suggestionBoxHeight - suggestionFontSize) / 2;
	int suggestionBoxPosY = searchBar->searchBarBoxPos.y + searchBar->searchBarHeight + suggestionMargin;
	for (string& suggestion : suggestions) {
		if (i == hightlightSuggestion)
			DrawRectangle(searchBar->searchBarBoxPos.x, suggestionBoxPosY, suggestionBoxWidth, suggestionBoxHeight, GRAY);
		else
			DrawRectangle(searchBar->searchBarBoxPos.x, suggestionBoxPosY, suggestionBoxWidth, suggestionBoxHeight, WHITE);
		DrawText(suggestion.c_str(),searchBar->searchBarBoxPos.x + 10, suggestionPosY, 
			suggestionFontSize, BLACK);
		suggestionPosY += suggestionBoxHeight + suggestionMargin;
		suggestionBoxPosY += suggestionBoxHeight + suggestionMargin;
		i++;
	}
}
void Suggestion::Reset() {
	hightlightSuggestion = -1;
	suggestions.clear();
}
void DrawTutorial() {
	int fontSize = 40;
	int posY = 400;
	int posX = 170;
	DrawText("Press 'Ctrl + V' to paste", posX, posY, fontSize, GRAY);
	posY += fontSize;
	DrawText("Press 'Ctrl + S' to search", posX, posY, fontSize, GRAY);
	posY += fontSize;
	DrawText("Press 'Ctrl + I' to insert", posX, posY, fontSize, GRAY);
	posY += fontSize;
	DrawText("Press 'Ctrl + D' to delete", posX, posY, fontSize, GRAY);
}

