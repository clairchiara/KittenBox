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

enum Deviation {
	none = 0,
	A = 1,
	B = 2,
	C = 3,
	D = 4,
	E = 5,
	F = 6,
	G = 7,
	H = 8
};

struct OutsideArea {
	StateOfArea state;
	Deviation deviation;
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
};

#endif /* defined(__KittenBox__game__) */
