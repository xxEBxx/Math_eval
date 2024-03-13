#include "4functions.h"
using namespace std;

double string_to_double(string s){
    return stod(s);
}
int string_to_int(string s){
    return stoi(s);
}
string int_to_string(int n){
    return to_string(n);
}
string double_to_string(double x){
    return to_string(x);
}
bool is_double(string a){
    for(int i=0;i<a.size();i++){
        if(a[i]=='.')return true;
    }
    return false;
}
string calculate(vector<string> arr) {
    //this function take the vector and calculates the result
    stack<string> s;
    int n=arr.size(),i=0;
    while(i<n){
        if(isdigit(arr[i][0])){
            s.push(arr[i]);
            //cout<<arr[i]<<"nmra d5lat"<<endl;
        }
        else{
            //arr[i] is an operation hihi
            double res;
            if(is_operator(arr[i][0]) || arr[i]=="pow"){
                string num1,num2;
                num1=s.top();
                s.pop();
                num2=s.top();
                s.pop();
                double value1= string_to_double(num1),value2=string_to_double(num2);
                if(arr[i][0]=='+'){
                    res=value2+value1;
                }
                else if(arr[i][0]=='-'){
                    res=value2-value1;
                }
                else if(arr[i][0]=='*'){
                    res=value2*value1;
                }
                else if(arr[i][0]=='/'){
                    if(value1==0){
                        throw MyError("Your expression contains a division by 0");
                    }
                    res=value2/value1;
                }
                else{
                    //for pow
                    res=to_pow(value2,value1);
                }
                s.push(double_to_string(res));
            }
            else{
                string num;
                num=s.top();
                s.pop();
                double value= string_to_double(num);
                if (arr[i]=="sin"){
                    res=to_sin(value);
                }
                else if(arr[i]=="cos"){
                    res= to_cos(value);
                }
                else if(arr[i]=="tan"){
                    res= to_tan(value);
                }
                else if(arr[i]=="acos"){
                    res= to_acos(value);
                }
                else if(arr[i]=="asin"){
                    res= to_asin(value);
                }
                else if(arr[i]=="atan"){
                    res= to_atan(value);
                }
                else if(arr[i]=="sqrt"){
                    res= to_sqrt(value);
                }
                s.push(double_to_string(res));
            }

        }
        i++;
}
return s.top();
}