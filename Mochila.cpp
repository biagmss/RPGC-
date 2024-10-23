#include "Mochila.h"
#include <iostream>
using namespace std;

Stack::Stack(){
    top = NULL;
}

bool Stack::Empty(){
    return top == NULL;
}

void Stack::Push(int x){
    StackPointer p;
    p = new StackNode;

    if(p == NULL){
        cout << "Não ha espaco para mais elementos na pilha" << endl;
        abort();
    }
    p->Entry = x;
    p->NextNode = top;
    top = p;
}

void Stack::Pop(int &x){
    if(Empty()){
        cout << "nao ha elementos para remover" << endl;
        abort();
    }
    x = top->Entry;
    StackPointer p = top;
    top = top->NextNode;
    delete p;
}

void Stack::Clear(){
    int x;
    while(!Empty()){
        Pop(x);
    }
}

Stack::~Stack(){
    Clear();
}
