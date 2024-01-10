#include <string.h>
#include "tokenType.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Returns the type of token encountered, if any.
TokenType GetTokenType(char *tokenString) {
	TokenType toReturn;	// Token type to return
	char firstChar;		// First character in the string

	// Check if the token type is one with special characters.
	if ((toReturn = GetSpecialTokenType(tokenString)) != INVALID)
		return toReturn;

	// Check if the token matches a special type.
	if (strcmp(tokenString, IF_TOKEN_STRING) == 0)
		return IF;
	if (strcmp(tokenString, PRINT_TOKEN_STRING) == 0)
		return PRINT;
	if (strcmp(tokenString, WHILE_TOKEN_STRING) == 0)
		return WHILE;
	if (strcmp(tokenString, SWITCH_TOKEN_STRING) == 0)
		return SWITCH;
	if (strcmp(tokenString, CASE_TOKEN_STRING) == 0)
		return CASE;
	if (strcmp(tokenString, DEFAULT_TOKEN_STRING) == 0)
		return DEFAULT;	

	// If the first character is not a digit, this is an ID.
	if (!isdigit(tokenString[0]))
		return ID;

	// Token is an integer.
	return NUM;
}

// Returns the string associated with the specified token.
char* GetTokenString(TokenType tokenType) {
	return NULL;
}

// Returns if the character could start a special token.
bool IsSpecialStart(char firstChar) {
	char specialString[2] = { firstChar, '\0' };	// String with the special character

	// All special tokens start with a single character that is a special token.
	return (GetSpecialTokenType(specialString) != INVALID);
}

// Returns the special type of token encountered, if any.
TokenType GetSpecialTokenType(char* tokenString) {
	// String must exist to be valid.
	if (tokenString == NULL)
		return INVALID;

	if (strcmp(tokenString, COLON_TOKEN_STRING) == 0)
		return COLON;
	if (strcmp(tokenString, SEMICOLON_TOKEN_STRING) == 0)
		return SEMICOLON;
	if (strcmp(tokenString, COMMA_TOKEN_STRING) == 0)
		return COMMA;
	if (strcmp(tokenString, LeftBRACE_TOKEN_STRING) == 0)
		return LeftBRACE;
	if (strcmp(tokenString, RightBRACE_TOKEN_STRING) == 0)
		return RightBRACE;
	if (strcmp(tokenString, EQUAL_TOKEN_STRING) == 0)
		return EQUAL;
	if (strcmp(tokenString, PLUS_TOKEN_STRING) == 0)
		return PLUS;
	if (strcmp(tokenString, MINUS_TOKEN_STRING) == 0)
		return MINUS;
	if (strcmp(tokenString, MULT_TOKEN_STRING) == 0)
		return MULT;
	if (strcmp(tokenString, DIV_TOKEN_STRING) == 0)
		return DIV;
	if (strcmp(tokenString, GREATER_TOKEN_STRING) == 0)
		return GREATER;
	if (strcmp(tokenString, LESS_TOKEN_STRING) == 0)
		return LESS;
	if (strcmp(tokenString, NotEQUAL_TOKEN_STRING) == 0)
		return NotEQUAL;

	// Token is not a special type.
	return INVALID;
}

// Returns if the token type is a special token (token string is NULL).
bool IsSpecialTokenType(TokenType tokenType) {
	return (tokenType >= NotEQUAL);
}
