#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>

using std::string;
using std::stack;
using std::unordered_map;
using std::endl;
using std::cout;

class Solution
{

public:
    bool isValid(string s){
        int n =s.size();
        if(n % 2 == 1){
            return false;
        }

        unordered_map<char,char> pairs =
        {
            {')','('},
            {']','['},
            {'}','{'}
        };

        stack<char> stk;
        for(char ch: s){//先让左括号入栈，再与右括号匹配
            if(pairs.count(ch)){
                if(stk.empty() || stk.top() != pairs[ch]){
                    return false;
                }            
                stk.pop();
            }
            else{
                stk.push(ch);
            }
        }
        return stk.empty();
    }

};

int main(void)
{   string s1("{()}");
    string s2(" ");
    string s3("[(]");
    string s4("{}()[]");
    Solution test;
    cout << test.isValid(s1) << endl;
    cout << test.isValid(s2) << endl;
    cout << test.isValid(s3) << endl;
    cout << test.isValid(s4) << endl;
    return 0;
}












