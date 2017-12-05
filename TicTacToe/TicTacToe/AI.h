#pragma once

class Board;

struct AIMove {
	AIMove(){}
	AIMove(int _score) : score(_score) {}
	int x;
	int y;
	int score = 0;
};

class AI {
public:
	AI(const bool& playerHasStarted);
	~AI();
	void initialize(const bool& playerHasStarted);
	void shutdown();
	void aiMove(Board& board);
private:
	char humanPlayer;
	char aiPlayer;
	char noVal = ' ';
	AIMove getBestMove(Board& board, char currentPlayer);
};