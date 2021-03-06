#include "Player.h"
#include "Board.h"
#include "Ship.h"
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

Player::Player(const char *playerName){
	name = new char [strlen(playerName)+1];
	strcpy(name, playerName);

	shipType = new char* [kShipQuantity];
	for(int i = 0; i < kShipQuantity; ++i)
		shipType[i] = new char [16];
	strcpy(shipType[0], "Aircraft");
	strcpy(shipType[1],	"Battleship");
	strcpy(shipType[2],	"Crusier");
	strcpy(shipType[3],	"Submarine");
	strcpy(shipType[4],	"Patorl");
	ship = new Ship *[kShipQuantity];
	for(int i = 0; i < kShipQuantity; ++i)
		ship[i] = new Ship(shipType[i][0]);
}

void Player::openBoard(){
	myBoard.showAll();
}

void Player::displayBoard(){
	cout << name << endl;
	myBoard.display();
}

bool Player::displayShip(){
	int totalHp = 0;
	cout << name << endl;
	for(int i = 0; i < kShipQuantity; ++i){
		totalHp += ship[i]->getHp();
		cout << *ship[i] << endl;
	}
	return totalHp == 0;
}

void Player::setShip(){
	char row;
    int	d, s, column;
	int setShip = 0;
	bool set[kShipQuantity] = {false};
	while(setShip < kShipQuantity){
		this->displayBoard();
		/*
		 * input flush or something mey need 
		 * when input error occur
		 */

		cout << "Choose one ship to set.\n";
		do{
			for(int i = 0; i < kShipQuantity; ++i)
				if(!set[i])
					cout << i+1 << ") " << shipType[i] << '\n';
			cin >> s;
		}while(s > 5 || s <= 0 || set[s-1]);
		cout << "Choose one point.\n";
		do{
	    	cout <<	"[A to J] [0 to 9]\n";
			cin >> row >> column;
		}while(row < 'A' || row > 'J' || column < 0 || column > 9);
		cout << "Choose direction:\n";
		do{
			cout << "1) Down, 2) Right\n";
			cin >> d;
		}while(d > 2 || s <= 0);

		ship[s-1]->setLocation(row, column);
		ship[s-1]->setDirection(Direction(d-1));
		if(myBoard.setShip(*ship[s-1])){
			set[s-1] = true;
			++setShip;
			cout << shipType[s-1] << " success to set.\n";
		}else{
			cout << shipType[s-1] << " fail to set.\n";
		}
	}
}

pair<char, int>  Player::attack(){
	pair<char, int> p;
	cout << "Choose one point to attack\n";
	do{
		cout <<	"[A to J] [0 to 9]\n";
		cin >> p.first >> p.second;
	}while(p.first < 'A' || p.first > 'J' || p.second < 0 || p.second > 9);
	return p;
}

bool Player::beAttcked(pair<char, int> p){
	myBoard.showPoint(p.first-'A', p.second);
	char s = myBoard.getChar(p.first-'A', p.second);
	if(s == 'O'){
		myBoard.setChar(p.first-'A', p.second, 'X');
		cout << "miss...\n";
		return false;
	}
	switch(s){
		case 'A':
		case 'B':
		case 'C':
			cout << name << "'s " << shipType[s-'A'] << "was hit!!!\n";
			ship[s-'A']->decreaseHp();
			break;
		case 'S':
			cout << name << "'s " << shipType[3] << "was hit!!!\n";
			ship[3]->decreaseHp();
			break;
		case 'P':
			cout << name << "'s " << shipType[4] << "was hit!!!\n";
			ship[4]->decreaseHp();
			break;
	}
	myBoard.setChar(p.first-'A', p.second, s-'A'+'a');
	return true;
}

Player::~Player(){
	for(int i = 0; i < kShipQuantity; ++i)
		delete ship[i];
	delete ship;
	delete name;
}
