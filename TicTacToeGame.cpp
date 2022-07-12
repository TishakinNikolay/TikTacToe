#include "TicTacToeGame.h"
#include "Enums.h"
#include <iostream>

char fieldTokenToChar(const FieldToken token) {
	if (token == FieldToken::CIRCLE) {
		return '0';
	}
	else if (token == FieldToken::CROSS) {
		return 'X';
	}
	else {
		return '_';
	}
}

std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game) {

	for (int i = 0; i < TicTacToeGame::TOTAL_TILES; ++i) {

		std::cout << " | " << fieldTokenToChar(game.m_fieldState[i]);

		if ((i + 1) % TicTacToeGame::FIELD_SIZE == 0) {
			std::cout << std::endl;
		}
	}

	return os;
}

TicTacToeGame::TicTacToeGame() {
	init();
}

void TicTacToeGame::init() {

	refreshGame();
}

void TicTacToeGame::refreshGame() {


	for (int i = 0; i < TOTAL_TILES; ++i) {

		m_fieldState[i] = FieldToken::EMPTY;
	}

	m_currentTurn = FieldToken::CROSS;

	m_gameState = GameState::INIT;

	m_turnsDone = 0;
}

void TicTacToeGame::startGame() {

	m_gameState = GameState::RUNNING;
	std::cout << *this;
	while (m_gameState == GameState::RUNNING) {

		int curIndex;
		std::cin >> curIndex;

		TurnResult turnResult;

		while ((turnResult = doTurn(curIndex)) == TurnResult::TAKEN);

		std::cout << *this;
		if (turnResult != TurnResult::NEXT) {
			m_gameState = GameState::END_GAME;

			std::cout << (turnResult == TurnResult::WIN_CROSS ? "cross win" : turnResult == TurnResult::DRAW ? "draw" : "circle win") << std::endl;
		}
	}
}

TurnResult TicTacToeGame::doTurn(int fieldIndex) {

	if (fieldIndex < 0 || fieldIndex > TOTAL_TILES || m_fieldState[fieldIndex] != FieldToken::EMPTY) {
		return TurnResult::TAKEN;
	}

	m_fieldState[fieldIndex] = m_currentTurn;

	FieldToken possibleWinner = m_currentTurn;

	m_currentTurn = m_currentTurn == FieldToken::CROSS ? FieldToken::CIRCLE : FieldToken::CROSS;

	TurnResult result = isWin() ? defineWinner(possibleWinner) : TurnResult::NEXT;

	if (++m_turnsDone == TOTAL_TILES && result == TurnResult::NEXT) {
		return TurnResult::DRAW;
	}

	return result;
}

TurnResult TicTacToeGame::defineWinner(const FieldToken currentTurn) const {
	return currentTurn == FieldToken::CROSS ? TurnResult::WIN_CROSS : TurnResult::WIN_CIRCLE;
}

bool TicTacToeGame::isWin() const {

	FieldToken currentLine[FIELD_SIZE];

	// Horizontal scan
	for (int i = 0; i < TOTAL_TILES; ++i) {

		currentLine[i % FIELD_SIZE] = m_fieldState[i];

		if (((i + 1) % FIELD_SIZE) == 0) {

			if (isWinCondition(currentLine)) {
				return true;
			}
		}
	}

	// Vertical scan
	for (int i = 0; i < TOTAL_TILES; ++i) {

		currentLine[i % FIELD_SIZE] = m_fieldState[(i / FIELD_SIZE) + (FIELD_SIZE * (i % FIELD_SIZE))];

		if (((i + 1) % FIELD_SIZE) == 0) {

			if (isWinCondition(currentLine)) {
				return true;
			}
		}
	}

	// Cross Scan
	// FIELD_SIZE * 2 because square has 2 only diagonals
	for (int i = 0; i < FIELD_SIZE * 2; ++i) {

		currentLine[i % FIELD_SIZE] = m_fieldState[((i % FIELD_SIZE) + (i < FIELD_SIZE ? 0 : 1)) * (FIELD_SIZE + (i < FIELD_SIZE ? 1 : -1))];

		if (((i + 1) % FIELD_SIZE) == 0) {

			if (isWinCondition(currentLine)) {
				return true;
			}
		}
	}

	return false;
}

bool TicTacToeGame::isWinCondition(const FieldToken* line) const {

	FieldToken firstToken = line[0];

	if (firstToken == FieldToken::EMPTY) {
		return false;
	}

	for (int i = 1; i < FIELD_SIZE; ++i) {

		if (line[i] != firstToken) {
			return false;
		}
	}

	return true;
}

TicTacToeGame::~TicTacToeGame() {
}