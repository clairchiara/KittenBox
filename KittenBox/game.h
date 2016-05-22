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
	int deviations;
	std::array<std::array<OutsideArea, 8>, 4> outsideArea;
	std::array<std::array<Cell, 8>, 8> board;
	bool kittensShown;
public:
	Game();
	std::array<std::array<Cell, 8>, 8> getBoard() const;
	void setBoard(std::array<std::array<Cell, 8>, 8> const&);
	void setContainsKitten(const int, const int, const bool);
	void setPlayerSelected(const int, const int, const bool);
	bool isPlayerSelected(const int, const int);
	std::array<std::array<OutsideArea, 8>, 4> getOutsideArea() const;
	Direction reverseDirection(const Direction&) const;
	bool clickedArea(const int, const Position&);
	void showKittens();
	void hideKittens();
	bool areKittensShown() const;
};

#endif /* defined(__KittenBox__game__) */
