#include <cstdio>
#include <iostream>
using namespace std;

#define MAX_STACK_SIZE 100

class Stack
{
private:
    char Data[MAX_STACK_SIZE];
    int TopOfStack = 0;

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

int main()
{
    Stack s;
    // s.push('&');
    // s.push('7');
    // s.push('%');
    // cout << s.peek() << endl;
    return 0;
}