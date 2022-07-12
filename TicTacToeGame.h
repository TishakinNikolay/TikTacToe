#pragma once
#include "Enums.h"
#include <iostream>

class TicTacToeGame {

public:
	friend std::ostream& operator<<(std::ostream&, const TicTacToeGame&);
	void startGame();
	TicTacToeGame();
	~TicTacToeGame();
private:

	// Square side size
	static const int FIELD_SIZE = 3;
	static const int TOTAL_TILES = FIELD_SIZE * FIELD_SIZE;

	FieldToken m_fieldState[TOTAL_TILES];
	FieldToken m_currentTurn;

	GameState m_gameState;

	int m_turnsDone;

	void init();

	void refreshGame();

	TurnResult doTurn(int);
	TurnResult defineWinner(const FieldToken) const;
	bool isWin() const;
	bool isWinCondition(const FieldToken*) const;
};