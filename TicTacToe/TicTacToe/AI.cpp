#include "AI.h"
#include "Game.h"
#include <vector>

AI::AI(const bool& playerHasStarted) {
	initialize(playerHasStarted);
}

AI::~AI() {
	shutdown();
}

void AI::initialize(const bool& playerHasStarted) {
	if (playerHasStarted == true) {
		humanPlayer = 'X';
		aiPlayer = 'O';		
	}
	else {
		humanPlayer = 'O';
		aiPlayer = 'X';
	}
}

void AI::shutdown() {

}

void AI::aiMove(Board& board) {
	AIMove bestMove = getBestMove(board, aiPlayer);
	board.setBoard(bestMove.x, bestMove.y, aiPlayer);
}

AIMove AI::getBestMove(Board& board, char currentPlayer) {

	bool rv = board.checkForWin(currentPlayer);
	if (rv == true && currentPlayer == humanPlayer && board.isTie == false)
		return AIMove(10);
	if (rv == true && currentPlayer == aiPlayer && board.isTie == false)
		return AIMove(-10);
	if (rv == true && board.isTie == true)
		return AIMove(0);

	std::vector<AIMove> moves;

	for (int i= 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board.getBoard(i, j) == noVal) {
				AIMove move;
				move.x = i;
				move.y = j;
				board.setBoard(i, j, currentPlayer);
				if (currentPlayer == aiPlayer) {
					move.score = getBestMove(board, humanPlayer).score;
				}
				else {
					move.score = getBestMove(board, aiPlayer).score;
				}
				moves.push_back(move);
				board.setBoard(i, j, noVal);
			}
		}
	}

	int bestMove = 0;
	if (currentPlayer == aiPlayer) {
		int bestScore = -100000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		int bestScore = 100000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}
