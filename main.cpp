#include<bits/stdc++.h>
#include "preprocess.h"

using namespace std;

string to_postfix(const std::vector<std::string>& tokens) {
    string postfix = "";
    stack<string> s;

    for (const std::string& token : tokens) {
        if (isdigit(token[0])) {
            postfix += token + " ";
        }
        else if (is_operator(token[0])) {
            while (!s.empty() && precedence(token) <= precedence(s.top())) {
                postfix += s.top() + " ";
                s.pop();
            }
            s.push(token);
        }
        else if (token[0] == '(') {
            s.push("(");
        }
        else if (token[0] == ')') {
            while (!s.empty() && s.top()[0] != '(') {
                postfix += s.top() + " ";
                s.pop();
            }
            if (!s.empty() && s.top()[0] == '(') {
                s.pop(); // Discard the left parenthesis
            }
            if (!s.empty() && is_function1(s.top())) {
                postfix += s.top() + " ";
                s.pop();
            }
        }
        else if (is_function1(token)) {
            s.push(token);
        }
        else {
            postfix += token + " ";
        }
    }

    while (!s.empty()) {
        postfix += s.top() + " ";
        s.pop();
    }
    for(int i=0;i<postfix.size();i++){
        if(postfix[i]==','){
            postfix.erase(i,2);
        }
    }
    return postfix;
}


int main() {
    try {
        string expression;
        cout << "Enter your expression: ";
        getline(cin, expression);

        vector<string> tokens= tokenize(expression);

        string result = parse_syntax(tokens);
        cout << "Syntax check passed. Result: " << result << endl;
        cout<<to_postfix(tokens)<<endl;
    } catch (const MyError& e) {
        std::cerr << "Error: " << e.message << std::endl;
        return 1; // Return a non-zero value to indicate failure
    }
    return 0;
}