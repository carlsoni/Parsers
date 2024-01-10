#ifndef NO_OP_STATEMENT_H
#define NO_OP_STATEMENT_H

#include "statementNode.h"

// Handles placeholder statements.
class NoOpStatement : public StatementNode {
public:
	// Constructors/Destructor
	NoOpStatement();
	~NoOpStatement();

	// Returns the type of statement.
	StatementType GetType();

	// Sets the next statement.
	void SetNextStatement(StatementNode* nextStatement);

	// Returns the next statement.
	StatementNode* GetNextStatement();

private:
	StatementNode* next;	// Next statement to goto
};

#endif
