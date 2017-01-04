#ifndef WORDMACHINE_H_
#define WORDMACHINE_H_

/* Frank Mock, January 2017
 * WordMachine is a class that represents the state
 * and operations of a typing program
 */

#include<vector>
#include<string>
#include<ctime>

class WordMachine{
private:
	std::vector<std::string> phrases;  // Word phrases presented to the user
	clock_t startTime;  // Start time of typing test
	clock_t stopTime;   // End time of typing test
	int curPos;	        // Index of current word
	void resetCurPos(); // Resets current word index to zero
	int wordCountTotal;		// The total number of words user is tested on

public:
	WordMachine();
	~WordMachine();
	std::string getWord(); // Returns currnt word
	void setStartTime();   // Sets the start time to current time
	void setStopTime();    // Sets the stop time to the current time
	float getTime();       // Returns test time duration
	bool runWordMachine(); // Reports if safe to run the WordMachine
};

#endif