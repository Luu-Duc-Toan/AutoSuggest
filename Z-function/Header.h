#pragma once
#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define NOGDI
#define NOUSER
#define WIN32_LEAN_AND_MEAN
#define CloseWindow CloseWindowWin32
#include <windows.h>
#undef CloseWindow

#include<chrono>
#include<raylib.h>
#include<stack>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

#include "UI.h"
#include "Dictionary.h"

#endif // !HEADER_H
