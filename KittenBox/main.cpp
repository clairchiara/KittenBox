//
//  main.cpp
//  KittenBox
//
//  Created by Clair Marchesani and Anna Winters on 05/12/2014.
//  Copyright (c) 2014 Clair Marchesani and Anna Winters. All rights reserved.
//

#include <array>
#include <iostream>
#include <string.h>

#include "game.h"
#include "ui.h"

Game *game;
UI *ui;

int main(int argc, const char * argv[]) {
	game = new Game;
	ui = new UI(game);
	while(true) {
		ui->update();
		ui->handle_events();
	}
	
    return 0;
}
