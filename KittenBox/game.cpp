//
//  game.cpp
//  KittenBox
//
//  Created by Clair Marchesani on 22/12/2014.
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include "game.h"

Game::Game() {
//	board = *new std::array<std::array<Cell, 8>, 8>;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].containsKitten = false;
			board[i][j].playerSelected = false;
		}
		top[i].state = empty;
		top[i].deviation = none;
		bottom[i].state = empty;
		bottom[i].deviation = none;
		left[i].state = empty;
		left[i].deviation = none;
		right[i].state = empty;
		right[i].deviation = none;
	}
}

std::array<std::array<Cell, 8>, 8> Game::getBoard() {
	return board;
}

void Game::setBoard(std::array<std::array<Cell, 8>, 8> _board) {
	board = _board;
}

void Game::setContainsKitten(int column, int row, bool value) {
	board[column][row].containsKitten = value;
}

void Game::setPlayerSelected(int column, int row, bool value) {
	board[column][row].playerSelected = value;
}