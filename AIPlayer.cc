#include "AIPlayer.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utility>
using namespace std;

AIPlayer::AIPlayer(const char *playerName): Player(playerName){
}

void AIPlayer::setShip(){
	char row;
	int column, direction;
	int setShip = 0;
	while(setShip < kShipQuantity){
		row = rand()%10 + 'A';
		column = rand()%10;
		direction = rand()%2;
		ship[setShip]->setLocation(row, column);
		ship[setShip]->setDirection(Direction(direction));
		if(myBoard.setShip(*ship[setShip]))
			++setShip;
	}
}

pair<char, int> AIPlayer::attack(){
	pair<char, int> p;
		p.first = rand()%10 + 'A'; 
		p.second  = rand()%10;
		return p;
}

AIPlayer::~AIPlayer(){
}
