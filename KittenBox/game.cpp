//
//  game.cpp
//  KittenBox
//
//  Created by Clair Marchesani on 22/12/2014.
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>

#include "game.h"

Game::Game() : deviations(1), kittensShown(false) {
	std::cout << "INITIALISED" << std::endl;
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
	for (int i = 0; i < 4; i++) {
		
		uint seed = (uint)(time(nullptr) * 0.05);
		std::mt19937 gen(seed * (time(nullptr) % 10));
		std::uniform_int_distribution<> dis(0,7);
		int firstGen = dis(gen);
		int secondGen = dis(gen);
		
		if (board[firstGen][secondGen].containsKitten) i--;
		else board[firstGen][secondGen].containsKitten = true;
	}
}

std::array<std::array<Cell, 8>, 8> Game::getBoard() const {
	return board;
}

void Game::setBoard(const std::array<std::array<Cell, 8>, 8>& board) {
	this->board = board;
}

void Game::setContainsKitten(const int column, const int row, const bool value) {
	board[column][row].containsKitten = value;
}

void Game::setPlayerSelected(const int column, const int row, const bool value) {
	board[column][row].playerSelected = value;
}

bool Game::isPlayerSelected(const int column, const int row) {
	return board[column][row].playerSelected;
}

std::array<std::array<OutsideArea, 8>, 4> Game::getOutsideArea() const {
	return outsideArea;
}

Direction Game::reverseDirection(const Direction& direction) const {
	switch (direction) {
		case UPW:
			return DOWNW;
		case DOWNW:
			return UPW;
		case LEFTW:
			return RIGHTW;
		case RIGHTW:
			return LEFTW;
	}
}


bool Game::clickedArea(const int i, const Position& pos) {
	
	Direction direction;
	Direction initialDirection;
	std::array<int, 2> position;
	std::array<int, 2> initialPosition;
	
	auto debuggingState = [&, this]() {
		std::string state[] = {
			"empty",
			"returned",
			"captured",
			"deviated"
		};
		std::cout << state[outsideArea[pos][i].state] << "\n";
	}; // Debugging lambda
	
	switch (pos) {
		case TOP:
			initialDirection = DOWNW;
			break;
		case BOTTOM:
			initialDirection = UPW;
			break;
		case LEFT:
			initialDirection = RIGHTW;
			break;
		case RIGHT:
			initialDirection = LEFTW;
			break;
	}
	direction = initialDirection;
	switch (pos) {
		case TOP:
			position = {i, 0};
			initialPosition = {i, 0};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[i][0].containsKitten) {
				outsideArea[pos][i].state = captured;
				debuggingState();
			} else {
				if (i == 0) {
					if (board[i+1][0].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState();
					}
				} else if (i == 7) {
					if (board[i-1][0].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (board[i-1][0].containsKitten or board[i+1][0].containsKitten) {
					outsideArea[pos][i].state = returned;
					debuggingState(); return true;
				}
			}
			break;
		case BOTTOM:
			position = {i, 7};
			initialPosition = {i, 7};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[i][7].containsKitten) {
				outsideArea[pos][i].state = captured;
				debuggingState(); return true;
			} else {
				if (i == 0) {
					if (board[i+1][7].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (i == 7) {
					if (board[i-1][7].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (board[i-1][7].containsKitten or board[i+1][7].containsKitten) {
					outsideArea[pos][i].state = returned;
					debuggingState(); return true;
				}
			}
			break;
		case LEFT:
			position = {0, i};
			initialPosition = {0, i};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[0][i].containsKitten) {
				outsideArea[pos][i].state = captured;
				debuggingState(); return true;
			}
			else {
				if (i == 0) {
					if (board[0][i+1].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (i == 7) {
					if (board[0][i-1].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (board[0][i-1].containsKitten or board[0][i+1].containsKitten) {
					outsideArea[pos][i].state = returned;
					debuggingState(); return true;
				}
			}
			break;
		case RIGHT:
			position = {7, i};
			initialPosition = {7, i};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[7][i].containsKitten) {
				outsideArea[pos][i].state = captured;
				debuggingState(); return true;
			}
			else {
				if (i == 0) {
					if (board[7][i+1].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (i == 7) {
					if (board[7][i-1].containsKitten) {
						outsideArea[pos][i].state = returned;
						debuggingState(); return true;
					}
				} else if (board[7][i-1].containsKitten or board[7][i+1].containsKitten) {
					outsideArea[pos][i].state = returned;
					debuggingState(); return true;
				}
			}
			break;
	}
	for ( ; ; ) {
		do {
			std::cout << position[0] << " " << position[1] << "\n"; // Debugging
			if (position[0] == 0) {
				if (position[1] == 0) {
					switch (direction) {
						case UPW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[TOP][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[TOP][position[0]].deviation = deviations++;
								debuggingState(); return true;
							}
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
							else position[1]++;
							break;
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
							else position[0]++;
							break;
					}
					
				} else if (position[1] == 7) {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
							else position[1]--;
							break;
						case DOWNW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[BOTTOM][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[BOTTOM][position[0]].deviation = deviations++;
								debuggingState(); return true;
							}
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
							else position[0]++;
							break;
							
					}
				} else {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
							else position[1]--;
							break;
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
							else position[1]++;
							break;
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							} else if (board[position[0]+1][position[1]-1].containsKitten) {
								if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
								else direction = DOWNW;
							} else if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
							else position[0]++;
							break;
					}
				}
			} else if (position[0] == 7) {
				if (position[1] == 0) {
					switch (direction) {
						case UPW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[TOP][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[TOP][position[0]].deviation = deviations++;
								debuggingState(); return true;
							}
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
							else position[1]++;
							break;
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
					}
				} else if (position[1] == 7) {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = RIGHTW;
							else position[1]--;
							break;
						case DOWNW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[BOTTOM][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[BOTTOM][position[0]].deviation = deviations++;
								debuggingState(); return true;
							}
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = DOWNW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
					}
				} else {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = RIGHTW;
							else position[1]--;
							break;
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
							else position[1]++;
							break;
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								debuggingState(); return true;
							} else if (board[position[0]-1][position[1]-1].containsKitten) {
								if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
								else direction = DOWNW;
							} else if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								debuggingState(); return true;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								debuggingState(); return true;
							}
					}
				}
			} else if (position[1] == 0) {
				switch (direction) {
					case UPW:
						if (position == initialPosition and direction == reverseDirection(initialDirection)) {
							outsideArea[pos][i].state = returned;
							debuggingState(); return true;
						} else {
							outsideArea[pos][i].state = deviated;
							outsideArea[TOP][position[0]].state = deviated;
							outsideArea[pos][i].deviation = deviations;
							outsideArea[TOP][position[0]].deviation = deviations++;
							debuggingState(); return true;
						}
					case DOWNW:
						if (board[position[0]][position[1]+1].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						} else if (board[position[0]-1][position[1]+1].containsKitten) {
							if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
							else direction = RIGHTW;
						} else if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
						else position[1]++;
						break;
					case LEFTW:
						if (board[position[0]-1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						}
						if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
						else position[0]--;
						break;
					case RIGHTW:
						if (board[position[0]+1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						}
						if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
						else position[0]++;
						break;
				}
			} else if (position[1] == 7) {
				switch (direction) {
					case UPW:
						if (board[position[0]][position[1]-1].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						} else if (board[position[0]-1][position[1]-1].containsKitten) {
							if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
							else direction = RIGHTW;
						} else if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
						else position[1]--;
						break;
					case DOWNW:
						if (position == initialPosition and direction == reverseDirection(initialDirection)) {
							outsideArea[pos][i].state = returned;
							debuggingState(); return true;
						} else {
							outsideArea[pos][i].state = deviated;
							outsideArea[BOTTOM][position[0]].state = deviated;
							outsideArea[pos][i].deviation = deviations;
							outsideArea[BOTTOM][position[0]].deviation = deviations++;
							debuggingState(); return true;
						}
					case LEFTW:
						if (board[position[0]-1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						}
						if (board[position[0]-1][position[1]-1].containsKitten) direction = DOWNW;
						else position[0]--;
						break;
					case RIGHTW:
						if (board[position[0]+1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							debuggingState(); return true;
						}
						if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
						else position[0]++;
						break;
				}
			}
		} while (position[0] == 0 or position[0] == 7 or position[1] == 0 or position[1] == 7);
		switch (direction) {
			case UPW:
				if (board[position[0]][position[1]-1].containsKitten) {
					outsideArea[pos][i].state = captured;
					debuggingState(); return true;
				} else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
				else position[1]--;
				break;
			case DOWNW:
				if (board[position[0]][position[1]+1].containsKitten) {
					outsideArea[pos][i].state = captured;
					debuggingState(); return true;
				} else if (board[position[0]-1][position[1]+1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
				else position[1]++;
				break;
			case LEFTW:
				if (board[position[0]-1][position[1]].containsKitten) {
					outsideArea[pos][i].state = captured;
					debuggingState(); return true;
				} else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
					else direction = DOWNW;
				} else if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
				else position[0]--;
				break;
			case RIGHTW:
				if (board[position[0]+1][position[1]].containsKitten) {
					outsideArea[pos][i].state = captured;
					debuggingState(); return true;
				} else if (board[position[0]+1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
					else direction = DOWNW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
				else position[0]++;
				break;
		}
		std::cout << position[0] << " " << position[1] << "\n"; // Debugging
		if (outsideArea[pos][i].state != empty) break;
	}
	return true;
}

void Game::showKittens() {
	kittensShown = true;
}

void Game::hideKittens() {
	kittensShown = false;
}

bool Game::areKittensShown() const {
	return kittensShown;
}