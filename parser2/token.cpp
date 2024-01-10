#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "tokenType.h"

// Constructors/Destructor for Token.
Token::Token() {
	string = NULL;
	type = INVALID;
	lineNum = NO_LINE_NUMBER;
}
Token::Token(TokenType newType, int lineNumber) : Token() {
	SetType(newType);
	SetLineNumber(lineNumber);
}
Token::Token(char* newString, int lineNumber) : Token() {
	if (newString != NULL) {
		SetType(GetTokenType(newString));
		SetString(newString);
		SetLineNumber(lineNumber);
	}
}
Token::~Token() {
}

// Sets the token's type.
void Token::SetType(TokenType newType) {
	type = newType;
}

// Returns the token's type.
TokenType Token::GetType() {
	if (this == NULL)
		return INVALID;
	return type;
}

// Sets the string for the token.
bool Token::SetString(char* newString) {
	string = newString;
	return true;
}

// Returns if the specified string matches the token.
bool Token::IsMatch(char* stringToMatch) {
	// Handle if one or both are NULL.
	if (GetString() == NULL)
		return (stringToMatch == NULL);
	else if (stringToMatch == NULL)
		return false;

	return strcmp(GetString(), stringToMatch);
}

// Returns the string for the token.
char* Token::GetString() {
	return string;
}

// Sets the line number that this token appears on.
void Token::SetLineNumber(int lineNumber) {
	lineNum = lineNumber;
}

// Returns the line number that this token appears on.
int Token::GetLineNumber() {
	return lineNum;
}
