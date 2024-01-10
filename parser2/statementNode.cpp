#include <stdlib.h>

#include "assignmentStatement.h"
#include "gotoStatement.h"
#include "ifStatement.h"
#include "noOpStatement.h"
#include "printStatement.h"
#include "statementNode.h"
#include "types.h"

#include <stdio.h>

// Constructor/Destructor
StatementNode::StatementNode() {
	type = STATEMENT_NONE;
}

StatementNode::~StatementNode() {
}

// Returns the type of statement.
StatementType StatementNode::GetType() {
	return type;
}

// Returns the next statement.
StatementNode* StatementNode::GetNextStatement() {
	switch (GetType()) {
		case STATEMENT_ASSIGN:	return ((AssignmentStatement*)this)->GetNextStatement();
		case STATEMENT_GOTO:	return ((GotoStatement*)this)->GetNextStatement();
		case STATEMENT_IF:		return ((IfStatement*)this)->GetNextStatement();
		case STATEMENT_NONE:	return ((NoOpStatement*)this)->GetNextStatement();
		case STATEMENT_PRINT:	return ((PrintStatement*)this)->GetNextStatement();
	}

	return NULL;
}
