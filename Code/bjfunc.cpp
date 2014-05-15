#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "bjfunc.h"

using namespace std;

string cardString(int card) { // give a card, outputs number/name and suit
	stringstream outString;
	string oS;
	
	if((card % 13) == 1) { // if card is 1, ace
		outString << "the Ace of ";
	} else if((card % 13) == 11) { // if 11, jack
		outString << "the Jack of ";
	} else if((card % 13) == 12) { // if 12, queen
		outString << "the Queen of ";
	} else if((card % 13) == 0) { // if 0, king
		outString << "the King of ";
	} else { // otherwise, card is the resulting number
		outString << "the " << (card % 13) << " of ";
	}
	if(((card - 1) / 13) == 0) { // if 0, spades
		outString << "Spades\0";
	} if(((card - 1) / 13) == 1) { // if 1, hearts
		outString << "Hearts\0";
	} if(((card - 1) / 13) == 2) { // if 2, clubs
		outString << "Clubs\0";
	} else if(((card - 1) / 13) == 3) { // if 3, diamonds
		outString << "Diamonds\0";
	}
	oS = outString.str();
	return oS;
}

string handString(int hand[]) { // input hand, outputs cards and value
	stringstream outString;
	string oS;
	bool ace = false;
	int value = cardValue(hand[1]);
	outString << cardString(hand[1]);
	if(isAce(hand[1])) {
		ace = true;
	}
	for(int i = 2; i <= hand[0]; i++) {
		outString << ", " << cardString(hand[i]);
		value += cardValue(hand[i]);
		if(isAce(hand[i])) {
			ace = true;
		}
	}
	outString << ", worth " << value;
	if(ace && value <= 11) {
		outString << " or " << value + 10;
	}
	outString << ".";
	oS = outString.str();
	hand[11] = value;
	return oS;
}

int cardValue(int card) { // input card, returns its value
	if(card % 13 == 1) { // ace worth 1 or 11
		return 1;
	} else if (card % 13 == 0 || (card % 13) > 9) { // jack, king, queen woth 10
		return 10;
	} else { // otherwise worth card number
		return card % 13;
	}
}

bool isAce(int card) { // returns if a card is an ace
	if((card % 13) == 1) {
		return true;
	} else {
		return false;
	}
}