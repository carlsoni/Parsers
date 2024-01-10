#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "programFile.h"
#include "tokenType.h"

// Constructors/Destructor for ProgramFile.
ProgramFile::ProgramFile() {
	tokenList = NULL;
	fileText = NULL;
	nextStart = NO_STRING_START;
}
ProgramFile::ProgramFile(const char* fileName) {
	LoadFile(fileName);
}
ProgramFile::~ProgramFile() {
	if (fileText != NULL)
		delete fileText;
	fileText = NULL;
}

// Loads the file.  Returns the token list.
TokenList* ProgramFile::LoadFile(const char* fileName) {
	FILE *programFile;	// File with the program
	TokenList *toReturn;	// List of tokens
	Token* nextToken;	// Next token in the program
	int fileSize;		// Size of the file

	// Open the file.  This must succeed to continue.
	if ((programFile = fopen(fileName, "r")) == NULL)
		return NULL;

	// Determine the file size.
	fseek(programFile, 0, SEEK_END);
	fileSize = (int)ftell(programFile);
	fseek(programFile, 0, 0);

	// Allocate memory so that the entire file can be stored.  This must succeed to continue.
	if (fileText != NULL)
		delete fileText;
	fileText = new char[fileSize + 2];
	fileText[0] = '\0';

	// Read in the entire file.  Add two end of strings to indicate the end of the file.
	while (fgets(&fileText[strlen(fileText)], fileSize, programFile) != NULL);
	nextStart = 0;
	fileText[fileSize] = '\0';
	lineNum = 1;

	// Go through the list of tokens.
	SetLastCharacter('\0');
	tokenList = new TokenList(true);
	while ((nextToken = GetNextToken()) != NULL)
		tokenList->AddToken(nextToken);

	fclose(programFile);
	return GetTokenList();
}

// Handles when the loading of the file fails.
void ProgramFile::FailLoad() {
	if (tokenList != NULL)
		delete tokenList;
	tokenList = NULL;
}

// Returns the list of tokens.
TokenList* ProgramFile::GetTokenList() {
	return tokenList;
}

// Returns the next token string from the file.
Token* ProgramFile::GetNextToken() {
	Token *token = NULL;	// Token to return
	TokenType curType = INVALID;		// Type of token found
	char curChar;	// Current character read in.
	int curStart;	// Current start of the string
	int tokenSize = 0;	// Size of the token
	bool isSpecial;		// Is this a special token?
	int numericType = 0;	// Is this an ID (1)/NUM (2)/RealNUM (3)

	// Handle the first character.
	if ((isSpecial = IsSpecialStart(GetLastCharacter())))	// Previous character was special, add it back
		fileText[--nextStart] = GetLastCharacter();
	curStart = GetNextStart();

	// Get characters until whitespace or the end of file is encountered.
	isSpecial = IsSpecialStart(fileText[curStart]);
	while (!isspace(curChar = fileText[nextStart++])) {
		// Nothing more to do if the end of file is encountered.
		if (curChar == '\0')
			break;

		// Current character must be a lowercase letter, uppercase letter, or a digit.
		if (((curChar >= 'a') && (curChar <= 'z')) || ((curChar >= 'A') && (curChar <= 'Z'))) {	// Letter
			// Special tokens can't have letters.
			if (isSpecial)
				break;

			if (numericType > 1) {	// Numeric can't have alpha characters
				FailLoad();
				return NULL;
			}
			else	// ID
				numericType = 1;
		}
		else if ((curChar >= '0') && (curChar <= '9')) {	// Digit
			// Special tokens can't have digits.
			if (isSpecial)
				break;

			if (numericType == 0)
				numericType = 2;
		}
		else if (curChar == '.') {	// Decimal point
			if (numericType == 2)	// Must be numeric
				numericType = 3;
			else {
				FailLoad();
				return NULL;
			}
		}
		else if (!IsSpecialStart(curChar)) {	// Invalid token - fail and return
			FailLoad();
			return NULL;
		}
		else {	// Must be special token
			if (!isSpecial)	// Current token isn't special, this starts next token.
				break;

			// Determine if this is multiple special tokens.
			SetLastCharacter(fileText[nextStart]);
			fileText[nextStart] = '\0';
			if (GetSpecialTokenType(&fileText[curStart]) == INVALID) {	// Token ended with previous character
				fileText[nextStart] = GetLastCharacter();
				break;
			}
			else
				curType = GetSpecialTokenType(&fileText[curStart]);
			fileText[nextStart] = GetLastCharacter();
		}
	}
	nextStart--;	// Found end of string - advanced one space too far.

	// If this character is a newline, advance one line.
	if (fileText[nextStart] == '\n') {
		IncrementLineNumber();
		fileText[nextStart] = '\r';
	}

	// If the first character is blank, go to the next one.
	if (isspace(fileText[curStart])) {
		nextStart++;
		return GetNextToken();
	}

	// Add the end of string (unless end of file) and return the result.
	if (fileText[curStart] == '\0')
		return NULL;
	if (isSpecial) {	// Started with special character - don't need to keep the string.
		fileText[curStart] = '\0';
	}
	else {
		SetLastCharacter(fileText[nextStart]);
		fileText[nextStart++] = '\0';
	}
	if (curType != INVALID)	// Token type has known string
		return new Token(curType, GetLineNumber());
	return new Token(&fileText[curStart], GetLineNumber());
}

// Returns the next starting point for the file.
int ProgramFile::GetNextStart() {
	return nextStart;
}

// Sets the last character read in from the file.
void ProgramFile::SetLastCharacter(char lastCharacter) {
	lastChar = lastCharacter;
}

// Returns the last character read in from the file.
char ProgramFile::GetLastCharacter() {
	return lastChar;
}

// Increments the line number.  Returns the previous line number.
int ProgramFile::IncrementLineNumber() {
	// Don't increment if not in the program.
	if (GetLineNumber() == NO_LINE_NUMBER)
		return NO_LINE_NUMBER;

	SetLineNumber(GetLineNumber() + 1);
	return GetLineNumber() - 1;
}

// Sets the line number that this token appears on.
void ProgramFile::SetLineNumber(int lineNumber) {
	lineNum = lineNumber;
}

// Returns the line number that this token appears on.
int ProgramFile::GetLineNumber() {
	return lineNum;
}
