#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class Deck {
		int deck[53]; // [0] cards remaining, [1-52] cards
	public:
		Deck();
		void createDeck();
		int getCard();
		bool isEmpty();
};

Deck::Deck() {
	createDeck();
}

void Deck::createDeck() { // populates array, shuffles deck
	srand(time(NULL));
	int ranNum,tempNum;
	for(int i = 1; i <= 52; i++) // populate deck
		deck[i] = i;
	deck[0] = 52; // 52 cards remaining
	for(int i = 0; i < 10; i++) { // shuffles 10 times
		for(int j = 1; j <= 52; j++) { // trades each card with random card in the array
			ranNum = rand() % 52 + 1;
			tempNum = deck[j];
			deck[j] = deck[ranNum];
			deck[ranNum] = tempNum;
		}
	}
}

int Deck::getCard() { // pulls card from the deck
	if(isEmpty()) // checks if cards remaining, if not, reshuffles
		createDeck();
	int card = deck[deck[0]];
	deck[0]--;
	return card;
}

bool Deck::isEmpty() { // checks if empty
	if(deck[0] == 0) {
		return true;
	} else {
		return false;
	}
}