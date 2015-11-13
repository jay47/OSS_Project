/*
===========================================================================
blockattack - Block Attack - Rise of the Blocks
Copyright (C) 2005-2012 Poul Sander

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

Source information and contacts persons can be found at
http://blockattack.sf.net
===========================================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>

#ifdef _WIN32
#ifndef CSIDL_PERSONAL
#define CSIDL_PERSONAL                  0x0005
#endif
#define _WIN32_IE  0x0400
#include "windows.h"
#include <shlobj.h>
#endif

using namespace std;

const int top = 10;

struct record
{
	char name[30];
	int score;
};

class Highscore
{
private:
	record tabel[top];
	string filename;
	int ourType;     //This is ugly, remove me, plz!
	void writeFile();
public:

	Highscore()
	{
	}

	Highscore(int type);

	bool isHighScore(int);
	void addScore(const std::string& newName, int);
	int getScoreNumber(int);
	char* getScoreName(int);
};
