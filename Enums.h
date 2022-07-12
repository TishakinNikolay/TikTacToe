#pragma once
enum class FieldToken {
	EMPTY,
	CROSS,
	CIRCLE
};

enum class TurnResult {
	TAKEN,
	NEXT,
	WIN_CROSS,
	WIN_CIRCLE,
	DRAW
};

enum class GameState {
	INIT,
	RUNNING,
	END_GAME
};