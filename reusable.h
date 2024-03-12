using namespace std;
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
bool is_function1(string a){
    vector<string> functions = {"sin", "cos", "sqrt", "asin", "acos", "tan", "atan", "pow"};
    for(int i=0;i<functions.size();i++){
        if(a==functions[i]){
            return true;
        }
    }
    return false;
}
int precedence(string i){
    if(i=="+" || i=="+") return 1;
    if(i=="*" || i=="/") return 2;
    if (is_function1(i) || i=="(") return 0;
}
