#include <stdlib.h>

#include "ifStatement.h"
#include "statementNode.h"
#include "types.h"
#include "valueNode.h"

#include <stdio.h>

// Constructors/Destructor
IfStatement::IfStatement() {
	relationalOperator = NO_COMPARATOR;
	conditionOperand1 = NULL;
	conditionOperand2 = NULL;
	trueBranch = NULL;
	falseBranch = NULL;
}
IfStatement::IfStatement(ComparatorType newOperator, ValueNode *firstOperand, ValueNode *secondOperand,
		StatementNode *statementIfTrue, StatementNode *statementIfFalse) : IfStatement() {
	SetOperator(newOperator);
	SetOperand(true, firstOperand);
	SetOperand(false, secondOperand);
	SetNextStatement(true, statementIfTrue);
	SetNextStatement(false, statementIfFalse);
}
IfStatement::~IfStatement() {
}

// Sets the condition operator.
void IfStatement::SetOperator(ComparatorType newOperator) {
	relationalOperator = newOperator;
}

// Returns the operator.
ComparatorType IfStatement::GetOperator() {
	return relationalOperator;
}

// Sets the operand.
void IfStatement::SetOperand(bool isFirst, ValueNode* conditionOperand) {
	if (isFirst)
		conditionOperand1 = conditionOperand;
	else
		conditionOperand2 = conditionOperand;
}

// Returns the operand.
ValueNode* IfStatement::GetOperand(bool isFirst) {
	return isFirst ? conditionOperand1 : conditionOperand2;
}

// Sets the next statement.
void IfStatement::SetNextStatement(StatementNode* nextStatement) {
	SetNextStatement(true, nextStatement);
}
void IfStatement::SetNextStatement(bool isConditionTrue, StatementNode* nextStatement) {
	if (isConditionTrue)
		trueBranch = nextStatement;
	else
		falseBranch = nextStatement;
}

// Returns the next statement.
StatementNode* IfStatement::GetNextStatement(bool isConditionTrue) {
	return (isConditionTrue ? trueBranch : falseBranch);
}
StatementNode* IfStatement::GetNextStatement() {
	int value1, value2;	// The two values
	bool isConditionTrue = false;	// Is the condition true?

	value1 = GetOperand(true)->GetValue();
	value2 = GetOperand(false)->GetValue();

	switch (GetOperator()) {
		case COMPARATOR_EQUAL:				// =
			isConditionTrue = (value1 == value2);
			break;
		case COMPARATOR_GREATER_THAN:		// >
			isConditionTrue = (value1 > value2);
			break;
		case COMPARATOR_GREATER_THAN_EQUAL:	// >=
			isConditionTrue = (value1 >= value2);
			break;	
		case COMPARATOR_LESS_THAN:			// <
			isConditionTrue = (value1 < value2);
			break;
		case COMPARATOR_LESS_THAN_EQUAL:	// <=
			isConditionTrue = (value1 <= value2);
			break;
		case COMPARATOR_NOT_EQUAL:			// !=
			isConditionTrue = (value1 != value2);
			break;
		default:	// Invalid comparator
			return NULL;
	}
	return GetNextStatement(isConditionTrue);
}

StatementType IfStatement::GetType() {
	return STATEMENT_IF;
}