#include "wordMachine.h"
using std::string;

/* Frank Mock, January 2017
* WordMachine is a class that represents the state
* and operations of a typing program
*/

WordMachine::WordMachine(){

	// Vector of strings that the user must type
	phrases = { "The quick brown fox jumps",
		"over the lazy dog",
		"Hollywood dragon go away",
		"Medicine man on the moon",
		"It's quarter past noon",
		"Chemistry improved her memory",
		"Zero time is coming soon" };

	startTime = 0;
	stopTime = 0;
	curPos = 0;
}

WordMachine::~WordMachine(){}

/* Reports if safe to run the WordMachine
 * returns true if so and false otherwise.
 * It's only safe to run if curPos is less
 * than the size of the vector of strings.
 */
bool WordMachine::runWordMachine(){
	return curPos < phrases.size() ? true : false;
}

/* Returns the word that the index, curPos represents
 * and increments curPos*/
string WordMachine::getWord(){
	string word = phrases[curPos];
	curPos++;
	return word;
}

// Set the start time
void WordMachine::setStartTime(){
	resetCurPos();
	startTime = clock();
}

// Set the stop time
void WordMachine::setStopTime(){
	stopTime = clock();
}

// Returns the difference between the start time and stop time
// in seconds
float WordMachine::getTime(){
	float t = (stopTime - startTime) / CLOCKS_PER_SEC;
	return t;
}

/* Resets curPos to zero, which represents the index of the first
 * word in the vector of word phrases */
void WordMachine::resetCurPos(){
	curPos = 0;
}
