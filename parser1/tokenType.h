#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType {
	// Punctuation/special characters
	COLON, SEMICOLON, COMMA, LeftBRACE, RightBRACE, EQUAL, PLUS, MINUS, MULT, DIV,
	LeftPAREN, RightPAREN, GREATER, GtEQ, LESS, LtEQ, NotEQUAL,

	// For handling types and variables
	TYPE, BOOLEAN, INT, LONG, REAL, STRING, VAR,

	// For handling code and names
	WHILE, DO,

	// All other tokens
	ID, NUM, RealNUM,

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
#define LeftPAREN_TOKEN_STRING	"("
#define RightPAREN_TOKEN_STRING	")"
#define GREATER_TOKEN_STRING	">"
#define GtEQ_TOKEN_STRING		">="
#define LESS_TOKEN_STRING		"<"
#define LtEQ_TOKEN_STRING		"<="
#define NotEQUAL_TOKEN_STRING	"<>"
#define TYPE_TOKEN_STRING		"TYPE"
#define REAL_TOKEN_STRING		"REAL"
#define INT_TOKEN_STRING		"INT"
#define BOOLEAN_TOKEN_STRING	"BOOLEAN"
#define STRING_TOKEN_STRING		"STRING"
#define LONG_TOKEN_STRING		"LONG"
#define VAR_TOKEN_STRING		"VAR"
#define WHILE_TOKEN_STRING		"WHILE"
#define DO_TOKEN_STRING			"DO"

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
