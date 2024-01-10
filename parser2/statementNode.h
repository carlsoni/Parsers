#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

#include "types.h"

// This class handles program statements.  This is virtual because 
class StatementNode {
public:
	// Constructor/Destructor
	StatementNode();
	~StatementNode();

	// Returns the type of statement.
	virtual StatementType GetType();

	// Returns the next statement.
	virtual StatementNode* GetNextStatement();

private:
	StatementType type;	// Type of statement
};

#endif
