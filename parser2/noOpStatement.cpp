#include <stdlib.h>

#include "noOpStatement.h"
#include "statementNode.h"
#include "types.h"

// Constructors/Destructor
NoOpStatement::NoOpStatement() : StatementNode() {
}
NoOpStatement::~NoOpStatement() {
}

// Returns the type of statement.
StatementType NoOpStatement::GetType() {
	return STATEMENT_NONE;
}

// Sets the next statement.
void NoOpStatement::SetNextStatement(StatementNode* nextStatement) {
	next = nextStatement;
}

// Returns the next statement.
StatementNode* NoOpStatement::GetNextStatement() {
	return next;
}
