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

int main(int argc, const char * argv[]) {
	
	UI ui;
	
	while (not ui.is_game_loaded()) {
		ui.loading_screen();
	}
	while(ui.is_game_loaded()) {
		ui.update();
		ui.handle_events();
	}
	
    return 0;
}