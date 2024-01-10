#ifndef ASSIGNMENT_STATEMENT_H
#define ASSIGNMENT_STATEMENT_H

#include "statementNode.h"
#include "types.h"
#include "valueNode.h"

class AssignmentStatement : public StatementNode {
public:
	// Constructors/Destructor
	AssignmentStatement();
	AssignmentStatement(ValueNode *newLeftHandSide, ValueNode *firstOperand,
			ValueNode *secondOperand, ArithmeticType newOperator);
	~AssignmentStatement();

	// Sets the left-hand side of the assignment.
	void SetLeftHandSide(ValueNode *newLeftHandSide);

	// Returns the left-hand side of the assignment.
	ValueNode* GetLeftHandSide();

	// Returns the value of the right-hand side of the assignment.
	int GetRightHandSideValue();

	// Sets the first or second operand.
	void SetOperand(ValueNode *operand, bool isFirst);

	// Returns the first or second operand.
	ValueNode* GetOperand(bool isFirst);

	// Sets the operator.
	void SetOperator(ArithmeticType newOperator);

	// Returns the operator.
	ArithmeticType GetOperator();

	// Returns the type.
	StatementType GetType();

	// Sets the next statement to run.
	void SetNextStatement(StatementNode *nextStatement);

	// Returns the next statement to run.
	StatementNode* GetNextStatement();

private:
	ValueNode *leftHandSide;	// Left side of the assignment
	ValueNode *operand1;		// First operand
	ValueNode *operand2;		// Second operand
	ArithmeticType oper;		// Operator
	StatementNode *next;		// Next statement to run
};

#endif
