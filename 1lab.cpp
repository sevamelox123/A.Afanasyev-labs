#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <optional>
using namespace std;

#define MAX_STACK_SIZE 10000

enum tetoEnum
{
    MOREEQUAL = ']',
    LESSEQUAL = '[',
    AND = '&',
    OR = 'O',
    IMPL = 'I',
    EQUAL = '=',
    NOTEQUAL = 'N'

};
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
            // exit(1);
            throw runtime_error("Aboba");
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
    else if (c == '<' || c == '>' || c == tetoEnum::MOREEQUAL || c == tetoEnum::LESSEQUAL || c == tetoEnum::EQUAL || c == tetoEnum::NOTEQUAL )
        return 5;
    else if (c == tetoEnum::AND)
        return 4;
    else if (c == tetoEnum::OR)
        return 3;
    else if (c == '^')
        return 2;
    else if (c == tetoEnum::IMPL)
        return 1;
    else
        return -1;
}

Stack infixToPostfix(string s)
{
    Stack st;
    Stack result;
    // int digitBuffer = 0;
    std::optional<int> digitBuffer;

    for (long unsigned i = 0; i < s.length(); i++)
    {
        char c = s[i];
        char c1 = s[i + 1];

        // std::cout << c << endl;

        if (isdigit(c))
        {
            // std::cout << c << endl;
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
            if ((c == '>' && c1 != '=') || (c == '<' && c1 != '=') || (c == '!' && c1 != '=') || c == '^')
            {
                // cout << c << " " << c1 << endl;
                teto.op = c;
            }
            else if (c == '>' && c1 == '=')
            {
                // cout << c << " " << c1 << endl;
                teto.op = tetoEnum::MOREEQUAL;
                i++;
            }
            else if (c == '<' && c1 == '=')
            {
                // cout << c << " " << c1 << endl;
                teto.op = tetoEnum::LESSEQUAL;
                i++;
            }
            else if (c == '&' && c1 == '&')
            {
                teto.op = tetoEnum::AND;
                i++;
            }
            else if (c == '|' && c1 == '|')
            {
                teto.op = tetoEnum::OR;
                i++;
            }
            else if (c == '-' && c1 == '>')
            {
                teto.op = tetoEnum::IMPL;
                i++;
            } else if(c == '=' && c1 == '=')
            {
                teto.op = tetoEnum::EQUAL;
                i++;
            } else if(c == '!' && c1 == '=')
            {
                teto.op = tetoEnum::NOTEQUAL;
                i++;
            }
            cout << "- " << teto.op << endl;
            st.push(teto);
            cout << st.itemsCheck() << " " << result.itemsCheck() << endl;
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

    return reversed;
}
bool TetoCalc(Stack tetoStack)
{
    Stack st;
    while (!tetoStack.EmptyCheck())
    {
        tetoStruct teto = tetoStack.pop();
        if (teto.tetobool)
        {
            if (teto.op == '!')
            {
                int right = st.pop().num;

                tetoStruct miku;
                miku.tetobool = false;
                miku.num = static_cast<int>(!static_cast<bool>(right));
                st.push(miku);
            }
            else
            {
                // std::cout << teto.op << std::endl;
                int right = st.pop().num;
                int left = st.pop().num;
                tetoStruct miku;
                if (teto.op == '>')
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left > right);
                }
                else if (teto.op == '<')
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left < right);
                } else if(teto.op == tetoEnum::MOREEQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left >= right);
                }else if(teto.op == tetoEnum::LESSEQUAL )
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left <= right);
                }else if(teto.op == tetoEnum::AND)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left && right);
                }else if(teto.op == tetoEnum::OR)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left || right);
                }else if(teto.op == '^')
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(static_cast<bool>(left) xor static_cast<bool>(right));
                }else if(teto.op == tetoEnum::EQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left == right);
                }else if(teto.op == tetoEnum::NOTEQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left != right);
                }else if(teto.op == tetoEnum::IMPL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(!static_cast<bool>(left) || static_cast<bool>(right));
                }

                st.push(miku);
            }
        }
        else
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
    string exp = "((1 > 2) -> (2 > 1))";
    Stack postfix = infixToPostfix(exp);
    while (!postfix.EmptyCheck()) {
        if (postfix.peek().tetobool) {
            std::cout << postfix.pop().op << " ";
        }
        else {
            std::cout << postfix.pop().num << " ";
        }
    }
    std::cout << endl;
    std::cout << TetoCalc(infixToPostfix(exp)) << std::endl;
    return 0;
}