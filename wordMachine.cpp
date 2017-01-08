#include "wordMachine.h"
#include "tokenizer.h"
#include <sstream>
#include <ostream>
#include <iostream>
#include <string>
#include <utility>

using std::ostringstream;
using std::string;
using std::cout;
using std::vector;

/* Frank Mock, January 2017
* WordMachine is a class that represents the state
* and operations of a typing program
*/

WordMachine::WordMachine(){

	// Default vector of strings that the user must type
	phrases = { "The quick cat",
		"The lazy dog",
		"Dragon go away",
		"On the moon",
		"Hello there Frank",
        "Rocket launch next week",
        "Not for sale",
        "Energy from the Sun",
        "Never stop dreaming",
        "Go ahead and try",
        "The test is over" };

	string delimiters = (" ,.!?\n");
	tokens = vector<string>(); // vector to hold the individual words
	findTokens(phrases, delimiters); // Fill tokens vector with tokens from phrases

	startTime = 0;
	stopTime = 0;
	curPos = 0;
	wordCountTotal = getWordCount();

	//fillWordFreqMap(); // Fill the map with the frequency of test words

	cout << this->to_string(); /*** For troubleshooting. Delete when not needed ***/
	//printWordFrequencyMap();  /* For troubleshooting. Delete when not needed*/
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

/* Determines the number of words in a vector of strings
 * and returns that number*/
int WordMachine::getWordCount(){
	return tokens.size();
}


/* Searches vector v for tokens and places them in
*  the tokens vector*/
void WordMachine::findTokens(vector<string> &v, string &delims){

	for (unsigned int i = 0; i < v.size(); i++){
		string nextToken;
		Tokenizer tok(v[i]);
		nextToken = tok.get_token(delims);
		while (nextToken != ""){
			tokens.push_back(nextToken);
			nextToken = tok.get_token(delims);
		}
	}
}

string WordMachine::getTestResults(Fl_Text_Buffer *userTypedBuffer){
	int i = 0; // index for tokens vector
	int start = 0; // starting position of word in buffer
	//int found = 0;
	int correct = 0; // count of correctly typed words
	std::string s; // word pulled from buffer

	while (start < userTypedBuffer->length() && i < tokens.size()){
		// get the end position of word in buffer
		int end = userTypedBuffer->word_end(start);
		// get the word from the buffer
		s = userTypedBuffer->text_range(start, end);
		rtrim(s);
		string token = tokens[i];
		if (token == s){
			// Word at position start in buffer matched the token
			cout << token << " matches " << s << std::endl;
			correct += 1;
			// Place start at the beginning of the next word
			start += token.length() + 1;
		}
		else{
			cout << token << " does not match " << s << std::endl;
			// Place start at the beginning of the next word
			start += s.length() + 1;
		}
		
		i++;
	}
	double accuracy = 0;
	accuracy = correct / (double)wordCountTotal;

	// Construct test result message
	std::ostringstream oss;
	oss << "Total words of test " << wordCountTotal << std::endl;
	oss << "Correctly typed " << correct << " in " << getTime() << " seconds" << std::endl;
	oss << "Accuracy is " << accuracy << std::endl;
	return oss.str();
}

/* Replace the vector of phrases and change the tokens and word
*  count to match.
*  This allows the user to import their own text into the program
*  to practice typing*/
void WordMachine::replacePhrases(vector<string> &vec){
	phrases.clear();
	for (unsigned int i = 0; i < vec.size(); i++){
		phrases.push_back(vec[i]);
	}

	// Change the tokens vector to match
	tokens.clear();
	findTokens(vec, delimiters);

	// Change the word count
	wordCountTotal = getWordCount();
}

// String representation of a WordMachine object
string WordMachine::to_string() const{
	ostringstream result;
	result << "WordMachine: wordCountTotal is " << wordCountTotal;
	return result.str();
}
