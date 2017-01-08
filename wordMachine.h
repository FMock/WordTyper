#ifndef WORDMACHINE_H_
#define WORDMACHINE_H_

/* Frank Mock, January 2017
 * WordMachine is a class that represents the state
 * and operations of a typing program
 */
#include <FL/Fl_Text_Buffer.H>
#include<vector>
#include<map>
#include<string>
#include<ctime>
#include <cctype>
#include <functional>
#include <algorithm>

class WordMachine{
private:
	std::vector<std::string> phrases;  // Word phrases presented to the user
	std::vector<std::string> tokens; // The individual words of the phrases
	std::string delimiters;
	clock_t startTime;  // Start time of typing test
	clock_t stopTime;   // End time of typing test
	int curPos;	        // Index of current word
	void resetCurPos(); // Resets current word index to zero
	int wordCountTotal;		// The total number of words user is tested on
	int getWordCount(); // Determines number of words in tokens
	
public:
	WordMachine();
	~WordMachine();
	std::string to_string() const; // string representing state of WordMachine
	std::string getWord(); // Returns currnt word
	void setStartTime();   // Sets the start time to current time
	void setStopTime();    // Sets the stop time to the current time
	float getTime();       // Returns test time duration
	bool runWordMachine(); // Reports if safe to run the WordMachine
	void findTokens(std::vector<std::string> &vecOfPhrases, std::string &delims);
	std::string getTestResults(Fl_Text_Buffer *userTypedBuffer); //returns results of typing test
	void replacePhrases(std::vector<std::string> &vec);

	// trim from end
	static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}
};

#endif