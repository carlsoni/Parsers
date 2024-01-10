#include <stdlib.h>

#include "program2.h"

#define PROGRAM_FILE_NAME	"C:\\Users\\Chris\\Desktop\\Starting Code 2.2\\text.txt"	// File with the program

int main(int argc, char** argv)
{
	// Load the program.
	LoadProgram((char*)PROGRAM_FILE_NAME);
	exit(0);
}
