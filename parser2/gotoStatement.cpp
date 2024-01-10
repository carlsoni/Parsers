#include <stdlib.h>

#include "gotoStatement.h"
#include "statementNode.h"
#include "types.h"

// Constructors/Destructor
GotoStatement::GotoStatement() {
}
GotoStatement::GotoStatement(StatementNode* gotoStatement) : GotoStatement() {
	SetNextStatement(gotoStatement);
}
GotoStatement::~GotoStatement() {
}

// Returns the type of statement.
StatementType GotoStatement::GetType() {
	return STATEMENT_GOTO;
}

// Sets the next statement.
void GotoStatement::SetNextStatement(StatementNode *nextStatement) {
	next = nextStatement;
}

// Returns the next statement.
StatementNode* GotoStatement::GetNextStatement() {
	return next;
}
