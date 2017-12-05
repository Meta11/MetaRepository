#pragma once
#include "AI.h"

class Board {
public:
	Board();
	~Board();
	void initialize();
	void shutdown();
	void printBoard();
	char getBoard(int i, int j) const;
	void setBoard(int i, int j, char& currentPlayer);
	bool checkForWin(const char& currentPlayer);
	bool isTie = false;
	int xCoord = 0;
	int yCoord = 0;
private:
	char boardArray[3][3];
};

class Game {
public:
	Game();
	~Game();
	bool playerHasStarted = true;
	void initialize();
	void shutdown();
	void playGame();
	void playerMove();
	void changePlayer(char& currentPlayer, bool& playerTurn);
private:
	char currentPlayer;
	char multiplayer = ' ';
	bool hasWon = false;
	bool playerTurn = false;
	Board board;
};

