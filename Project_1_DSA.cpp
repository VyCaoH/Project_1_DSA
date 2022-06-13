#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

bool isNum(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;
    return false;
}
int isBracket(char c)
{
    if (c == '(' || c == '{' || c == '[')
        return 1;
    if (c == '}' || c == ']' || c == ')')
        return 2;
    return 0;
}
bool isBalanced(string s)
{
    int cnt_operator = 0;
    int cnt_operand = 0;
    stack<char> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (isBracket(s[i]))
        {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                st.push(s[i]);
            }
            else
            {
                if (st.empty())
                    return false;
                char c = st.top();
                st.pop();
                if (s[i] == ')')
                {
                    if (c != '(')
                        return false;
                }
                else if (s[i] == '}')
                {
                    if (c != '{')
                        return false;
                }
                else
                {
                    if (c != '[')
                    {
                        return false;
                    }
                }
            }
        }
        else if (isNum(s[i]))
        {
            if (i - 1 >= 0)
            {
                if (!isNum(s[i - 1]) && s[i - 1] != '.')
                    cnt_operand++;
            }
            else
                cnt_operand++;
        }
        else if (isOperator(s[i]))
        {
            cnt_operator++;
        }
    }
    if (!st.empty() || (cnt_operator != cnt_operand - 1))
    {
        return false;
    }
    return true;
}
bool isValidSpace(string s)
{
    int n = s.length();
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ' && ((i + 1 < n && s[i + 1] == ' ') || (i - 1 >= 0 && s[i - 1] == ' ')))
        {
            return false;
        }
        int temp = isBracket(s[i]);
        if (temp)
        {
            if (temp == 2 && i + 1 < n && s[i + 1] != ' ')
            {
                return false;
            }
            if (temp == 1 && i - 1 >= 0 && s[i - 1] != ' ')
            {
                return false;
            }

        }
        if (isOperator(s[i]))
        {
            if (i + 1 < n && s[i + 1] != ' ')
            {
                return false;
            }
            if (i - 1 >= 0 && s[i - 1] != ' ')
            {
                return false;
            }
        }
    }
    return true;
}
bool checkString(string s)
{
    int len = s.length();
    if (s == "" || !isBalanced(s) || !isValidSpace(s))
    {
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        if (s[i] == '.')
        {
            if (i == len - 1 || !isNum(s[i + 1]))
                return false;
            for (int j = i + 1; j < len; j++)
            {
                if (!isNum(s[j]))
                    break;
                if (isNum(s[j]) && j == i + 3)
                    return false;
            }
        }
        else if (isOperator(s[i]))
        {
            if (i - 2 < 0 || i + 2 > len)
                return false;
            if ((!isNum(s[i - 2]) && !isBracket(s[i - 2]) && !isBracket(s[i + 2])) || isBracket(s[i - 2]) == 1 || isBracket(s[i + 2]) == 2)
                return false;
        }
    }
    return true;
}

void prepare(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            s.insert(s.begin() + i + 1, ' ');
        }
        else if (s[i] == ')')
        {
            s.insert(s.begin() + i, ' ');
            i++;
        }
    }
}
void printResult(vector<string> result)
{
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    /*/for (string i : result) {
        cout << i<< " ";
    }*/
}
double caculate(vector<string> s)
{
    stack < double > num;
    double tmp;
    double result = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != "+" && s[i] != "-" && s[i] != "*" && s[i] != "/" && s[i] != "^")
        {
            tmp = stof(s[i]);
            num.push(tmp);
        }
        else {
            double tmp1 = num.top();
            num.pop();
            double tmp2 = num.top();
            num.pop();
            if (s[i] == "+")
            {
                result = tmp1 + tmp2;
            }
            else if (s[i] == "-")
            {
                result = tmp2 - tmp1;
            }
            else if (s[i] == "*")
            {
                result = tmp2 * tmp1;
            }
            else if (s[i] == "/")
            {
                result = tmp2 / tmp1;
            }
            else if (s[i] == "^")
            {
                result = pow(tmp2, tmp1);
            }
            num.push(result);
        }
    }
    return num.top();
}

// Function to return precedence of operators
int prec(string c)
{
    if (c == "^")
        return 3;
    else if (c == "/" || c == "*")
        return 2;
    else if (c == "+" || c == "-")
        return 1;
    else
        return -1;
}

// The main function to convert infix expression
// to postfix expression
vector<string> infixToPostfix(string s)
{
    vector<string> vs;
    stringstream fi(s);

    string tmp;

    stack<string> st; // For stack operations, we are using
                   // C++ built in stack
    vector<string> result;

    while (fi >> tmp)
    {
        vs.push_back(tmp);
    }
    /*for (int i = 0; i < vs.size(); i++)
    {
        cout << vs[i] << endl;
    }*/


    for (int i = 0; i < vs.size(); i++) {
        string c = vs[i];

        // If the scanned character is
        // an operand, add it to output string.

        if (vs[i] != "+" && vs[i] != "-" && vs[i] != "*" && vs[i] != "/" && vs[i] != "^" && vs[i] != "(" && vs[i] != ")")
            result.push_back(c);

        // If the scanned character is an
        // �(�, push it to the stack.
        else if (c == "(")
            st.push("(");

        // If the scanned character is an �)�,
        // pop and to output string from the stack
        // until an �(� is encountered.
        else if (c == ")") {
            while (st.top() != "(") {
                result.push_back(st.top());
                st.pop();
            }
            st.pop();
        }

        // If an operator is scanned
        else {
            while (!st.empty() && prec(vs[i]) <= prec(st.top())) {
                if (c == "^" && st.top() == "^")
                    break;
                else {
                    result.push_back(st.top());
                    st.pop();
                }
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    //printResult(result);
    return result;
    //cout << "\n" << caculate(result) << endl;
}

// Driver program to test above functions
void main_debug(string input_file, int x, string action, string output_file) {
    ifstream input(input_file);
    ofstream output(output_file);
    string exp;
    for (int i = 0; i < x; i++) {
        getline(input, exp);
        if (!checkString(exp))
        {
            output << 'E' << endl;
            continue;
        }
        prepare(exp);
        vector<string> postFix = infixToPostfix(exp);
        if (action == "-c") {
            output << caculate(postFix) << endl;
        }
        else if (action == "-t") {
            //printResult(postFix);
            for (int i = 0; i < postFix.size(); i++)
            {
                output << postFix[i] << " ";
            }
            output << endl;
        }
    }
}
void main_testcases(string input_file, int x, string action, string output_file) {
    main_debug(input_file, x, action, output_file);
}
int main(int argc, char* argv[])
{
    string input_file, action, output_file; int x;
    if (argc > 4) {
        input_file = argv[1];
        output_file = argv[4];
        x = atoi(argv[2]);
        action = argv[3];
        main_testcases(input_file, x, action, output_file); return 0;
    }
    else {
        cout << "Enter input_file: "; cin >> input_file;
        cout << "Enter x: "; cin >> x;
        cout << "Enter action: "; cin >> action;
        cout << "Enter output_file: "; cin >> output_file;
    }
    main_debug(input_file, x, action, output_file);
    if (!system(NULL)) system("pause"); return 0;
    return 0;
}
