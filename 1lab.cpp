#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <optional>
#include <tetostack.hpp>
using namespace std;

int prec(char c)
{
    if (c == '!')
        return 6;
    else if (c == '<' || c == '>' || c == tetoEnum::MOREEQUAL || c == tetoEnum::LESSEQUAL || c == tetoEnum::EQUAL || c == tetoEnum::NOTEQUAL)
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
        char c1;
        if (i + 1 < s.length())
            c1 = s[i + 1];
        else 
            c1 = ' ';

        // std::cout << c << endl;

        if (isdigit(c))
        {
            // std::cout << c << endl;
            if (!digitBuffer.has_value()) {
                digitBuffer = 0;
            }
            digitBuffer = digitBuffer.value() * 10;
            digitBuffer = digitBuffer.value() + (c - '0');
            continue;
        }
        if (digitBuffer.has_value())
        {
            tetoStruct teto;
            teto.tetobool = false;
            teto.num = digitBuffer.value();
            result.push(teto);
            // cout <<"( " << digitBuffer.value() << " )\n";
            digitBuffer.reset();
        }
        if (c == '(')
        {
            tetoStruct teto;
            teto.tetobool = true;
            teto.op = c;
            st.push(teto);
        }
        else if (c == ')')
        {
            // if (digitBuffer.has_value())
            // {
            //     tetoStruct teto;
            //     teto.tetobool = false;
            //     teto.num = digitBuffer.value();
            //     result.push(teto);
            //     digitBuffer.reset();
            // }
            while (!st.EmptyCheck() && (st.peek().op != '('))
            {
                // cout << st.peek().op << endl;
                result.push(st.pop());
            }
            st.pop();
        }
        else if (c != ' ')
        {

            while (!st.EmptyCheck() && prec(st.peek().op) > prec(c))
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
            }
            else if (c == '=' && c1 == '=')
            {
                teto.op = tetoEnum::EQUAL;
                i++;
            }
            else if (c == '!' && c1 == '=')
            {
                teto.op = tetoEnum::NOTEQUAL;
                i++;
            }
            // cout << "- " << teto.op << endl;
            st.push(teto);
            // cout << st.itemsCheck() << " " << result.itemsCheck() << endl;
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
        // cout << tetoStack.peek().num << " ";
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
                }
                else if (teto.op == tetoEnum::MOREEQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left >= right);
                }
                else if (teto.op == tetoEnum::LESSEQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left <= right);
                }
                else if (teto.op == tetoEnum::AND)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left && right);
                }
                else if (teto.op == tetoEnum::OR)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left || right);
                }
                else if (teto.op == '^')
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(static_cast<bool>(left) xor static_cast<bool>(right));
                }
                else if (teto.op == tetoEnum::EQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left == right);
                }
                else if (teto.op == tetoEnum::NOTEQUAL)
                {
                    miku.tetobool = false;
                    miku.num = static_cast<int>(left != right);
                }
                else if (teto.op == tetoEnum::IMPL)
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
    string exp = "((1||0)->(2>3))";
    Stack postfix = infixToPostfix(exp);
    std::cout << TetoCalc(infixToPostfix(exp)) << std::endl;
    return 0;
}