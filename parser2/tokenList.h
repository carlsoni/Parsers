#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "token.h"

// Defines a list of tokens.
class TokenList {
public:
	// Constructor/Destructor for TokenList.
	TokenList();
	TokenList(bool isMasterList);
	~TokenList();

	// Adds the specified token to the list.  Returns if it succeeded.
	bool AddToken(Token *toAdd);

	// Sets the token in the specified location.  Returns if it succeeded.
	bool SetToken(int tokenNumber, Token *newToken);

	// Returns the token matching the specified string.
	Token* GetToken(char* toMatch);

	// Returns the token in the specified position.
	Token* GetToken(int tokenPosition);

	// Sets the capacity of the token list.  Returns if it succeeded.
	bool SetCapacity(int newCapacity);

	// Returns the number of tokens the list can handle.
	int GetCapacity();

	// Returns the number of tokens in the list.
	int GetNumberOfTokens();

	// Returns if this is the master list of tokens.
	bool IsMasterList();

private:
	Token **tokenList;	// List of tokens
	int capacity;		// Number of tokens the list can store.
	int numTokens;		// Number of tokens
	bool isMaster;		// Is this the master list of tokens?
};

#endif
