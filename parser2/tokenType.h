#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType {
	// Punctuation/special characters

	COLON, SEMICOLON, COMMA, LeftBRACE, RightBRACE, EQUAL, PLUS, MINUS, MULT, DIV,
	GREATER, LESS, NotEQUAL,

	// For handling code and names
	WHILE, IF, PRINT, SWITCH, CASE, DEFAULT,

	// All other tokens
	ID, NUM,

	// Invalid token type
	INVALID,
};


// Constants
	// Strings for tokens.
#define COLON_TOKEN_STRING		":"
#define SEMICOLON_TOKEN_STRING	";"
#define COMMA_TOKEN_STRING		","
#define LeftBRACE_TOKEN_STRING	"{"
#define RightBRACE_TOKEN_STRING	"}"
#define EQUAL_TOKEN_STRING		"="
#define PLUS_TOKEN_STRING		"+"
#define MINUS_TOKEN_STRING		"-"
#define MULT_TOKEN_STRING		"*"
#define DIV_TOKEN_STRING		"/"
#define GREATER_TOKEN_STRING	">"
#define LESS_TOKEN_STRING		"<"
#define NotEQUAL_TOKEN_STRING	"<>"
#define WHILE_TOKEN_STRING		"WHILE"
#define IF_TOKEN_STRING			"IF"
#define PRINT_TOKEN_STRING		"print"
#define SWITCH_TOKEN_STRING		"SWITCH"
#define CASE_TOKEN_STRING		"CASE"
#define DEFAULT_TOKEN_STRING	"DEFAULT"

	// Type tokens
#define MIN_TYPE_TOKEN			BOOLEAN

// Returns the type of token encountered, if any.
TokenType GetTokenType(char* tokenString);

// Returns the string associated with the specified token.
char* GetTokenString(TokenType tokenType);

// Returns if the character could start a special token.
bool IsSpecialStart(char firstChar);

// Returns the special type of token encountered, if any.
TokenType GetSpecialTokenType(char* tokenString);

// Returns if the token type is a special token (token string is NULL).
bool IsSpecialTokenType(TokenType tokenType);

#endif
