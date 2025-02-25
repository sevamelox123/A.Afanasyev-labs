#include <tetostack.hpp>
#include <iostream>

using namespace std;
bool Stack::EmptyCheck() const
{
    return TopOfStack == 0;
}


bool Stack::FullCheck() const
{
    return TopOfStack == MAX_STACK_SIZE;
}


void Stack::push(tetoStruct item)
{
    if (FullCheck())
    {
        cerr << "Stack overflow\n";
        exit(1);
    }
    Data[++TopOfStack] = item;
}


tetoStruct Stack::pop()
{
    if (EmptyCheck())
    {
        cerr << "Stack underflow\n";
        // exit(1);
        throw runtime_error("Aboba");
    }
    return Data[TopOfStack--];
}


tetoStruct Stack::peek() const
{
    if (EmptyCheck())
    {
        cerr << "Stack is empty\n";
        exit(1);
    }
    return Data[TopOfStack];
}

int Stack::itemsCheck()
{
    return TopOfStack;
}