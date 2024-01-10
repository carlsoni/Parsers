#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include "statementNode.h"
#include "types.h"
#include "valueNode.h"

class IfStatement : public StatementNode {
public:
	// Constructors/Destructor
	IfStatement();
	IfStatement(ComparatorType newOperator, ValueNode *firstOperand, ValueNode *secondOperand,
			StatementNode *statementIfTrue, StatementNode *statementIfFalse);
	~IfStatement();

	// Sets the condition operator.
	void SetOperator(ComparatorType newOperator);

	// Returns the operator.
	ComparatorType GetOperator();

	// Sets the operand.
	void SetOperand(bool isFirst, ValueNode *conditionOperand);

	// Returns the operand.
	ValueNode* GetOperand(bool isFirst);

	// Sets the next statement.
	void SetNextStatement(StatementNode *nextStatement);
	void SetNextStatement(bool isConditionTrue, StatementNode *nextStatement);

	// Returns the next statement.
	StatementNode* GetNextStatement(bool isConditionTrue);
	StatementNode* GetNextStatement();

	// Returns the type of statement this is.
	StatementType GetType();

private:
	ComparatorType relationalOperator;	// Comparison being made
	ValueNode *conditionOperand1;	// First operand
	ValueNode *conditionOperand2;	// Second operand
	StatementNode *trueBranch;	// Statement to execute if condition is true
	StatementNode *falseBranch;	// Statement to execute if condition is false
};

#endif
