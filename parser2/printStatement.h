#ifndef PRINT_STATEMENT_H
#define PRINT_STATEMENT_H

#include "statementNode.h"
#include "valueNode.h"

class PrintStatement : public StatementNode {
public:
	// Constructors/Destructor
	PrintStatement();
	PrintStatement(ValueNode *newID);
	~PrintStatement();

	// Sets the ID to print.
	void SetID(ValueNode *newID);

	// Returns the ID to print.
	ValueNode* GetID();

	// Returns the type of statement.
	StatementType GetType();

	// Sets the next statement.
	void SetNextStatement(StatementNode* nextStatement);

	// Returns the next statement.
	StatementNode* GetNextStatement();

private:
	ValueNode *id;			// ID to print
	StatementNode* next;	// Next statement to goto
};

#endif
