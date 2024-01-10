#ifndef TYPES_H
#define TYPES_H

// Types of arithmetic operators.
enum ArithmeticType {
	OPERATOR_ADD,		// +
	OPERATOR_SUBTRACT,	// -
	OPERATOR_MULTIPLY,	// *
	OPERATOR_DIVIDE,	// /
	OPERATOR_NONE,		// No operator
};

// Types of relational operators.
enum ComparatorType {
	COMPARATOR_EQUAL,				// =
	COMPARATOR_GREATER_THAN,		// >
	COMPARATOR_GREATER_THAN_EQUAL,	// >=
	COMPARATOR_LESS_THAN,			// <
	COMPARATOR_LESS_THAN_EQUAL,		// <=
	COMPARATOR_NOT_EQUAL,			// !=
	NO_COMPARATOR,					// No comparator
};

// Types of statements.
enum StatementType {
	STATEMENT_ASSIGN,	// Assignment
	STATEMENT_GOTO,		// Goto
	STATEMENT_IF,		// If
	STATEMENT_PRINT,	// Print
	STATEMENT_NONE,		// No statement (use if you need a statement, but nothing should happen)
};

#endif