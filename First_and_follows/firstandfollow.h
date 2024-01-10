
#ifndef FIRSTANDFOLLOW_H

#define FIRSTANDFOLLOW_H
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;


vector<string> remove_duplicates(vector<string> input);

vector<string> unionVecs(vector<string> vec1, vector<string> vec2);

bool searchForString(vector<string> vec, string str);

string generateFirstSet(string nonTerm, vector<vector<string>> grammer);

unordered_set<string> generateFirstSetsforfollowsets(string nonTerm, vector<vector<string>> grammer);

unordered_set<string> generateFollowSet(string nonTerm, vector<vector<string>> grammer, unordered_set<string>& visited);


#endif