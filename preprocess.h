#include<vector>
#include<string>
#include<algorithm>
#include<stack>

#include "reusable.h"
using namespace std;

class MyError {
public:
    std::string message;
    MyError(const std::string& msg) : message(msg) {}
};

vector<string> tokenize(string s){
    vector<string> tokens;
    int n=s.size();
    int i=0;
    while(i<n){
        if(isspace(s[i])){
            i++;
        }
        else if(isdigit(s[i]) || s[i]=='.'){
            string num;
            while (i<n && (isdigit(s[i]) || s[i]=='.')){
                num+=s[i];
                i++;
            }
            tokens.push_back(num);
        }
        else if(isalpha(s[i])){
            string word;
            while(i<n && isalpha(s[i])){
                word+=s[i];
                i++;
            }
            tokens.push_back(word);
        }
        else{
            //operators, single parenthesis,commas(for pow)
            tokens.push_back(string(1,s[i]));
            i++;
        }
    }
    return tokens;
}

string parse_syntax(vector<string>& tokens) {
    int n = tokens.size();
    if(is_operator(tokens[0][0])){
        throw MyError("Can't start with operator :( ");
    }
    if(is_operator(tokens[n-1][0])){
        throw MyError("Can't end with operator :( ");
    }
    stack<char> parenthesis;
    for (int i = 0; i < n; i++) {
        if (tokens[i] == "(") {
            parenthesis.push('(');
        } else if (tokens[i] == ")") {
            if (parenthesis.empty()) {
                throw MyError("Syntax ERROR: Unmatched parenthesis");
            } else {
                parenthesis.pop();
            }
        } else if (tokens[i].size() > 1) { // numbers and functions
            if (isalpha(tokens[i][0])) {
                if (! is_function1(tokens[i])) {
                    throw MyError("ERROR: Unknown function used (" + tokens[i] + ")");
                }
                if (i == n - 1 || tokens[i + 1] != "(") {
                    throw MyError("Syntax ERROR: Use \"(\" after functions");
                }
            } else {
                if (tokens[i][0] == '.') {
                    tokens[i].insert(0,"0");
                }
                if (count(tokens[i].begin(), tokens[i].end(), '.') > 1) {
                    throw MyError("Syntax ERROR: Invalid number " + tokens[i]);
                }
                if (i != n - 1 && isdigit(tokens[i + 1][0])) {
                    throw MyError("Syntax ERROR: Two successive numbers " + tokens[i] + " " + tokens[i + 1]);
                }
            }
        } else if (tokens[i].size() == 1 && i < n - 1 && tokens[i + 1].size() == 1) {
            if (is_operator(tokens[i][0]) && is_operator(tokens[i + 1][0])) {
                throw MyError("Syntax ERROR: Two successive operators: " + tokens[i] + " " + tokens[i + 1]);
            }
        }
    }
    if (!parenthesis.empty()) {
        throw MyError("Unbalanced parenthesis");
    }
    return "OK";
}
