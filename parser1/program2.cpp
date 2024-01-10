

#include <stdio.h>

#include "program2.h"
#include "programFile.h"
#include "funky.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

void printsyn(vector<syntaxandType> syn){
	for(auto row : syn){
		cout << row.name << " :	" << row.type << " : " << row.t << endl;
	}
}

struct stringandtype{
	string type;
	string snip;
};

struct codeandLineNum{
	string snip;
	int lineNum;
	string tt = "";
};

vector<syntaxandType> syntax;
vector<tsandvs> types;
vector<tsandvs> vars;
vector<stringandtype> helper3;
// Loads the program.
void LoadProgram(char *programFileName) {
	ProgramFile program;	// Current program
	TokenList *tokenList;	// List of tokens

	tokenList = program.LoadFile(programFileName);
	int varLinenum = 0;

	if(tokenList == NULL){
		cout << "TOKENIZER ERROR";
		return;
	}


	syntaxandType temp1;
	TokenType tp;

	tsandvs temp;
	multiset<string> code;
	vector<codeandLineNum> codeVec;

	multiset<string> s;
	vector<string> o;
	bool inTypes = false;
	bool inVars = false;
	bool inCode = false;
	bool outCode = false;
	bool colon = false;
	int bracount = 0;

	for(int i = 1; i <= tokenList->GetNumberOfTokens(); ++i){

		Token * t = tokenList->GetToken(i);

		codeandLineNum cl;
		cl.lineNum = t->GetLineNumber();
		temp1.lineNum = t->GetLineNumber();
		cl.snip = "";
		cl.tt = "";
		temp1.t = t->GetType();
		switch (t->GetType())
		{
		case TYPE:
			temp1.name = "TYPE";
			syntax.push_back(temp1);
			temp1.name = "";
		
			inTypes = true;
			inVars = false;
			inCode = false;
			outCode = false;
			break;
		case VAR:
			temp1.name = "VAR";
			syntax.push_back(temp1);
			temp1.name = "";

			varLinenum = t->GetLineNumber() - 1;
			inTypes = false;
			inVars = true;
			inCode = false;
			outCode = false;
			break;
		case LeftBRACE:
			temp1.name = "{";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("{");
				cl.snip = "{";
				codeVec.push_back(cl);
				++bracount;
			}
			else{
				inTypes = false;
				inVars = false;
				inCode = true;
				outCode = false;
			}
			break;
		case RightBRACE:
			temp1.name = "}";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode && bracount == 0){
				inTypes = false;
				inVars = false;
				inCode = false;
				outCode = true;
			}
			else if(inCode){
				--bracount;
				code.insert("}");
				cl.snip = "}";
				codeVec.push_back(cl);

			}
			break;
		case COLON:
			temp1.name = ":";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inTypes || inVars){
				colon = true;
			}
			if(inCode){
				code.insert(":");
				cl.snip = ":";
				codeVec.push_back(cl);

			}
			break;
		case SEMICOLON:
			temp1.name = ";";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inTypes || inVars){
				colon = false;
			}
			if(inCode){
				code.insert(";");
				cl.snip = ";";
				codeVec.push_back(cl);

			}
			break;
		case ID:
		case INT:
		case BOOLEAN:
		case REAL:
		case LONG:
		case STRING:
			temp1.name = t->GetString();
			syntax.push_back(temp1);
			temp1.name = "";
			if(inTypes){
				if(colon){
					temp.names = s;
					temp.ordered = o;
					temp.identfier = t->GetString();
					types.push_back(temp);
					temp.identfier = "";
					temp.ordered.clear();
					temp.names.clear();
					s.clear();
					o.clear();
				}
				else{
					s.insert(t->GetString());
					o.push_back(t->GetString());
				}
			}
			else if(inVars){
				if(colon){
					temp.names = s;
					temp.ordered = o;
					temp.identfier = t->GetString();
					vars.push_back(temp);
					temp.identfier = "";
					temp.names.clear();
					temp.ordered.clear();
					s.clear();
					o.clear();
				}
				else{
					s.insert(t->GetString());
					o.push_back(t->GetString());
				}
			}
			else if(inCode){
				code.insert(t->GetString());
				cl.snip = t->GetString();
				codeVec.push_back(cl);

			}
			break;
		case WHILE:
			temp1.name = "WHILE";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("WHILE");
				cl.snip = "WHILE";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case DO:
			temp1.name = "DO";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("DO");
				cl.snip = "DO";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case COMMA:
			temp1.name = ",";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert(",");
				cl.snip = ",";
				codeVec.push_back(cl);
			}
			break;
		case EQUAL:
			temp1.name = "=";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("=");
				cl.snip = "=";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case PLUS:
			temp1.name = "+";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("+");
				cl.snip = "+";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			} 
			break;
		case MINUS:
			temp1.name = "-";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("-");
				cl.snip = "-";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case MULT:
			temp1.name = "*";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("*");
				cl.snip = "*";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case DIV:
			temp1.name = "/";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("/");
				cl.snip = "/";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case LeftPAREN:
			temp1.name = "(";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("(");
				cl.snip = "(";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case RightPAREN:
			temp1.name = ")";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert(")");
				cl.snip = ")";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case GREATER:
			temp1.name = ">";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert(">");
				cl.snip = ">";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case GtEQ:
			temp1.name = ">=";
			syntax.push_back(temp1);
			temp1.name = "";
			if(inCode){
				code.insert(">=");
				cl.snip = ">=";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case LESS:
			temp1.name = "<";
			syntax.push_back(temp1);
			temp1.name = "";
			if(inCode){
				code.insert("<");
				cl.snip = "<";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case LtEQ:
			temp1.name = "<=";
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert("<=");
				cl.snip = "<=";
				codeVec.push_back(cl);

			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case NotEQUAL:
			temp1.name = "!=";
			syntax.push_back(temp1);
			temp1.name = "";
			if(inCode){
				code.insert("!=");
				cl.snip = "!=";
				codeVec.push_back(cl);
			}
			else{
				cout << "SYNTAX ERROR";
				exit(0);
			}
			break;
		case NUM:
			temp1.name = t->GetString();
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert(t->GetString());
				cl.snip = t->GetString();
				cl.tt = "INT";
				codeVec.push_back(cl);
				cl.tt = "";
			}

			break;

		case RealNUM:
			temp1.name = t->GetString();
			syntax.push_back(temp1);
			temp1.name = "";

			if(inCode){
				code.insert(t->GetString());
				cl.snip = t->GetString();
				cl.tt = "REAL";
				codeVec.push_back(cl);
				cl.tt = "";
			}
			break;

		default:
			if(inCode){

			}
			break;
		}
	
	}


	if(code.size() == 0){
		cout << "SYNTAX ERROR";
		exit(0);
	}

	for(auto row : types){
		if(row.identfier == ""){
			cout << "SYNTAX ERROR";
			exit(0);
		}
	}

	for(auto row : vars){
		if(row.identfier == ""){
			cout << "SYNTAX ERROR";
			exit(0);
		}
	}

	
	vector<tsandvs> typesClone = types;
	vector<tsandvs> varsClone = vars;

	multiset<string> tse;

	for(auto row : types){
		for(auto str : row.names){
			tse.insert(str);
		}
	}

	multiset<string> vse;
	for(auto row : vars){
		for(auto str : row.names){
			vse.insert(str);
		}
	}


	for (int i = 0; i < types.size(); ++i) {
        if (types[i].identfier != "INT" && types[i].identfier != "BOOLEAN" && types[i].identfier != "REAL" && types[i].identfier != "LONG"&& types[i].identfier != "STRING" ) {
			string temp6 = resolveIdentifier(types, types[i].identfier);
			if(temp6 != ""){
				types[i].identfier = resolveIdentifier(types, types[i].identfier);
			}
        	
		}                   
    }    
    
	for(int i = 0; i < vars.size(); ++i){
		if(vars[i].identfier != "INT" && vars[i].identfier != "BOOLEAN" && vars[i].identfier != "REAL" && vars[i].identfier != "LONG"&& vars[i].identfier != "STRING" ){
			for(auto row : types){
				if(row.names.count(vars[i].identfier) > 0){
					vars[i].identfier = row.identfier;
				}
			}
		}
	}


	for(int i = 0; i < syntax.size(); ++i){
        if(syntax[i].t == ID){
            for(auto row : types){
                if(row.names.count(syntax[i].name) > 0){
                    syntax[i].type = row.identfier;
                }
            }
            for(auto row : vars){
                if(row.names.count(syntax[i].name) > 0){
                    syntax[i].type = row.identfier;
                }
            }
        }
    }


	//printsyn(syntax);

	checkSytax(syntax, typesClone, varsClone, tse, vse, code);


	for(int i = 0; i < codeVec.size(); ++i){
		for(auto row : vars){
			if(row.names.count(codeVec[i].snip) > 0){
				codeVec[i].tt = row.identfier;
			}
		}
	}


	// type mismatch loop



	for(int i = 0; i < codeVec.size(); ++i){
		if(codeVec[i].snip == "="){
			if(codeVec[i-1].tt != codeVec[i+1].tt || codeVec[i+1].tt == "" && codeVec[i+1].snip != "("){
				if(codeVec[i+1].tt == "INT" && codeVec[i-1].tt == "" ){
					codeVec[i-1].tt = "INT"; 
					tsandvs sf;
					sf.identfier = "INT";
					sf.ordered.push_back(codeVec[i-1].snip);
					vars.push_back(sf);
				}
				else if(codeVec[i-1].tt == "LONG" && (codeVec[i+1].tt == ""  || codeVec[i+1].tt == "TYPE")){
					codeVec[i+1].tt = "LONG"; 
					tsandvs sf;
					sf.identfier = "LONG";
					sf.ordered.push_back(codeVec[i+1].snip);
					vars.push_back(sf);
				}
				else if(codeVec[i-1].tt == "STRING" && (codeVec[i+1].tt == ""  || codeVec[i+1].tt == "TYPE")){

				}
				else{
					cout << "TYPE MISMATCH 1 " << codeVec[i].lineNum;
					exit(0);
				}
				
				
			}
		}
		else if(codeVec[i].snip == "+" || codeVec[i].snip == "-" || codeVec[i].snip == "/" || codeVec[i].snip == "*"){
			if(codeVec[i+1].tt == ""  || codeVec[i+1].tt == "TYPE" && (codeVec[i-1].tt == "STRING")){
					codeVec[i+1].tt = "STRING"; 
					tsandvs sf;
					sf.identfier = "STRING";
					sf.ordered.push_back(codeVec[i+1].snip);
					vars.push_back(sf);
			}
			if(codeVec[i-1].tt == ""  || codeVec[i-1].tt == "TYPE" && codeVec[i-1].snip != ")" && (codeVec[i+1].tt == "STRING")){
					codeVec[i-1].tt = "STRING"; 
					tsandvs sf;
					sf.identfier = "STRING";
					sf.ordered.push_back(codeVec[i-1].snip);
					vars.push_back(sf);
			}
			else if(codeVec[i-1].tt != codeVec[i+1].tt && codeVec[i+1].snip != "(" && codeVec[i+1].snip != ")" && codeVec[i-1].snip != "(" && codeVec[i-1].snip != ")"){
				cout << "TYPE MISMATCH 2 " << codeVec[i].lineNum;
				exit(0);
			}
		}
		else if(codeVec[i].snip == ">" || codeVec[i].snip == ">=" || codeVec[i].snip == "<" || codeVec[i].snip == "<="){
			if((codeVec[i-1].tt == "" ||  codeVec[i-1].tt == "TYPE") &&  (codeVec[i+1].tt != "" ||  codeVec[i+1].tt != "TYPE")){
				codeVec[i-1].tt = codeVec[i+1].tt;
				stringandtype stry;
				stry.type = codeVec[i-1].tt;
				stry.snip = codeVec[i-1].snip;
				helper3.push_back(stry);
			}
			else if((codeVec[i+1].tt == "" ||  codeVec[i+1].tt == "TYPE") && (codeVec[i-1].tt != "" ||  codeVec[i-1].tt != "TYPE")){
				codeVec[i+1].tt = codeVec[i-1].tt;
				stringandtype stry;
				stry.type = codeVec[i+1].tt;
				stry.snip = codeVec[i+1].snip;
				helper3.push_back(stry);
			}
			if(codeVec[i-1].tt != codeVec[i+1].tt || ((codeVec[i+1].tt == "" ||  codeVec[i+1].tt == "TYPE") && (codeVec[i-1].tt == "" ||  codeVec[i-1].tt == "TYPE"))){
				cout << "TYPE MISMATCH 3 " << codeVec[i].lineNum;
				exit(0);
			}
		}
		else if(codeVec[i].snip == "WHILE"){
			if(codeVec[i+1].tt == "" &&  codeVec[i+2].snip != ">" && codeVec[i+2].snip != ">=" && codeVec[i+2].snip != "<" && codeVec[i+2].snip != "<="){
				codeVec[i+1].tt = "BOOLEAN";
				stringandtype stry;
				stry.type = codeVec[i+1].tt;
				stry.snip = codeVec[i+1].snip;
				helper3.push_back(stry);
			}
			if(codeVec[i+1].tt != "BOOLEAN" && (codeVec[i+2].snip != ">" && codeVec[i+2].snip != ">=" && codeVec[i+2].snip != "<" && codeVec[i+2].snip != "<=")){
				cout << "TYPE MISMATCH 4 " << codeVec[i].lineNum;
				exit(0);
			}
		}
	}


	string boolset = "BOOLEAN ";
	string intset = "INT ";
	string longset = "LONG ";
	string realset = "REAL ";
	string stringset = "STRING ";
	string others = "";
	vector<string> otherTypes;
	multiset<string> temp3;
	tsandvs temp4;



	for(auto row : types){
		if(row.identfier == "BOOLEAN"){
			for(auto str : row.ordered){
				boolset += str + " "; 
			}
		}
		else if(row.identfier == "INT"){
			for(auto str : row.ordered){
				intset += str + " ";
			}
		}
		else if(row.identfier == "LONG"){
			for(auto str : row.ordered){
				longset += str + " ";
			}
		}
		else if(row.identfier == "REAL"){
			for(auto str : row.ordered){
				realset += str + " ";
			}
		}
		else if(row.identfier == "STRING"){
			for(auto str : row.ordered){
				stringset += str + " ";
			}
		}
		else{
			if(temp3.count(row.identfier) < 1){
				temp3.insert(row.identfier);
				otherTypes.push_back(row.identfier);
				for(auto str : row.ordered){
					if(temp3.count(str) < 1){
						temp3.insert(str);
						otherTypes.push_back(str);
					}	
				}
			}
		}
	}

	vector<tsandvs> other;


	for(auto row : helper3){
		for(int i = vars.size(); i >= 0; --i){
			if(vars[i].names.count(row.snip) < 1 && vars[i].identfier == row.type){
				vars[i].names.insert(row.snip);
				vars[i].ordered.push_back(row.snip);
				i = 0;
			}
		}
	}


	for(auto str : otherTypes){
		temp4.identfier = str;
		other.push_back(temp4);
	}

	vector<string> temp8;

	for(auto row : vars){
		if(row.identfier == "BOOLEAN"){
			for(auto str : row.ordered){
				boolset += str + " "; 
			}
		}
		else if(row.identfier == "INT"){
			for(auto str : row.ordered){
				intset += str + " ";
			}
		}
		else if(row.identfier == "LONG"){
			for(auto str : row.ordered){
				longset += str + " ";
			}
		}
		else if(row.identfier == "REAL"){
			for(auto str : row.ordered){
				realset += str + " ";
			}
		}
		else if(row.identfier == "STRING"){
			for(auto str : row.ordered){
				stringset += str + " ";
			}
		}
		else{
			for(int i = 0; i < other.size(); ++i){
				if(row.identfier == other[i].identfier){
					for(auto str : row.names){
						other[i].ordered.push_back(str);
					}
				}
			}
		}
	}

	multiset<string> helper1;
	for(auto row : other){
		helper1.insert(row.identfier);
	}
	for(auto row : types){
		helper1.insert(row.identfier);
	}
	for(auto row : vars){
		if(helper1.count(row.identfier) < 1 && (row.identfier != "INT" && row.identfier != "BOOLEAN" && row.identfier != "LONG" && row.identfier != "REAL" && row.identfier != "STRING")){
			helper1.insert(row.identfier);
			tsandvs fuuuuuck;
			fuuuuuck.identfier = row.identfier;
			for(auto str : row.ordered){
				fuuuuuck.ordered.push_back(str);
			}
			other.push_back(fuuuuuck);
		}
	}

/*
	multiset<string> helper;


	for(auto row : types){
		helper.insert(row.identfier);
		for(auto str : row.ordered){
			helper.insert(str);
		}
	}
	for(auto row : vars){
		helper.insert(row.identfier);
		for(auto str : row.ordered){
			helper.insert(str);
		}
	}
	for(auto str : syntax){
		if(str.t == ID){
			if(helper.count(str.name) > 1){
				helper.insert(str.name);
				tsandvs derp;
				derp.identfier = str.name;
				other.push_back(derp);
			}
		}
	}
	*/

	for(auto row : other){
		others += row.identfier + " ";

	}
	for(auto row : other){
		for(auto str : row.ordered){
			others +=  str + " ";
		}
	}



	if(others != ""){
		others += "#\n";
	}
	
	char ch = ')';
	int index = -1;
	index = stringset.find(ch);

	if(index > -1){
		stringset.erase(index, 2);
	}	

	boolset += "#\n";
	intset += "#\n";
	longset += "#\n";
	realset += "#\n";
	stringset += "#\n";

	cout << boolset << intset << longset << realset << stringset << others;


	//cout << "SYNTAX ERROR";
}


