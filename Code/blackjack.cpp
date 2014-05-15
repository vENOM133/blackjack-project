/* Scott J Dick
   Text based blackjack game.
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "deck.cpp"
#include "bjfunc.cpp"

using namespace std;

int main() {
	Deck d1; // card deck
	int card, dealerType; // current card, type of dealer
	int dealerHand[12], playerHand[12]; // dealer cards, player cards
		// [0] stores number of cards, [1-10] stores cards, [11] stores value of cards
	char conVar = 'Y', dHit = 'Y', hors = 'H'; // control variables
		// conVar: loop control(new game)
		// dHit: dealer hit or stay
		// hors: player hit or stay
	bool dbj, pbj; // dealer/player blackjack
	bool haveAce[2]; // [0] dealer ace, [1] player ace
	cout << "What type of dealer would you prefer?" << endl
		<< "1) Stay on soft 17." << endl
		<< "2) Stay on hard 17 only." << endl;
	cin >> dealerType;
	while(dealerType < 1 || dealerType > 2) { // loops while incorrect input is given
		cout << "This is not a valid input, please try again." << endl;
		cout << "What type of dealer would you prefer?" << endl
			<< "1) Stay on soft 17." << endl
			<< "2) Stay on hard 17 only." << endl;
		cin >> dealerType;
	}
	while(conVar == 'Y') { // game loop
		playerHand[1] = d1.getCard(); // dealer and player initial cards
		dealerHand[1] = d1.getCard();
		playerHand[2] = d1.getCard();
		dealerHand[2] = d1.getCard();
		playerHand[0] = 2; // player/dealer number of cards in hand
		dealerHand[0] = 2;
		haveAce[0] = false; // initialize false for aces and blackjacks
		haveAce[1] = false;
		dbj = false;
		pbj = false;
		hors = 'H';
		cout << string(75, '\n'); // clear screen
		cout << "The dealer hand is " << handString(dealerHand) << endl; // outputs dealer hand and value
		if((isAce(dealerHand[1]) || isAce(dealerHand[2])) && dealerHand[11] == 11) { // check for dealer BJ
			dbj = true;
			cout << "The dealer has a blackjack." << endl;
		}
		cout << "Your hand is " << handString(playerHand) << endl; // outputs player hand and value
		if((isAce(playerHand[1]) || isAce(playerHand[2])) && playerHand[11] == 11) { // check for player BJ
			pbj = true;
			cout << "You have a blackjack." << endl;
		}
		if(dbj || pbj){ // if player or dealer have BJ, skip to end
		} else { // if no BJ, check if player wants to hit/stay
			cout << "Would you like to <h>it or <s>tay? ";
			cin >> hors;
			hors = toupper(hors);
			while(hors != 'H' && hors != 'S') { // checks for correct input
				cout << "This is not a valid input." << endl;
				cout << "Would you like to <h>it or <s>tay? ";
				cin >> hors;
				hors = toupper(hors);
			}
			while(hors == 'H') { // while you continue hitting
				playerHand[0]++; // increment number of cards in hand
				playerHand[playerHand[0]] = d1.getCard(); // get a new card
				cout << "Your hand is now " << handString(playerHand) << endl; // print new hand
				if(playerHand[11] < 21) { // if 21 or over, automatically stays
					cout << "Would you like to <h>it or <s>tay? ";
					cin >> hors;
					hors = toupper(hors);
					while(hors != 'H' && hors != 'S') {
						cout << "This is not a valid input." << endl;
						cout << "Would you like to <h>it or <s>tay? ";
						cin >> hors;
						hors = toupper(hors);
					}
				} else {
					hors = 'S';
				}
			}
			for(int i = 1; i <= playerHand[0]; i++) { // checks for player ace
				if(isAce(playerHand[i])) {
					haveAce[1] = true;
				}
			}
			if(haveAce[1]) { // if ace and value is 11 or less, adds 10
				if(playerHand[11] <= 11) {
					playerHand[11] += 10;
				}
			}
			for(int i = 1; i <= dealerHand[0]; i++) { // checks for dealer ace
				if(isAce(dealerHand[i])) {
					haveAce[0] = true;
				}
			}
			if(dealerType == 1) { // dealer hit/stay for soft 17
				if(dealerHand[11] >= 17) {
					dHit = 'N';
				} else if(dealerHand[11] >= 7 && dealerHand[11] <= 11 && haveAce[0]) {
					dHit = 'N';
					dealerHand[11] += 10;
				} else {
					dHit = 'Y';
				}
			}
			if(dealerType == 2) { // dealer hit/stay for hard 17
				if(dealerHand[11] >= 17) {
					dHit = 'N';
				} else if(dealerHand[11] >= 8 && dealerHand[11] <= 11 && haveAce[0]) {
					dHit = 'N';
					dealerHand[11] += 10;
				} else {
					dHit = 'Y';
				}
			}
			while(dHit == 'Y' && dealerHand[11] <= 21) { // dealer hit/stay loop
				dealerHand[0]++;
				dealerHand[dealerHand[0]] = d1.getCard();
				cout << "The dealer has hit, The dealer hand is now " << handString(dealerHand) << endl;
				if(haveAce[0]) {
					if(dealerHand[11] <= 11) {
						dealerHand[11] += 10;
					}
				}
				if(dealerType == 1) {
					if(dealerHand[11] >= 17) {
						dHit = 'N';
					} else if(dealerHand[11] >= 7 && dealerHand[11] <= 11 && haveAce[0]) {
						dHit = 'N';
						dealerHand[11] += 10;
					} else {
						dHit = 'Y';
					}
				}
				if(dealerType == 2) {
					if(dealerHand[11] >= 17) {
						dHit = 'N';
					} else if(dealerHand[11] >= 8 && dealerHand[11] <= 11 && haveAce[0]) {
						dHit = 'N';
						dealerHand[11] += 10;
					} else {
						dHit = 'Y';
					}
				}
			}
		}
		if(haveAce[0]) { // adds 10 if ace and <= 11
			if(dealerHand[11] <= 11) {
				dealerHand[11] += 10;
			}
		}
		if(dbj)
			dealerHand[11] += 10;
		if(pbj)
			playerHand[11] += 10;
		cout << endl << endl << "The value of the dealer's hand is " << dealerHand[11] << "." << endl;
			// outputs value of dealer hand
		cout << "The value of your hand is " << playerHand[11] << "." << endl;
			// outputs value of player hand
		if(dbj && pbj) { // if both have BJ
			cout << "You both have a blackjack, it is a draw." << endl;
		} else if(dbj) { // dealer BJ only
			cout << "You lose." << endl;
		} else if(pbj) { // player BJ only
			cout << "You win." << endl;
		} else if(dealerHand[11] > 21 && playerHand[11] > 21) { // both bust
			cout << "You both exceeded 21, it is a draw." << endl;
		} else if(dealerHand[11] <= 21 && playerHand[11] > 21) { // player bust
			cout << "You exceeded 21, you lose." << endl;
		} else if(dealerHand[11] > 21 && playerHand[11] <= 21) { // dealer bust
			cout << "The dealer exceeded 21, you win." << endl;
		} else if(dealerHand[11] == playerHand[11]) { // same score
			cout << "It is a draw." << endl;
		} else if(dealerHand[11] < playerHand[11]) { // player score higher than dealer
			cout << "You Win." << endl;
		} else { // dealer score higher than player
			cout << "You lose." << endl;
		}
		cout << "Would you like to play another hand? " << endl << "<y>es or <n>o: ";
		cin >> conVar;
		conVar = toupper(conVar);
		while(conVar != 'Y' && conVar != 'N') {
			cout << "This is not a valid input." << endl;
			cout << "Would you like to play another hand? " << endl << "<y>es or <n>o: ";
			cin >> conVar;
			conVar = toupper(conVar);
		}
	}
	
	return 0;
}