//
//  game.h
//  KittenBox
//
//  Created by Clair Marchesani on 22/12/2014.
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef __KittenBox__game__
#define __KittenBox__game__

#include <stdio.h>
#include <array>

struct Cell {
	bool containsKitten;
	bool playerSelected;
};

enum StateOfArea {
	empty = 0,
	returned = 1,
	captured = 2,
	deviated = 3
};

enum Direction {
	UPW = 0,
	DOWNW = 1,
	LEFTW = 2,
	RIGHTW = 3
};

enum Position {
	TOP = 0,
	BOTTOM = 1,
	LEFT = 2,
	RIGHT = 3
};

struct OutsideArea {
	StateOfArea state;
	int deviation;
};

class Game {
private:
	int deviations = 0;
	std::array<std::array<OutsideArea, 8>, 4> outsideArea;
	std::array<std::array<Cell, 8>, 8> board;
public:
	Game();
	std::array<std::array<Cell, 8>, 8> getBoard();
	void setBoard(std::array<std::array<Cell, 8>, 8>);
	void setContainsKitten(int, int, bool);
	void setPlayerSelected(int, int, bool);
	std::array<std::array<OutsideArea, 8>, 4> getOutsideArea();
	Direction reverseDirection(Direction);
	bool clickedArea(int, Position);
};

#endif /* defined(__KittenBox__game__) */
