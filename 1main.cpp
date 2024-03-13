#include<bits/stdc++.h>
#include "3calculate.h"

using namespace std;


int main() {
    try {
        string expression;
        cout << "Enter your expression: ";
        getline(cin, expression);

        vector<string> tokens= tokenize(expression);
        /*for(int i=0;i<tokens.size();i++){
            cout <<tokens[i]<<" ";
        }*/
        string result = parse_syntax(tokens);
        /*
        cout<<endl;
        cout << "Syntax check passed. Result: " << result << endl;*/
        vector<string> postfix= to_postfix(tokens);
        /*for(string x:postfix){
            cout<<x<<" ";
        }*/
        cout<<endl;
        string res=calculate(postfix);
        cout<<"Here is the result : "<<res<<endl;
    } catch (const MyError& e) {
        std::cerr << "Error: " << e.message << std::endl;
        return 1; // Return a non-zero value to indicate failure
    }
    return 0;
}