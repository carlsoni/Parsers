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
	if (strcmp(tokenString, TYPE_TOKEN_STRING) == 0)
		return TYPE;
	if (strcmp(tokenString, REAL_TOKEN_STRING) == 0)
		return REAL;
	if (strcmp(tokenString, INT_TOKEN_STRING) == 0)
		return INT;
	if (strcmp(tokenString, BOOLEAN_TOKEN_STRING) == 0)
		return BOOLEAN;
	if (strcmp(tokenString, STRING_TOKEN_STRING) == 0)
		return STRING;
	if (strcmp(tokenString, LONG_TOKEN_STRING) == 0)
		return LONG;
	if (strcmp(tokenString, VAR_TOKEN_STRING) == 0)
		return VAR;
	if (strcmp(tokenString, WHILE_TOKEN_STRING) == 0)
		return WHILE;
	if (strcmp(tokenString, DO_TOKEN_STRING) == 0)
		return DO;

	// If the first character is not a digit, this is an ID.
	if (!isdigit(tokenString[0]))
		return ID;

	// If the number has a decimal point, it is a real.
	if (strchr(tokenString, '.') != NULL)
		return RealNUM;

	// Token is an integer.
	return NUM;
}

// Returns the string associated with the specified token.
char* GetTokenString(TokenType tokenType) {
	switch (tokenType) {
		case BOOLEAN:
			return (char*)BOOLEAN_TOKEN_STRING;
		case INT:
			return (char*)INT_TOKEN_STRING;
		case LONG:
			return (char*)LONG_TOKEN_STRING;
		case REAL:
			return (char*)REAL_TOKEN_STRING;
		case STRING:
			return (char*)STRING_TOKEN_STRING;
	}

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
	if (strcmp(tokenString, LeftPAREN_TOKEN_STRING) == 0)
		return LeftPAREN;
	if (strcmp(tokenString, RightPAREN_TOKEN_STRING) == 0)
		return RightPAREN;
	if (strcmp(tokenString, GREATER_TOKEN_STRING) == 0)
		return GREATER;
	if (strcmp(tokenString, GtEQ_TOKEN_STRING) == 0)
		return GtEQ;
	if (strcmp(tokenString, LESS_TOKEN_STRING) == 0)
		return LESS;
	if (strcmp(tokenString, LtEQ_TOKEN_STRING) == 0)
		return LtEQ;
	if (strcmp(tokenString, NotEQUAL_TOKEN_STRING) == 0)
		return NotEQUAL;

	// Token is not a special type.
	return INVALID;
}

// Returns if the token type is a special token (token string is NULL).
bool IsSpecialTokenType(TokenType tokenType) {
	return (tokenType >= NotEQUAL);
}
