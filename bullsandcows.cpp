//============================================================================
// Name        : bullsandcows.cpp
// Author      : Claire Stromboe
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

int checkDigits(int userGuess, int numDigits, int theCode[]){
	//checkDigits takes a userGuess and keeps running until userGuess can be returned
	// as the proper length and with no duplicates.


	int countNums = userGuess;
	int lengthCount = 0;
	int i;
	int userGuessArray[numDigits];

	while (countNums != 0) {
		countNums = countNums/10;
		++lengthCount;
	}

	countNums = userGuess;

	if (lengthCount > numDigits){
		cout << "You can only enter " << numDigits << " digits." << endl;
		cout << "Enter Guess: ";
		cin >> userGuess;

		userGuess = checkDigits(userGuess, numDigits, theCode);

		countNums = userGuess;

		for (i = 0; i < numDigits; ++ i){
			userGuessArray[numDigits - (i + 1)] = countNums % 10;
			countNums = countNums / 10;
		}
		countNums = userGuess;
	}

	int j;
	int k;
	bool duplicate = false;

	for (i = 0; i < numDigits; ++ i){
		userGuessArray[numDigits - (i + 1)] = countNums % 10;
		countNums = countNums / 10;
	}

	countNums = userGuess;

	for (i = 0; i < numDigits; ++i){
		k = 1 + i;
		for (j = k; j < numDigits; ++j){
			if (userGuessArray[i] == userGuessArray[j]) {
				duplicate = true;
			}
		}
	}

	if (duplicate == true){
		cout << "Each number must be different." << endl;
		cout << "Enter Guess: ";
		cin >> userGuess;

		countNums = userGuess;

		for (i = 0; i < numDigits; ++ i){
			userGuessArray[numDigits - (i + 1)] = countNums % 10;
			countNums = countNums / 10;
		}

		userGuess = checkDigits(userGuess,numDigits,theCode);
	}
	else {
		return userGuess;
	}
}


void BullsandCows(int userGuessArray[], int theCode[], int numDigits, int userGuess) {
	//userGuessArray and theCode are compared to find cows and bulls.

	int cowCount = 0;
	int bullCount = 0;
	int i;
	int j = 0;
	int countNums;


	userGuess = checkDigits(userGuess, numDigits, theCode);


	countNums = userGuess;

	for (i = 0; i < numDigits; ++ i){
		userGuessArray[numDigits - (i + 1)] = countNums % 10;
		countNums = countNums / 10;
	}

	countNums = userGuess;


	for (i = 0; i < numDigits; ++ i) {
		for (j = 0; j < numDigits; ++ j) {
			if (userGuessArray[i] == theCode[j]) {
					cowCount = cowCount + 1;
			}
		}
	}

	for (i = 0; i < numDigits; ++i) {
		if (userGuessArray[i] == theCode[i]) {
			bullCount = bullCount + 1;
			if (cowCount > 0){
				cowCount = cowCount - 1;
			}
		}
	}


	if (bullCount == numDigits) {
		cout << bullCount << " bulls... ";

		int j;

		for (j = 0; j < numDigits; ++j ) {

			while ((numDigits - numDigits + j) != (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << "-";
				break;
			}

			if ((numDigits - numDigits + j) == (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << " is correct!" << endl;
				return;
			}
		}
	}
	else {
		cout << bullCount << " bulls" << endl;
		cout << cowCount << " cows" << endl;


		cout << "Enter Guess: ";
		cin >> userGuess;

		userGuess = checkDigits(userGuess, numDigits, theCode);

		int countNums;
		countNums = userGuess;


		for (i = 0; i < numDigits; ++ i){
			userGuessArray[numDigits - (i + 1)] = countNums % 10;
			countNums = countNums / 10;
		}

		countNums = userGuess;

		BullsandCows(userGuessArray, theCode, numDigits, userGuess);
	}
}

void userGuessing(int numDigits, int userGuess, int theCode[]) {
	// takes the guessed number as an input from the user and makes sure
	// the length is correct and there are no duplicates.

	int lengthCount = 0;
	int countNums = userGuess;
	// countNums is a temp used to count digits of userGuess and form an array of userGuess

	while (countNums != 0) {
		countNums = countNums/10;
		++lengthCount;
	}

	countNums = userGuess;


	if (lengthCount > numDigits) {
		cout << "You can only enter " << numDigits << " digits." << endl;
		cout << "Enter Guess: ";
		cin >> userGuess;
		userGuessing(numDigits, userGuess, theCode);
	}
	else {
		// This section checks for duplicated digits if the length is correct
		int userGuessArray[numDigits];
		// an array of userGuess must be created to check for duplicates and compare against
		// theCode.
		int i;
		int j;
		int k;
		bool duplicate = false;

		for (i = 0; i < numDigits; ++ i){
			userGuessArray[numDigits - (i + 1)] = countNums % 10;
			countNums = countNums / 10;
		}

		countNums = userGuess;

		for (i = 0; i < numDigits; ++i){
			k = 1 + i;
			for (j = k; j < numDigits; ++j){
				if (userGuessArray[i] == userGuessArray[j]) {
					duplicate = true;
				}
			}
		}

		if (duplicate == true) {
			cout << "Each number must be different." << endl;
			cout << "Enter Guess: ";
			cin >> userGuess;
			userGuessing(numDigits, userGuess, theCode);
		}
		else {
			BullsandCows(userGuessArray, theCode, numDigits, userGuess);
		}
	}
}



void processCode(int numDigits) {
	// Here the code to be guessed is generated either randomly or by input.

	int i;
	int j;
	int theCode[numDigits];
	int userGuess;


	// If numDigits == 0, theCode is inputted
	if (numDigits == 0) {
		int cheatCode;

		cout << "Enter code: ";
		cin >> cheatCode;
		cout << "Enter number of digits in code: ";
		cin >> numDigits;

		for (i = 1; i <= numDigits; ++i) {
			theCode [numDigits - i] = cheatCode % 10;
			cheatCode = cheatCode / 10;
		}
		// The above for loop creates array theCode, which is the number to be guessed

		cout << "Number to guess: ";

		for (j = 0; j < numDigits; ++j ) {

			while ((numDigits - numDigits + j) != (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << "-";
				break;
			}

			if ((numDigits - numDigits + j) == (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << endl;
			}
		}
		// The number to guess is printed

		cout << "Enter Guess: ";
		cin >> userGuess;

		userGuessing(numDigits, userGuess, theCode);
		// Once the user makes a guess, the guess is transferred to userGuessing
	}

	// If numDigits is 3,4, or 5, theCode is randomly generated.
	else {
		int numSet[10] = {0,1,2,3,4,5,6,7,8,9};


		for (i = 9; i > 0; --i) {
			int randNum = rand() % 10;
			int temp = numSet[i];

			numSet[i] = numSet[randNum];
			numSet[randNum] = temp;
		}
		// numSet is shuffled around randomly to generate theCode and ensure no duplicates

		for (i = 0; i < numDigits; ++i) {
			theCode[i] = numSet[i];
		}

		cout << "Number to guess: ";

		for (j = 0; j < numDigits; ++j ) {
			while ((numDigits - numDigits + j) != (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << "-";
				break;
			}
			if ((numDigits - numDigits + j) == (numDigits - 1)) {
				cout << theCode[numDigits - numDigits + j] << endl;
			}
		}

		cout << "Enter Guess: ";
		cin >> userGuess;

		userGuessing(numDigits, userGuess, theCode);
	}
}


void processDigits(int numDigits) {
	// processDigits makes sure the user inputs a correct number of digits before moving on.
	// If 0 is entered, a different section of processCode runs.

	while (numDigits != 0 && (numDigits < 3 || numDigits > 5)) {
		cout << "Enter number of digits in code (3, 4, or 5): " << endl;
		cin >> numDigits;
		break;
	}

	if (numDigits == 0) {
		processCode(0);
	}
	else {
		processCode(numDigits);
	}

}



int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
     (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000);
    // needed to autograde some test cases in Mimir

    int numDigits;

    cout << "Enter number of digits in code (3, 4 or 5): ";
    cin >> numDigits;
    processDigits(numDigits);

}


