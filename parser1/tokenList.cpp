#include <stdlib.h>
#include <string.h>

#include "tokenList.h"

#define INITIAL_CAPACITY	2	// Initial capacity of a token list

// Constructors/Destructor for TokenList.
TokenList::TokenList() {
	tokenList = NULL;
	capacity = 0;
	numTokens = 0;
}
TokenList::TokenList(bool isMasterList) : TokenList() {
	isMaster = isMasterList;
}
TokenList::~TokenList() {
	// Only delete tokens if this is a master list.
	if (IsMasterList()) {
		for (int cnt = 0; cnt < GetNumberOfTokens(); cnt++)
		{
			if (tokenList[cnt] != NULL)
				delete tokenList[cnt];
		}
	}
	delete tokenList;
}

// Adds the specified token to the list.  Returns if it succeeded.
bool TokenList::AddToken(Token *toAdd) {
	Token **newList;	// New list of tokens

	// Token being added must be valid.
	if (toAdd == NULL)
		return false;

	// Expand capacity if necessary.
	if (GetNumberOfTokens() == GetCapacity()) {
		if (GetCapacity() == 0)
			SetCapacity(INITIAL_CAPACITY);
		else
			SetCapacity(GetCapacity() * 2);
	}

	tokenList[numTokens++] = toAdd;
	return true;
}

// Sets the token in the specified location.  Returns if it succeeded.
bool TokenList::SetToken(int tokenNumber, Token* newToken) {
	// Token number must be valid.
	if ((tokenNumber < 1) || (tokenNumber > GetNumberOfTokens()))
		return false;

	tokenList[tokenNumber - 1] = newToken;
	return true;
}

// Returns the token matching the specified string.
Token* TokenList::GetToken(char* toMatch) {
	Token* curToken;	// Current token

	// The token must have a chance to match.
	if (toMatch == NULL)
		return NULL;

	for (int cnt = 1; cnt <= GetNumberOfTokens(); cnt++) {
		curToken = GetToken(cnt);
		if (strcmp(toMatch, curToken->GetString()) == 0)
			return curToken;
	}

	return NULL;
}

// Returns the token in the specified position.
Token* TokenList::GetToken(int tokenPosition) {
	// Token position must be valid.
	if ((tokenPosition < 1) || (tokenPosition > GetNumberOfTokens()))
		return NULL;

	// Return the token.
	return tokenList[tokenPosition - 1];
}

// Sets the capacity of the token list.  Returns if it succeeded.
bool TokenList::SetCapacity(int newCapacity) {
	Token** newList;	// New list of tokens

	// Capacity must be larger than the current number of tokens.
	if (newCapacity <= GetNumberOfTokens())
		return false;

	newList = new Token*[newCapacity];
	for (int cnt = 0; cnt < GetNumberOfTokens(); cnt++)
		newList[cnt] = GetToken(cnt + 1);
	capacity = newCapacity;
	delete tokenList;
	tokenList = newList;

	return true;
}

// Returns the number of tokens the list can handle.
int TokenList::GetCapacity() {
	return capacity;
}

// Returns the number of tokens in the list.
int TokenList::GetNumberOfTokens() {
	return numTokens;
}

// Returns if this is the master list of tokens.
bool TokenList::IsMasterList() {
	return isMaster;
}
