
#include <iostream>
#include "MochilaCinto.h"

using namespace std;

Stack::Stack()
{
    top = NULL;
}

bool Stack::Empty()
{
    return top == NULL;
}

void Stack::Push(Item x)
{
    StackPointer p;
    p = new StackNode;

    if (p == NULL)
    {
        cout << "Nao ha espaco para mais elementos na pilha" << endl;
        abort();
    }
    p->Entry = x;
    p->NextNode = top;
    top = p;
}

void Stack::Pop(Item &x)
{
    if (Empty())
    {
        cout << "nao ha elementos para remover" << endl;
        abort();
    }
    x = top->Entry;
    StackPointer p = top;
    top = top->NextNode;
    delete p;
}

void Stack::Clear()
{
    Item x;
    while (!Empty())
    {
        Pop(x);
    }
}

void Stack::Top(Item &x)
{
    if (top == NULL)
    {
        cout << "Mochila vazia";
        abort();
    }
    x = top->Entry;
}

Stack::~Stack()
{
    Clear();
}
