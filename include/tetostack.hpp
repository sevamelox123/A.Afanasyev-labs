
#pragma once
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
    Stack() : TopOfStack() {}

    bool EmptyCheck() const;
    bool FullCheck() const;
    void push(tetoStruct item);
    tetoStruct pop();
    tetoStruct peek() const;
    int itemsCheck();
};