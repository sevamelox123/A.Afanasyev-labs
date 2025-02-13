#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <optional>
using namespace std;

#define MAX_STACK_SIZE 10000
struct tetoStruct
{
    bool tetobool;
    union
    {
        int num;
        char op;
    };
};

class Stack
{
private:
    tetoStruct Data[MAX_STACK_SIZE];
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

    void push(tetoStruct item)
    {
        if (FullCheck())
        {
            cerr << "Stack overflow\n";
            exit(1);
        }
        Data[++TopOfStack] = item;
    }

    tetoStruct pop()
    {
        if (EmptyCheck())
        {
            cerr << "Stack underflow\n";
            exit(1);
        }
        return Data[TopOfStack--];
    }

    tetoStruct peek() const
    {
        if (EmptyCheck())
        {
            cerr << "Stack is empty\n";
            exit(1);
        }
        return Data[TopOfStack];
    }
    int itemsCheck()
    {
        return TopOfStack;
    }
};

int prec(char c)
{
    if (c == '!')
        return 6;
    else if (c == '<' || c == '>')
        return 5;
    else if (c == '&&')
        return 4;
    else if (c == '||')
        return 3;
    else if (c == '^')
        return 2;
    else if (c == '→')
        return 1;
    else
        return -1;
}

Stack infixToPostfix(string s)
{
    Stack st;
    Stack result;
    // int digitBuffer = 0;
    std::optional<int> digitBuffer = 0;

    for (long unsigned i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if (isdigit(c))
        {
            if (!digitBuffer.has_value())
                digitBuffer = 0;
            digitBuffer = digitBuffer.value() * 10;
            digitBuffer = digitBuffer.value() + (c - '0');
            continue;
        }
        else if (c == '(')
        {
            tetoStruct teto;
            teto.tetobool = true;
            teto.op = c;
            st.push(teto);
        }
        else if (c == ')')
        {
            if (digitBuffer.has_value())
            {
                tetoStruct teto;
                teto.tetobool = false;
                teto.num = digitBuffer.value();
                result.push(teto);
                digitBuffer.reset();
            }
            while (!st.EmptyCheck() && st.peek().op != '(')
            {
                result.push(st.pop());
            }
            st.pop();
        }
        else if (c != ' ')
        {

            while (!st.EmptyCheck() && prec(st.peek().op) >= prec(c))
            {
                result.push(st.pop());
            }
            tetoStruct teto;
            teto.tetobool = true;
            teto.op = c;
            st.push(teto);
        }
        if (digitBuffer.has_value())
        {
            tetoStruct teto;
            teto.tetobool = false;
            teto.num = digitBuffer.value();
            result.push(teto);
            digitBuffer.reset();
        }
    }
    if (digitBuffer.has_value())
    {
        tetoStruct teto;
        teto.tetobool = false;
        teto.num = digitBuffer.value();
        result.push(teto);
    }

    while (!st.EmptyCheck())
    {
        result.push(st.pop());
    }
    Stack reversed;
    while (!result.EmptyCheck())
    {
        reversed.push(result.pop());
    }
    // while (!reversed.EmptyCheck())
    // {
    //     tetoStruct res = reversed.pop();
    //     if (res.tetobool)
    //     {
    //         std::cout << res.op << " ";
    //     }
    //     else
    //     {
    //         std::cout << res.num << " ";
    //     }
    // }
    // std::cout << std::endl;

    return reversed;
}
bool TetoCalc(Stack tetoStack)
{
    Stack st;
    while(!tetoStack.EmptyCheck())
    {
        tetoStruct teto = tetoStack.pop();
        if(teto.tetobool)
        {
            // int right = st.pop().num;
            if (teto.op == '!') {
                int right = st.pop().num;
            }
            else {
                int right = st.pop().num;
                int left = st.pop().num;
                tetoStruct miku;
                if (teto.op == '>') {
                    miku.op = false;
                    miku.num = static_cast<int>(left > right);
                }
                else if (teto.op == '<') {
                    miku.op = false;
                    miku.num = static_cast<int>(left < right);
                }
                
                st.push(miku);
            }
        } else 
        {
            st.push(teto);
        }
    }
    return static_cast<bool>(st.pop().num);
}

int main()
{
    Stack st;
    Stack result;
    string exp = "100 < (0 < 2)";
    std::cout << TetoCalc(infixToPostfix(exp)) << std::endl;
    return 0;
}