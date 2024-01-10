#include <stdlib.h>

#include "assignmentStatement.h"
#include "statementNode.h"
#include "types.h"
#include "valueNode.h"

#include <stdio.h>

// Constructors/Destructor
AssignmentStatement::AssignmentStatement() {
	leftHandSide = NULL;
	operand1 = NULL;
	operand2 = NULL;
	oper = OPERATOR_NONE;
	next = NULL;
}
AssignmentStatement::AssignmentStatement(ValueNode *newLeftHandSide, ValueNode *firstOperand,
		ValueNode *secondOperand, ArithmeticType newOperator) : AssignmentStatement() {
}
AssignmentStatement::~AssignmentStatement() {
}

// Sets the left-hand side of the assignment.
void AssignmentStatement::SetLeftHandSide(ValueNode *newLeftHandSide) {
	leftHandSide = newLeftHandSide;
}

// Returns the left-hand side of the assignment.
ValueNode* AssignmentStatement::GetLeftHandSide() {
	return leftHandSide;
}

// Returns the value of the right-hand side of the assignment.
int AssignmentStatement::GetRightHandSideValue() {
	int value1, value2;	// The values of the operands

	value1 = GetOperand(true)->GetValue();
	value2 = GetOperand(false)->GetValue();
	switch (GetOperator()) {
		case OPERATOR_ADD:		// +
			return value1 + value2;
		case OPERATOR_SUBTRACT:	// -
			return value1 - value2;
		case OPERATOR_MULTIPLY:	// *
			return value1 * value2;
		case OPERATOR_DIVIDE:	// /
			return value1 / value2;
		default:	// Just return the value
			return value1;
	}
}

// Sets the first or second operand.
void AssignmentStatement::SetOperand(ValueNode* operand, bool isFirst) {
	if (isFirst)
		operand1 = operand;
	else
		operand2 = operand;
}

// Returns the first or second operand.
ValueNode* AssignmentStatement::GetOperand(bool isFirst) {
	return (isFirst ? operand1 : operand2);
}

// Sets the operator.
void AssignmentStatement::SetOperator(ArithmeticType newOperator) {
	oper = newOperator;
}

// Returns the operator.
ArithmeticType AssignmentStatement::GetOperator() {
	return oper;
}

// Returns the type.
StatementType AssignmentStatement::GetType() {
	return STATEMENT_ASSIGN;
}

// Sets the next statement to run.
void AssignmentStatement::SetNextStatement(StatementNode *nextStatement) {
	next = nextStatement;
}

// Returns the next statement to run.
StatementNode* AssignmentStatement::GetNextStatement() {
	return next;
}
