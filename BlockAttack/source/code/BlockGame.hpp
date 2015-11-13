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

#ifndef BLOCKGAME_HPP
#define BLOCKGAME_HPP 1

#include "stats.h"
#include "common.h"

#define NUMBEROFCHAINS 100
#define BLOCKWAIT 100000
#define BLOCKHANG 1000

#define ACTION_UPDATE 0
#define ACTION_MOVECURSOR 1
#define ACTION_MOVECURSORTO 2
#define ACTION_SWITCH 3
#define ACTION_PUSH 4
#define ACTION_CREATEGARBAGE 5
#define ACTION_CREATEGRAYGARBAGE 6
#define ACTION_GAMEOVER 7
#define ACTION_WIN 8
#define ACTION_DRAW 9
#define ACTION_GAMESPEED 10
#define ACTION_HANDICAP 11
#define ACTION_NEW 12
#define ACTION_NEWTT 13
#define ACTION_NEWVS 14
#define ACTION_STARTBLOCKS 15
#define ACTION_NOP 16

////////////////////////////////////////////////////////////////////////////////
//The BloackGame class represents a board, score, time etc. for a single player/
////////////////////////////////////////////////////////////////////////////////
class BlockGame
{
private:
	int prevTowerHeight;
	bool bGarbageFallLeft;

	Uint32 nextGarbageNumber;
	Uint32 pushedPixelAt;
	Uint32 nrPushedPixel, nrFellDown, nrStops;
	bool garbageToBeCleared[7][30];
	Uint32 lastAImove;

	Sint16 AI_LineOffset; //how many lines have changed since command
	Uint32 hangTicks;    //How many times have hang been decreased?
	//int the two following index 0 may NOT be used (what the fuck did I meen?)
	Uint8 chainSize[NUMBEROFCHAINS]; //Contains the chains
	bool chainUsed[NUMBEROFCHAINS];   //True if the chain is used

	Uint32 nextRandomNumber;

	Uint16 rand2();
	int firstUnusedChain();

//public:
protected:
	int lastCounter;
	string strHolder;
	bool bDraw;
	unsigned int ticks;
	unsigned int gameStartedAt;
	unsigned int gameEndedAfter;		//How long did the game last?
	int linesCleared;
	int TowerHeight;
	BlockGame *garbageTarget;
	Sint32 board[7][30];
	int stop;
	int speedLevel;
	int pixels;
	int MovesLeft;
	bool timetrial, stageClear, vsMode, puzzleMode;
	int Level; //Only used in stageClear and puzzle (not implemented)
	int stageClearLimit; //stores number of lines user must clear to win
	int combo;
	int chain;
	int cursorx; //stores cursor position
	int cursory; // -||-
	double speed, baseSpeed; //factor for speed. Lower value = faster gameplay
	Uint32 score;
	bool bGameOver;
	bool hasWonTheGame;
	int AI_MoveSpeed;   //How often will the computer move? milliseconds
	bool AI_Enabled;

	Uint32 handicap;


	int AIlineToClear;

	short AIstatus;   //Status flags:
	//0: nothing, 2: clear tower, 3: clear horisontal, 4: clear vertical
	//1: make more lines, 5: make 2 lines, 6: make 1 line

public:

	std::string name;

public:
	//Constructor
	BlockGame();

	//Deconstructor, never really used... game used to crash when called, cause of the way sBoard was created
	//It should work now and can be used if we want to assign more players in network games that we need to free later
	~BlockGame();

	void setGameSpeed(Uint8 globalSpeedLevel);
	void setHandicap(Uint8 globalHandicap);
	//Set the move speed of the AI based on the aiLevel parameter
	//Also enables AI
	void setAIlevel(Uint8 aiLevel);
	Uint8 getAIlevel()  const;
	
	virtual void AddText(int x, int y, const std::string& text, int time) const  {}
	virtual void AddBall(int x, int y, bool right, int color) const  {}
	virtual void AddExplosion(int x, int y) const  {}
	virtual void PlayerWonEvent() const  {}
	virtual void DrawEvent() const {}
	virtual void BlockPopEvent() const  {}
	virtual void LongChainDoneEvent() const  {}
	virtual void TimeTrialEndEvent() const  {}
	virtual void EndlessHighscoreEvent() const  {}
	
	int GetScore() const;
	int GetHandicap() const;
	bool isGameOver() const;
	Sint32 GetGameStartedAt() const;
	Sint32 GetGameEndedAt() const;
	bool isTimeTrial() const;
	bool isStageClear() const;
	bool isVsMode() const;
	bool isPuzzleMode() const;
	int GetLinesCleared() const;
	int GetStageClearLimit() const;
	int GetChains() const;
	int GetPixels() const;
	int GetSpeedLevel() const;
	int GetTowerHeight() const;
	int GetCursorX() const;
	int GetCursorY() const;
	void MoveCursorTo(int x, int y);
	bool GetIsWinner() const;
	//Instead of creating new object new game is called, to prevent memory leaks
	void NewGame(unsigned int ticks);
	void NewTimeTrialGame(unsigned int ticks);
	//Starts a new stage game, takes level as input!
	void NewStageGame(int level, unsigned int ticks);
	void NewPuzzleGame(int level, unsigned int ticks);
	//Replay the current level
	void retryLevel(unsigned int ticks);
	//Play the next level
	void nextLevel(unsigned int ticks);
	//Starts new Vs Game (two Player)
	void NewVsGame(BlockGame *target,unsigned int ticks);
	//Starts new Vs Game (two Player)
	void NewVsGame(BlockGame *target, bool AI,unsigned int ticks);
	void putStartBlocks(Uint32 n);
	//Creates garbage using a given wide and height
	bool CreateGarbage(int wide, int height);
	//Creates garbage using a given wide and height
	bool CreateGreyGarbage();
	//prints "Game Over" and ends game
	void SetGameOver();
	bool GetAIenabled();
	bool IsNearDeath();
	//Moves the cursor, receaves N,S,E or W as a char an moves as desired
	void MoveCursor(char way);
	//switches the two blocks at the cursor position, unless game over
	void SwitchAtCursor();
	//Generates a new line and moves the field one block up (restart puzzle mode)
	void PushLine();
	void Update(unsigned int newtick);
	void PerformAction(unsigned int tick, int action, string param);
	/**
	 *
	 * @param tick Tick of the action
	 * @param action The action
	 * @param param Params.
	 * @return 1 if an action was selected
	 */
	int GotAction(unsigned int &tick,int &action,string &param);
	//Prints "winner" and ends game
	void setPlayerWon();
	//void SetGameOver();
	//Prints "draw" and ends the game
	void setDraw();
private:
	//Test if LineNr is an empty line, returns false otherwise.
	bool LineEmpty(int lineNr) const;
	//Test if the entire board is empty (used for Puzzles)
	bool BoardEmpty() const;
	//Anything that the user can't move? In that case Game Over cannot occur
	bool hasStaticContent() const;
	void putStartBlocks();
	//decreases hang for all hanging blocks and wait for waiting blocks
	void ReduceStuff();
	//Clears garbage, must take one the lower left corner!
	int GarbageClearer(int x, int y, int number, bool aLineToClear, int chain);
	//Marks garbage that must be cleared
	int GarbageMarker(int x, int y);
	int FirstGarbageMarker(int x, int y);
	//Clear Blocks if 3 or more is alligned (naive implemented)
	void ClearBlocks();
	//Moves all peaces a spot down if possible
	int FallBlock(int x, int y, int number);
	//Makes all Garbage fall one spot
	void GarbageFall();
	//Makes the blocks fall (it doesn't test time, this must be done before hand)
	void FallDown();
	//Pushes a single pixel, so it appears to scrool
	void PushPixels();
	//See how high the tower is, saved in integer TowerHeight
	void FindTowerHeight();
///////////////////////////////////////////////////////////////////////////
/////////////////////////// AI starts here! ///////////////////////////////
///////////////////////////////////////////////////////////////////////////
	//First the helpet functions:
	int nrOfType(int line, int type);
	int AIcolorToClear;
	//See if a combo can be made in this line
	int horiInLine(int line);
	bool horiClearPossible();
	//the Line Has Unmoveable Objects witch might stall the AI
	bool lineHasGarbage(int line);
	//Types 0..6 in line
	int nrOfRealTypes(int line);
	//See if there is a tower
	bool ThereIsATower();
	double firstInLine1(int line);
	//returns the first coordinate of the block of type
	double firstInLine(int line, int type);
	//There in the line shall we move
	int closestTo(int line, int place);
	//The AI will remove a tower
	void AI_ClearTower();
	//The AI will try to clear block horisontally
	void AI_ClearHori();
	//Test if vertical clear is possible
	bool veriClearPossible();
	//There in the line shall we move
	int closestTo(int line, int type, int place);
	//The AI will try to clear blocks vertically
	void AI_ClearVertical();
	bool firstLineCreated;
	void AI_Move();
//////////////////////////////////////////////////////////////////////////
///////////////////////////// AI ends here! //////////////////////////////
//////////////////////////////////////////////////////////////////////////

	void PushLineInternal();
	//Updates evrything, if not called nothing happends
	void Update();
	void UpdateInternal(unsigned int newtick);
};
////////////////////////////////////////////////////////////////////////////////
///////////////////////// BlockAttack class end ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif
