#ifndef GOTO_STATEMENT_H
#define GOTO_STATEMENT_H

#include "statementNode.h"

class GotoStatement : public StatementNode {
public:
	// Constructors/Destructor
	GotoStatement();
	GotoStatement(StatementNode *gotoStatement);
	~GotoStatement();


	// Returns the type of statement.
	StatementType GetType();

	// Sets the next statement.
	void SetNextStatement(StatementNode* nextStatement);

	// Returns the next statement.
	StatementNode* GetNextStatement();

private:
	StatementNode *next;	// Next statement to goto
};

#endif
