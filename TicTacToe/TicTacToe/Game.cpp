#include "Game.h"
#include <iostream>

Board::Board() {
	this->initialize();
}

Board::~Board() {
	this->shutdown();
}

void Board::initialize() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			boardArray[i][j] = ' ';
}

void Board::shutdown() {

}

void Board::printBoard() {
	std::cout << "-----------------" << std::endl;
	std::cout << "||||| 1 | 2 | 3 |" << std::endl;
	std::cout << "-----------------" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << "| " << i + 1 << " ";
		for (int j = 0; j < 3; j++) {
			std::cout << "| ";
			std::cout << boardArray[i][j];
			std::cout << " ";
		}
		std::cout << "|" << std::endl;
		std::cout << "-----------------" << std::endl;
	}
}

char Board::getBoard(int i, int j) const {
	return boardArray[i][j];
}

void Board::setBoard(int i, int j, char& currentPlayer) {
	if (boardArray[i][j] == ' ')
		boardArray[i][j] = currentPlayer;
	else if(boardArray[i][j] != ' ' && currentPlayer == ' ') {
		isTie = false;
		boardArray[i][j] = currentPlayer;
	}
	else {
		std::cout << "Coordenada no válida, vuelve a introducirla" << std::endl;
		if (currentPlayer == 'X')
			currentPlayer = 'O';
		else
			currentPlayer = 'X';
	}		
}

bool Board::checkForWin(const char& currentPlayer) {

	bool fooTie = true;
	//horizontal
	for (int i = 0; i < 3; i++) {
		if ((this->getBoard(i, 0) == this->getBoard(i, 1)) && (this->getBoard(i, 0) == this->getBoard(i, 2)) && this->getBoard(i, 0) != ' ') {
			return true;
		}
	}
	//vertical
	for (int i = 0; i < 3; i++) {
		if ((this->getBoard(0, i) == this->getBoard(1, i)) && (this->getBoard(0, i) == this->getBoard(2, i)) && this->getBoard(0, i) != ' ') {
			return true;
		}
	}
	//diagonales
	if ((this->getBoard(0, 0) == this->getBoard(1, 1)) && (this->getBoard(1, 1) == this->getBoard(2, 2)) && this->getBoard(0, 0) != ' ') {
		return true;
	}
	if ((this->getBoard(0, 2) == this->getBoard(1, 1)) && (this->getBoard(1, 1) == this->getBoard(2, 0)) && this->getBoard(2, 0) != ' ') {
		return true;
	}
	//Hay empate?
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fooTie &= (this->getBoard(i, j) != ' ');
		}
	}
	isTie = fooTie;

	if (isTie) {
		return true;
	}
	else
		return false;
}

Game::Game() {
	this->initialize();
}

Game::~Game() {
	this->shutdown();
}

void Game::initialize() {
	board.initialize();
	currentPlayer = 'X';
}

void Game::shutdown() {

}

void Game::playGame() {
	board.printBoard();
	currentPlayer = 'X';
	std::cout << "Multiplayer (y/n)? ";
	while((multiplayer != 'y') && (multiplayer !='n')){
		std::cin >> multiplayer;
	}
	if (multiplayer == 'n') {
		std::cout << "Quieres empezar? (y/n) ";
		char playTurn = ' ';
		while((playTurn != 'y') && (playTurn != 'n'))
			std::cin >> playTurn;
		if (playTurn == 'y') {
			playerHasStarted = true;
			playerTurn = true;
		}
		else {
			playerHasStarted = false;
			playerTurn = false;
		}
	}
	AI aiPlayer(playerHasStarted);
	while (!hasWon) {

		if (multiplayer == 'n' && !playerTurn)
			aiPlayer.aiMove(board);
		else {
			playerMove();
			board.setBoard(board.xCoord - 1, board.yCoord - 1, currentPlayer);
		}
		board.printBoard();
		hasWon = board.checkForWin(currentPlayer);
		if(!hasWon)
			this->changePlayer(currentPlayer, playerTurn);
	}
	if(board.isTie)
		std::cout << "Ha habido un empate!!!" << std::endl;
	else
		std::cout << "Han ganado las " << currentPlayer << "!!!" << std::endl;
	char salir;
	std::cout << "Introduce una tecla para cerrar." << std::endl;
	std::cin >> salir;
}

void Game::playerMove() {
	std::cout << "Turno de las " << currentPlayer << std::endl;
	std::cout << "Escoge la coordenada X: " << std::endl;
	std::cin >> board.xCoord;
	std::cout << "Escoge la coordenada Y: " << std::endl;
	std::cin >> board.yCoord;
}

void Game::changePlayer(char& currentPlayer, bool& playerTurn) {
	if (currentPlayer == 'X')
		currentPlayer = 'O';
	else
		currentPlayer = 'X';
	if (!playerTurn)
		playerTurn = true;
	else
		playerTurn = false;
}
