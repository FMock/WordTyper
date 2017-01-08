#include"tokenizer.h"

using std::string;

// Construct a Tokenizer. Input is the string to tokenize
Tokenizer::Tokenizer(const string &str){
	s = str;
	startidx = 0;
	endidx = 0;
}

// Return a token from the string or an empty string
// if no more tokens are found
// Input delims are the delimiters used to find tokens
string Tokenizer::get_token(const string &delims){

	// return empty string if no more tokens found
	if (startidx == string::npos)
		return string("");

	// Beginning at startidx, find the next delimiter
	endidx = s.find_first_of(delims, startidx);

	// Construct a string that contains the token
	string tok(s.substr(startidx, endidx - startidx));

	// Find the start of the next token. This is a character 
	// that is not a delimiter
	startidx = s.find_first_not_of(delims, endidx);

	// Return the next token
	return tok;
}
