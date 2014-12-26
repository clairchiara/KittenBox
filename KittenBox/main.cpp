//
//  main.cpp
//  KittenBox
//
//  Created by Clair Marchesani and Anna Winters on 05/12/2014.
//  Copyright (c) 2014 Clair Marchesani and Anna Winters. All rights reserved.
//

#include <array>
#include <iostream>
#include <random>
#include <string.h>

#include "game.h"
#include "ui.h"

Game game;
UI *ui;

int main(int argc, const char * argv[]) {
	ui = new UI(&game);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			game.setContainsKitten(i, j, false);
		}
	}
	for (int i = 0; i < 4; i++) {
		
		uint seed = (uint)(time(nullptr) * 0.05);
		std::mt19937 gen(seed * (time(nullptr) % 10));
		std::uniform_int_distribution<> dis(0,7);
		int firstGen = dis(gen);
		int secondGen = dis(gen);
		
		if (game.getBoard()[firstGen][secondGen].containsKitten) {
			i --;
		} else game.setContainsKitten(firstGen, secondGen, true);
	}
	
	while(true) {
		ui->update();
		ui->handle_events();
	}
	
    return 0;
}
