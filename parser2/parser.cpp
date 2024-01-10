#include "compiler.h"
#include "programFile.h"
#include "assignmentStatement.h"
#include "gotoStatement.h"
#include "ifStatement.h"
#include "printStatement.h"
#include "statementNode.h"
#include "noOpStatement.h"
#include "valueNode.h"
#include <vector>
#include <map>
#include <set>
#include <string>

#include <iostream>
using namespace std;


class Parser {
public:
    Parser(TokenList * tokens) : tokens(tokens), index(1) {}

    StatementNode * head = nullptr;
    StatementNode * tail = nullptr;
    StatementNode * goToTail = nullptr;

    void parse() {
        //printTokenList();
        variables();
        initalizeValueMap();
        //printValueMap();
        
        expect(LeftBRACE);
        while (index < tokens->GetNumberOfTokens()) {
            statement();
        }
        expect(RightBRACE);
    }

private:
    TokenList * tokens;
    size_t index;
    map<string, ValueNode*> valueNodeMap;
    vector<string> currentIdList;

    void initalizeValueMap(){
        for (const auto& varName : currentIdList) {
            valueNodeMap[varName] = new ValueNode();
        }
    }

    void printLinkedList(){
        auto nod = head;
        while(nod != nullptr){
            cout << nod->GetType() <<endl;
            nod = nod->GetNextStatement();
        }
        cout << "\n\n\n";
    }

    void printValueMap(){
        for(auto val : valueNodeMap){
            cout << val.first << endl;
        }
    }

    void printTokenList(){
        for(int i = 1; i <= tokens->GetNumberOfTokens(); ++i){
            cout << tokens->GetToken(i)->GetType() << " ";
            if(tokens->GetToken(i)->GetType() == ID){
                cout << tokens->GetToken(i)->GetString();
            }
            cout << endl;
        }
    }

    void variables() {
        idList();
        expect(SEMICOLON);
    }

    void idList() {
        expect(ID);
        currentIdList.push_back(tokens->GetToken(index-1)->GetString());

        while (tokens->GetToken(index)->GetType() == COMMA) {
            expect(COMMA);
            expect(ID);
            currentIdList.push_back(tokens->GetToken(index-1)->GetString());

        }
    }


    void addStatement(StatementNode* newStatement) {
        if (head == nullptr) {
            head = tail = newStatement;
        } else {
            StatementType tailType = tail->GetType();

            switch (tailType) {
                case STATEMENT_ASSIGN:
                    static_cast<AssignmentStatement*>(tail)->SetNextStatement(newStatement);
                    break;
                case STATEMENT_IF:
                    static_cast<IfStatement*>(tail)->SetNextStatement(newStatement);
                    break;
                case STATEMENT_GOTO:
                    static_cast<GotoStatement*>(tail)->SetNextStatement(newStatement);
                    break;
                case STATEMENT_PRINT:
                    static_cast<PrintStatement*>(tail)->SetNextStatement(newStatement);
                    break;
                case STATEMENT_NONE:
                    static_cast<NoOpStatement*>(tail)->SetNextStatement(newStatement);
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }

            tail = newStatement;
        }
    }



    void statement() {
        switch (tokens->GetToken(index)->GetType()) {
            case ID:
                assignStatement();
                break;
            case IF:
                ifStatement();
                break;
            case PRINT:
                printStatement();
                break;
            case SWITCH:
                switchStatement();
                break;
            case WHILE:
                whileStatement();
                break;
            default:
                cout << "ERROR in statement func" << endl;
                exit(0);
        }
    }

    void assignStatement() {

        string leftHandSideIndex = tokens->GetToken(index)->GetString();
        bool isExpression = false;
        int secondVal;
        ArithmeticType oper;
        expect(ID);
        expect(EQUAL);
        ValueNode * n;
        ValueNode * no;
        if (tokens->GetToken(index + 1)->GetType() == SEMICOLON) {
            n = primary();
        } else {
            n = primary();
            oper = op();
            no = primary();
            isExpression = true;
        }
        expect(SEMICOLON);


        AssignmentStatement* newAssign = new AssignmentStatement();
        newAssign->SetLeftHandSide(valueNodeMap[leftHandSideIndex]);
        if(!isExpression){
            newAssign->SetOperand(n, true);
            newAssign->SetOperator(OPERATOR_NONE);
        }
        else{
            newAssign->SetOperand(n, true);
            newAssign->SetOperand(no, false);
            newAssign->SetOperator(oper);
        }

        addStatement(newAssign);
    }



    void ifStatement() {
        IfStatement *ifStatement = new IfStatement();
        GotoStatement *isFalse = new GotoStatement();

        expect(IF);
        
        ValueNode *firstNode = primary();
        ComparatorType comp = relationalOperator();
        ValueNode *secondNode = primary();
        
        
        ifStatement->SetOperator(comp);
        ifStatement->SetOperand(true, firstNode);
        ifStatement->SetOperand(false, secondNode);
        addStatement(ifStatement);

        body();

        static_cast<IfStatement*>(ifStatement)->SetNextStatement(false, isFalse);
        addStatement(isFalse);
        //printLinkedList();
    }

    void printStatement() {
        expect(PRINT);
        
        string s = tokens->GetToken(index)->GetString();
        expect(ID);
        expect(SEMICOLON);


        PrintStatement *print = new PrintStatement(valueNodeMap[s]);
        addStatement(print);
    }

    void switchStatement() {
        expect(SWITCH);
        ValueNode * firstVal = primary();
        expect(LeftBRACE);
        IfStatement * previous = nullptr;
        GotoStatement * endSwitch = new GotoStatement();
        vector<pair<StatementNode*, StatementNode*>> states;


        while (tokens->GetToken(index)->GetType() != DEFAULT && tokens->GetToken(index)->GetType() != RightBRACE) {
            if (tokens->GetToken(index)->GetType() == CASE) {
                
                expect(CASE);
                ValueNode * secondVal = primary();
                expect(COLON);

                IfStatement *ifStatement = new IfStatement();

                ifStatement->SetOperator(COMPARATOR_EQUAL);
                ifStatement->SetOperand(true, firstVal);
                ifStatement->SetOperand(false, secondVal);
                addStatement(ifStatement);

                if(previous == nullptr){
                    previous = ifStatement;
                }
                else{
                    previous->SetNextStatement(false, ifStatement);
                    previous = ifStatement;
                }
                body();

                GotoStatement *caseGoto = new GotoStatement();
                addStatement(caseGoto);
                states.push_back(make_pair(caseGoto, tail));                
                    
                
            } else {
                cout << "ERROR in switch func" << endl;
                exit(0);
            }
        }

        for (auto state : states) {
            StatementNode * caseGoto = state.first;
            StatementNode * tailNode = state.second;
            StatementType tailType = tailNode->GetType();

            switch (tailType) {
                case STATEMENT_ASSIGN:
                    static_cast<AssignmentStatement*>(tailNode)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_IF:
                    static_cast<IfStatement*>(tailNode)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_GOTO:
                    static_cast<GotoStatement*>(tailNode)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_PRINT:
                    static_cast<PrintStatement*>(tailNode)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_NONE:
                    static_cast<NoOpStatement*>(tailNode)->SetNextStatement(endSwitch);
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }

            tailType = caseGoto->GetType();

            switch (tailType) {
                case STATEMENT_ASSIGN:
                    static_cast<AssignmentStatement*>(caseGoto)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_IF:
                    static_cast<IfStatement*>(caseGoto)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_GOTO:
                    static_cast<GotoStatement*>(caseGoto)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_PRINT:
                    static_cast<PrintStatement*>(caseGoto)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_NONE:
                    static_cast<NoOpStatement*>(caseGoto)->SetNextStatement(endSwitch);
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }
        }

        StatementNode * prev = tail;

        if(tokens->GetToken(index)->GetType() == DEFAULT){
            expect(DEFAULT);
            expect(COLON);

            GotoStatement * defaul = new GotoStatement();
            previous->SetNextStatement(false, defaul);
            addStatement(defaul);

            body();

            StatementNode * defaultTail = tail;
            StatementType defaultTailType = defaultTail->GetType();

            switch (defaultTailType) {
                case STATEMENT_ASSIGN:
                    static_cast<AssignmentStatement*>(defaultTail)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_IF:
                    static_cast<IfStatement*>(defaultTail)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_GOTO:
                    static_cast<GotoStatement*>(defaultTail)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_PRINT:
                    static_cast<PrintStatement*>(defaultTail)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_NONE:
                    static_cast<NoOpStatement*>(defaultTail)->SetNextStatement(endSwitch);
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }
        }
        else{
            previous->SetNextStatement(false, endSwitch);
        }


        StatementType tt = prev->GetType();
            switch (tt) {
                case STATEMENT_ASSIGN:
                    static_cast<AssignmentStatement*>(prev)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_IF:
                    static_cast<IfStatement*>(prev)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_GOTO:
                    static_cast<GotoStatement*>(prev)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_PRINT:
                    static_cast<PrintStatement*>(prev)->SetNextStatement(endSwitch);
                    break;
                case STATEMENT_NONE:
                    static_cast<NoOpStatement*>(prev)->SetNextStatement(endSwitch);
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }
        addStatement(endSwitch);
        expect(RightBRACE);
    }

    

        void whileStatement() {
            IfStatement *ifStatement = new IfStatement();
            GotoStatement *isFalse = new GotoStatement();
            GotoStatement *isTrue = new GotoStatement();

            expect(WHILE);
            ValueNode *firstNode = primary();
            ComparatorType comp = relationalOperator();
            ValueNode *secondNode = primary();
            
            
            ifStatement->SetOperator(comp);
            ifStatement->SetOperand(true, firstNode);
            ifStatement->SetOperand(false, secondNode);
            addStatement(ifStatement);

            body();
            addStatement(isTrue); 
            
            static_cast<IfStatement*>(ifStatement)->SetNextStatement(false, isFalse);               
            addStatement(isFalse);
            isTrue->SetNextStatement(ifStatement);

        }

    void conditional() {
        primary();
        relationalOperator();
        primary();
    }

    ValueNode * primary() {
        string s;
        if (tokens->GetToken(index)->GetType() == ID || tokens->GetToken(index)->GetType() == NUM) {
            s = tokens->GetToken(index)->GetString();
            index++;
        } else {
            cout << "ERROR in primary func" << endl;
            exit(0);
        }
        if(tokens->GetToken(index - 1)->GetType() == NUM){
            ValueNode * n = new ValueNode(stoi(s));
            return n;
        }
        else{
            return valueNodeMap[s];
        }
    }

    ArithmeticType op() {
        ArithmeticType op = OPERATOR_NONE;
        switch (tokens->GetToken(index)->GetType()) {
            case PLUS:
                op = OPERATOR_ADD;
                index++;
                break;
            case MINUS:
                op = OPERATOR_SUBTRACT;
                index++;
                break;
            case MULT:
                op = OPERATOR_MULTIPLY;
                index++;
                break;
            case DIV:
                op = OPERATOR_DIVIDE;
                index++;
                break;
            default:
                cout << "ERROR in op func" << endl;
                exit(0);
        }
        return op;
    }

    ComparatorType relationalOperator() {
        ComparatorType comp = NO_COMPARATOR;
        switch (tokens->GetToken(index)->GetType()) {
            case GREATER:
                index++;
                comp = COMPARATOR_GREATER_THAN;
                break;
            case LESS:
                comp = COMPARATOR_LESS_THAN;
                index++;
                break;
            case NotEQUAL:
                comp = COMPARATOR_NOT_EQUAL;
                index++;
                break;
            default:
                cout << "ERROR in relational operator func" << endl;
                exit(0);
        }
        return comp;
    }

    int body() {
        expect(LeftBRACE);
        int i = 0;
        while (tokens->GetToken(index)->GetType() != RightBRACE) {
            statement();
            ++i;
        }
        expect(RightBRACE);
        return i;
    }

    void caseStatement() {
        expect(CASE);
        expect(NUM);
        expect(COLON);
        body();
    }

    void defaultCase() {
        expect(DEFAULT);
        expect(COLON);
        body();
    }

    void expect(TokenType type) {
        //cout << type << " " << tokens->GetToken(index)->GetType() << endl;
        if (tokens->GetToken(index)->GetType() == type) {
            index++;
        } else {
            cout << "ERROR unexpected token" << endl;
            exit(0);
        }
}

};

void printLL(StatementNode * head){
    StatementNode * curent = head;
    while(curent != nullptr){
            StatementType tailType = curent->GetType();

            switch (tailType) {
                case STATEMENT_ASSIGN:
                    cout << "Assignement\n";
                    break;
                case STATEMENT_IF:
                    cout << "IF\n";
                    curent = static_cast<IfStatement*>(curent)->GetNextStatement(false);
                    break;
                case STATEMENT_GOTO:
                    cout << "GoTo\n";
                    break;
                case STATEMENT_PRINT:
                    cout << "Print\n";
                    break;
                case STATEMENT_NONE:
                    cout << "none\n";
                    break;
                default:
                    cout << "error in add statment";
                    exit(0);
            }
        curent = curent->GetNextStatement();
    }
}

StatementNode* parseGenerateIntermediateRepresentation(char *fileName){
    ProgramFile p;
	TokenList *tokenList;
	tokenList = p.LoadFile(fileName);

	if(tokenList == NULL){
		cout << "TOKENIZER ERROR";
		exit(0);
	}
   // printTokenList(tokenList);
    Parser * par = new Parser(tokenList);
    par->parse();
    //printLL(par->head);
    return par->head;
}


