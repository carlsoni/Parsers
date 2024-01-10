#include <stdio.h>
#include <stdlib.h>

#include "assignmentStatement.h"
#include "compiler.h"
#include "gotoStatement.h"
#include "ifStatement.h"
#include "printStatement.h"
#include "statementNode.h"

#define PROGRAM_FILE_NAME	"C:\\Users\\Chris\\Desktop\\Assignment 3 starter Code\\text.txt"	// File with the program
using namespace std;

// Executes the program.
void ExecuteProgram(StatementNode *program) {
	AssignmentStatement* curAssignment = NULL;	// Current assignment

	while (program != NULL) {
		switch (program->GetType()) {
			case STATEMENT_ASSIGN:	// Assignment
				curAssignment = (AssignmentStatement*)program;	// Current assignment
				curAssignment->GetLeftHandSide()->SetValue(curAssignment->GetRightHandSideValue());
				program = curAssignment->GetNextStatement();
				break;

			case STATEMENT_GOTO:	// Goto - do nothing, as only the next 
				program = ((GotoStatement*)program)->GetNextStatement();
				break;

			case STATEMENT_IF:	// If
				program = ((IfStatement*)program)->GetNextStatement();
				break;

			case STATEMENT_NONE:	// No operation
				program = program->GetNextStatement();
				break;

			case STATEMENT_PRINT:	// Print
				printf("%d\n", ((PrintStatement*)program)->GetID()->GetValue());
				program = program->GetNextStatement();
				break;
		}
//		program = program->GetNextStatement();
	}
}

// Runs the main program.
int main(int argc, char *argv[]) {
	StatementNode *program;	// Program	

//	program = parseGenerateIntermediateRepresentation(argv[1]);
	program = parseGenerateIntermediateRepresentation((char*)PROGRAM_FILE_NAME);
	ExecuteProgram(program);
	return 0;
}