#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

// Tokenizer class is used to tokenize a string

class Tokenizer{

	std::string s;
	std::string::size_type startidx;
	std::string::size_type endidx;
public:

	// Construct a Tokenizer. Input is the string to tokenize
	Tokenizer(const std::string &str);

	// Return a token from the string or an empty string
	// if no more tokens are found
	std::string get_token(const std::string &delims);
};

#endif