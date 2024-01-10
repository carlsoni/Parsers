all: compiler

compiler: compiler.o parser.o assignmentStatement.o gotoStatement.o ifStatement.o noOpStatement.o printStatement.o statementNode.o valueNode.o programFile.o token.o tokenList.o tokenType.o 
	g++ -o compiler compiler.o parser.o assignmentStatement.o gotoStatement.o ifStatement.o noOpStatement.o printStatement.o statementNode.o valueNode.o programFile.o token.o tokenList.o tokenType.o 

parser.o : parser.cpp
	g++ -c parser.cpp

assignmentStatement.o : assignmentStatement.cpp
	g++ -c assignmentStatement.cpp

compiler.o : compiler.cpp
	g++ -c compiler.cpp

gotoStatement.o : gotoStatement.cpp
	g++ -c gotoStatement.cpp

ifStatement.o : ifStatement.cpp
	g++ -c ifStatement.cpp

noOpStatement.o : noOpStatement.cpp
	g++ -c noOpStatement.cpp

printStatement.o : printStatement.cpp
	g++ -c printStatement.cpp

statementNode.o : statementNode.cpp
	g++ -c statementNode.cpp

valueNode.o: valueNode.cpp
	g++ -c valueNode.cpp

programFile.o: programFile.cpp
	g++ -c programFile.cpp

token.o: token.cpp
	g++ -c token.cpp

tokenList.o: tokenList.cpp
	g++ -c tokenList.cpp

tokenType.o: tokenType.cpp
	g++ -c tokenType.cpp

clean:
	rm -f compiler *.o

run: compiler
	./compiler
