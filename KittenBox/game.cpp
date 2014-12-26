//
//  game.cpp
//  KittenBox
//
//  Created by Clair Marchesani on 22/12/2014.
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include "game.h"

Game::Game() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].containsKitten = false;
			board[i][j].playerSelected = false;
		}
		outsideArea[TOP][i].state = empty;
		outsideArea[TOP][i].deviation = 0;
		outsideArea[BOTTOM][i].state = empty;
		outsideArea[BOTTOM][i].deviation = 0;
		outsideArea[LEFT][i].state = empty;
		outsideArea[LEFT][i].deviation = 0;
		outsideArea[RIGHT][i].state = empty;
		outsideArea[RIGHT][i].deviation = 0;
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

std::array<std::array<OutsideArea, 8>, 4> Game::getOutsideArea() {
	return outsideArea;
}

bool Game::clickedArea(int i, Position a) {
	
	Direction direction;
	std::array<int, 2> position;
	std::array<int, 2> initialPosition;
	
	switch (a) {
		case TOP:
			direction = DOWNW;
			break;
		case BOTTOM:
			direction = UPW;
			break;
		case LEFT:
			direction = RIGHTW;
			break;
		case RIGHT:
			direction = LEFTW;
			break;
	}
	switch (a) {
		case TOP:
			position = {i, 0};
			initialPosition = {i, 0};
			if (outsideArea[a][i].state != empty) return false;
			if (board[i][0].containsKitten) outsideArea[a][i].state = captured;
			else if (board[i-1][0].containsKitten or board[i+1][0].containsKitten) outsideArea[a][i].state = returned;
			break;
		case BOTTOM:
			position = {i, 7};
			initialPosition = {i, 7};
			if (outsideArea[a][i].state != empty) return false;
			if (board[i][7].containsKitten) outsideArea[a][i].state = captured;
			else if (board[i-1][7].containsKitten or board[i+1][7].containsKitten) outsideArea[a][i].state = returned;
			break;
		case LEFT:
			position = {0, i};
			initialPosition = {0, i};
			if (outsideArea[a][i].state != empty) return false;
			if (board[0][i].containsKitten) outsideArea[a][i].state = captured;
			else if (board[0][i-1].containsKitten or board[0][i+1].containsKitten) outsideArea[a][i].state = returned;
			break;
		case RIGHT:
			position = {7, i};
			initialPosition = {7, i};
			if (outsideArea[a][i].state != empty) return false;
			if (board[7][i].containsKitten) outsideArea[a][i].state = captured;
			else if (board[7][i-1].containsKitten or board[7][i+1].containsKitten) outsideArea[a][i].state = returned;
			break;
	}
	for ( ; ; ) {
		if (position[0] == 0 or position[0] == 7 or position[1] == 0 or position[1] == 7) {
			switch (direction) {
				case TOP:
					if (position[1] == 0) {
						if (position == initialPosition) {
							outsideArea[a][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[a][i].state = deviated;
							outsideArea[a][i].deviation = deviations;
							outsideArea[TOP][position[0]].deviation = deviations++;
							goto end_loop;
						}
					}
					break;
				case BOTTOM:
					if (position[1] == 7) {
						if (position == initialPosition) {
							outsideArea[a][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[a][i].state = deviated;
							outsideArea[a][i].deviation = deviations;
							outsideArea[BOTTOM][position[0]].deviation = deviations++;
							goto end_loop;
						}
					}
					break;
				case LEFT:
					if (position[0] == 0) {
						if (position == initialPosition) {
							outsideArea[a][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[a][i].state = deviated;
							outsideArea[a][i].deviation = deviations;
							outsideArea[LEFT][position[1]].deviation = deviations++;
							goto end_loop;
						}
					}
					break;
				case RIGHT:
					if (position[0] == 7) {
						if (position == initialPosition) {
							outsideArea[a][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[a][i].state = deviated;
							outsideArea[a][i].deviation = deviations;
							outsideArea[RIGHT][position[1]].deviation = deviations++;
							goto end_loop;
						}
					}
					break;
			}
		}
		switch (direction) {
			case TOP:
				if (board[position[0]][position[1]-1].containsKitten) outsideArea[a][i].state = captured;
				else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
				else position[1]--;
				break;
			case BOTTOM:
				if (board[position[0]][position[1]+1].containsKitten) outsideArea[a][i].state = captured;
				else if (board[position[0]-1][position[1]+1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = RIGHTW;
				else position[1]++;
				break;
			case LEFT:
				if (board[position[0]-1][position[1]].containsKitten) outsideArea[a][i].state = captured;
				else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
					else direction = DOWNW;
				} else if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
				else position[0]--;
				break;
			case RIGHT:
				if (board[position[0]+1][position[1]].containsKitten) outsideArea[a][i].state = captured;
				else if (board[position[0]+1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
					else direction = DOWNW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
				else position[0]++;
				break;
		}
	}
end_loop:
	return true;
}