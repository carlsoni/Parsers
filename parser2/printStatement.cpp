#include <stdlib.h>

#include "printStatement.h"
#include "valueNode.h"

#include <stdio.h>

// Constructors/Destructor
PrintStatement::PrintStatement() {
	id = NULL;
	next = NULL;
}
PrintStatement::PrintStatement(ValueNode* newID) : PrintStatement() {
	id = newID;
}
PrintStatement::~PrintStatement() {
}

// Sets the ID to print.
void PrintStatement::SetID(ValueNode* newID) {
	id = newID;
}

// Returns the ID to print.
ValueNode* PrintStatement::GetID() {
	return id;
}

// Returns the type of statement.
StatementType PrintStatement::GetType() {
	return STATEMENT_PRINT;
}

// Sets the next statement.
void PrintStatement::SetNextStatement(StatementNode* nextStatement) {
	next = nextStatement;
}

// Returns the next statement.
StatementNode* PrintStatement::GetNextStatement() {
	return next;
}
