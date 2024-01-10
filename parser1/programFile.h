#ifndef PROGRAM_FILE_H
#define PROGRAM_FILE_H

#include "tokenList.h"
#include "token.h"

#define NO_STRING_START	-1	// Start indicating there is no next string

// Handles a file containing a program.
class ProgramFile {
public:
	// Constructors/Destructor for ProgramFile.
	ProgramFile();
	ProgramFile(const char* fileName);
	~ProgramFile();

	// Loads the file.  Returns the list of tokens.
	TokenList* LoadFile(const char* fileName);

	// Handles when the loading of the file fails.
	void FailLoad();

	// Returns the list of tokens.
	TokenList* GetTokenList();

	// Returns the next token string from the file.
	Token* GetNextToken();

	// Returns the next starting point for the file.
	int GetNextStart();

	// Sets the last character read in from the file.
	void SetLastCharacter(char lastCharacter);

	// Returns the last character read in from the file.
	char GetLastCharacter();

	// Increments the line number.  Returns the previous line number.
	int IncrementLineNumber();

	// Sets the line number that this token appears on.
	void SetLineNumber(int lineNumber);

	// Returns the line number that this token appears on.
	int GetLineNumber();

private:
	TokenList *tokenList;	// List of tokens
	char *fileText;	// Text of the entire file
	int nextStart;	// Start of the next string
	char lastChar;	// Last char read in
	int lineNum;	// Line number
};

#endif
