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
	empty,
	returned,
	captured,
	deviated
};

enum Direction {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct OutsideArea {
	StateOfArea state;
	int deviation;
};

class Game {
private:
	int deviations = 0;
	std::array<std::array<Cell, 8>, 8> board;
	std::array<OutsideArea, 8> top;
	std::array<OutsideArea, 8> bottom;
	std::array<OutsideArea, 8> left;
	std::array<OutsideArea, 8> right;
public:
	Game();
	std::array<std::array<Cell, 8>, 8> getBoard();
	void setBoard(std::array<std::array<Cell, 8>, 8>);
	void setContainsKitten(int, int, bool);
	void setPlayerSelected(int, int, bool);
	bool clickedArea(int, Direction);
};

#endif /* defined(__KittenBox__game__) */
