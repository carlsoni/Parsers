#include "program1.h"
#include "firstandfollow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> 
#include <cstring>


using namespace std;

vector<vector<string>> grammerFinalized;

struct Rule {
    string left;             
    vector<string> right; 
};


// Loads the grammar.
void LoadGrammar(char *grammarFileName) {
	
	vector<string> grammerByLine;
	ifstream file(grammarFileName);
	string line;
	unordered_set<string> curow;

	if (!file.is_open()) {
    	//cout << "Error: File " << grammarFileName << " does not exist." << endl;
    	return;
  	}

	while (getline(file, line)) {
    	grammerByLine.push_back(line);
  	}

	file.close();

	vector<string> row;
	bool row1 = true;
    for (string str : grammerByLine) {

        istringstream iss(str);
        string token;
		string previous;
        while (iss >> token) {
			if (token == "@" || token == "@@") {
            	grammerFinalized.push_back(row);
            	row.clear();
				curow.clear();
				previous = token;
				row1 = false;
        	}else if(token == "->"){
				if(previous == "->" || row1){
					grammerFinalized.clear();
					return;
				}
				previous = token;
			}
			else if(curow.count("#") > 0 && curow.size() > 2){
				grammerFinalized.clear();
				return;
			}
			else{
				previous = token;
				curow.insert(token);
				row.push_back(token);
			}
         
        }
    }


	unordered_set<string> uunt;
	unordered_set<string> gram;
	for(const auto& str : grammerFinalized[0]){
		uunt.insert(str);
	}

	for(const auto& row : grammerFinalized){
		for(const auto& str : row){
			gram.insert(str);
		}
	}
	
	if(gram.count("##") > 0){
		grammerFinalized.clear();
		return;
	}

	if(uunt.count("#") > 0 || uunt.count("##") > 0 ){
		grammerFinalized.clear();
		return;
	}
}



// Returns a string with some statistics for the grammar.
char* GetStats() {

	int m = grammerFinalized.size();
	int n = grammerFinalized[0].size();
	int nonTerminalCount[n];


	//cout << m << "  " << n << endl;

	for(int j = 0; j < n; ++j){

		nonTerminalCount[j] = 0;

		for (int i = 1; i < m - 1; ++i) {

			if(grammerFinalized[0][j] == grammerFinalized[i][0]){
				nonTerminalCount[j]++;
			} 
    	}

	}


	unordered_set<string> uut;		//unique unorderd terminals
	unordered_set<string> uunt;		//unique unorderd non terminals

	vector<string> ut;		//unique terminals
	vector<string> unt;		//unique non terminals

    
    for (const auto& str : grammerFinalized[0]) {
    	if (uunt.count(str) == 0) {
    		uunt.insert(str);
			unt.push_back(str);
      	}
    }

	for (const auto& sub_vector : grammerFinalized) {
    	for (const auto& str : sub_vector) {
    		if (uut.count(str) == 0 && uunt.count(str) == 0) {
        		uut.insert(str);
				ut.push_back(str);
      		}
    	}
  	}

	sort(ut.begin(), ut.end());
	

	int terminalCount[ut.size()];	

	for(int i = 0; i < ut.size(); i++){
		terminalCount[i] = 0;
		for(const auto& subvect: grammerFinalized){
			for(const auto& str : subvect){
				if(ut[i] == str){
					terminalCount[i]++;
				}
			}
			
		}
	}
	
	//cout << "Output for the sample grammar\n\n"; 
	//cout << "Returned from GetStats: " << endl;
	string str = "";

	for(int i = 0; i < unt.size(); i++){
		if(i < unt.size() -1){
			//cout << unt[i] << " - " << nonTerminalCount[i] << ", ";
			str += unt[i] + " - " + to_string(nonTerminalCount[i]) + ", ";
			
		}
		else{
			//cout << unt[i] << " - " << nonTerminalCount[i] << endl;
			str += unt[i] + " - " + to_string(nonTerminalCount[i]);
		}
	}
	str += "\n";


	for(int i = 0; i < ut.size(); i++){
		if(i < ut.size() - 1){
			//cout << ut[i] << " - " << terminalCount[i] << ", ";
			str += ut[i] + " - " + to_string(terminalCount[i]) + ", ";
		}
		else{
			//cout << ut[i] << " - " << terminalCount[i] << endl;
			str += ut[i] + " - " + to_string(terminalCount[i]);
		}
	}
	str += "\n";

	//cout << str ;
	char* strs = new char[str.size() + 1];
	

	strcpy(strs, str.c_str());
	

	return strs;
}

// Returns the first sets of all nonterminals.
char* GetFirstSets() {
	vector<string> firstSets;
	
	for(const auto& str : grammerFinalized[0]){
		char* strs = new char[str.size() + 1];
		strcpy(strs, str.c_str());
		char* firstSet = GetFirstSet(strs);
		firstSets.push_back(firstSet);
	}

	string fs = "";
	if(firstSets.size() < 2){
		fs += firstSets[0];
	}
	else{
		for(int i = 0; i < grammerFinalized[0].size(); ++i){
			fs += firstSets[i] + "\n";
		}		
	}


	//cout << fs;
	char* fsc = new char[fs.size() + 1];
	strcpy(fsc, fs.c_str());

	return fsc;
}



// Returns the first set of the specified nonterminal.
char* GetFirstSet(char *nonTerminal) {
	
	string nonTerm(nonTerminal);
	string fs = generateFirstSet(nonTerm, grammerFinalized);
	

	if(fs == ""){
		return "";
	}
	string fs1 = "";

	fs1 += "FIRST(" + nonTerm + ") = { " + fs + " }";
	
	char* fsc = new char[fs1.size() + 1];
	strcpy(fsc, fs1.c_str());

	return fsc;
}


// Returns the follow sets of all nonterminals.
char* GetFollowSets() {
	vector<string> followtSets;
	unordered_set<string> done;	

	for(const auto& str : grammerFinalized[0]){


		char* strs = new char[str.size() + 1];
		strcpy(strs, str.c_str());


		if(done.count(str) == 0){
			done.insert(str);
			char* followtSet = GetFollowSet(strs);
			followtSets.push_back(followtSet);	
		}
	}

	string fs = "";

	if(followtSets.size() > 1){
		for(int i = 0; i < grammerFinalized[0].size(); ++i){
			fs += followtSets[i] + "\n";
		}	
	}else{
		fs += followtSets[0];
	}


	//cout << fs;
	char* fsc = new char[fs.size() + 1];
	strcpy(fsc, fs.c_str());

	return fsc;
}

// Returns the follow set of the specified nonterminal.
char* GetFollowSet(char *nonTerminal) {
	unordered_set<string> visted;
	string nonTerm(nonTerminal);

	unordered_set<string> nonterms;
	for(const auto& str : grammerFinalized[0]){
		nonterms.insert(str);
	}

	if(nonterms.count(nonTerm) < 1){
		return "";
	}

	unordered_set<string> fs = generateFollowSet(nonTerm, grammerFinalized, visted);

	vector<string> temp1(fs.begin(), fs.end());
	sort(temp1.begin(), temp1.end());


	

	string fs1 = "";

	fs1 += "FOLLOW(" + nonTerm + ") = {" ;
	int i = 0;
	for(const auto& str : temp1){
		if(str == ""){
			++i;
		}
		else if(i < temp1.size() - 1){
			fs1 += " " + str + ",";
			++i;
		}
		else{
			fs1 += " " + str;
			++i;
		}
		
	}
	fs1 += " }";
	char* fsc = new char[fs1.size() + 1];
	strcpy(fsc, fs1.c_str());

	return fsc;
}
