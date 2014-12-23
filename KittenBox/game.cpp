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
		top[i].deviation = 0;
		bottom[i].state = empty;
		bottom[i].deviation = 0;
		left[i].state = empty;
		left[i].deviation = 0;
		right[i].state = empty;
		right[i].deviation = 0;
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

bool Game::clickedArea(int i, Direction a) {
	
	Direction direction;
	std::array<int, 2> position;
	std::array<int, 2> initialPosition;
	
	switch (a) {
		case TOP:
			direction = BOTTOM;
			break;
		case BOTTOM:
			direction = TOP;
			break;
		case LEFT:
			direction = RIGHT;
			break;
		case RIGHT:
			direction = LEFT;
			break;
		default:
			break;
	}
	switch (a) {
		case TOP:
			position = {i, 0};
			initialPosition = {i, 0};
			if (top[i].state != empty) return false;
			if (board[i][0].containsKitten) top[i].state = captured;
			else if (board[i-1][0].containsKitten or board[i+1][0].containsKitten) top[i].state = returned;
			break;
		case BOTTOM:
			position = {i, 7};
			initialPosition = {i, 7};
			if (bottom[i].state != empty) return false;
			if (board[i][7].containsKitten) bottom[i].state = captured;
			else if (board[i-1][7].containsKitten or board[i+1][7].containsKitten) bottom[i].state = returned;
			break;
		case LEFT:
			position = {0, i};
			initialPosition = {0, i};
			if (left[i].state != empty) return false;
			if (board[0][i].containsKitten) left[i].state = captured;
			else if (board[0][i-1].containsKitten or board[0][i+1].containsKitten) left[i].state = returned;
			break;
		case RIGHT:
			position = {7, i};
			initialPosition = {7, i};
			if (right[i].state != empty) return false;
			if (board[7][i].containsKitten) right[i].state = captured;
			else if (board[7][i-1].containsKitten or board[7][i+1].containsKitten) right[i].state = returned;
			break;
		default:
			break;
	}
	for ( ; ; ) {
		if (position[0] == -1 or position[0] == 8 or position[1] == -1 or position[1] == 8) {
		}
		switch (direction) {
			case TOP:
				
				break;
		}
	}
	return true;
}