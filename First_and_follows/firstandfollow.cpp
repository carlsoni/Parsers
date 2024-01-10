#include "firstandfollow.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>
using namespace std;



vector<string> remove_duplicates(vector<string> input) {
    unordered_set<string> unique_strings;
    vector<string> result;
    
    
    for (const auto& str : input) {
        if (unique_strings.count(str) == 0) {
            result.push_back(str);
            unique_strings.insert(str);
        }
    }
    
    return result;
}


vector<string> unionVecs(vector<string> vec1, vector<string> vec2){
	vector<string> result = vec1;

    for (const auto& elem : vec2) {
        if (find(result.begin(), result.end(), elem) == result.end()) {
            result.push_back(elem);
        }
    }

    return result;
}


string generateFirstSet(string nonTerm, vector<vector<string>> grammer){
    unordered_set<string> uunt;
    vector<string> firstSet;
	bool setwoEp = false;


	for(const auto& str : grammer[0]){
		uunt.insert(str);
	}

	if(uunt.count(nonTerm) == 0){
		return "";
	}

	bool notfirstit = false;
	for(const auto& row : grammer){
		if(!row.empty()){
			if(notfirstit){
				
				if(nonTerm == row[0]){
					if(uunt.count(row[1]) == 0){
						firstSet.push_back(row[1]);
					}else{
						for(int i = 1; i < row.size(); i++){

							unordered_set<string> firs = generateFirstSetsforfollowsets(row[i], grammer);
							vector<string> tmp(firs.begin(), firs.end());

							if(firs.count("#") > 0){
								firstSet = unionVecs(firstSet, tmp);
							}
							else{
								firstSet = unionVecs(firstSet, tmp);
								setwoEp = true;
								break;
							}
							
						}
						
					}
				}
			}else{
				notfirstit = true;
			}	
		}

	}
	


	firstSet = remove_duplicates(firstSet);
	if(setwoEp){
		firstSet.erase(remove(firstSet.begin(), firstSet.end(), "#"), firstSet.end());
	}

	sort(firstSet.begin(), firstSet.end());

	string fs = "";
	for(int i = 0; i < firstSet.size(); ++i){
		if(i < firstSet.size() - 1){
			fs += firstSet[i] + ", ";
		}
		else{
			fs += firstSet[i];
		}
	}

    return fs;   
}


unordered_set<string> generateFirstSetsforfollowsets(string nonTerm, vector<vector<string>> grammer){
	string fs = generateFirstSet(nonTerm, grammer);
	unordered_set<string> firstSet;
	    
	stringstream ss(fs);
	string item;
    while (getline(ss, item, ',')) {
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        if (!item.empty()) { 
            firstSet.insert(item);
        }
    }
	vector<string> temporay(firstSet.begin(), firstSet.end());
	sort(temporay.begin(), temporay.end());
	firstSet.clear();

	for (const auto& elem : temporay) {
        firstSet.insert(elem);
    }
        return firstSet;
    }



unordered_set<string> generateFollowSet(string nonTerm, vector<vector<string>> grammer, unordered_set<string>& visited){
        unordered_set<string> uunt;
        string epsilon = "#";
        char epsil = '#';
		string eofsym = "##";

        vector<unordered_set<string>> firstSets;
        unordered_set<string> followSet;

	    for(const auto& str : grammer[0]){
		    uunt.insert(str);
	    }
	    bool notfirstit = false;

		if (nonTerm == grammer[0][0]) {
        	followSet.insert("##");
    	}

		for (const auto& production : grammer) {
			if(notfirstit){
				for (size_t i = 1; i < production.size(); ++i) {
            		if (production[i] == nonTerm) {
						if (i == production.size() - 1) {
							if (visited.count(production[0]) == 0) {
                        		visited.insert(production[0]);
                        		auto follow = generateFollowSet(production[0], grammer, visited);
                        		followSet.insert(follow.begin(), follow.end());
                    		}
						}
						else if(uunt.count(production[i+1]) <= 0){
							followSet.insert(production[i+1]);
						}
						else{
							auto first = generateFirstSetsforfollowsets(production[i+1], grammer);

							if(first.count("#") > 0) {
								
								if(visited.count(production[0]) == 0){
									visited.insert(production[0]);
									auto follow = generateFollowSet(production[0], grammer, visited);
									followSet.insert(follow.begin(), follow.end());
								}
								first.erase("#");
							}
							followSet.insert(first.begin(), first.end());
						}
					}
				}	
			}
			else{
				notfirstit = true;
			}
		}

	return followSet;

}
