//
//  game.cpp
//  KittenBox
//
//  Created by Clair Marchesani on 22/12/2014.
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <iostream>
#include <string>

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

Direction Game::reverseDirection(Direction _direction) {
	switch (_direction) {
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

bool Game::clickedArea(int i, Position pos) {
	
	Direction direction;
	Direction initialDirection;
	std::array<int, 2> position;
	std::array<int, 2> initialPosition;
	
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
				goto end_loop;
			} else {
				if (i == 0) {
					if (board[i+1][0].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (i == 7) {
					if (board[i-1][0].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (board[i-1][0].containsKitten or board[i+1][0].containsKitten) {
					outsideArea[pos][i].state = returned;
					goto end_loop;
				}
			}
			break;
		case BOTTOM:
			position = {i, 7};
			initialPosition = {i, 7};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[i][7].containsKitten) {
				outsideArea[pos][i].state = captured;
				goto end_loop;
			} else {
				if (i == 0) {
					if (board[i+1][7].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (i == 7) {
					if (board[i-1][7].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (board[i-1][7].containsKitten or board[i+1][7].containsKitten) {
					outsideArea[pos][i].state = returned;
					goto end_loop;
				}
			}
			break;
		case LEFT:
			position = {0, i};
			initialPosition = {0, i};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[0][i].containsKitten) {
				outsideArea[pos][i].state = captured;
				goto end_loop;
			}
			else {
				if (i == 0) {
					if (board[0][i+1].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (i == 7) {
					if (board[0][i-1].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (board[0][i-1].containsKitten or board[0][i+1].containsKitten) {
					outsideArea[pos][i].state = returned;
					goto end_loop;
				}
			}
			break;
		case RIGHT:
			position = {7, i};
			initialPosition = {7, i};
			if (outsideArea[pos][i].state != empty) return false;
			if (board[7][i].containsKitten) {
				outsideArea[pos][i].state = captured;
				goto end_loop;
			}
			else {
				if (i == 0) {
					if (board[7][i+1].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (i == 7) {
					if (board[7][i-1].containsKitten) {
						outsideArea[pos][i].state = returned;
						goto end_loop;
					}
				} else if (board[7][i-1].containsKitten or board[7][i+1].containsKitten) {
					outsideArea[pos][i].state = returned;
					goto end_loop;
				}
			}
			break;
	}
	for ( ; ; ) {
		do {
			std::cout << position[0] << " " << position[1] << "\n";
			if (position[0] == 0) {
				if (position[1] == 0) {
					switch (direction) {
						case UPW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[TOP][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[TOP][position[0]].deviation = deviations++;
								goto end_loop;
							}
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
							else position[1]++;
							break;
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								goto end_loop;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
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
								goto end_loop;
							}
							if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
							else position[1]--;
							break;
						case DOWNW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[BOTTOM][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[BOTTOM][position[0]].deviation = deviations++;
								goto end_loop;
							}
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								goto end_loop;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
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
								goto end_loop;
							}
							if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
							else position[1]--;
							break;
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
							else position[1]++;
							break;
						case LEFTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[LEFT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[LEFT][position[1]].deviation = deviations++;
								goto end_loop;
							}
						case RIGHTW:
							if (board[position[0]+1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
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
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[TOP][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[TOP][position[0]].deviation = deviations++;
								goto end_loop;
							}
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
							else position[1]++;
							break;
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								goto end_loop;
							}
					}
				} else if (position[1] == 7) {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = RIGHTW;
							else position[1]--;
							break;
						case DOWNW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[BOTTOM][position[0]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[BOTTOM][position[0]].deviation = deviations++;
								goto end_loop;
							}
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = DOWNW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								goto end_loop;
							}
					}
				} else {
					switch (direction) {
						case UPW:
							if (board[position[0]][position[1]-1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]-1].containsKitten) direction = RIGHTW;
							else position[1]--;
							break;
						case DOWNW:
							if (board[position[0]][position[1]+1].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							}
							if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
							else position[1]++;
							break;
						case LEFTW:
							if (board[position[0]-1][position[1]].containsKitten) {
								outsideArea[pos][i].state = captured;
								goto end_loop;
							} else if (board[position[0]-1][position[1]-1].containsKitten) {
								if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
								else direction = DOWNW;
							} else if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
							else position[0]--;
							break;
						case RIGHTW:
							if (position == initialPosition and direction == reverseDirection(initialDirection)) {
								outsideArea[pos][i].state = returned;
								goto end_loop;
							} else {
								outsideArea[pos][i].state = deviated;
								outsideArea[RIGHT][position[1]].state = deviated;
								outsideArea[pos][i].deviation = deviations;
								outsideArea[RIGHT][position[1]].deviation = deviations++;
								goto end_loop;
							}
					}
				}
			} else if (position[1] == 0) {
				switch (direction) {
					case UPW:
						if (position == initialPosition and direction == reverseDirection(initialDirection)) {
							outsideArea[pos][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[pos][i].state = deviated;
							outsideArea[TOP][position[0]].state = deviated;
							outsideArea[pos][i].deviation = deviations;
							outsideArea[TOP][position[0]].deviation = deviations++;
							goto end_loop;
						}
					case DOWNW:
						if (board[position[0]][position[1]+1].containsKitten) {
							outsideArea[pos][i].state = captured;
							goto end_loop;
						} else if (board[position[0]-1][position[1]+1].containsKitten) {
							if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
							else direction = RIGHTW;
						} else if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
						else position[1]++;
						break;
					case LEFTW:
						if (board[position[0]-1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							goto end_loop;
						}
						if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
						else position[0]--;
						break;
					case RIGHTW:
						if (board[position[0]+1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							goto end_loop;
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
							goto end_loop;
						} else if (board[position[0]-1][position[1]-1].containsKitten) {
							if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
							else direction = RIGHTW;
						} else if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
						else position[1]--;
						break;
					case DOWNW:
						if (position == initialPosition and direction == reverseDirection(initialDirection)) {
							outsideArea[pos][i].state = returned;
							goto end_loop;
						} else {
							outsideArea[pos][i].state = deviated;
							outsideArea[BOTTOM][position[0]].state = deviated;
							outsideArea[pos][i].deviation = deviations;
							outsideArea[BOTTOM][position[0]].deviation = deviations++;
							goto end_loop;
						}
					case LEFTW:
						if (board[position[0]-1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							goto end_loop;
						}
						if (board[position[0]-1][position[1]-1].containsKitten) direction = DOWNW;
						else position[0]--;
						break;
					case RIGHTW:
						if (board[position[0]+1][position[1]].containsKitten) {
							outsideArea[pos][i].state = captured;
							goto end_loop;
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
					goto end_loop;
				} else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]-1].containsKitten) direction = DOWNW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]-1].containsKitten) direction = LEFTW;
				else position[1]--;
				break;
			case DOWNW:
				if (board[position[0]][position[1]+1].containsKitten) {
					outsideArea[pos][i].state = captured;
					goto end_loop;
				} else if (board[position[0]-1][position[1]+1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
					else direction = RIGHTW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
				else position[1]++;
				break;
			case LEFTW:
				if (board[position[0]-1][position[1]].containsKitten) {
					outsideArea[pos][i].state = captured;
					goto end_loop;
				} else if (board[position[0]-1][position[1]-1].containsKitten) {
					if (board[position[0]-1][position[1]+1].containsKitten) direction = RIGHTW;
					else direction = DOWNW;
				} else if (board[position[0]-1][position[1]+1].containsKitten) direction = UPW;
				else position[0]--;
				break;
			case RIGHTW:
				if (board[position[0]+1][position[1]].containsKitten) {
					outsideArea[pos][i].state = captured;
					goto end_loop;
				} else if (board[position[0]+1][position[1]-1].containsKitten) {
					if (board[position[0]+1][position[1]+1].containsKitten) direction = LEFTW;
					else direction = DOWNW;
				} else if (board[position[0]+1][position[1]+1].containsKitten) direction = UPW;
				else position[0]++;
				break;
		}
		std::cout << position[0] << " " << position[1] << "\n";
		if (outsideArea[pos][i].state != empty) break;
	}
end_loop:
	std::string state[] = {
		"empty",
		"returned",
		"captured",
		"deviated"
	};
	std::cout << state[outsideArea[pos][i].state] << "\n";
	return true;
}