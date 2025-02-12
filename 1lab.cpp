#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cctype>
using namespace std;

#define MAX_STACK_SIZE 10000
union operands
{
    char less;
    char lessEqual;
    char more;
    char moreEqual;
    char _and;
    char _or;
};

class Stack
{
private:
    char Data[MAX_STACK_SIZE];
    int TopOfStack;

public:
    Stack() : TopOfStack(-1) {}

    bool EmptyCheck() const
    {
        return TopOfStack == -1;
    }

    bool FullCheck() const
    {
        return TopOfStack == MAX_STACK_SIZE - 1;
    }

    void push(char item)
    {
        if (FullCheck())
        {
            cerr << "Stack overflow\n";
            exit(1);
        }
        Data[++TopOfStack] = item;
    }

    char pop()
    {
        if (EmptyCheck())
        {
            cerr << "Stack underflow\n";
            exit(1);
        }
        return Data[TopOfStack--];
    }

    char peek() const
    {
        if (EmptyCheck())
        {
            cerr << "Stack is empty\n";
            exit(1);
        }
        return Data[TopOfStack];
    }
};

int prec(char c)
{
    if (c == '!')
        return 6;
    else if (c == '<' || c == '>')
        return 5;
    // else if (c == '&&')
    //     return 4;
    // else if (c == '||')
    //     return 3;
    else if (c == '^')
        return 2;
    // else if (c == '→')
    //     return 1;
    else
        return -1;
}

Stack infixToPostfix(string s)
{
    Stack st;
    Stack result;

    for (long unsigned i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if (c == ' '){
            continue;
        }


        if (isalpha(c)){
            result.push(c);
        }
        else if(c == '('){
            st.push('(');
        }
        else if (c == ')'){
            while(!st.EmptyCheck() && st.peek()!= '('){
                result.push(st.peek());
                st.pop();
            }
        }
        else{
            while(!st.EmptyCheck() && prec(st.peek()) >= prec(c)){
                result.push(st.peek());
                st.pop();
            }
        st.push(c);
        }

    }
    while(!result.EmptyCheck())
    {
        cout << result.pop() << " ";
    }
    
}

int main()
{
    Stack st;
    Stack result;
    string exp = "a == b";
    infixToPostfix(exp);
    return 0;
}