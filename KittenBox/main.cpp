//
//  main.cpp
//  KittenBox
//
//  Created by Clair Marchesani and Anna Winters on 05/12/2014.
//  Copyright (c) 2014 Clair Marchesani and Anna Winters. All rights reserved.
//

#include <iostream>
#include <array>
#include <random>
#include <string.h>

using namespace std;

array<array<bool, 8>, 8> board;

void printBoard() {
	cout << (char) 12;
	for (int h = 0; h < 2; h++) {
		cout << "     ";
		for (int x = 0; x < 8; x++) {
			if (h == 0){
				cout << "  " << x+1 << "   ";
			} else {
				cout << "_____ ";
			}
		}
		cout << endl;
	}
	
	for (int y = 0; y < 8; y++) {
		for (int h = 0; h < 3; h++) {
			if (h == 1){
				cout << " " << (char) (y+65) << "  ";
			} else {
				cout << "    ";
			}
			for (int x = 0; x < 8; x++){
				switch (h) {
					case 2:
						cout << "|_____";
						break;
					case 1:
						if (board[x][y]) {
							cout << "|Kittn";
							break;
						}
					default:
						cout << "|     ";
				}
			}
			cout << "|" << endl;
		}
	}
}

int main(int argc, const char * argv[]) {
	cout << "Welcome to Kitten Box!\n";
	cout << "Find the location of the kittens!\n";
	cin.ignore();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = false;
		}
	}
	for (int i = 0; i < 4; i++) {
		
		uint seed = (uint)time(nullptr) + (uint)random();
		mt19937 gen(seed);
		uniform_int_distribution<> dis(0,7);
		int firstGen = dis(gen);
		int secondGen = dis(gen);
		
		board[firstGen][secondGen] ? i-- : board[firstGen][secondGen] = true;
	}
	printBoard();
	
	char direction;
	char row;
	int column;
	
	scanf("%s", &direction);
	if (direction == 'l' || direction == 'r') {
		scanf("%d", &column);
		if (column < 1 || column > 8) cout << "NEIN NEIN NEIN\n";
		scanf("%d", &column);
	} else if (direction == 't' || direction == 'b') {
		scanf("%s", &row);
		if (strchr("abcdefgh", direction) == 0) cout << "NEIN NEIN NEIN\n";
	} else cout << "NEIN NEIN NEIN\n";
    return 0;
}