#ifndef TOKEN_H
#define TOKEN_H

#include "tokenType.h"

#define NO_LINE_NUMBER	-1	// Line number indicating the token is not in the code

// Defines a token.
class Token {
public:
	// Constructors/Destructor for Token.
	Token();
	Token(TokenType newType, int lineNumber);
	Token(char* newString, int lineNumber);
	~Token();

	// Sets the token's type.
	void SetType(TokenType newType);

	// Returns the token's type.
	TokenType GetType();

	// Sets the string for the token.  Returns if it succeeded.
	bool SetString(char *newString);

	// Returns if the specified string matches the token.
	bool IsMatch(char* stringToMatch);

	// Returns the string for the token.
	char* GetString();

	// Sets the line number that this token appears on.
	void SetLineNumber(int lineNumber);

	// Returns the line number that this token appears on.
	int GetLineNumber();

private:
	TokenType type;	// Type of token encountered
	char *string;	// String representing the token
	int lineNum;	// Line number for the token
};

#endif
